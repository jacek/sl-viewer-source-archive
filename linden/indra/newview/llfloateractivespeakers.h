/** 
 * @file llfloateractivespeakers.h
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

#ifndef LL_LLFLOATERACTIVESPEAKERS_H
#define LL_LLFLOATERACTIVESPEAKERS_H

#include "llfloater.h"
#include "llpanel.h"
#include "llscrolllistctrl.h"
#include "llspeakers.h"
#include "llvoiceclient.h"

class LLPanelActiveSpeakers;

class LLFloaterActiveSpeakers : 
	public LLFloater, 
	public LLVoiceClientParticipantObserver
{
	friend class LLFloaterReg;
public:
	
	/*virtual*/ BOOL postBuild();
	/*virtual*/ void draw();

	/*virtual*/ void onChange();

	static void* createSpeakersPanel(void* data);

private:
	
	LLFloaterActiveSpeakers(const LLSD& seed);
	virtual ~LLFloaterActiveSpeakers();

protected:
	LLPanelActiveSpeakers*	mPanel;
};

class LLPanelActiveSpeakers : public LLPanel
{
public:
	LLPanelActiveSpeakers(LLSpeakerMgr* data_source, BOOL show_text_chatters);

	/*virtual*/ BOOL postBuild();

	void handleSpeakerSelect(const LLSD& data = LLSD());
	void refreshSpeakers();
	
	void setSpeaker(const LLUUID& id, 
					const std::string& name = LLStringUtil::null, 
					LLSpeaker::ESpeakerStatus status = LLSpeaker::STATUS_TEXT_ONLY, 
					LLSpeaker::ESpeakerType = LLSpeaker::SPEAKER_AGENT);

	void setVoiceModerationCtrlMode(const BOOL& moderated_voice);
	
	void onClickMuteVoiceCommit(const LLSD& data);
	void onClickMuteTextCommit(const LLSD& data);
	void onVolumeChange(const LLSD& data);
	static void onClickProfile(void* user_data);
	static void onDoubleClickSpeaker(void* user_data);
	void onSortChanged();
	void onModeratorMuteVoice(LLUICtrl* ctrl);
	void onModeratorMuteText(LLUICtrl* ctrl);
	void onChangeModerationMode(LLUICtrl* ctrl);

protected:
	class SpeakerMuteListener : public LLOldEvents::LLSimpleListener
	{
	public:
		SpeakerMuteListener(LLPanelActiveSpeakers* panel) : mPanel(panel) {}

		/*virtual*/ bool handleEvent(LLPointer<LLOldEvents::LLEvent> event, const LLSD& userdata);

		LLPanelActiveSpeakers* mPanel;
	};

	friend class SpeakerAddListener;
	class SpeakerAddListener : public LLOldEvents::LLSimpleListener
	{
	public:
		SpeakerAddListener(LLPanelActiveSpeakers* panel) : mPanel(panel) {}

		/*virtual*/ bool handleEvent(LLPointer<LLOldEvents::LLEvent> event, const LLSD& userdata);

		LLPanelActiveSpeakers* mPanel;
	};

	friend class SpeakerRemoveListener;
	class SpeakerRemoveListener : public LLOldEvents::LLSimpleListener
	{
	public:
		SpeakerRemoveListener(LLPanelActiveSpeakers* panel) : mPanel(panel) {}

		/*virtual*/ bool handleEvent(LLPointer<LLOldEvents::LLEvent> event, const LLSD& userdata);

		LLPanelActiveSpeakers* mPanel;
	};


	friend class SpeakerClearListener;
	class SpeakerClearListener : public LLOldEvents::LLSimpleListener
	{
	public:
		SpeakerClearListener(LLPanelActiveSpeakers* panel) : mPanel(panel) {}

		/*virtual*/ bool handleEvent(LLPointer<LLOldEvents::LLEvent> event, const LLSD& userdata);

		LLPanelActiveSpeakers* mPanel;
	};

	void addSpeaker(const LLUUID& id);
	void removeSpeaker(const LLUUID& id);


	LLScrollListCtrl*	mSpeakerList;
	LLUICtrl*			mMuteVoiceCtrl;
	LLUICtrl*			mMuteTextCtrl;
	LLTextBox*			mNameText;
	LLButton*			mProfileBtn;
	BOOL				mShowTextChatters;
	LLSpeakerMgr*		mSpeakerMgr;
	LLFrameTimer		mIconAnimationTimer;
	LLPointer<SpeakerMuteListener> mSpeakerMuteListener;
	LLPointer<SpeakerAddListener> mSpeakerAddListener;
	LLPointer<SpeakerRemoveListener> mSpeakerRemoveListener;
	LLPointer<SpeakerClearListener> mSpeakerClearListener;
};


#endif // LL_LLFLOATERACTIVESPEAKERS_H
