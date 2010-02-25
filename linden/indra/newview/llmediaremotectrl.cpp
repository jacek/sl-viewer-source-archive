/** 
 * @file llmediaremotectrl.cpp
 * @brief A remote control for media (video and music)
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

#include "llmediaremotectrl.h"

#include "llaudioengine.h"
#include "llagent.h"
#include "llbutton.h"
#include "llfloaterchatterbox.h"
#include "llfloaterpreference.h"
#include "llfloaterreg.h"
#include "lliconctrl.h"
#include "llparcel.h"
#include "llmimetypes.h"
#include "lloverlaybar.h"
#include "llviewercontrol.h"
#include "llviewermedia.h"
#include "llviewerparcelmedia.h"
#include "llviewerparcelmgr.h"
#include "llvoicechannel.h"
#include "llvoiceclient.h"
#include "lluictrlfactory.h"
#include "lltextbox.h"




////////////////////////////////////////////////////////////////////////////////
//
//

LLMediaRemoteCtrl::LLMediaRemoteCtrl() 
:	LLPanel()
{
	setIsChrome(TRUE);
	setFocusRoot(TRUE);
	LLUICtrlFactory::getInstance()->buildPanel(this, "panel_media_remote.xml");
}

void LLMediaRemoteCtrl::expandOrCollapse()
{
	//HACK: only works because we don't have any implicit children (i.e. titlebars, close button, etc)
	deleteAllChildren();
	if (gSavedSettings.getBOOL("ShowVolumeSettingsPopup"))
	{
		LLUICtrlFactory::getInstance()->buildPanel(this, "panel_media_remote_expanded.xml");
	}
	else
	{
		LLUICtrlFactory::getInstance()->buildPanel(this, "panel_media_remote.xml");
	}
}

BOOL LLMediaRemoteCtrl::postBuild()
{
	mControls = getChild<LLPanel>("media_controls");
	llassert_always(mControls);
	
	childSetAction("media_play",LLOverlayBar::toggleMediaPlay,this);
	childSetAction("music_play",LLOverlayBar::toggleMusicPlay,this);
	childSetAction("media_stop",LLOverlayBar::mediaStop,this);
	childSetAction("music_stop",LLOverlayBar::toggleMusicPlay,this);
	childSetAction("media_pause",LLOverlayBar::toggleMediaPlay,this);
	childSetAction("music_pause",LLOverlayBar::toggleMusicPlay,this);

	childSetAction("expand", onClickExpandBtn, this);	
	return TRUE;
}

void LLMediaRemoteCtrl::draw()
{
	enableMediaButtons();
	
	LLButton* expand_button = getChild<LLButton>("expand");
	if (expand_button)
	{
		if (expand_button->getToggleState())
		{
			expand_button->setImageOverlay("arrow_down.tga");
		}
		else
		{
			expand_button->setImageOverlay("arrow_up.tga");
		}
	}

	LLPanel::draw();
}

LLMediaRemoteCtrl::~LLMediaRemoteCtrl ()
{
}

//static 
void LLMediaRemoteCtrl::onClickExpandBtn(void* user_data)
{
	LLMediaRemoteCtrl* remotep = (LLMediaRemoteCtrl*)user_data;

	remotep->expandOrCollapse();
	gOverlayBar->layoutButtons();

}

void LLMediaRemoteCtrl::enableMediaButtons()
{
	// Media
	bool play_media_enabled = false;
	bool stop_media_enabled = false;
	bool play_music_enabled = false;
	bool stop_music_enabled = false;
	bool music_show_pause = false;
	bool media_show_pause = false;
	static LLUIColor icon_disabled_color = LLUIColorTable::instance().getColor("IconDisabledColor");
	static LLUIColor icon_enabled_color = LLUIColorTable::instance().getColor("IconEnabledColor", LLColor4::white);
	LLColor4 music_icon_color = icon_disabled_color;
	LLColor4 media_icon_color = icon_disabled_color;
	std::string media_type = "none/none";

	// Put this in xui file
	std::string media_url = mControls->getString("default_tooltip_label");
	LLParcel* parcel = LLViewerParcelMgr::getInstance()->getAgentParcel();

	if(gSavedSettings.getBOOL("AudioStreamingMedia"))
	{
		if ( parcel && parcel->getMediaURL()[0])
		{
			// Set the tooltip
			// Put this text into xui file
			media_url = parcel->getObscureMedia() ? mControls->getString("media_hidden_label") : parcel->getMediaURL();
			media_type = parcel->getMediaType();

			play_media_enabled = true;
			media_icon_color = icon_enabled_color;

			LLViewerMediaImpl::EMediaStatus status = LLViewerParcelMedia::getStatus();
			switch(status)
			{
				case LLPluginClassMediaOwner::MEDIA_NONE:
					media_show_pause = false;
					stop_media_enabled = false;
					break;
				case LLPluginClassMediaOwner::MEDIA_LOADING:
				case LLPluginClassMediaOwner::MEDIA_LOADED:
				case LLPluginClassMediaOwner::MEDIA_PLAYING:
					// HACK: only show the pause button for movie types
					media_show_pause = LLMIMETypes::widgetType(parcel->getMediaType()) == "movie" ? true : false;
					stop_media_enabled = true;
					play_media_enabled = false;
					break;
				case LLPluginClassMediaOwner::MEDIA_PAUSED:
					media_show_pause = false;
					stop_media_enabled = true;
					break;
				default:
					// inherit defaults above
					break;
			}
		}
		if (gSavedSettings.getBOOL("AudioStreamingMusic") && gAudiop)
		{
			if ( parcel && parcel->getMusicURL()[0])
			{
				play_music_enabled = true;
				music_icon_color = icon_enabled_color;
/*
				if (gOverlayBar->musicPlaying())
				{
					music_show_pause = true;
					stop_music_enabled = true;
				}
				else
				{
					music_show_pause = false;
					stop_music_enabled = false;
				}
*/
			}
			// if no mime type has been set disable play
			if( LLViewerParcelMedia::getMimeType().empty() 
				|| LLViewerParcelMedia::getMimeType() == "none/none")
			{
				// FIXME: This seems to be in the wrong logic block... what's going on here?
				play_media_enabled = false;
				stop_media_enabled = false;
			}
		}
	}
	   
	const std::string media_icon_name = LLMIMETypes::findIcon(media_type);
	LLButton* music_play_btn = getChild<LLButton>("music_play");
	LLButton* music_stop_btn = getChild<LLButton>("music_stop");
	LLButton* music_pause_btn = getChild<LLButton>("music_pause");
	LLButton* media_play_btn = getChild<LLButton>("media_play");
	LLButton* media_stop_btn = getChild<LLButton>("media_stop");
	LLButton* media_pause_btn = getChild<LLButton>("media_pause");
	LLIconCtrl* media_icon = getChild<LLIconCtrl>("media_icon");

	music_play_btn->setEnabled(play_music_enabled);
	music_stop_btn->setEnabled(stop_music_enabled);
	music_pause_btn->setEnabled(music_show_pause);
	music_pause_btn->setVisible(music_show_pause);
	music_play_btn->setVisible(! music_show_pause);
	childSetColor("music_icon", music_icon_color);
	if(!media_icon_name.empty())
	{
		media_icon->setValue(media_icon_name);
	}

	media_play_btn->setEnabled(play_media_enabled);
	media_stop_btn->setEnabled(stop_media_enabled);
	media_pause_btn->setEnabled(media_show_pause);
	media_pause_btn->setVisible(media_show_pause);
	media_play_btn->setVisible(! media_show_pause);
	childSetColor("media_icon", media_icon_color);

	// TODO: this gets removed for Media on a Prim
	
	const std::string mime_type = LLViewerParcelMedia::getMimeType();
	std::string tool_tip = LLMIMETypes::findToolTip(mime_type);
	std::string play_tip = LLMIMETypes::findPlayTip(mime_type);
	// childSetToolTip("media_stop", mControls->getString("stop_label") + "\n" + tool_tip);
	childSetToolTip("media_icon", tool_tip);
	childSetToolTip("media_play", play_tip);
}



////////////////////////////////////////////////////////////////////////////////
//  Debug Floater
//

LLFloaterMediaRemoteCtrl::LLFloaterMediaRemoteCtrl(const LLSD& key) 
:	LLFloater(key)
{	
//	LLUICtrlFactory::getInstance()->buildPanel(this, "panel_media_remote_expanded.xml");
	setIsChrome(TRUE);
	setFocusRoot(TRUE);
	
	mCommitCallbackRegistrar.add("VoiceRemote.Lock",     boost::bind(&LLFloaterMediaRemoteCtrl::onBtnLock, this));		
}

BOOL LLFloaterMediaRemoteCtrl::postBuild()
{
	mControls = getChild<LLPanel>("media_controls");
	llassert_always(mControls);
	
	childSetAction("media_play",LLOverlayBar::toggleMediaPlay,this);
	childSetAction("music_play",LLOverlayBar::toggleMusicPlay,this);
	childSetAction("media_stop",LLOverlayBar::mediaStop,this);
	childSetAction("music_stop",LLOverlayBar::toggleMusicPlay,this);
	childSetAction("media_pause",LLOverlayBar::toggleMediaPlay,this);
	childSetAction("music_pause",LLOverlayBar::toggleMusicPlay,this);
	childSetVisible("expand", false);	
	
	childSetVisible("show_channel", false);	
	mTalkBtn = getChild<LLButton>("push_to_talk");
	mTalkBtn->setClickedCallback(onBtnTalkClicked, this);
	mTalkBtn->setHeldDownCallback(onBtnTalkHeld, this);
	mTalkBtn->setMouseUpCallback(onBtnTalkReleased, this);
	mTalkLockBtn = getChild<LLButton>("ptt_lock");
	mSpeakersBtn = getChild<LLButton>("speakers_btn");
	
	return TRUE;
}

void LLFloaterMediaRemoteCtrl::draw()
{
	enableMediaButtons();
	voiceRemoteDraw();
	LLFloater::draw();
}

LLFloaterMediaRemoteCtrl::LLFloaterMediaRemoteCtrl ()
	: LLFloater(LLSD())
{
}

void LLFloaterMediaRemoteCtrl::onBtnLock()
{
	gSavedSettings.setBOOL("PTTCurrentlyEnabled",mTalkLockBtn->getToggleState());
}

void LLFloaterMediaRemoteCtrl::voiceRemoteDraw()
{	
	BOOL voice_active = FALSE;
	LLVoiceChannel* channelp = LLVoiceChannel::getCurrentVoiceChannel();
	if (channelp)
	{
		voice_active = channelp->isActive();
	}
	
	mTalkBtn->setEnabled(voice_active);
	mTalkLockBtn->setEnabled(voice_active);
	
	// propagate ptt state to button display,
	if (!mTalkBtn->hasMouseCapture())
	{
		// not in push to talk mode, or push to talk is active means I'm talking
		mTalkBtn->setToggleState(!gSavedSettings.getBOOL("PTTCurrentlyEnabled") || gVoiceClient->getUserPTTState());
	}
	mSpeakersBtn->setToggleState(LLFloaterReg::instanceVisible("active_speakers",LLSD()));
	mTalkLockBtn->setToggleState(!gSavedSettings.getBOOL("PTTCurrentlyEnabled"));
	
	std::string talk_blip_image;
	if (gVoiceClient->getIsSpeaking(gAgent.getID()))
	{
		F32 voice_power = gVoiceClient->getCurrentPower(gAgent.getID());
		
		if (voice_power > LLVoiceClient::OVERDRIVEN_POWER_LEVEL)
		{
			talk_blip_image = "icn_voice_ptt-on-lvl3.tga";
		}
		else
		{
			F32 power = gVoiceClient->getCurrentPower(gAgent.getID());
			S32 icon_image_idx = llmin(2, llfloor((power / LLVoiceClient::OVERDRIVEN_POWER_LEVEL) * 3.f));
			
			switch(icon_image_idx)
			{
				case 0:
					talk_blip_image = "icn_voice_ptt-on.tga";
					break;
				case 1:
					talk_blip_image = "icn_voice_ptt-on-lvl1.tga";
					break;
				case 2:
					talk_blip_image = "icn_voice_ptt-on-lvl2.tga";
					break;
			}
		}
	}
	else
	{
		talk_blip_image = "icn_voice_ptt-off.tga";
	}
	
	LLIconCtrl* icon = getChild<LLIconCtrl>("voice_volume");
	if (icon)
	{
		icon->setValue(talk_blip_image);
	}
	
	LLFloater* voice_floater = LLFloaterChatterBox::getCurrentVoiceFloater();
	std::string active_channel_name;
	if (voice_floater)
	{
		active_channel_name = voice_floater->getShortTitle();
	}
	
	LLVoiceChannel* current_channel = LLVoiceChannel::getCurrentVoiceChannel();
	//childSetEnabled("end_call_btn", LLVoiceClient::voiceEnabled() 
	//							&& current_channel
	//							&& current_channel->isActive()
	//							&& current_channel != LLVoiceChannelProximal::getInstance());
	
	childSetValue("channel_label", active_channel_name);
	childSetToolTip("voice_channel_bg", active_channel_name);
	
	if (current_channel)
	{
		if (voice_floater)
		{
			childSetValue("voice_channel_icon", voice_floater->getString("voice_icon"));
		}
		
		LLButton* voice_channel_bg = getChild<LLButton>("voice_channel_bg", FALSE);
		LLColor4 bg_color;
		if (current_channel->isActive())
		{
			bg_color = lerp(LLColor4::green, LLColor4::white, 0.7f);
		}
		else if (current_channel->getState() == LLVoiceChannel::STATE_ERROR)
		{
			bg_color = lerp(LLColor4::red, LLColor4::white, 0.7f);
		}
		else // active, but not connected
		{
			bg_color = lerp(LLColor4::yellow, LLColor4::white, 0.7f);
		}
		voice_channel_bg->setImageColor(bg_color);
	}
		
}

void LLFloaterMediaRemoteCtrl::enableMediaButtons()
{	
	// Media
	bool play_media_enabled = false;
	bool stop_media_enabled = false;
	bool play_music_enabled = false;
	bool stop_music_enabled = false;
	bool music_show_pause = false;
	bool media_show_pause = false;
	static LLUIColor icon_disabled_color = LLUIColorTable::instance().getColor("IconDisabledColor");
	static LLUIColor icon_enabled_color = LLUIColorTable::instance().getColor("IconEnabledColor", LLColor4::white);
	LLColor4 music_icon_color = icon_disabled_color;
	LLColor4 media_icon_color = icon_disabled_color;
	std::string media_type = "none/none";
	
	// Put this in xui file
	std::string media_url = mControls->getString("default_tooltip_label");
	LLParcel* parcel = LLViewerParcelMgr::getInstance()->getAgentParcel();
	
	if (gSavedSettings.getBOOL("AudioStreamingMedia"))
	{
		if ( parcel && !parcel->getMediaURL().empty())
		{
			// Set the tooltip
			// Put this text into xui file
			media_url = parcel->getObscureMedia() ? mControls->getString("media_hidden_label") : parcel->getMediaURL();
			media_type = parcel->getMediaType();
			
			play_media_enabled = true;
			media_icon_color = icon_enabled_color;
			
			LLViewerMediaImpl::EMediaStatus status = LLViewerParcelMedia::getStatus();
			switch(status)
			{
			case LLViewerMediaImpl::MEDIA_NONE:
				media_show_pause = false;
				stop_media_enabled = false;
				break;
			case LLViewerMediaImpl::MEDIA_LOADING:
			case LLViewerMediaImpl::MEDIA_LOADED:
			case LLViewerMediaImpl::MEDIA_PLAYING:
				// HACK: only show the pause button for movie types
				media_show_pause = LLMIMETypes::widgetType(parcel->getMediaType()) == "movie" ? true : false;
				stop_media_enabled = true;
				play_media_enabled = false;
				break;
			case LLViewerMediaImpl::MEDIA_PAUSED:
				media_show_pause = false;
				stop_media_enabled = true;
				break;
			default:
				// inherit defaults above
				break;
			}
		}
	}
	
	if (gSavedSettings.getBOOL("AudioStreamingMusic") && gAudiop)
	{
		
		if ( parcel && !parcel->getMusicURL().empty())
		{
			play_music_enabled = true;
			music_icon_color = icon_enabled_color;
			
			if (gAudiop->isInternetStreamPlaying() == 1)
			{
				music_show_pause = true;
				stop_music_enabled = true;
			}
			else
			{
				music_show_pause = false;
				stop_music_enabled = false;
			}
		}
	}
	const std::string media_icon_name = LLMIMETypes::findIcon(media_type);
	LLButton* music_play_btn = getChild<LLButton>("music_play");
	LLButton* music_stop_btn = getChild<LLButton>("music_stop");
	LLButton* music_pause_btn = getChild<LLButton>("music_pause");
	LLButton* media_play_btn = getChild<LLButton>("media_play");
	LLButton* media_stop_btn = getChild<LLButton>("media_stop");
	LLButton* media_pause_btn = getChild<LLButton>("media_pause");
	LLIconCtrl* media_icon = getChild<LLIconCtrl>("media_icon");
	
	music_play_btn->setEnabled(play_music_enabled);
	music_stop_btn->setEnabled(stop_music_enabled);
	music_pause_btn->setEnabled(music_show_pause);
	music_pause_btn->setVisible(music_show_pause);
	music_play_btn->setVisible(! music_show_pause);
	childSetColor("music_icon", music_icon_color);
	if(!media_icon_name.empty())
	{
		media_icon->setValue(media_icon_name);
	}
	
	media_play_btn->setEnabled(play_media_enabled);
	media_stop_btn->setEnabled(stop_media_enabled);
	media_pause_btn->setEnabled(media_show_pause);
	media_pause_btn->setVisible(media_show_pause);
	media_play_btn->setVisible(! media_show_pause);
	childSetColor("media_icon", media_icon_color);
	
	std::string mime_type = LLMIMETypes::translate(LLViewerParcelMedia::getMimeType());
	std::string tool_tip = LLMIMETypes::findToolTip(LLViewerParcelMedia::getMimeType());
	std::string play_tip = LLMIMETypes::findPlayTip(LLViewerParcelMedia::getMimeType());
	// childSetToolTip("media_stop", mControls->getString("stop_label") + "\n" + tool_tip);
	childSetToolTip("media_icon", tool_tip);
	childSetToolTip("media_play", play_tip);
}

//static
void LLFloaterMediaRemoteCtrl::onBtnTalkClicked(void *user_data)
{
	// when in toggle mode, clicking talk button turns mic on/off
	if (gSavedSettings.getBOOL("PushToTalkToggle"))
	{
		gVoiceClient->toggleUserPTTState();
	}
}

//static
void LLFloaterMediaRemoteCtrl::onBtnTalkHeld(void *user_data)
{
	// when not in toggle mode, holding down talk button turns on mic
	if (!gSavedSettings.getBOOL("PushToTalkToggle"))
	{
		gVoiceClient->setUserPTTState(true);
	}
}

//static
void LLFloaterMediaRemoteCtrl::onBtnTalkReleased(void* user_data)
{
	// when not in toggle mode, releasing talk button turns off mic
	if (!gSavedSettings.getBOOL("PushToTalkToggle"))
	{
		gVoiceClient->setUserPTTState(false);
	}
}

//static
void LLFloaterMediaRemoteCtrl::onClickEndCall(void* user_data)
{
	LLVoiceChannel* current_channel = LLVoiceChannel::getCurrentVoiceChannel();
	
	if (current_channel && current_channel != LLVoiceChannelProximal::getInstance())
	{
		current_channel->deactivate();
	}
}

