/** 
 * @file llfloateractivespeakers.cpp
 * @brief Management interface for muting and controlling volume of residents currently speaking
 *
 * $LicenseInfo:firstyear=2005&license=viewergpl$
 * 
 * Copyright (c) 2005-2010, Linden Research, Inc.
 * 
 * Second Life Viewer Source Code
 * The source code in this file ("Source Code") is provided by Linden Lab
 * to you under the terms of the GNU General Public License, version 2.0
 * ("GPL"), unless you have obtained a separate licensing agreement
 * ("Other License"), formally executed by you and Linden Lab.  Terms of
 * the GPL can be found in doc/GPL-license.txt in this distribution, or
 * online at http://secondlifegrid.net/programs/open_source/licensing/gplv2
 * 
 * There are special exceptions to the terms and conditions of the GPL as
 * it is applied to this Source Code. View the full text of the exception
 * in the file doc/FLOSS-exception.txt in this software distribution, or
 * online at
 * http://secondlifegrid.net/programs/open_source/licensing/flossexception
 * 
 * By copying, modifying or distributing this software, you acknowledge
 * that you have read and understood your obligations described above,
 * and agree to abide by those obligations.
 * 
 * ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
 * WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
 * COMPLETENESS OR PERFORMANCE.
 * $/LicenseInfo$
 */

#include "llviewerprecompiledheaders.h"

#include "llfloateractivespeakers.h"

#include "llagent.h"
#include "llavataractions.h"
#include "llimview.h"
#include "llscrolllistctrl.h"
#include "llscrolllistitem.h"
#include "llscrolllistcell.h"
#include "llbutton.h"
#include "lltextbox.h"
#include "llmutelist.h"
#include "llviewerobjectlist.h"
#include "llsdutil.h"
#include "llspeakers.h"
#include "llviewercontrol.h"
#include "llviewerwindow.h"
#include "llvoicechannel.h"
#include "llimfloater.h"


using namespace LLOldEvents;

const F32 RESORT_TIMEOUT = 5.f; // seconds of mouse inactivity before it's ok to sort regardless of mouse-in-view.


//
// LLFloaterActiveSpeakers
//

LLFloaterActiveSpeakers::LLFloaterActiveSpeakers(const LLSD& seed)
	: LLFloater(seed),
	  mPanel(NULL)
{
	mFactoryMap["active_speakers_panel"] = LLCallbackMap(createSpeakersPanel, NULL);
//	// do not automatically open singleton floaters (as result of getInstance())
//	BOOL no_open = FALSE;
//	LLUICtrlFactory::getInstance()->buildFloater(this, "floater_active_speakers.xml", no_open);	
}

LLFloaterActiveSpeakers::~LLFloaterActiveSpeakers()
{
}

void LLFloaterActiveSpeakers::draw()
{
	// update state every frame to get live amplitude feedback
	mPanel->refreshSpeakers();
	LLFloater::draw();
}

BOOL LLFloaterActiveSpeakers::postBuild()
{
	mPanel = findChild<LLPanelActiveSpeakers>("active_speakers_panel");
	if (!mPanel) return FALSE;

	//RN: for now, we poll voice client every frame to get voice amplitude feedback
	//gVoiceClient->addObserver(this);
	mPanel->refreshSpeakers();

	return TRUE;
}

void LLFloaterActiveSpeakers::onChange()
{
	//refresh();
}

//static
void* LLFloaterActiveSpeakers::createSpeakersPanel(void* data)
{
	// don't show text only speakers
	return new LLPanelActiveSpeakers(LLActiveSpeakerMgr::getInstance(), FALSE);
}

//
// LLPanelActiveSpeakers::SpeakerMuteListener
//
bool LLPanelActiveSpeakers::SpeakerMuteListener::handleEvent(LLPointer<LLEvent> event, const LLSD& userdata)
{
	LLPointer<LLSpeaker> speakerp = (LLSpeaker*)event->getSource();
	if (speakerp.isNull()) return false;

	// update UI on confirmation of moderator mutes
	if (event->getValue().asString() == "voice")
	{
		mPanel->childSetValue("moderator_allow_voice", !speakerp->mModeratorMutedVoice);
	}
	if (event->getValue().asString() == "text")
	{
		mPanel->childSetValue("moderator_allow_text", !speakerp->mModeratorMutedText);
	}
	return true;
}


//
// LLPanelActiveSpeakers::SpeakerAddListener
//
bool LLPanelActiveSpeakers::SpeakerAddListener::handleEvent(LLPointer<LLEvent> event, const LLSD& userdata)
{
	mPanel->addSpeaker(event->getValue().asUUID());
	return true;
}


//
// LLPanelActiveSpeakers::SpeakerRemoveListener
//
bool LLPanelActiveSpeakers::SpeakerRemoveListener::handleEvent(LLPointer<LLEvent> event, const LLSD& userdata)
{
	mPanel->removeSpeaker(event->getValue().asUUID());
	return true;
}

//
// LLPanelActiveSpeakers::SpeakerClearListener
//
bool LLPanelActiveSpeakers::SpeakerClearListener::handleEvent(LLPointer<LLEvent> event, const LLSD& userdata)
{
	mPanel->mSpeakerList->clearRows();
	return true;
}


//
// LLPanelActiveSpeakers
//
LLPanelActiveSpeakers::LLPanelActiveSpeakers(LLSpeakerMgr* data_source, BOOL show_text_chatters)
: 	LLPanel(),
	mSpeakerList(NULL),
	mMuteVoiceCtrl(NULL),
	mMuteTextCtrl(NULL),
	mNameText(NULL),
	mProfileBtn(NULL),
	mShowTextChatters(show_text_chatters),
	mSpeakerMgr(data_source)
{
	setMouseOpaque(FALSE);
	mSpeakerMuteListener = new SpeakerMuteListener(this);
	mSpeakerAddListener = new SpeakerAddListener(this);
	mSpeakerRemoveListener = new SpeakerRemoveListener(this);
	mSpeakerClearListener = new SpeakerClearListener(this);

	mSpeakerMgr->addListener(mSpeakerAddListener, "add");
	mSpeakerMgr->addListener(mSpeakerRemoveListener, "remove");
	mSpeakerMgr->addListener(mSpeakerClearListener, "clear");
}

BOOL LLPanelActiveSpeakers::postBuild()
{
	std::string sort_column = gSavedSettings.getString(std::string("FloaterActiveSpeakersSortColumn"));
	BOOL sort_ascending     = gSavedSettings.getBOOL(  std::string("FloaterActiveSpeakersSortAscending"));

	mSpeakerList = getChild<LLScrollListCtrl>("speakers_list");
	mSpeakerList->sortByColumn(sort_column, sort_ascending);
	mSpeakerList->setDoubleClickCallback(onDoubleClickSpeaker, this);
	mSpeakerList->setCommitOnSelectionChange(TRUE);
	mSpeakerList->setCommitCallback(boost::bind(&LLPanelActiveSpeakers::handleSpeakerSelect, this, _2));
	mSpeakerList->setSortChangedCallback(boost::bind(&LLPanelActiveSpeakers::onSortChanged, this));
	mSpeakerList->setContextMenu(LLScrollListCtrl::MENU_AVATAR);

	mMuteTextCtrl = getChild<LLUICtrl>("mute_text_btn");
	mMuteTextCtrl->setCommitCallback(boost::bind(&LLPanelActiveSpeakers::onClickMuteTextCommit, this, _2));

	mMuteVoiceCtrl = getChild<LLUICtrl>("mute_btn");
	mMuteVoiceCtrl->setCommitCallback(boost::bind(&LLPanelActiveSpeakers::onClickMuteVoiceCommit, this, _2));

	getChild<LLUICtrl>("speaker_volume")->setCommitCallback(boost::bind(&LLPanelActiveSpeakers::onVolumeChange, this, _2));

	mNameText = getChild<LLTextBox>("resident_name");
	
	mProfileBtn = getChild<LLButton>("profile_btn");
	childSetAction("profile_btn", onClickProfile, this);

	getChild<LLUICtrl>("moderator_allow_voice")->setCommitCallback(boost::bind(&LLPanelActiveSpeakers::onModeratorMuteVoice, this, _1));
	getChild<LLUICtrl>("moderator_allow_text")->setCommitCallback(boost::bind(&LLPanelActiveSpeakers::onModeratorMuteText, this, _1));
	getChild<LLUICtrl>("moderation_mode")->setCommitCallback(boost::bind(&LLPanelActiveSpeakers::onChangeModerationMode, this, _1));

	// update speaker UI
	handleSpeakerSelect();

	return TRUE;
}

void LLPanelActiveSpeakers::addSpeaker(const LLUUID& speaker_id)
{
	if (mSpeakerList->getItemIndex(speaker_id) >= 0)
	{
		// already have this speaker
		return;
	}

	LLPointer<LLSpeaker> speakerp = mSpeakerMgr->findSpeaker(speaker_id);
	if (speakerp)
	{
		// since we are forced to sort by text, encode sort order as string
		std::string speaking_order_sort_string = llformat("%010d", speakerp->mSortIndex);

		LLSD row;
		row["id"] = speaker_id;

		LLSD& columns = row["columns"];

		columns[0]["column"] = "icon_speaking_status";
		columns[0]["type"] = "icon";
		columns[0]["value"] = "icn_active-speakers-dot-lvl0.tga";

		std::string speaker_name;
		if (speakerp->mDisplayName.empty())
		{
			speaker_name = LLCacheName::getDefaultName();
		}
		else
		{
			speaker_name = speakerp->mDisplayName;
		}
		columns[1]["column"] = "speaker_name";
		columns[1]["type"] = "text";
		columns[1]["value"] = speaker_name;

		columns[2]["column"] = "speaking_status";
		columns[2]["type"] = "text";
		
		// print speaking ordinal in a text-sorting friendly manner
		columns[2]["value"] = speaking_order_sort_string;

		mSpeakerList->addElement(row);
	}
}

void LLPanelActiveSpeakers::removeSpeaker(const LLUUID& speaker_id)
{
	mSpeakerList->deleteSingleItem(mSpeakerList->getItemIndex(speaker_id));
}

void LLPanelActiveSpeakers::handleSpeakerSelect(const LLSD& data)
{
	LLUUID speaker_id = mSpeakerList->getValue().asUUID();
	LLPointer<LLSpeaker> selected_speakerp = mSpeakerMgr->findSpeaker(speaker_id);

	if (selected_speakerp.notNull())
	{
		// since setting these values is delayed by a round trip to the Vivox servers
		// update them only when selecting a new speaker or
		// asynchronously when an update arrives
		childSetValue("moderator_allow_voice", selected_speakerp ? !selected_speakerp->mModeratorMutedVoice : TRUE);
		childSetValue("moderator_allow_text", selected_speakerp ? !selected_speakerp->mModeratorMutedText : TRUE);

		mSpeakerMuteListener->clearDispatchers();
		selected_speakerp->addListener(mSpeakerMuteListener);
	}
}

void LLPanelActiveSpeakers::refreshSpeakers()
{
	// store off current selection and scroll state to preserve across list rebuilds
	LLUUID selected_id = mSpeakerList->getSelectedValue().asUUID();
	S32 scroll_pos = mSpeakerList->getScrollInterface()->getScrollPos();

	// decide whether it's ok to resort the list then update the speaker manager appropriately.
	// rapid resorting by activity makes it hard to interact with speakers in the list
	// so we freeze the sorting while the user appears to be interacting with the control.
	// we assume this is the case whenever the mouse pointer is within the active speaker
	// panel and hasn't been motionless for more than a few seconds. see DEV-6655 -MG
	LLRect screen_rect;
	localRectToScreen(getLocalRect(), &screen_rect);
	BOOL mouse_in_view = screen_rect.pointInRect(gViewerWindow->getCurrentMouseX(), gViewerWindow->getCurrentMouseY());
	F32 mouses_last_movement = LLUI::getMouseIdleTime();
	BOOL sort_ok = ! (mouse_in_view && mouses_last_movement<RESORT_TIMEOUT);
	mSpeakerMgr->update(sort_ok);

	const std::string icon_image_0 = "icn_active-speakers-dot-lvl0.tga";
	const std::string icon_image_1 = "icn_active-speakers-dot-lvl1.tga";
	const std::string icon_image_2 = "icn_active-speakers-dot-lvl2.tga";

	std::vector<LLScrollListItem*> items = mSpeakerList->getAllData();

	std::string mute_icon_image = "mute_icon.tga";

	LLSpeakerMgr::speaker_list_t speaker_list;
	mSpeakerMgr->getSpeakerList(&speaker_list, mShowTextChatters);
	for (std::vector<LLScrollListItem*>::iterator item_it = items.begin();
		item_it != items.end();
		++item_it)
	{
		LLScrollListItem* itemp = (*item_it);
		LLUUID speaker_id = itemp->getUUID();

		LLPointer<LLSpeaker> speakerp = mSpeakerMgr->findSpeaker(speaker_id);
		if (!speakerp)
		{
			continue;
		}

		// since we are forced to sort by text, encode sort order as string
		std::string speaking_order_sort_string = llformat("%010d", speakerp->mSortIndex);

		LLScrollListCell* icon_cell = itemp->getColumn(0);
		if (icon_cell)
		{

			std::string icon_image_id;

			S32 icon_image_idx = llmin(2, llfloor((speakerp->mSpeechVolume / LLVoiceClient::OVERDRIVEN_POWER_LEVEL) * 3.f));
			switch(icon_image_idx)
			{
			case 0:
				icon_image_id = icon_image_0;
				break;
			case 1:
				icon_image_id = icon_image_1;
				break;
			case 2:
				icon_image_id = icon_image_2;
				break;
			}

			LLColor4 icon_color;
			if (speakerp->mStatus == LLSpeaker::STATUS_MUTED)
			{
				icon_cell->setValue(mute_icon_image);
				if(speakerp->mModeratorMutedVoice)
				{
					icon_color.setVec(0.5f, 0.5f, 0.5f, 1.f);
				}
				else
				{
					icon_color.setVec(1.f, 71.f / 255.f, 71.f / 255.f, 1.f);
				}
			}
			else
			{
				icon_cell->setValue(icon_image_id);
				icon_color = speakerp->mDotColor;

				if (speakerp->mStatus > LLSpeaker::STATUS_VOICE_ACTIVE) // if voice is disabled for this speaker
				{
					// non voice speakers have hidden icons, render as transparent
					icon_color.setVec(0.f, 0.f, 0.f, 0.f);
				}
			}

			icon_cell->setColor(icon_color);

			if (speakerp->mStatus > LLSpeaker::STATUS_VOICE_ACTIVE && speakerp->mStatus != LLSpeaker::STATUS_MUTED) // if voice is disabled for this speaker
			{
				// non voice speakers have hidden icons, render as transparent
				icon_cell->setColor(LLColor4::transparent);
			}
		}

		// update name column
		LLScrollListCell* name_cell = itemp->getColumn(1);
		if (name_cell)
		{
			//FIXME: remove hard coding of font colors
			if (speakerp->mStatus == LLSpeaker::STATUS_NOT_IN_CHANNEL)	
			{
				// draw inactive speakers in gray
				name_cell->setColor(LLColor4::grey4);
			}
			else
			{
				name_cell->setColor(LLColor4::black);
			}

			std::string speaker_name;
			if (speakerp->mDisplayName.empty())
			{
				speaker_name = LLCacheName::getDefaultName();
			}
			else
			{
				speaker_name = speakerp->mDisplayName;
			}

			if (speakerp->mIsModerator)
			{
				speaker_name += std::string(" ") + getString("moderator_label");
			}
			
			name_cell->setValue(speaker_name);
			((LLScrollListText*)name_cell)->setFontStyle(speakerp->mIsModerator ? LLFontGL::BOLD : LLFontGL::NORMAL);
		}

		// update speaking order column
		LLScrollListCell* speaking_status_cell = itemp->getColumn(2);
		if (speaking_status_cell)
		{
			// print speaking ordinal in a text-sorting friendly manner
			speaking_status_cell->setValue(speaking_order_sort_string);
		}
	}
	
	// we potentially modified the sort order by touching the list items
	mSpeakerList->setNeedsSort();

	LLPointer<LLSpeaker> selected_speakerp = mSpeakerMgr->findSpeaker(selected_id);
	// update UI for selected participant
	if (mMuteVoiceCtrl)
	{
		mMuteVoiceCtrl->setValue(LLMuteList::getInstance()->isMuted(selected_id, LLMute::flagVoiceChat));
		mMuteVoiceCtrl->setEnabled(LLVoiceClient::voiceEnabled()
									&& gVoiceClient->getVoiceEnabled(selected_id)
									&& selected_id.notNull() 
									&& selected_id != gAgent.getID() 
									&& (selected_speakerp.notNull() && (selected_speakerp->mType == LLSpeaker::SPEAKER_AGENT || selected_speakerp->mType == LLSpeaker::SPEAKER_EXTERNAL)));

	}
	if (mMuteTextCtrl)
	{
		mMuteTextCtrl->setValue(LLMuteList::getInstance()->isMuted(selected_id, LLMute::flagTextChat));
		mMuteTextCtrl->setEnabled(selected_id.notNull() 
								&& selected_id != gAgent.getID() 
								&& selected_speakerp.notNull() 
								&& selected_speakerp->mType != LLSpeaker::SPEAKER_EXTERNAL
								&& !LLMuteList::getInstance()->isLinden(selected_speakerp->mDisplayName));
	}
	childSetValue("speaker_volume", gVoiceClient->getUserVolume(selected_id));
	childSetEnabled("speaker_volume", LLVoiceClient::voiceEnabled()
					&& gVoiceClient->getVoiceEnabled(selected_id)
					&& selected_id.notNull() 
					&& selected_id != gAgent.getID() 
					&& (selected_speakerp.notNull() && (selected_speakerp->mType == LLSpeaker::SPEAKER_AGENT || selected_speakerp->mType == LLSpeaker::SPEAKER_EXTERNAL)));

	childSetEnabled(
		"moderator_controls_label",
		selected_id.notNull());

	childSetEnabled(
		"moderator_allow_voice", 
		selected_id.notNull() 
		&& mSpeakerMgr->isVoiceActive()
		&& gVoiceClient->getVoiceEnabled(selected_id));

	childSetEnabled(
		"moderator_allow_text", 
		selected_id.notNull());

	if (mProfileBtn)
	{
		mProfileBtn->setEnabled(selected_id.notNull() && (selected_speakerp.notNull() && selected_speakerp->mType != LLSpeaker::SPEAKER_EXTERNAL) );
	}

	// show selected user name in large font
	if (mNameText)
	{
		if (selected_speakerp)
		{
			mNameText->setValue(selected_speakerp->mDisplayName);
		}
		else
		{
			mNameText->setValue(LLStringUtil::null);
		}
	}

	//update moderator capabilities
	LLPointer<LLSpeaker> self_speakerp = mSpeakerMgr->findSpeaker(gAgent.getID());
	if(self_speakerp)
	{
		childSetVisible("moderation_mode_panel", self_speakerp->mIsModerator && mSpeakerMgr->isVoiceActive());
		childSetVisible("moderator_controls", self_speakerp->mIsModerator);
	}

	// keep scroll value stable
	mSpeakerList->getScrollInterface()->setScrollPos(scroll_pos);
}

void LLPanelActiveSpeakers::setSpeaker(const LLUUID& id, const std::string& name, LLSpeaker::ESpeakerStatus status, LLSpeaker::ESpeakerType type)
{
	mSpeakerMgr->setSpeaker(id, name, status, type);
}

void LLPanelActiveSpeakers::setVoiceModerationCtrlMode(
	const BOOL& moderated_voice)
{
	LLUICtrl* voice_moderation_ctrl = getChild<LLUICtrl>("moderation_mode");

	if ( voice_moderation_ctrl )
	{
		std::string value;

		value = moderated_voice ? "moderated" : "unmoderated";
		voice_moderation_ctrl->setValue(value);
	}
}

void LLPanelActiveSpeakers::onClickMuteTextCommit(const LLSD& data)
{
	LLUUID speaker_id = mSpeakerList->getValue().asUUID();
	BOOL is_muted = LLMuteList::getInstance()->isMuted(speaker_id, LLMute::flagTextChat);
	std::string name;

	//fill in name using voice client's copy of name cache
	LLPointer<LLSpeaker> speakerp = mSpeakerMgr->findSpeaker(speaker_id);
	if (speakerp.isNull())
	{
		return;
	}
	
	name = speakerp->mDisplayName;

	LLMute mute(speaker_id, name, speakerp->mType == LLSpeaker::SPEAKER_AGENT ? LLMute::AGENT : LLMute::OBJECT);

	if (!is_muted)
	{
		LLMuteList::getInstance()->add(mute, LLMute::flagTextChat);
	}
	else
	{
		LLMuteList::getInstance()->remove(mute, LLMute::flagTextChat);
	}
}

void LLPanelActiveSpeakers::onClickMuteVoiceCommit(const LLSD& data)
{
	LLUUID speaker_id = mSpeakerList->getValue().asUUID();
	BOOL is_muted = LLMuteList::getInstance()->isMuted(speaker_id, LLMute::flagVoiceChat);
	std::string name;

	LLPointer<LLSpeaker> speakerp = mSpeakerMgr->findSpeaker(speaker_id);
	if (speakerp.isNull())
	{
		return;
	}

	name = speakerp->mDisplayName;

	// muting voice means we're dealing with an agent
	LLMute mute(speaker_id, name, LLMute::AGENT);

	if (!is_muted)
	{
		LLMuteList::getInstance()->add(mute, LLMute::flagVoiceChat);
	}
	else
	{
		LLMuteList::getInstance()->remove(mute, LLMute::flagVoiceChat);
	}
}


void LLPanelActiveSpeakers::onVolumeChange(const LLSD& data)
{
	LLUUID speaker_id = mSpeakerList->getValue().asUUID();

	F32 new_volume = (F32)childGetValue("speaker_volume").asReal();
	gVoiceClient->setUserVolume(speaker_id, new_volume); 
}

//static 
void LLPanelActiveSpeakers::onClickProfile(void* user_data)
{
	LLPanelActiveSpeakers* panelp = (LLPanelActiveSpeakers*)user_data;
	LLUUID speaker_id = panelp->mSpeakerList->getValue().asUUID();

	LLAvatarActions::showProfile(speaker_id);
}

//static
void LLPanelActiveSpeakers::onDoubleClickSpeaker(void* user_data)
{
	LLPanelActiveSpeakers* panelp = (LLPanelActiveSpeakers*)user_data;
	LLUUID speaker_id = panelp->mSpeakerList->getValue().asUUID();

	LLPointer<LLSpeaker> speakerp = panelp->mSpeakerMgr->findSpeaker(speaker_id);

	if (speaker_id != gAgent.getID() && speakerp.notNull())
	{
		LLUUID session_id = gIMMgr->addSession(speakerp->mDisplayName,
				IM_NOTHING_SPECIAL, speaker_id);
		if (session_id != LLUUID::null)
		{
			LLIMFloater::show(session_id);
		}
	}
}

void LLPanelActiveSpeakers::onSortChanged()
{
	std::string sort_column = mSpeakerList->getSortColumnName();
	BOOL sort_ascending = mSpeakerList->getSortAscending();
	gSavedSettings.setString(std::string("FloaterActiveSpeakersSortColumn"), sort_column);
	gSavedSettings.setBOOL(  std::string("FloaterActiveSpeakersSortAscending"), sort_ascending);
}


void LLPanelActiveSpeakers::onModeratorMuteVoice(LLUICtrl* ctrl)
{
	LLUICtrl* speakers_list = getChild<LLUICtrl>("speakers_list");
	if (!speakers_list || !gAgent.getRegion())
		return;

	std::string url = gAgent.getRegion()->getCapability("ChatSessionRequest");
	LLSD data;
	data["method"] = "mute update";
	data["session-id"] = mSpeakerMgr->getSessionID();
	data["params"] = LLSD::emptyMap();
	data["params"]["agent_id"] = speakers_list->getValue();
	data["params"]["mute_info"] = LLSD::emptyMap();
	// ctrl value represents ability to type, so invert
	data["params"]["mute_info"]["voice"] = !ctrl->getValue().asBoolean();

	class MuteVoiceResponder : public LLHTTPClient::Responder
	{
	public:
		MuteVoiceResponder(const LLUUID& session_id)
		{
			mSessionID = session_id;
		}

		virtual void error(U32 status, const std::string& reason)
		{
			llwarns << status << ": " << reason << llendl;

			if ( gIMMgr )
			{
				//403 == you're not a mod
				//should be disabled if you're not a moderator
				if ( 403 == status )
				{
					gIMMgr->showSessionEventError(
						"mute",
						"not_a_mod_error",
						mSessionID);
				}
				else
				{
					gIMMgr->showSessionEventError(
						"mute",
						"generic_request_error",
						mSessionID);
				}
			}
		}

	private:
		LLUUID mSessionID;
	};

	LLHTTPClient::post(
		url,
		data,
		new MuteVoiceResponder(mSpeakerMgr->getSessionID()));
}

void LLPanelActiveSpeakers::onModeratorMuteText(LLUICtrl* ctrl)
{
	LLUICtrl* speakers_list = getChild<LLUICtrl>("speakers_list");
	if (!speakers_list || !gAgent.getRegion())
		return;

	std::string url = gAgent.getRegion()->getCapability("ChatSessionRequest");
	LLSD data;
	data["method"] = "mute update";
	data["session-id"] = mSpeakerMgr->getSessionID();
	data["params"] = LLSD::emptyMap();
	data["params"]["agent_id"] = speakers_list->getValue();
	data["params"]["mute_info"] = LLSD::emptyMap();
	// ctrl value represents ability to type, so invert
	data["params"]["mute_info"]["text"] = !ctrl->getValue().asBoolean();

	class MuteTextResponder : public LLHTTPClient::Responder
	{
	public:
		MuteTextResponder(const LLUUID& session_id)
		{
			mSessionID = session_id;
		}

		virtual void error(U32 status, const std::string& reason)
		{
			llwarns << status << ": " << reason << llendl;

			if ( gIMMgr )
			{
				//403 == you're not a mod
				//should be disabled if you're not a moderator
				if ( 403 == status )
				{
					gIMMgr->showSessionEventError(
						"mute",
						"not_a_mod_error",
						mSessionID);
				}
				else
				{
					gIMMgr->showSessionEventError(
						"mute",
						"generic_request_error",
						mSessionID);
				}
			}
		}

	private:
		LLUUID mSessionID;
	};

	LLHTTPClient::post(
		url,
		data,
		new MuteTextResponder(mSpeakerMgr->getSessionID()));
}

void LLPanelActiveSpeakers::onChangeModerationMode(LLUICtrl* ctrl)
{
	if (!gAgent.getRegion())
		return;

	std::string url = gAgent.getRegion()->getCapability("ChatSessionRequest");
	LLSD data;
	data["method"] = "session update";
	data["session-id"] = mSpeakerMgr->getSessionID();
	data["params"] = LLSD::emptyMap();

	data["params"]["update_info"] = LLSD::emptyMap();

	data["params"]["update_info"]["moderated_mode"] = LLSD::emptyMap();
	std::string value = ctrl->getValue().asString();
	if (value == "unmoderated")
	{
		data["params"]["update_info"]["moderated_mode"]["voice"] = false;
	}
	else if (value == "moderated")
	{
		data["params"]["update_info"]["moderated_mode"]["voice"] = true;
	}

	struct ModerationModeResponder : public LLHTTPClient::Responder
	{
		virtual void error(U32 status, const std::string& reason)
		{
			llwarns << status << ": " << reason << llendl;
		}
	};

	LLHTTPClient::post(url, data, new ModerationModeResponder());
}

