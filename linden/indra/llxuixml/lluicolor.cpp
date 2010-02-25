/** 
 * @file lluicolor.cpp
 * @brief brief LLUIColor class implementation file
 *
 * $LicenseInfo:firstyear=2009&license=viewergpl$
 * 
 * Copyright (c) 2009-2010, Linden Research, Inc.
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

#include "linden_common.h"

#include "lluicolor.h"

LLUIColor::LLUIColor()
	:mColorPtr(NULL)
{
}


LLUIColor::LLUIColor(const LLColor4& color)
:	mColor(color), 
	mColorPtr(NULL)
{
}

LLUIColor::LLUIColor(const LLUIColor* color)
:	mColorPtr(color)
{
}

void LLUIColor::set(const LLColor4& color)
{
	mColor = color;
	mColorPtr = NULL;
}

void LLUIColor::set(const LLUIColor* color)
{
	mColorPtr = color;
}

const LLColor4& LLUIColor::get() const
{
	return (mColorPtr == NULL ? mColor : mColorPtr->get());
}

LLUIColor::operator const LLColor4& () const
{
	return get();
}

const LLColor4& LLUIColor::operator()() const
{
	return get();
}

bool LLUIColor::isReference() const
{
	return mColorPtr != NULL;
}

namespace LLInitParam
{
	// used to detect equivalence with default values on export
	bool ParamCompare<LLUIColor, false>::equals(const LLUIColor &a, const LLUIColor &b)
	{
		// do not detect value equivalence, treat pointers to colors as distinct from color values
		return (a.mColorPtr == NULL && b.mColorPtr == NULL ? a.mColor == b.mColor : a.mColorPtr == b.mColorPtr);
	}
}
