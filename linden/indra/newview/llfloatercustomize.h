/** 
 * @file llfloatercustomize.h
 * @brief The customize avatar floater, triggered by "Appearance..."
 *
 * $LicenseInfo:firstyear=2002&license=viewergpl$
 * 
 * Copyright (c) 2002-2010, Linden Research, Inc.
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

#ifndef LL_LLFLOATERCUSTOMIZE_H
#define LL_LLFLOATERCUSTOMIZE_H

#include <map>

#include "llfloater.h"
#include "llstring.h"
#include "v3dmath.h"
#include "lltimer.h"
#include "llundo.h"
#include "llviewermenu.h"
#include "llwearable.h"
#include "lliconctrl.h"

class LLButton;
class LLIconCtrl;
class LLColorSwatchCtrl;
class LLGenePool;
class LLInventoryObserver;
class LLJoint;
class LLLineEditor;
class LLRadioGroup;
class LLScrollContainer;
class LLScrollingPanelList;
class LLTextBox;
class LLTextureCtrl;
class LLViewerJointMesh;
class LLViewerVisualParam;
class LLVisualParam;
class LLVisualParamReset;
class LLWearableSaveAsDialog;
class LLPanelWearable;

/////////////////////////////////////////////////////////////////////
// LLFloaterCustomize

class LLFloaterCustomize : public LLFloater
{
public:
	typedef std::pair<BOOL, LLViewerVisualParam*> editable_param;
	typedef std::map<F32, editable_param> param_map;

public:
	LLFloaterCustomize();
	virtual ~LLFloaterCustomize();
	virtual BOOL 	postBuild();

	// Inherted methods from LLFloater (and above)
	virtual BOOL	canClose();
	virtual void	draw();
	/*virtual*/ void openFloater();


	// New methods
	void			clearScrollingPanelList();
	void			generateVisualParamHints(LLViewerJointMesh* joint_mesh,
											 param_map& params, LLPanelWearable* panel);

	const std::string& getEditGroup();
	void 			updateScrollingPanelList(BOOL allow_modify);

	void			setWearable(EWearableType type, LLWearable* wearable, U32 perm_mask, BOOL is_complete);
	void			setWearable(EWearableType type, U32 index);
	LLPanelWearable* getCurrentWearablePanel();

	virtual BOOL	isDirty() const;
	
	typedef boost::function<void (BOOL proceed)> next_step_callback_t;
	void			askToSaveIfDirty( next_step_callback_t next_step_callback );

	void			switchToDefaultSubpart();

	void			setCurrentWearableType( EWearableType type, bool force_change = false );
	EWearableType 	getCurrentWearableType() { return mCurrentWearableType; }

	// Callbacks
	static void		onBtnOk( void* userdata );
	static void		onBtnMakeOutfit( void* userdata );
	static void		onBtnScriptInfo( void* userdata );

	void			onTabChanged( const LLSD& data );
	bool			onTabPrecommit( LLUICtrl* ctrl, const LLSD& data );
	bool			onSaveDialog(const LLSD& notification, const LLSD& response);
	void			onCommitChangeTab(BOOL proceed, LLUICtrl* ctrl, const std::string& selected_tab);

	void fetchInventory();
	void updateInventoryUI();
	void updateScrollingPanelUI();

protected:
	LLPanelWearable*	mWearablePanelList[ WT_COUNT ];

	EWearableType			mCurrentWearableType;

	LLScrollingPanelList*	mScrollingPanelList;
	LLScrollContainer* 		mScrollContainer;
	LLPointer<LLVisualParamReset>		mResetParams;

	LLInventoryObserver* 	mInventoryObserver;

	next_step_callback_t	mNextStepAfterSaveCallback;

protected:
	
	static void* createWearablePanel(void* userdata);
	
	void			initWearablePanels();
};

extern LLFloaterCustomize* gFloaterCustomize;


#endif  // LL_LLFLOATERCUSTOMIZE_H
