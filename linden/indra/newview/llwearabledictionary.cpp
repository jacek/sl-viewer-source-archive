/** 
 * @file llwearableDictionary.cpp
 * @brief LLWearableDictionary class implementation
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
#include "llwearabledictionary.h"
#include "lltrans.h"

LLWearableDictionary::LLWearableDictionary()
{
}

LLWearableDictionary::~LLWearableDictionary()
{
}

LLWearableDictionary::Wearables::Wearables()
{
	addEntry(WT_SHAPE,        new WearableEntry("shape",       LLAssetType::AT_BODYPART));
	addEntry(WT_SKIN,         new WearableEntry("skin",        LLAssetType::AT_BODYPART));
	addEntry(WT_HAIR,         new WearableEntry("hair",        LLAssetType::AT_BODYPART));
	addEntry(WT_EYES,         new WearableEntry("eyes",        LLAssetType::AT_BODYPART));
	addEntry(WT_SHIRT,        new WearableEntry("shirt",       LLAssetType::AT_CLOTHING));
	addEntry(WT_PANTS,        new WearableEntry("pants",       LLAssetType::AT_CLOTHING));
	addEntry(WT_SHOES,        new WearableEntry("shoes",       LLAssetType::AT_CLOTHING));
	addEntry(WT_SOCKS,        new WearableEntry("socks",       LLAssetType::AT_CLOTHING));
	addEntry(WT_JACKET,       new WearableEntry("jacket",      LLAssetType::AT_CLOTHING));
	addEntry(WT_GLOVES,       new WearableEntry("gloves",      LLAssetType::AT_CLOTHING));
	addEntry(WT_UNDERSHIRT,   new WearableEntry("undershirt",  LLAssetType::AT_CLOTHING));
	addEntry(WT_UNDERPANTS,   new WearableEntry("underpants",  LLAssetType::AT_CLOTHING));
	addEntry(WT_SKIRT,        new WearableEntry("skirt",       LLAssetType::AT_CLOTHING));
	addEntry(WT_ALPHA,        new WearableEntry("alpha",       LLAssetType::AT_CLOTHING));
	addEntry(WT_TATTOO,       new WearableEntry("tattoo",      LLAssetType::AT_CLOTHING));
	addEntry(WT_INVALID,      new WearableEntry("invalid",     LLAssetType::AT_NONE));
	addEntry(WT_COUNT,        NULL);
}

LLWearableDictionary::WearableEntry::WearableEntry(const std::string &name,
												   LLAssetType::EType assetType) :
	LLDictionaryEntry(name),
	mAssetType(assetType),
	mLabel(LLTrans::getString(name))
{
}

// static
EWearableType LLWearableDictionary::typeNameToType(const std::string& type_name)
{
	const EWearableType wearable = getInstance()->getWearableEntry(type_name);
	return wearable;
}

// static 
const std::string& LLWearableDictionary::getTypeName(EWearableType type)
{ 
	return getInstance()->getWearableEntry(type)->mName;
}

// static 
const std::string& LLWearableDictionary::getTypeLabel(EWearableType type)
{ 
	return getInstance()->getWearableEntry(type)->mLabel;
}

// static 
LLAssetType::EType LLWearableDictionary::getAssetType(EWearableType type)
{
	return getInstance()->getWearableEntry(type)->mAssetType;
}
