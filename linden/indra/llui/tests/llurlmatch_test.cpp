/**
 * @file llurlmatch_test.cpp
 * @author Martin Reddy
 * @brief Unit tests for LLUrlMatch
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

#include "../llurlmatch.h"
#include "lltut.h"

// link seam
LLUIColor::LLUIColor()
	: mColorPtr(NULL)
{}

namespace tut
{
	struct LLUrlMatchData
	{
	};

	typedef test_group<LLUrlMatchData> factory;
	typedef factory::object object;
}

namespace
{
	tut::factory tf("LLUrlMatch");
}

namespace tut
{
	template<> template<>
	void object::test<1>()
	{
		//
		// test the empty() method
		//
		LLUrlMatch match;
		ensure("empty()", match.empty());

		match.setValues(0, 1, "http://secondlife.com", "Second Life", "", "", LLUIColor(), "", "", false);
		ensure("! empty()", ! match.empty());
	}

	template<> template<>
	void object::test<2>()
	{
		//
		// test the getStart() method
		//
		LLUrlMatch match;
		ensure_equals("getStart() == 0", match.getStart(), 0);

		match.setValues(10, 20, "", "", "", "", LLUIColor(), "", "", false);
		ensure_equals("getStart() == 10", match.getStart(), 10);
	}

	template<> template<>
	void object::test<3>()
	{
		//
		// test the getEnd() method
		//
		LLUrlMatch match;
		ensure_equals("getEnd() == 0", match.getEnd(), 0);

		match.setValues(10, 20, "", "", "", "", LLUIColor(), "", "", false);
		ensure_equals("getEnd() == 20", match.getEnd(), 20);
	}

	template<> template<>
	void object::test<4>()
	{
		//
		// test the getUrl() method
		//
		LLUrlMatch match;
		ensure_equals("getUrl() == ''", match.getUrl(), "");

		match.setValues(10, 20, "http://slurl.com/", "", "", "", LLUIColor(), "", "", false);
		ensure_equals("getUrl() == 'http://slurl.com/'", match.getUrl(), "http://slurl.com/");

		match.setValues(10, 20, "", "", "", "", LLUIColor(), "", "", false);
		ensure_equals("getUrl() == '' (2)", match.getUrl(), "");
	}

	template<> template<>
	void object::test<5>()
	{
		//
		// test the getLabel() method
		//
		LLUrlMatch match;
		ensure_equals("getLabel() == ''", match.getLabel(), "");

		match.setValues(10, 20, "", "Label", "", "", LLUIColor(), "", "", false);
		ensure_equals("getLabel() == 'Label'", match.getLabel(), "Label");

		match.setValues(10, 20, "", "", "", "", LLUIColor(), "", "", false);
		ensure_equals("getLabel() == '' (2)", match.getLabel(), "");
	}

	template<> template<>
	void object::test<6>()
	{
		//
		// test the getTooltip() method
		//
		LLUrlMatch match;
		ensure_equals("getTooltip() == ''", match.getTooltip(), "");

		match.setValues(10, 20, "", "", "Info", "", LLUIColor(), "", "", false);
		ensure_equals("getTooltip() == 'Info'", match.getTooltip(), "Info");

		match.setValues(10, 20, "", "", "", "", LLUIColor(), "", "", false);
		ensure_equals("getTooltip() == '' (2)", match.getTooltip(), "");
	}

	template<> template<>
	void object::test<7>()
	{
		//
		// test the getIcon() method
		//
		LLUrlMatch match;
		ensure_equals("getIcon() == ''", match.getIcon(), "");

		match.setValues(10, 20, "", "", "", "Icon", LLUIColor(), "", "", false);
		ensure_equals("getIcon() == 'Icon'", match.getIcon(), "Icon");

		match.setValues(10, 20, "", "", "", "", LLUIColor(), "", "", false);
		ensure_equals("getIcon() == '' (2)", match.getIcon(), "");
	}

	template<> template<>
	void object::test<8>()
	{
		//
		// test the getMenuName() method
		//
		LLUrlMatch match;
		ensure("getMenuName() empty", match.getMenuName().empty());

		match.setValues(10, 20, "", "", "", "Icon", LLUIColor(), "xui_file.xml", "", false);
		ensure_equals("getMenuName() == \"xui_file.xml\"", match.getMenuName(), "xui_file.xml");

		match.setValues(10, 20, "", "", "", "", LLUIColor(), "", "", false);
		ensure("getMenuName() empty (2)", match.getMenuName().empty());
	}

	template<> template<>
	void object::test<9>()
	{
		//
		// test the getLocation() method
		//
		LLUrlMatch match;
		ensure("getLocation() empty", match.getLocation().empty());

		match.setValues(10, 20, "", "", "", "Icon", LLUIColor(), "xui_file.xml", "Paris", false);
		ensure_equals("getLocation() == \"Paris\"", match.getLocation(), "Paris");

		match.setValues(10, 20, "", "", "", "", LLUIColor(), "", "", false);
		ensure("getLocation() empty (2)", match.getLocation().empty());
	}
}
