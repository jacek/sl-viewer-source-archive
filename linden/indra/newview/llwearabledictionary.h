/** 
 * @file llwearableDictionary.h
 * @brief LLWearableDictionary class header file
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

#ifndef LL_LLWEARABLEDICTIONARY_H
#define LL_LLWEARABLEDICTIONARY_H

/*
#include "lluuid.h"
#include "llstring.h"
#include "llpermissions.h"
#include "llsaleinfo.h"
#include "llassetstorage.h"
*/
#include "llassettype.h"
#include "lldictionary.h"
#include "llsingleton.h"

//--------------------------------------------------------------------
// Enums
//--------------------------------------------------------------------
enum EWearableType
{
	WT_SHAPE	  = 0,
	WT_SKIN		  = 1,
	WT_HAIR		  = 2,
	WT_EYES		  = 3,
	WT_SHIRT	  = 4,
	WT_PANTS	  = 5,
	WT_SHOES	  = 6,
	WT_SOCKS	  = 7,
	WT_JACKET	  = 8,
	WT_GLOVES	  = 9,
	WT_UNDERSHIRT = 10,
	WT_UNDERPANTS = 11,
	WT_SKIRT	  = 12,
	WT_ALPHA	  = 13,
	WT_TATTOO	  = 14,
	WT_COUNT	  = 15,
	WT_INVALID	  = 255
};

class LLWearableDictionary : public LLSingleton<LLWearableDictionary>
{
	//--------------------------------------------------------------------
	// Constructors and Destructors
	//--------------------------------------------------------------------
public:
	LLWearableDictionary();
	virtual ~LLWearableDictionary();

	//--------------------------------------------------------------------
	// Wearables
	//--------------------------------------------------------------------
	struct WearableEntry : public LLDictionaryEntry
	{
		WearableEntry(const std::string &name,
					  LLAssetType::EType assetType);
		const LLAssetType::EType mAssetType;
		const std::string mLabel;
	};
	struct Wearables : public LLDictionary<EWearableType, WearableEntry>
	{
		Wearables();
	} mWearables;
	const WearableEntry *getWearableEntry(EWearableType index) const { return mWearables.lookup(index); }
 	const EWearableType getWearableEntry(const std::string &name) const { return mWearables.lookup(name); }
	const Wearables &getWearableEntries() const { return mWearables; }
	
	// Convenience functions
	static const std::string& getTypeName(EWearableType type);
	static const std::string& getTypeLabel(EWearableType type);
	static LLAssetType::EType getAssetType(EWearableType type);
	static EWearableType typeNameToType(const std::string& type_name);
};

#endif  // LL_LLWEARABLEDICTIONARY_H
