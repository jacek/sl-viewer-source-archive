/** 
 * @file llfloatercustomize.cpp
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

#include "llviewerprecompiledheaders.h"

#include "llfloatercustomize.h"

#include "llagent.h"
#include "llagentwearables.h"
#include "llappearance.h"
#include "llappearancemgr.h"
#include "llassetstorage.h"
#include "llbutton.h"
#include "llcolorswatch.h"
#include "lldbstrings.h"
#include "llfilepicker.h"
#include "llfloaterreg.h"
#include "llfloaterscriptlimits.h"
#include "llfloatertools.h"
#include "llfocusmgr.h"
#include "llfontgl.h"
#include "llglheaders.h"
#include "llimagejpeg.h"
#include "llinventoryobserver.h"
#include "lllineeditor.h"
#include "llmodaldialog.h"
#include "llmorphview.h"
#include "llnotificationsutil.h"
#include "llradiogroup.h"
#include "llresmgr.h"
#include "llscrollcontainer.h"
#include "llscrollingpanellist.h"
#include "llsidepanelappearance.h"
#include "llsidetray.h"
#include "llsliderctrl.h"
#include "llspinctrl.h"
#include "lltabcontainer.h"
#include "lltextbox.h"
#include "lltexturectrl.h"
#include "lltextureentry.h"
#include "lltoolmgr.h"
#include "lltoolmorph.h"
#include "lltrans.h"
#include "llui.h"
#include "lluictrlfactory.h"
#include "llviewercamera.h"
#include "llviewercontrol.h"
#include "llviewermessage.h"
#include "llviewermenu.h"
#include "llviewertexturelist.h"
#include "llviewerregion.h"
#include "llviewerwindow.h"
#include "llvoavatarself.h"
#include "llwearablelist.h"
#include "imageids.h"

#include "llscrollingpanelparam.h"

using namespace LLVOAvatarDefines;

//*TODO: Translate : The ui xml for this really needs to be integrated with the appearance paramaters

// Globals
LLFloaterCustomize* gFloaterCustomize = NULL;

const F32 PARAM_STEP_TIME_THRESHOLD = 0.25f;

/////////////////////////////////////////////////////////////////////
// LLFloaterCustomizeObserver

class LLFloaterCustomizeObserver : public LLInventoryObserver
{
public:
	LLFloaterCustomizeObserver(LLFloaterCustomize* fc) : mFC(fc) {}
	virtual ~LLFloaterCustomizeObserver() {}
	virtual void changed(U32 mask) { mFC->updateScrollingPanelUI(); }
protected:
	LLFloaterCustomize* mFC;
};

////////////////////////////////////////////////////////////////////////////

// Local Constants 

class LLWearableSaveAsDialog : public LLModalDialog
{
private:
	std::string	mItemName;
	std::string mTempItemName;
	
	boost::signals2::signal<void (const std::string&)> mSaveAsSignal;

public:
	LLWearableSaveAsDialog( const LLSD& key )
		: LLModalDialog( key ),
		  mTempItemName(key.asString())
	{
	}
		
	BOOL postBuild()
	{
		getChild<LLUICtrl>("Save")->setCommitCallback(boost::bind(&LLWearableSaveAsDialog::onSave, this ));
		getChild<LLUICtrl>("Cancel")->setCommitCallback(boost::bind(&LLWearableSaveAsDialog::onCancel, this ));
		
		childSetTextArg("name ed", "[DESC]", mTempItemName);
		return TRUE;
	}

	void setSaveAsCommit( const boost::signals2::signal<void (const std::string&)>::slot_type& cb )
	{
		mSaveAsSignal.connect(cb);
	}

	virtual void onOpen(const LLSD& key)
	{
		LLLineEditor* edit = getChild<LLLineEditor>("name ed");
		if (edit)
		{
			edit->setFocus(TRUE);
			edit->selectAll();
		}
	}

	void onSave()
	{
		mItemName = childGetValue("name ed").asString();
		LLStringUtil::trim(mItemName);
		if( !mItemName.empty() )
		{
			mSaveAsSignal(mItemName);
			closeFloater(); // destroys this object
		}
	}

	void onCancel()
	{
		closeFloater(); // destroys this object
	}
};

////////////////////////////////////////////////////////////////////////////

BOOL edit_wearable_for_teens(EWearableType type)
{
	switch(type)
	{
	case WT_UNDERSHIRT:
	case WT_UNDERPANTS:
		return FALSE;
	default:
		return TRUE;
	}
}

/////////////////////////////////////////////////////////////////////
// LLPanelWearable

enum ESubpart {
	SUBPART_SHAPE_uninit = 0,

	SUBPART_SHAPE_HEAD,
	SUBPART_SHAPE_EYES,
	SUBPART_SHAPE_EARS,
	SUBPART_SHAPE_NOSE,
	SUBPART_SHAPE_MOUTH,
	SUBPART_SHAPE_CHIN,
	SUBPART_SHAPE_TORSO,
	SUBPART_SHAPE_LEGS,
	SUBPART_SHAPE_WHOLE,
	SUBPART_SHAPE_DETAIL,
	SUBPART_SKIN_COLOR,
	SUBPART_SKIN_FACEDETAIL,
	SUBPART_SKIN_MAKEUP,
	SUBPART_SKIN_BODYDETAIL,
	SUBPART_HAIR_COLOR,
	SUBPART_HAIR_STYLE,
	SUBPART_HAIR_EYEBROWS,
	SUBPART_HAIR_FACIAL,
	SUBPART_EYES,
	SUBPART_SHIRT,
	SUBPART_PANTS,
	SUBPART_SHOES,
	SUBPART_SOCKS,
	SUBPART_JACKET,
	SUBPART_GLOVES,
	SUBPART_UNDERSHIRT,
	SUBPART_UNDERPANTS,
	SUBPART_SKIRT,
	SUBPART_ALPHA,
	SUBPART_TATTOO
 };

struct LLSubpart
{
	LLSubpart() : mSex( SEX_BOTH ) {}

	std::string			mButtonName;
	std::string			mTargetJoint;
	std::string			mEditGroup;
	LLVector3d			mTargetOffset;
	LLVector3d			mCameraOffset;
	ESex				mSex;
};

////////////////////////////////////////////////////////////////////////////

class LLPanelWearable : public LLPanel
{
public:
	LLPanelWearable( EWearableType type );
	virtual ~LLPanelWearable();
	void				onParentFloaterClosed(); // Parent (i.e. llfloatercustomize floater) was closed

	virtual BOOL 		postBuild();
	virtual void		draw();
	virtual BOOL		isDirty() const;	// LLUICtrl
	
	void				addSubpart(const std::string& name, ESubpart id, LLSubpart* part );
	void				addTextureDropTarget( LLVOAvatarDefines::ETextureIndex te, const std::string& name, const LLUUID& default_image_id, BOOL allow_no_texture );
	void				addInvisibilityCheckbox( LLVOAvatarDefines::ETextureIndex te, const std::string& name );
	void				addColorSwatch( LLVOAvatarDefines::ETextureIndex te, const std::string& name );

	const std::string&	getLabel() const 	{ return LLWearableDictionary::getTypeLabel( mType ); }
	EWearableType		getType() const 	{ return mType; }
	U32					getIndex() const 	{ return mIndex; }
	LLWearable*			getWearable() const { return gAgentWearables.getWearable(mType, mIndex); }

	void				cleanupIndex();

	LLSubpart*			getCurrentSubpart() { return mSubpartList[mCurrentSubpart]; }
	ESubpart			getDefaultSubpart();
	void				setSubpart( ESubpart subpart );
	void				switchToDefaultSubpart();
	void				reset();

	void 				setWearable(LLWearable* wearable, U32 perm_mask, BOOL is_complete);

	void 				setUIPermissions(U32 perm_mask, BOOL is_complete);
	
	void				hideTextureControls();
	bool				textureIsInvisible( LLVOAvatarDefines::ETextureIndex te );
	void				initPreviousTextureList();
	void				initPreviousTextureListEntry(ETextureIndex te);
	
	virtual void		setVisible( BOOL visible );

	// Callbacks
	static void			onBtnSubpart( void* userdata );
	static void			onBtnTakeOff( void* userdata );
	static void			onBtnSave( void* userdata );

	static void			onBtnSaveAs( void* userdata );
	void				onSaveAsCommit(const std::string& item_name);

	static void			onBtnRevert( void* userdata );
	static void			onBtnTakeOffDialog( S32 option, void* userdata );
	static void			onBtnCreateNew( void* userdata );
	static void			onTextureCommit( LLUICtrl* ctrl, void* userdata );
	static void			onInvisibilityCommit( LLUICtrl* ctrl, void* userdata );
	static void			onColorCommit( LLUICtrl* ctrl, void* userdata );
	static void			onCommitSexChange( LLUICtrl*, void* userdata );
	static bool			onSelectAutoWearOption(const LLSD& notification, const LLSD& response);
	static void			onIndexSet( LLUICtrl*, void* userdata );



private:
	EWearableType		mType;
	U32					mIndex;
	bool				mCanTakeOff;
	typedef std::map<std::string, S32> string_s32_map_t;
	string_s32_map_t mTextureList;
	string_s32_map_t mInvisibilityList;
	string_s32_map_t mColorList;

	typedef std::map<S32,LLUUID> s32_uuid_map_t;
	s32_uuid_map_t mPreviousTextureList;
	
	std::map<ESubpart, LLSubpart*> mSubpartList;
	ESubpart			mCurrentSubpart;
};

////////////////////////////////////////////////////////////////////////////

LLPanelWearable::LLPanelWearable( EWearableType type )
	: LLPanel(),
	  mType(type),
	  mIndex(0),
	  mCanTakeOff(false),
	  mCurrentSubpart(SUBPART_SHAPE_uninit)
{
	static bool registered_dialog = false;
	if (!registered_dialog)
	{
		LLFloaterReg::add("wearable_save_as", "floater_wearable_save_as.xml", (LLFloaterBuildFunc)&LLFloaterReg::build<LLWearableSaveAsDialog>);
		registered_dialog = true;
	}
}

void LLPanelWearable::onParentFloaterClosed()
{
	// Commit and close all children.
	for (string_s32_map_t::const_iterator iter = mColorList.begin();
		 iter != mColorList.end(); 
		 ++iter)
	{
		const std::string name = iter->first;
		LLColorSwatchCtrl* ctrl = getChild<LLColorSwatchCtrl>(name);
		if (ctrl)
		{
			ctrl->onParentFloaterClosed();
		}
	}
}

BOOL LLPanelWearable::postBuild()
{
	LLAssetType::EType asset_type = LLWearableDictionary::getAssetType( mType );
	std::string icon_name = (asset_type == LLAssetType::AT_CLOTHING ?
										 "Inv_Clothing" :
										 "Inv_Skin" );
	childSetValue("icon", icon_name);

	childSetAction("Create New", LLPanelWearable::onBtnCreateNew, this );

	// If PG, can't take off underclothing or shirt
	mCanTakeOff =
		LLWearableDictionary::getAssetType( mType ) == LLAssetType::AT_CLOTHING &&
		!( gAgent.isTeen() && (mType == WT_UNDERSHIRT || mType == WT_UNDERPANTS) );
	childSetVisible("Take Off", mCanTakeOff);
	childSetAction("Take Off", LLPanelWearable::onBtnTakeOff, this );

	childSetAction("Save",  &LLPanelWearable::onBtnSave, (void*)this );

	childSetAction("Save As", &LLPanelWearable::onBtnSaveAs, (void*)this );

	childSetAction("Revert", &LLPanelWearable::onBtnRevert, (void*)this );

	childSetCommitCallback("index", &LLPanelWearable::onIndexSet, (void*)this );

	return TRUE;
}

LLPanelWearable::~LLPanelWearable()
{
	std::for_each(mSubpartList.begin(), mSubpartList.end(), DeletePairedPointer());

}

void LLPanelWearable::addSubpart( const std::string& name, ESubpart id, LLSubpart* part )
{
	if (!name.empty())
	{
		childSetAction(name, &LLPanelWearable::onBtnSubpart, (void*)id);
		part->mButtonName = name;
	}
	mSubpartList[id] = part;
	
}

// static
void LLPanelWearable::onBtnSubpart(void* userdata)
{
	LLFloaterCustomize* floater_customize = gFloaterCustomize;
	if (!floater_customize) return;
	LLPanelWearable* self = floater_customize->getCurrentWearablePanel();
	if (!self) return;
	ESubpart subpart = (ESubpart) (intptr_t)userdata;
	self->setSubpart( subpart );
}

void LLPanelWearable::setSubpart( ESubpart subpart )
{
	mCurrentSubpart = subpart;

	LLSubpart* part = get_if_there(mSubpartList, (ESubpart)subpart, (LLSubpart*)NULL);
	if( part )
	{
		// Update the thumbnails we display
		LLFloaterCustomize::param_map sorted_params;
		LLVOAvatar* avatar = gAgent.getAvatarObject();
		ESex avatar_sex = avatar->getSex();
		LLViewerInventoryItem* item = NULL;
		LLWearable* wearable = getWearable();
		// MULTI_WEARABLE:
		if (wearable)
		{
			item = (LLViewerInventoryItem*)gInventory.getItem(wearable->getItemID());
		}
		U32 perm_mask = 0x0;
		BOOL is_complete = FALSE;
		if(item)
		{
			perm_mask = item->getPermissions().getMaskOwner();
			is_complete = item->isComplete();
		}
		setUIPermissions(perm_mask, is_complete);
		BOOL editable = ((perm_mask & PERM_MODIFY) && is_complete) ? TRUE : FALSE;
		
		for (std::map<ESubpart, LLSubpart*>::iterator iter = mSubpartList.begin();
			 iter != mSubpartList.end(); ++iter)
		{
			LLButton* btn = getChild<LLButton>(iter->second->mButtonName);
			if (btn)
			{
				btn->setVisible(editable);
				btn->setToggleState( (subpart == iter->first) );
			}
		}
		
		if (wearable && editable)
		{
			for(LLViewerVisualParam* param = (LLViewerVisualParam *)avatar->getFirstVisualParam(); 
				param; 
				param = (LLViewerVisualParam *)avatar->getNextVisualParam())
			{
				if (param->getID() == -1
					|| param->getGroup() != VISUAL_PARAM_GROUP_TWEAKABLE 
					|| param->getEditGroup() != part->mEditGroup 
					|| !(param->getSex() & avatar_sex))
				{
					continue;
				}
	
				// negative getDisplayOrder() to make lowest order the highest priority
				LLFloaterCustomize::param_map::value_type vt(-param->getDisplayOrder(), LLFloaterCustomize::editable_param(editable, param));
				llassert( sorted_params.find(-param->getDisplayOrder()) == sorted_params.end() );  // Check for duplicates
				sorted_params.insert(vt);
			}
			gFloaterCustomize->generateVisualParamHints(NULL, sorted_params, this);
			gFloaterCustomize->updateScrollingPanelUI();
		} 
		else
		{
			gFloaterCustomize->clearScrollingPanelList();
		}


		// Update the camera
		gMorphView->setCameraTargetJoint( gAgent.getAvatarObject()->getJoint( part->mTargetJoint ) );
		gMorphView->setCameraTargetOffset( part->mTargetOffset );
		gMorphView->setCameraOffset( part->mCameraOffset );
		gMorphView->setCameraDistToDefault();
		if (gSavedSettings.getBOOL("AppearanceCameraMovement"))
		{
			gMorphView->updateCamera();
		}
	}
}

// static
void LLPanelWearable::onBtnTakeOff( void* userdata )
{
	LLPanelWearable* self = (LLPanelWearable*) userdata;
	
	LLWearable* wearable = gAgentWearables.getWearable( self->mType, self->mIndex );
	if( !wearable )
	{
		return;
	}

	LLAppearanceManager::instance().removeCOFItemLinks(wearable->getItemID(), true);
}

// static
void LLPanelWearable::onBtnSave( void* userdata )
{
	LLPanelWearable* self = (LLPanelWearable*) userdata;
	gAgentWearables.saveWearable( self->mType, self->mIndex );
	if (gFloaterCustomize)
	{
		gFloaterCustomize->setWearable(self->mType, 
									   self->mIndex);
		gFloaterCustomize->getCurrentWearablePanel()->reset();
	}
}

// static
void LLPanelWearable::onBtnSaveAs( void* userdata )
{
	LLPanelWearable* self = (LLPanelWearable*) userdata;
	// MULTI_WEARABLE:
	LLWearable* wearable = gAgentWearables.getWearable( self->getType(), 0 );
	if( wearable )
	{
		LLWearableSaveAsDialog* save_as_dialog = LLFloaterReg::showTypedInstance<LLWearableSaveAsDialog>("wearable_save_as", LLSD(wearable->getName()), TRUE);
		if (save_as_dialog)
		{
			save_as_dialog->setSaveAsCommit(boost::bind(&LLPanelWearable::onSaveAsCommit, self, _1 ));
		}
	}
}

void LLPanelWearable::onSaveAsCommit(const std::string& item_name)
{
	LLVOAvatar* avatar = gAgent.getAvatarObject();
	if( avatar )
	{
		gAgentWearables.saveWearableAs( mType, mIndex, item_name, FALSE );
	}
}

// static
void LLPanelWearable::onBtnRevert( void* userdata )
{
	LLPanelWearable* self = (LLPanelWearable*) userdata;
	gAgentWearables.revertWearable( self->mType, self->mIndex );
}

// static
void LLPanelWearable::onBtnCreateNew( void* userdata )
{
	LLPanelWearable* self = (LLPanelWearable*) userdata;
	LLSD payload;
	payload["wearable_type"] = (S32)self->getType();
	LLNotificationsUtil::add("AutoWearNewClothing", LLSD(), payload, &onSelectAutoWearOption);
}

bool LLPanelWearable::onSelectAutoWearOption(const LLSD& notification, const LLSD& response)
{
	S32 option = LLNotificationsUtil::getSelectedOption(notification, response);
	LLVOAvatar* avatar = gAgent.getAvatarObject();
	if(avatar)
	{
		// Create a new wearable in the default folder for the wearable's asset type.
		LLWearable* wearable = LLWearableList::instance().createNewWearable( (EWearableType)notification["payload"]["wearable_type"].asInteger() );
		LLAssetType::EType asset_type = wearable->getAssetType();

		LLUUID folder_id;
		// regular UI, items get created in normal folder
		folder_id = gInventory.findCategoryUUIDForType(LLFolderType::assetTypeToFolderType(asset_type));

		// Only auto wear the new item if the AutoWearNewClothing checkbox is selected.
		LLPointer<LLInventoryCallback> cb = option == 0 ? 
			new WearOnAvatarCallback : NULL;
		create_inventory_item(gAgent.getID(), gAgent.getSessionID(),
			folder_id, wearable->getTransactionID(), wearable->getName(), wearable->getDescription(),
			asset_type, LLInventoryType::IT_WEARABLE, wearable->getType(),
			wearable->getPermissions().getMaskNextOwner(), cb);
	}
	return false;
}

// static
void LLPanelWearable::onIndexSet( LLUICtrl*, void* userdata )
{
	LLPanelWearable* self = (LLPanelWearable*) userdata;
	U32 new_index = self->childGetValue("index").asInteger();
	if (self->mIndex != new_index)
	{
		self->mIndex = new_index;
		llinfos << "type " << self->mType << " index " << self->mIndex << " wearable ptr: " << self->getWearable() << llendl;
	}
}

bool LLPanelWearable::textureIsInvisible( LLVOAvatarDefines::ETextureIndex te )
{
	if( getWearable() )
	{
		LLViewerTexture* curr_image = getWearable()->getLocalTextureObject(te)->getImage();
		return (curr_image && curr_image->getID() == IMG_INVISIBLE);
	}
	else
		return false;
}

void LLPanelWearable::addInvisibilityCheckbox( LLVOAvatarDefines::ETextureIndex te, const std::string& name )
{
	childSetCommitCallback(name, LLPanelWearable::onInvisibilityCommit, this);
	
	mInvisibilityList[name] = te;
}

// static
void LLPanelWearable::onInvisibilityCommit( LLUICtrl* ctrl, void* userdata )
{
	LLPanelWearable* self = (LLPanelWearable*) userdata;
	LLCheckBoxCtrl* checkbox_ctrl = (LLCheckBoxCtrl*) ctrl;
	llinfos << "onInvisibilityCommit, self " << self << " checkbox_ctrl " << checkbox_ctrl << llendl;
	LLVOAvatarSelf *avatar = gAgent.getAvatarObject();

	ETextureIndex te = (ETextureIndex)(self->mInvisibilityList[ctrl->getName()]);

	bool new_invis_state = checkbox_ctrl->get();
	if (new_invis_state)
	{
		LLViewerFetchedTexture* image = LLViewerTextureManager::getFetchedTexture( IMG_INVISIBLE );
		LLLocalTextureObject *lto = self->getWearable()->getLocalTextureObject(te);
		self->mPreviousTextureList[(S32)te] = lto->getID();
		U32 index = gAgentWearables.getWearableIndex(self->getWearable());
		avatar->setLocalTexture(te,image,FALSE,index);
		avatar->wearableUpdated(self->getWearable()->getType(), FALSE);
	}
	else
	{
		// Try to restore previous texture, if any.
		LLUUID prev_id = self->mPreviousTextureList[(S32)te];
		if (prev_id.isNull() || (prev_id == IMG_INVISIBLE))
		{
			prev_id = LLUUID( gSavedSettings.getString( "UIImgDefaultAlphaUUID" ) );
		}
		if (prev_id.notNull())
		{
			LLViewerFetchedTexture* image = LLViewerTextureManager::getFetchedTexture( prev_id );
			U32 index = gAgentWearables.getWearableIndex(self->getWearable());
			avatar->setLocalTexture(te,image,FALSE,index);
			avatar->wearableUpdated(self->getWearable()->getType(), FALSE);
		}
		
	}
}

void LLPanelWearable::addColorSwatch( LLVOAvatarDefines::ETextureIndex te, const std::string& name )
{
	childSetCommitCallback(name, LLPanelWearable::onColorCommit, this);
	mColorList[name] = te;
}

// static
void LLPanelWearable::onColorCommit( LLUICtrl* ctrl, void* userdata )
{
	LLPanelWearable* self = (LLPanelWearable*) userdata;
	LLColorSwatchCtrl* color_ctrl = (LLColorSwatchCtrl*) ctrl;

	ETextureIndex te = (ETextureIndex)(self->mColorList[ctrl->getName()]);
	LLVOAvatarSelf *avatar = gAgent.getAvatarObject();

	LLColor4 old_color = self->getWearable()->getClothesColor(te);
	const LLColor4& new_color = color_ctrl->get();
	if( old_color != new_color )
	{
		// Set the new version
		self->getWearable()->setClothesColor( te, new_color, TRUE );

		LLVisualParamHint::requestHintUpdates();
		avatar->wearableUpdated(self->getWearable()->getType(), FALSE);
	}
}

void LLPanelWearable::initPreviousTextureList()
{
	initPreviousTextureListEntry(TEX_LOWER_ALPHA);
	initPreviousTextureListEntry(TEX_UPPER_ALPHA);
	initPreviousTextureListEntry(TEX_HEAD_ALPHA);
	initPreviousTextureListEntry(TEX_EYES_ALPHA);
	initPreviousTextureListEntry(TEX_LOWER_ALPHA);
}

void LLPanelWearable::initPreviousTextureListEntry(ETextureIndex te)
{
	LLLocalTextureObject *lto = getWearable()->getLocalTextureObject(te);
	if (lto)
	{
		mPreviousTextureList[te] = lto->getID();
	}
}

void LLPanelWearable::addTextureDropTarget( ETextureIndex te, const std::string& name,
												const LLUUID& default_image_id, BOOL allow_no_texture )
{
	childSetCommitCallback(name, LLPanelWearable::onTextureCommit, this);
	LLTextureCtrl* texture_ctrl = getChild<LLTextureCtrl>(name);
	if (texture_ctrl)
	{
		texture_ctrl->setDefaultImageAssetID(default_image_id);
		texture_ctrl->setAllowNoTexture( allow_no_texture );
		// Don't allow (no copy) or (no transfer) textures to be selected.
		texture_ctrl->setImmediateFilterPermMask(PERM_NONE);//PERM_COPY | PERM_TRANSFER);
		texture_ctrl->setNonImmediateFilterPermMask(PERM_NONE);//PERM_COPY | PERM_TRANSFER);
	}
	mTextureList[name] = te;
	if (getWearable())
	{
		LLLocalTextureObject *lto = getWearable()->getLocalTextureObject(te);
		if (lto)
		{
			mPreviousTextureList[te] = lto->getID();
		}
	}
}

// static
void LLPanelWearable::onTextureCommit( LLUICtrl* ctrl, void* userdata )
{
	LLPanelWearable* self = (LLPanelWearable*) userdata;
	LLTextureCtrl* texture_ctrl = (LLTextureCtrl*) ctrl;

	ETextureIndex te = (ETextureIndex)(self->mTextureList[ctrl->getName()]);

	// Set the new version
	LLViewerFetchedTexture* image = LLViewerTextureManager::getFetchedTexture( texture_ctrl->getImageAssetID() );
	if( image->getID().isNull() )
	{
		image = LLViewerTextureManager::getFetchedTexture(IMG_DEFAULT_AVATAR);
	}
	if (self->getWearable())
	{
		LLVOAvatarSelf *avatar = gAgent.getAvatarObject();
		U32 index = gAgentWearables.getWearableIndex(self->getWearable());
		avatar->setLocalTexture(te,image,FALSE,index);
		avatar->wearableUpdated(self->getWearable()->getType(), FALSE);
	}
	if (image->getID() != IMG_INVISIBLE)
	{
		self->mPreviousTextureList[te] = image->getID();
	}
}


ESubpart LLPanelWearable::getDefaultSubpart()
{
	switch( mType )
	{
		case WT_SHAPE:		return SUBPART_SHAPE_WHOLE;
		case WT_SKIN:		return SUBPART_SKIN_COLOR;
		case WT_HAIR:		return SUBPART_HAIR_COLOR;
		case WT_EYES:		return SUBPART_EYES;
		case WT_SHIRT:		return SUBPART_SHIRT;
		case WT_PANTS:		return SUBPART_PANTS;
		case WT_SHOES:		return SUBPART_SHOES;
		case WT_SOCKS:		return SUBPART_SOCKS;
		case WT_JACKET:		return SUBPART_JACKET;
		case WT_GLOVES:		return SUBPART_GLOVES;
		case WT_UNDERSHIRT:	return SUBPART_UNDERSHIRT;
		case WT_UNDERPANTS:	return SUBPART_UNDERPANTS;
		case WT_SKIRT:		return SUBPART_SKIRT;
		case WT_ALPHA:		return SUBPART_ALPHA;
		case WT_TATTOO:		return SUBPART_TATTOO;

		default:	llassert(0);		return SUBPART_SHAPE_WHOLE;
	}
}


void LLPanelWearable::draw()
{
	if( gFloaterCustomize->isMinimized() )
	{
		return;
	}

	LLVOAvatar* avatar = gAgent.getAvatarObject();
	if( !avatar )
	{
		return;
	}

	cleanupIndex();
	BOOL has_wearable = (getWearable() != NULL );
	BOOL is_dirty = isDirty();
	BOOL is_modifiable = FALSE;
	BOOL is_copyable = FALSE;
	BOOL is_complete = FALSE;
	LLViewerInventoryItem* item;

	item = (LLViewerInventoryItem*)gAgentWearables.getWearableInventoryItem(mType, mIndex);
	if(item)
	{
		const LLPermissions& perm = item->getPermissions();
		is_modifiable = perm.allowModifyBy(gAgent.getID(), gAgent.getGroupID());
		is_copyable = perm.allowCopyBy(gAgent.getID(), gAgent.getGroupID());
		is_complete = item->isComplete();
	}

	childSetEnabled("Save", is_modifiable && is_complete && has_wearable && is_dirty);
	childSetEnabled("Save As", is_copyable && is_complete && has_wearable);
	childSetEnabled("Revert", has_wearable && is_dirty );
	childSetEnabled("Take Off",  has_wearable );
	childSetVisible("Take Off", mCanTakeOff && has_wearable  );
	childSetVisible("Create New", !has_wearable );

	childSetVisible("not worn instructions",  !has_wearable );
	childSetVisible("no modify instructions",  has_wearable && !is_modifiable);

	for (std::map<ESubpart, LLSubpart*>::iterator iter = mSubpartList.begin();
		 iter != mSubpartList.end(); ++iter)
	{
		if( has_wearable && is_complete && is_modifiable )
		{
			childSetEnabled(iter->second->mButtonName, iter->second->mSex & avatar->getSex() );
		}
		else
		{
			childSetEnabled(iter->second->mButtonName, FALSE );
		}
	}

	childSetVisible("square", !is_modifiable);

	childSetVisible("title", FALSE);
	childSetVisible("title_no_modify", FALSE);
	childSetVisible("title_not_worn", FALSE);
	childSetVisible("title_loading", FALSE);

	childSetVisible("path", FALSE);
	LLSpinCtrl* spin_ctrl = findChild<LLSpinCtrl>("index",FALSE);
	if (spin_ctrl)
	{
		spin_ctrl->setVisible(FALSE);
	}
	
	if(has_wearable && !is_modifiable)
	{
		childSetVisible("title_no_modify", TRUE);
		childSetTextArg("title_no_modify", "[DESC]", std::string(LLWearableDictionary::getTypeLabel( mType )));
		
		hideTextureControls();
	}
	else if(has_wearable && !is_complete)
	{
		childSetVisible("title_loading", TRUE);
		childSetTextArg("title_loading", "[DESC]", std::string(LLWearableDictionary::getTypeLabel( mType )));
			
		std::string path;
		const LLUUID& item_id = gAgentWearables.getWearableItemID( getWearable()->getType(), mIndex );
		llassert_always(item_id.notNull()); // MULTI_WEARABLE:
		gInventory.appendPath(item_id, path);
		childSetVisible("path", TRUE);
		childSetTextArg("path", "[PATH]", path);
		U32 count = gAgentWearables.getWearableCount( getWearable()->getType() );
		if ((count>0) && spin_ctrl)
		{
			spin_ctrl->setMinValue((F32)0);
			spin_ctrl->setMaxValue((F32)(count-1));
			spin_ctrl->setValue( (F32)mIndex );
			spin_ctrl->setVisible(TRUE);
		}

		hideTextureControls();
	}
	else if(has_wearable && is_modifiable)
	{
		childSetVisible("title", TRUE);
		childSetTextArg("title", "[DESC]", getWearable()->getName() );

		std::string path;
		const LLUUID& item_id = gAgentWearables.getWearableItemID( getWearable()->getType(), mIndex );
		llassert_always(item_id.notNull()); // MULTI_WEARABLE:
		gInventory.appendPath(item_id, path);
		childSetVisible("path", TRUE);
		childSetTextArg("path", "[PATH]", path);
		U32 count = gAgentWearables.getWearableCount( getWearable()->getType() );
		if ((count>0) && spin_ctrl)
		{
			spin_ctrl->setMinValue((F32)0);
			spin_ctrl->setMaxValue((F32)(count-1));
			spin_ctrl->setValue( (F32)mIndex );
			spin_ctrl->setVisible(TRUE);
		}

		for( string_s32_map_t::iterator iter = mTextureList.begin();
			 iter != mTextureList.end(); ++iter )
		{
			std::string name = iter->first;
			LLTextureCtrl* texture_ctrl = getChild<LLTextureCtrl>(name);
			S32 te_index = iter->second;
			childSetVisible(name, is_copyable && is_modifiable && is_complete );
			if (texture_ctrl)
			{
				LLLocalTextureObject *lto = getWearable()->getLocalTextureObject(te_index);

				LLUUID new_id;
				
				if( lto && (lto->getID() != IMG_DEFAULT_AVATAR) )
				{
					new_id = lto->getID();
				}
				else
				{
					new_id = LLUUID::null;
				}

				LLUUID old_id = texture_ctrl->getImageAssetID();

				if (old_id != new_id)
				{
					// texture has changed, close the floater to avoid DEV-22461
					texture_ctrl->closeDependentFloater();
				}
				
				texture_ctrl->setImageAssetID(new_id);
			}
		}

		for( string_s32_map_t::iterator iter = mColorList.begin();
			 iter != mColorList.end(); ++iter )
		{
			std::string name = iter->first;
			S32 te_index = iter->second;
			childSetVisible(name, is_modifiable && is_complete );
			childSetEnabled(name, is_modifiable && is_complete );
			LLColorSwatchCtrl* ctrl = getChild<LLColorSwatchCtrl>(name);
			if (ctrl)
			{
				ctrl->set(getWearable()->getClothesColor( (ETextureIndex)te_index ) );
			}
		}

		for( string_s32_map_t::iterator iter = mInvisibilityList.begin();
			 iter != mInvisibilityList.end(); ++iter )
		{
			std::string name = iter->first;
			LLVOAvatarDefines::ETextureIndex te = (LLVOAvatarDefines::ETextureIndex)iter->second;
			childSetVisible(name, is_copyable && is_modifiable && is_complete );
			childSetEnabled(name, is_copyable && is_modifiable && is_complete );
			LLCheckBoxCtrl* ctrl = getChild<LLCheckBoxCtrl>(name);
			if (ctrl)
			{
				ctrl->set(textureIsInvisible(te));
			}
		}

	}
	else
	{
		childSetVisible("title_not_worn", TRUE);
		childSetTextArg("title_not_worn", "[DESC]", std::string(LLWearableDictionary::getTypeLabel( mType )));

		hideTextureControls();
	}
	
	childSetVisible("icon", has_wearable && is_modifiable);

	LLPanel::draw();
}

void LLPanelWearable::hideTextureControls()
{
	for( string_s32_map_t::iterator iter = mTextureList.begin();
			 iter != mTextureList.end(); ++iter )
		{
			childSetVisible(iter->first, FALSE );
		}
	for( string_s32_map_t::iterator iter = mColorList.begin();
			 iter != mColorList.end(); ++iter )
		{
			childSetVisible(iter->first, FALSE );
		}
	for( string_s32_map_t::iterator iter = mInvisibilityList.begin();
		 iter != mInvisibilityList.end(); ++iter )
	{
		childSetVisible(iter->first, FALSE );
	}
}

void LLPanelWearable::setWearable(LLWearable* wearable, U32 perm_mask, BOOL is_complete)
{
	if( wearable )
	{
		setUIPermissions(perm_mask, is_complete);
		if (wearable->getType() == WT_ALPHA)
		{
			initPreviousTextureList();
		}
	}
}

// Fix mIndex in case clothing has disappeared from gAgentWearables since it was last set.
void LLPanelWearable::cleanupIndex()
{
	U32 count = gAgentWearables.getWearableCount(mType);
	if ((count > 0) && (mIndex >= count))
	{
		mIndex = count-1;
	}
}

void LLPanelWearable::switchToDefaultSubpart()
{
	setSubpart( getDefaultSubpart() );
}

void LLPanelWearable::reset()
{
	setSubpart(mCurrentSubpart);
}

void LLPanelWearable::setVisible(BOOL visible)
{
	LLPanel::setVisible( visible );
	if( !visible )
	{
		for( string_s32_map_t::iterator iter = mColorList.begin();
			 iter != mColorList.end(); ++iter )
		{
			// this forces any open color pickers to cancel their selection
			childSetEnabled(iter->first, FALSE );
		}
	}
}

BOOL LLPanelWearable::isDirty() const
{
	if( !getWearable() )
	{
		return FALSE;
	}

	if( getWearable()->isDirty() )
	{
		return TRUE;
	}

	return FALSE;
}

// static
void LLPanelWearable::onCommitSexChange( LLUICtrl*, void* userdata )
{
	LLPanelWearable* self = (LLPanelWearable*) userdata;

	LLVOAvatar* avatar = gAgent.getAvatarObject();
	if (!avatar)
	{
		return;
	}

	if( !gAgentWearables.isWearableModifiable(self->mType, self->mIndex))
	{
		return;
	}

	ESex new_sex = gSavedSettings.getU32("AvatarSex") ? SEX_MALE : SEX_FEMALE;

	LLViewerVisualParam* param = (LLViewerVisualParam*)avatar->getVisualParam( "male" );
	if( !param )
	{
		return;
	}

	if (self->getWearable())
	{
		self->getWearable()->setVisualParamWeight(param->getID(), (new_sex==SEX_MALE), FALSE);
	}
	param->setWeight( (new_sex == SEX_MALE), FALSE );

	avatar->updateSexDependentLayerSets( FALSE );

	avatar->updateVisualParams();

	gFloaterCustomize->clearScrollingPanelList();

	// Assumes that we're in the "Shape" Panel.
	self->setSubpart( SUBPART_SHAPE_WHOLE );
}

void LLPanelWearable::setUIPermissions(U32 perm_mask, BOOL is_complete)
{
	BOOL is_copyable = (perm_mask & PERM_COPY) ? TRUE : FALSE;
	BOOL is_modifiable = (perm_mask & PERM_MODIFY) ? TRUE : FALSE;

	childSetEnabled("Save", is_modifiable && is_complete);
	childSetEnabled("Save As", is_copyable && is_complete);
	childSetEnabled("sex radio", is_modifiable && is_complete);
	for( string_s32_map_t::iterator iter = mTextureList.begin();
		 iter != mTextureList.end(); ++iter )
	{
		childSetVisible(iter->first, is_copyable && is_modifiable && is_complete );
	}
	for( string_s32_map_t::iterator iter = mColorList.begin();
		 iter != mColorList.end(); ++iter )
	{
		childSetVisible(iter->first, is_modifiable && is_complete );
	}
	for( string_s32_map_t::iterator iter = mInvisibilityList.begin();
		 iter != mInvisibilityList.end(); ++iter )
	{
		childSetVisible(iter->first, is_copyable && is_modifiable && is_complete );
	}
}

/////////////////////////////////////////////////////////////////////
// LLFloaterCustomize

struct WearablePanelData
{
	const char* mPanelName;
	EWearableType mType;
	LLFloaterCustomize* mFloater;
} wearable_panel_data[] = {
	{ "Shape", WT_SHAPE, NULL },
	{ "Skin", WT_SKIN, NULL },
	{ "Hair", WT_HAIR, NULL },
	{ "Eyes", WT_EYES, NULL },
	{ "Shirt", WT_SHIRT, NULL },
	{ "Pants", WT_PANTS, NULL },
	{ "Shoes", WT_SHOES, NULL },
	{ "Socks", WT_SOCKS, NULL },
	{ "Jacket", WT_JACKET, NULL },
	{ "Gloves", WT_GLOVES, NULL },
	{ "Undershirt", WT_UNDERSHIRT, NULL },
	{ "Underpants", WT_UNDERPANTS, NULL },
	{ "Skirt", WT_SKIRT, NULL },
	{ "Alpha", WT_ALPHA, NULL },
	{ "Tattoo", WT_TATTOO, NULL }
};

static EWearableType get_wearable_type_from_panel_name(const std::string& name)
{
	for (S32 i=0; i<LL_ARRAY_SIZE(wearable_panel_data); i++)
	{
		if (name == wearable_panel_data[i].mPanelName)
			return wearable_panel_data[i].mType;
	}
	return WT_INVALID;
}

LLFloaterCustomize::LLFloaterCustomize()
:	LLFloater(LLSD()),
	mCurrentWearableType( WT_SHIRT ),
	mScrollingPanelList( NULL ),
	mInventoryObserver(NULL)
{
	gSavedSettings.setU32("AvatarSex", (gAgent.getAvatarObject()->getSex() == SEX_MALE) );

	mResetParams = new LLVisualParamReset();
	
	// create the observer which will watch for matching incoming inventory
	mInventoryObserver = new LLFloaterCustomizeObserver(this);
	gInventory.addObserver(mInventoryObserver);

	for (S32 i=0; i<LL_ARRAY_SIZE(wearable_panel_data); i++)
	{
		wearable_panel_data[i].mFloater = this;
		mFactoryMap[wearable_panel_data[i].mPanelName] = LLCallbackMap(createWearablePanel, (void*)(&wearable_panel_data[i]) );
	}

	LLUICtrlFactory::getInstance()->buildFloater(this, "floater_customize.xml", NULL);
}

BOOL LLFloaterCustomize::postBuild()
{
	childSetAction("Ok", LLFloaterCustomize::onBtnOk, (void*)this);
	childSetAction("make_outfit_btn", LLFloaterCustomize::onBtnMakeOutfit, (void*)this);
	
	// note: on region change this will not be re checked, should not matter on Agni as
	// 99% of the time all regions will return the same caps. In case of an erroneous setting
	// to enabled the floater will just throw an error when trying to get it's cap
	std::string url = gAgent.getRegion()->getCapability("AttachmentResources");
	if (!url.empty())
	{
		childSetAction("script_info", LLFloaterCustomize::onBtnScriptInfo, (void*)this);
	}
	else
	{
		LLButton* script_info_button = getChild<LLButton>("script_info");
		if(script_info_button)
		{
			script_info_button->setVisible(false);
		}
	}

	getChild<LLButton>("Cancel")->setClickedCallback(boost::bind(LLFloater::onClickClose, (LLFloater*)this));

	// Wearable panels
	initWearablePanels();

	// Tab container
	LLTabContainer* tab_container = getChild<LLTabContainer>("customize tab container");
	tab_container->setCommitCallback(boost::bind(&LLFloaterCustomize::onTabChanged, this, _2));
	tab_container->setValidateCallback(boost::bind(&LLFloaterCustomize::onTabPrecommit, this, _1, _2));

	// Remove underwear panels for teens
	if (gAgent.isTeen())
	{
		LLTabContainer* tab_container = getChild<LLTabContainer>("customize tab container");
		if (tab_container)
		{
			LLPanel* panel;
			panel = tab_container->getPanelByName("Undershirt");
			if (panel) tab_container->removeTabPanel(panel);
			panel = tab_container->getPanelByName("Underpants");
			if (panel) tab_container->removeTabPanel(panel);
		}
	}
	
	mScrollingPanelList = getChild<LLScrollingPanelList>("panel_list");
	
	return TRUE;
}

void LLFloaterCustomize::openFloater()
{
	LLFloater::openFloater();
	// setCurrentWearableType depends on gFloaterCustomize being defined and therefore must be called after the constructor. - Nyx
	EWearableType type = WT_SHAPE;
	for(S32 i = 0; i < WT_COUNT; i++)
	{
		if( mWearablePanelList[i]
			&& mWearablePanelList[i]->isDirty() )
		{
			type = (EWearableType) i;
		}
	}
	setCurrentWearableType(type, true);
}

////////////////////////////////////////////////////////////////////////////

void LLFloaterCustomize::setCurrentWearableType( EWearableType type, bool force_change )
{
	if( mCurrentWearableType != type  || force_change)
	{
		mCurrentWearableType = type; 

		S32 type_int = (S32)type;
		if( mWearablePanelList[type_int])
		{
			std::string panelname = mWearablePanelList[type_int]->getName();
			childShowTab("customize tab container", panelname);
			switchToDefaultSubpart();
		}
	}
}

// static
void LLFloaterCustomize::onBtnOk( void* userdata )
{
	LLFloaterCustomize* floater = (LLFloaterCustomize*) userdata;
	gAgentWearables.saveAllWearables();

	gFloaterView->sendChildToBack(floater);
	handle_reset_view();  // Calls askToSaveIfDirty
}


void LLFloaterCustomize::onBtnMakeOutfit( void* userdata )
{
	LLSidepanelAppearance* panel_appearance =
		dynamic_cast<LLSidepanelAppearance *>(LLSideTray::getInstance()->getPanel("sidepanel_appearance"));
	if (panel_appearance)
	{
		panel_appearance->onNewOutfitButtonClicked();
	}
}

void LLFloaterCustomize::onBtnScriptInfo( void* userdata )
{
	LLFloaterReg::showInstance("script_limits");
}

////////////////////////////////////////////////////////////////////////////

// static
void* LLFloaterCustomize::createWearablePanel(void* userdata)
{
	WearablePanelData* data = (WearablePanelData*)userdata;
	EWearableType type = data->mType;
	LLPanelWearable* panel;
	if ((gAgent.isTeen() && !edit_wearable_for_teens(data->mType) ))
	{
		panel = NULL;
	}
	else
	{
		panel = new LLPanelWearable( type );
	}
	data->mFloater->mWearablePanelList[type] = panel;
	return panel;
}

void LLFloaterCustomize::initWearablePanels()
{
	LLSubpart* part;
	
	/////////////////////////////////////////
	// Shape
	LLPanelWearable* panel = mWearablePanelList[ WT_SHAPE ];

	// body
	part = new LLSubpart();
	part->mTargetJoint = "mPelvis";
	part->mEditGroup = "shape_body";
	part->mTargetOffset.setVec(0.f, 0.f, 0.1f);
	part->mCameraOffset.setVec(-2.5f, 0.5f, 0.8f);
	panel->addSubpart( "Body", SUBPART_SHAPE_WHOLE, part );

	// head supparts
	part = new LLSubpart();
	part->mTargetJoint = "mHead";
	part->mEditGroup = "shape_head";
	part->mTargetOffset.setVec(0.f, 0.f, 0.05f );
	part->mCameraOffset.setVec(-0.5f, 0.05f, 0.07f );
	panel->addSubpart( "Head", SUBPART_SHAPE_HEAD, part );

	part = new LLSubpart();
	part->mTargetJoint = "mHead";
	part->mEditGroup = "shape_eyes";
	part->mTargetOffset.setVec(0.f, 0.f, 0.05f );
	part->mCameraOffset.setVec(-0.5f, 0.05f, 0.07f );
	panel->addSubpart( "Eyes", SUBPART_SHAPE_EYES, part );

	part = new LLSubpart();
	part->mTargetJoint = "mHead";
	part->mEditGroup = "shape_ears";
	part->mTargetOffset.setVec(0.f, 0.f, 0.05f );
	part->mCameraOffset.setVec(-0.5f, 0.05f, 0.07f );
	panel->addSubpart( "Ears", SUBPART_SHAPE_EARS, part );

	part = new LLSubpart();
	part->mTargetJoint = "mHead";
	part->mEditGroup = "shape_nose";
	part->mTargetOffset.setVec(0.f, 0.f, 0.05f );
	part->mCameraOffset.setVec(-0.5f, 0.05f, 0.07f );
	panel->addSubpart( "Nose", SUBPART_SHAPE_NOSE, part );


	part = new LLSubpart();
	part->mTargetJoint = "mHead";
	part->mEditGroup = "shape_mouth";
	part->mTargetOffset.setVec(0.f, 0.f, 0.05f );
	part->mCameraOffset.setVec(-0.5f, 0.05f, 0.07f );
	panel->addSubpart( "Mouth", SUBPART_SHAPE_MOUTH, part );


	part = new LLSubpart();
	part->mTargetJoint = "mHead";
	part->mEditGroup = "shape_chin";
	part->mTargetOffset.setVec(0.f, 0.f, 0.05f );
	part->mCameraOffset.setVec(-0.5f, 0.05f, 0.07f );
	panel->addSubpart( "Chin", SUBPART_SHAPE_CHIN, part );

	// torso
	part = new LLSubpart();
	part->mTargetJoint = "mTorso";
	part->mEditGroup = "shape_torso";
	part->mTargetOffset.setVec(0.f, 0.f, 0.3f);
	part->mCameraOffset.setVec(-1.f, 0.15f, 0.3f);
	panel->addSubpart( "Torso", SUBPART_SHAPE_TORSO, part );

	// legs
	part = new LLSubpart();
	part->mTargetJoint = "mPelvis";
	part->mEditGroup = "shape_legs";
	part->mTargetOffset.setVec(0.f, 0.f, -0.5f);
	part->mCameraOffset.setVec(-1.6f, 0.15f, -0.5f);
	panel->addSubpart( "Legs", SUBPART_SHAPE_LEGS, part );

	panel->childSetCommitCallback("sex radio", LLPanelWearable::onCommitSexChange, panel);

	/////////////////////////////////////////
	// Skin
	panel = mWearablePanelList[ WT_SKIN ];

	part = new LLSubpart();
	part->mTargetJoint = "mHead";
	part->mEditGroup = "skin_color";
	part->mTargetOffset.setVec(0.f, 0.f, 0.05f);
	part->mCameraOffset.setVec(-0.5f, 0.05f, 0.07f);
	panel->addSubpart( "Skin Color", SUBPART_SKIN_COLOR, part );

	part = new LLSubpart();
	part->mTargetJoint = "mHead";
	part->mEditGroup = "skin_facedetail";
	part->mTargetOffset.setVec(0.f, 0.f, 0.05f);
	part->mCameraOffset.setVec(-0.5f, 0.05f, 0.07f);
	panel->addSubpart( "Face Detail", SUBPART_SKIN_FACEDETAIL, part );

	part = new LLSubpart();
	part->mTargetJoint = "mHead";
	part->mEditGroup = "skin_makeup";
	part->mTargetOffset.setVec(0.f, 0.f, 0.05f);
	part->mCameraOffset.setVec(-0.5f, 0.05f, 0.07f);
	panel->addSubpart( "Makeup", SUBPART_SKIN_MAKEUP, part );

	part = new LLSubpart();
	part->mTargetJoint = "mPelvis";
	part->mEditGroup = "skin_bodydetail";
	part->mTargetOffset.setVec(0.f, 0.f, -0.2f);
	part->mCameraOffset.setVec(-2.5f, 0.5f, 0.5f);
	panel->addSubpart( "Body Detail", SUBPART_SKIN_BODYDETAIL, part );

	panel->addTextureDropTarget( TEX_HEAD_BODYPAINT,  "Head Tattoos", 	LLUUID::null, TRUE );
	panel->addTextureDropTarget( TEX_UPPER_BODYPAINT, "Upper Tattoos", 	LLUUID::null, TRUE );
	panel->addTextureDropTarget( TEX_LOWER_BODYPAINT, "Lower Tattoos", 	LLUUID::null, TRUE );

	/////////////////////////////////////////
	// Hair
	panel = mWearablePanelList[ WT_HAIR ];

	part = new LLSubpart();
	part->mTargetJoint = "mHead";
	part->mEditGroup = "hair_color";
	part->mTargetOffset.setVec(0.f, 0.f, 0.10f);
	part->mCameraOffset.setVec(-0.4f, 0.05f, 0.10f);
	panel->addSubpart( "Color", SUBPART_HAIR_COLOR, part );

	part = new LLSubpart();
	part->mTargetJoint = "mHead";
	part->mEditGroup = "hair_style";
	part->mTargetOffset.setVec(0.f, 0.f, 0.10f);
	part->mCameraOffset.setVec(-0.4f, 0.05f, 0.10f);
	panel->addSubpart( "Style", SUBPART_HAIR_STYLE, part );

	part = new LLSubpart();
	part->mTargetJoint = "mHead";
	part->mEditGroup = "hair_eyebrows";
	part->mTargetOffset.setVec(0.f, 0.f, 0.05f);
	part->mCameraOffset.setVec(-0.5f, 0.05f, 0.07f);
	panel->addSubpart( "Eyebrows", SUBPART_HAIR_EYEBROWS, part );

	part = new LLSubpart();
	part->mSex = SEX_MALE;
	part->mTargetJoint = "mHead";
	part->mEditGroup = "hair_facial";
	part->mTargetOffset.setVec(0.f, 0.f, 0.05f);
	part->mCameraOffset.setVec(-0.5f, 0.05f, 0.07f);
	panel->addSubpart( "Facial", SUBPART_HAIR_FACIAL, part );

	panel->addTextureDropTarget(TEX_HAIR, "Texture",
								LLUUID( gSavedSettings.getString( "UIImgDefaultHairUUID" ) ),
								FALSE );

	/////////////////////////////////////////
	// Eyes
	panel = mWearablePanelList[ WT_EYES ];

	part = new LLSubpart();
	part->mTargetJoint = "mHead";
	part->mEditGroup = "eyes";
	part->mTargetOffset.setVec(0.f, 0.f, 0.05f);
	part->mCameraOffset.setVec(-0.5f, 0.05f, 0.07f);
	panel->addSubpart( LLStringUtil::null, SUBPART_EYES, part );

	panel->addTextureDropTarget(TEX_EYES_IRIS, "Iris",
								LLUUID( gSavedSettings.getString( "UIImgDefaultEyesUUID" ) ),
								FALSE );

	/////////////////////////////////////////
	// Shirt
	panel = mWearablePanelList[ WT_SHIRT ];

	part = new LLSubpart();
	part->mTargetJoint = "mTorso";
	part->mEditGroup = "shirt";
	part->mTargetOffset.setVec(0.f, 0.f, 0.3f);
	part->mCameraOffset.setVec(-1.f, 0.15f, 0.3f);
	panel->addSubpart( LLStringUtil::null, SUBPART_SHIRT, part );

	panel->addTextureDropTarget( TEX_UPPER_SHIRT, "Fabric",
								 LLUUID( gSavedSettings.getString( "UIImgDefaultShirtUUID" ) ),
								 FALSE );

	panel->addColorSwatch( TEX_UPPER_SHIRT, "Color/Tint" );


	/////////////////////////////////////////
	// Pants
	panel = mWearablePanelList[ WT_PANTS ];

	part = new LLSubpart();
	part->mTargetJoint = "mPelvis";
	part->mEditGroup = "pants";
	part->mTargetOffset.setVec(0.f, 0.f, -0.5f);
	part->mCameraOffset.setVec(-1.6f, 0.15f, -0.5f);
	panel->addSubpart( LLStringUtil::null, SUBPART_PANTS, part );

	panel->addTextureDropTarget(TEX_LOWER_PANTS, "Fabric",
								LLUUID( gSavedSettings.getString( "UIImgDefaultPantsUUID" ) ),
								FALSE );

	panel->addColorSwatch( TEX_LOWER_PANTS, "Color/Tint" );


	/////////////////////////////////////////
	// Shoes
	panel = mWearablePanelList[ WT_SHOES ];

	if (panel)
	{
		part = new LLSubpart();
		part->mTargetJoint = "mPelvis";
		part->mEditGroup = "shoes";
		part->mTargetOffset.setVec(0.f, 0.f, -0.5f);
		part->mCameraOffset.setVec(-1.6f, 0.15f, -0.5f);
		panel->addSubpart( LLStringUtil::null, SUBPART_SHOES, part );

		panel->addTextureDropTarget( TEX_LOWER_SHOES, "Fabric",
									 LLUUID( gSavedSettings.getString( "UIImgDefaultShoesUUID" ) ),
									 FALSE );

		panel->addColorSwatch( TEX_LOWER_SHOES, "Color/Tint" );
	}


	/////////////////////////////////////////
	// Socks
	panel = mWearablePanelList[ WT_SOCKS ];

	if (panel)
	{
		part = new LLSubpart();
		part->mTargetJoint = "mPelvis";
		part->mEditGroup = "socks";
		part->mTargetOffset.setVec(0.f, 0.f, -0.5f);
		part->mCameraOffset.setVec(-1.6f, 0.15f, -0.5f);
		panel->addSubpart( LLStringUtil::null, SUBPART_SOCKS, part );

		panel->addTextureDropTarget( TEX_LOWER_SOCKS, "Fabric",
									 LLUUID( gSavedSettings.getString( "UIImgDefaultSocksUUID" ) ),
									 FALSE );

		panel->addColorSwatch( TEX_LOWER_SOCKS, "Color/Tint" );
	}

	/////////////////////////////////////////
	// Jacket
	panel = mWearablePanelList[ WT_JACKET ];

	if (panel)
	{
		part = new LLSubpart();
		part->mTargetJoint = "mTorso";
		part->mEditGroup = "jacket";
		part->mTargetOffset.setVec(0.f, 0.f, 0.f);
		part->mCameraOffset.setVec(-2.f, 0.1f, 0.3f);
		panel->addSubpart( LLStringUtil::null, SUBPART_JACKET, part );

		panel->addTextureDropTarget( TEX_UPPER_JACKET, "Upper Fabric",
									 LLUUID( gSavedSettings.getString( "UIImgDefaultJacketUUID" ) ),
									 FALSE );
		panel->addTextureDropTarget( TEX_LOWER_JACKET, "Lower Fabric",
									 LLUUID( gSavedSettings.getString( "UIImgDefaultJacketUUID" ) ),
									 FALSE );

		panel->addColorSwatch( TEX_UPPER_JACKET, "Color/Tint" );
	}

	/////////////////////////////////////////
	// Skirt
	panel = mWearablePanelList[ WT_SKIRT ];

	if (panel)
	{
		part = new LLSubpart();
		part->mTargetJoint = "mPelvis";
		part->mEditGroup = "skirt";
		part->mTargetOffset.setVec(0.f, 0.f, -0.5f);
		part->mCameraOffset.setVec(-1.6f, 0.15f, -0.5f);
		panel->addSubpart( LLStringUtil::null, SUBPART_SKIRT, part );

		panel->addTextureDropTarget( TEX_SKIRT,  "Fabric",
									 LLUUID( gSavedSettings.getString( "UIImgDefaultSkirtUUID" ) ),
									 FALSE );

		panel->addColorSwatch( TEX_SKIRT, "Color/Tint" );
	}


	/////////////////////////////////////////
	// Gloves
	panel = mWearablePanelList[ WT_GLOVES ];

	if (panel)
	{
		part = new LLSubpart();
		part->mTargetJoint = "mTorso";
		part->mEditGroup = "gloves";
		part->mTargetOffset.setVec(0.f, 0.f, 0.f);
		part->mCameraOffset.setVec(-1.f, 0.15f, 0.f);
		panel->addSubpart( LLStringUtil::null, SUBPART_GLOVES, part );

		panel->addTextureDropTarget( TEX_UPPER_GLOVES,  "Fabric",
									 LLUUID( gSavedSettings.getString( "UIImgDefaultGlovesUUID" ) ),
									 FALSE );

		panel->addColorSwatch( TEX_UPPER_GLOVES, "Color/Tint" );
	}


	/////////////////////////////////////////
	// Undershirt
	panel = mWearablePanelList[ WT_UNDERSHIRT ];

	if (panel)
	{
		part = new LLSubpart();
		part->mTargetJoint = "mTorso";
		part->mEditGroup = "undershirt";
		part->mTargetOffset.setVec(0.f, 0.f, 0.3f);
		part->mCameraOffset.setVec(-1.f, 0.15f, 0.3f);
		panel->addSubpart( LLStringUtil::null, SUBPART_UNDERSHIRT, part );

		panel->addTextureDropTarget( TEX_UPPER_UNDERSHIRT,  "Fabric",
									 LLUUID( gSavedSettings.getString( "UIImgDefaultUnderwearUUID" ) ),
									 FALSE );

		panel->addColorSwatch( TEX_UPPER_UNDERSHIRT, "Color/Tint" );
	}

	/////////////////////////////////////////
	// Underpants
	panel = mWearablePanelList[ WT_UNDERPANTS ];

	if (panel)
	{
		part = new LLSubpart();
		part->mTargetJoint = "mPelvis";
		part->mEditGroup = "underpants";
		part->mTargetOffset.setVec(0.f, 0.f, -0.5f);
		part->mCameraOffset.setVec(-1.6f, 0.15f, -0.5f);
		panel->addSubpart( LLStringUtil::null, SUBPART_UNDERPANTS, part );

		panel->addTextureDropTarget( TEX_LOWER_UNDERPANTS, "Fabric",
									 LLUUID( gSavedSettings.getString( "UIImgDefaultUnderwearUUID" ) ),
									 FALSE );

		panel->addColorSwatch( TEX_LOWER_UNDERPANTS, "Color/Tint" );
	}

	/////////////////////////////////////////
	// Alpha
	panel = mWearablePanelList[ WT_ALPHA ];

	if (panel)
	{
		part = new LLSubpart();
		part->mTargetJoint = "mPelvis";
		part->mEditGroup = "alpha";
		part->mTargetOffset.setVec(0.f, 0.f, 0.1f);
		part->mCameraOffset.setVec(-2.5f, 0.5f, 0.8f);
		panel->addSubpart( LLStringUtil::null, SUBPART_ALPHA, part );

		panel->addTextureDropTarget( LLVOAvatarDefines::TEX_LOWER_ALPHA, "Lower Alpha",
									 LLUUID( gSavedSettings.getString( "UIImgDefaultAlphaUUID" ) ),
									 TRUE );
		panel->addTextureDropTarget( LLVOAvatarDefines::TEX_UPPER_ALPHA, "Upper Alpha",
									 LLUUID( gSavedSettings.getString( "UIImgDefaultAlphaUUID" ) ),
									 TRUE );
		panel->addTextureDropTarget( LLVOAvatarDefines::TEX_HEAD_ALPHA, "Head Alpha",
									 LLUUID( gSavedSettings.getString( "UIImgDefaultAlphaUUID" ) ),
									 TRUE );
		panel->addTextureDropTarget( LLVOAvatarDefines::TEX_EYES_ALPHA, "Eye Alpha",
									 LLUUID( gSavedSettings.getString( "UIImgDefaultAlphaUUID" ) ),
									 TRUE );
		panel->addTextureDropTarget( LLVOAvatarDefines::TEX_HAIR_ALPHA, "Hair Alpha",
									 LLUUID( gSavedSettings.getString( "UIImgDefaultAlphaUUID" ) ),
									 TRUE );

		panel->addInvisibilityCheckbox( LLVOAvatarDefines::TEX_LOWER_ALPHA, "lower alpha texture invisible" );
		panel->addInvisibilityCheckbox( LLVOAvatarDefines::TEX_UPPER_ALPHA, "upper alpha texture invisible" );
		panel->addInvisibilityCheckbox( LLVOAvatarDefines::TEX_HEAD_ALPHA, "head alpha texture invisible" );
		panel->addInvisibilityCheckbox( LLVOAvatarDefines::TEX_EYES_ALPHA, "eye alpha texture invisible" );
		panel->addInvisibilityCheckbox( LLVOAvatarDefines::TEX_HAIR_ALPHA, "hair alpha texture invisible" );
	}

	/////////////////////////////////////////
	// Tattoo
	panel = mWearablePanelList[ WT_TATTOO ];

	if (panel)
	{
		part = new LLSubpart();
		part->mTargetJoint = "mPelvis";
		part->mEditGroup = "tattoo";
		part->mTargetOffset.setVec(0.f, 0.f, 0.1f);
		part->mCameraOffset.setVec(-2.5f, 0.5f, 0.8f);
		panel->addSubpart( LLStringUtil::null, SUBPART_TATTOO, part );

		panel->addTextureDropTarget( LLVOAvatarDefines::TEX_LOWER_TATTOO, "Lower Tattoo",
									 LLUUID::null,
									 TRUE );
		panel->addTextureDropTarget( LLVOAvatarDefines::TEX_UPPER_TATTOO, "Upper Tattoo",
									 LLUUID::null,
									 TRUE );
		panel->addTextureDropTarget( LLVOAvatarDefines::TEX_HEAD_TATTOO, "Head Tattoo",
									 LLUUID::null,
									 TRUE );
	}
}

////////////////////////////////////////////////////////////////////////////

LLFloaterCustomize::~LLFloaterCustomize()
{
	// Close these panels now, since they have elements that depend on parents,
	// which would cause a crash under the normal order of deletion.
	for (U8 i=0; i < WT_COUNT; i++)
	{
		LLPanelWearable* wearable_panel = mWearablePanelList[i];
		if (wearable_panel)
		{
			wearable_panel->onParentFloaterClosed();
		}
	}

	llinfos << "Destroying LLFloaterCustomize" << llendl;
	gInventory.removeObserver(mInventoryObserver);
	delete mInventoryObserver;

}

void LLFloaterCustomize::switchToDefaultSubpart()
{
	getCurrentWearablePanel()->switchToDefaultSubpart();
}

void LLFloaterCustomize::draw()
{
	if( isMinimized() )
	{
		LLFloater::draw();
		return;
	}

	// only do this if we are in the customize avatar mode
	// and not transitioning into or out of it
	// *TODO: This is a sort of expensive call, which only needs
	// to be called when the tabs change or an inventory item
	// arrives. Figure out some way to avoid this if possible.
	updateInventoryUI();

	LLScrollingPanelParam::sUpdateDelayFrames = 0;
	
	LLFloater::draw();
}

BOOL LLFloaterCustomize::isDirty() const
{
	for(S32 i = 0; i < WT_COUNT; i++)
	{
		if( mWearablePanelList[i]
			&& mWearablePanelList[i]->isDirty() )
		{
			return TRUE;
		}
	}
	return FALSE;
}

bool LLFloaterCustomize::onTabPrecommit(LLUICtrl* ctrl, const LLSD& data)
{
	std::string panel_name = data.asString();	
	EWearableType type = get_wearable_type_from_panel_name(panel_name);
	if (type != WT_INVALID && getCurrentWearableType() != type)
	{
		// Do a redundant isDirty() call to avoid infinite recursion
		//  i.e. if not dirty, return true and do a normal commit
		if( isDirty())
{
			askToSaveIfDirty(boost::bind(&LLFloaterCustomize::onCommitChangeTab, this, _1, ctrl, panel_name));
			return false;
		}
		else
	{
			return true;
		}
	}
	else
	{
		return true;
	}
}


void LLFloaterCustomize::onTabChanged( const LLSD& data )
{
	std::string panel_name = data.asString();	
	EWearableType type = get_wearable_type_from_panel_name(panel_name);
	if (type != WT_INVALID)
		setCurrentWearableType( type );
}

//virtual
BOOL LLFloaterCustomize::canClose()
{
	// *TODO: Hack! Fix this!
	
	// since this window is potentially staying open, push to back to let next window take focus
	gFloaterView->sendChildToBack(this);
	handle_reset_view();  // Calls askToSaveIfDirty
	return FALSE; // LLFloaterCustomize is never closed, just destroyed
}

void LLFloaterCustomize::onCommitChangeTab(BOOL proceed, LLUICtrl* ctrl, const std::string& selected_tab)
{
	if (!proceed)
	{
		return;
	}

	LLTabContainer* tab_container = dynamic_cast<LLTabContainer*>(ctrl);
	if (tab_container)
	{
		// Note: This will trigger the precommit / commit callbacks again,
		//  make sure this will succeed (i.e. never produce an infinite loop)
		tab_container->selectTabByName(selected_tab);
	}
}



////////////////////////////////////////////////////////////////////////////

void LLFloaterCustomize::clearScrollingPanelList()
{
	if( mScrollingPanelList )
	{
		mScrollingPanelList->clearPanels();
	}
}

void LLFloaterCustomize::generateVisualParamHints(LLViewerJointMesh* joint_mesh, LLFloaterCustomize::param_map& params, LLPanelWearable* panel)
{
	// sorted_params is sorted according to magnitude of effect from
	// least to greatest.  Adding to the front of the child list
	// reverses that order.
	if( mScrollingPanelList )
	{
		mScrollingPanelList->clearPanels();
		param_map::iterator end = params.end();
		for(param_map::iterator it = params.begin(); it != end; ++it)
		{
			LLPanel::Params p;
			p.name("LLScrollingPanelParam");
			p.rect(LLRect(0, LLScrollingPanelParam::PARAM_PANEL_HEIGHT, LLScrollingPanelParam::PARAM_PANEL_WIDTH, 0 ));
			LLScrollingPanelParam* panel_param = new LLScrollingPanelParam( p, joint_mesh, (*it).second.second, (*it).second.first, panel->getWearable());
			mScrollingPanelList->addPanel( panel_param );
		}
	}
}

LLPanelWearable* LLFloaterCustomize::getCurrentWearablePanel() 
{ 
	llassert(mCurrentWearableType >= 0 && mCurrentWearableType < WT_COUNT);
	if (mCurrentWearableType < 0 || mCurrentWearableType >= WT_COUNT)
	{
		llwarns << "Invalid wearable type: " << mCurrentWearableType << llendl;
		return NULL;
	}
	return mWearablePanelList[ mCurrentWearableType ]; 
}


void LLFloaterCustomize::setWearable(EWearableType type, LLWearable* wearable, U32 perm_mask, BOOL is_complete)
{
	llassert( type < WT_COUNT );
	gSavedSettings.setU32("AvatarSex", (gAgent.getAvatarObject()->getSex() == SEX_MALE) );
	
	LLPanelWearable* panel = mWearablePanelList[ type ];
	if( panel )
	{
		panel->setWearable(wearable, perm_mask, is_complete);
		updateScrollingPanelList((perm_mask & PERM_MODIFY) ? is_complete : FALSE);
	}
}

void LLFloaterCustomize::setWearable(EWearableType type, U32 index)
{
	LLWearable *wearable = gAgentWearables.getWearable(type,index);
	LLViewerInventoryItem* item;
	// MULTI_WEARABLE:
	item = (LLViewerInventoryItem*)gInventory.getItem(gAgentWearables.getWearableItemID(type,index));
	U32 perm_mask = PERM_NONE;
	BOOL is_complete = FALSE;
	if(item)
	{
		perm_mask = item->getPermissions().getMaskOwner();
		is_complete = item->isComplete();
		if(!is_complete)
		{
			item->fetchFromServer();
		}
	}
	setWearable(type,wearable,perm_mask,is_complete);
}

void LLFloaterCustomize::updateScrollingPanelList(BOOL allow_modify)
{
	if( mScrollingPanelList )
	{
		LLScrollingPanelParam::sUpdateDelayFrames = 0;
		mScrollingPanelList->updatePanels(allow_modify );
	}
}


void LLFloaterCustomize::askToSaveIfDirty( next_step_callback_t next_step_callback )
{
	if( isDirty())
	{
		// Ask if user wants to save, then continue to next step afterwards
		mNextStepAfterSaveCallback = next_step_callback;

		// Bring up view-modal dialog: Save changes? Yes, No, Cancel
		LLNotificationsUtil::add("SaveClothingBodyChanges", LLSD(), LLSD(),
			boost::bind(&LLFloaterCustomize::onSaveDialog, this, _1, _2));
	}
	else
	{
		next_step_callback( TRUE );
	}
}


bool LLFloaterCustomize::onSaveDialog(const LLSD& notification, const LLSD& response )
{
	S32 option = LLNotificationsUtil::getSelectedOption(notification, response);

	BOOL proceed = FALSE;
	EWearableType cur = getCurrentWearableType();

	switch( option )
	{
	case 0:  // "Save"
		// MULTI_WEARABLE:
		gAgentWearables.saveWearable( cur, 0 );
		setWearable( cur, 0 );
		getCurrentWearablePanel()->reset();
		proceed = TRUE;
		break;

	case 1:  // "Don't Save"
		{
			// MULTI_WEARABLE:
			gAgentWearables.revertWearable( cur, 0 );
			proceed = TRUE;
		}
		break;

	case 2: // "Cancel"
		break;

	default:
		llassert(0);
		break;
	}

	if( mNextStepAfterSaveCallback )
	{
		mNextStepAfterSaveCallback( proceed );
	}
	return false;
}

// fetch observer
class LLCurrentlyWorn : public LLInventoryFetchObserver
{
public:
	LLCurrentlyWorn() {}
	~LLCurrentlyWorn() {}
	virtual void done() { /* no operation necessary */}
};

void LLFloaterCustomize::fetchInventory()
{
	// Fetch currently worn items
	LLInventoryFetchObserver::item_ref_t ids;
	LLUUID item_id;
	for(S32 type = (S32)WT_SHAPE; type < (S32)WT_COUNT; ++type)
	{
		// MULTI_WEARABLE:
		item_id = gAgentWearables.getWearableItemID((EWearableType)type,0);
		if(item_id.notNull())
		{
			ids.push_back(item_id);
		}
	}

	// Fire & forget. The mInventoryObserver will catch inventory
	// updates and correct the UI as necessary.
	LLCurrentlyWorn worn;
	worn.fetchItems(ids);
}

void LLFloaterCustomize::updateInventoryUI()
{
	BOOL all_complete = TRUE;
	BOOL is_complete = FALSE;
	U32 perm_mask = 0x0;
	LLPanelWearable* panel = NULL;
	LLViewerInventoryItem* item = NULL;
	for(S32 i = 0; i < WT_COUNT; ++i)
	{
		item = NULL;
		panel = mWearablePanelList[i];
		if(panel)
		{
			// MULTI_WEARABLE:
			item = (LLViewerInventoryItem*)gAgentWearables.getWearableInventoryItem(panel->getType(),0);
		}
		if(item)
		{
			is_complete = item->isComplete();
			if(!is_complete)
			{
				all_complete = FALSE;
			}
			perm_mask = item->getPermissions().getMaskOwner();
		}
		else
		{
			is_complete = false;
			perm_mask = 0x0;
		}
		if(i == mCurrentWearableType)
		{
			if(panel)
			{
	    		panel->setUIPermissions(perm_mask, is_complete);
			}
			BOOL is_vis = panel && item && is_complete && (perm_mask & PERM_MODIFY);
			childSetVisible("panel_container", is_vis);
		}
	}
	childSetEnabled("Make Outfit", all_complete);
}

void LLFloaterCustomize::updateScrollingPanelUI()
{
	LLPanelWearable* panel = mWearablePanelList[mCurrentWearableType];
	if(panel && (panel->getWearable() != NULL) && (panel->getWearable()->getItemID().notNull()))
	{
		LLViewerInventoryItem* item = (LLViewerInventoryItem*)gInventory.getItem(panel->getWearable()->getItemID());
		if(item)
		{
			U32 perm_mask = item->getPermissions().getMaskOwner();
			BOOL is_complete = item->isComplete();
			updateScrollingPanelList((perm_mask & PERM_MODIFY) ? is_complete : FALSE);
		}
	}
}

