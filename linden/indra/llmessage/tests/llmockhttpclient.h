/** 
 * @file 
 * @brief 
 *
 * $LicenseInfo:firstyear=2008&license=viewergpl$
 * 
 * Copyright (c) 2008-2010, Linden Research, Inc.
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

/* Macro Definitions */
#ifndef LL_LLMOCKHTTPCLIENT_H
#define LL_LLMOCKHTTPCLIENT_H

#include "linden_common.h"
#include "llhttpclientinterface.h"

#include <gmock/gmock.h>

class LLMockHTTPClient : public LLHTTPClientInterface
{
public:
  MOCK_METHOD2(get, void(const std::string& url, LLCurl::ResponderPtr responder));
  MOCK_METHOD3(get, void(const std::string& url, LLCurl::ResponderPtr responder, const LLSD& headers));
  MOCK_METHOD3(put, void(const std::string& url, const LLSD& body, LLCurl::ResponderPtr responder));
};

// A helper to match responder types
template<typename T>
struct ResponderType
{
	bool operator()(LLCurl::ResponderPtr ptr) const
	{
		T* p = dynamic_cast<T*>(ptr.get());
		return p != NULL;
	}
};

inline bool operator==(const LLSD& l, const LLSD& r)
{
	std::ostringstream ls, rs;
	ls << l;
	rs << r;
	return ls.str() == rs.str();

}


#endif //LL_LLMOCKHTTPCLIENT_H

