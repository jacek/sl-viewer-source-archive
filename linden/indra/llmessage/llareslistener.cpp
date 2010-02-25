/**
 * @file   llareslistener.cpp
 * @author Nat Goodspeed
 * @date   2009-03-18
 * @brief  Implementation for llareslistener.
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

// Precompiled header
#include "linden_common.h"
// associated header
#include "llareslistener.h"
// STL headers
// std headers
// external library headers
// other Linden headers
#include "llares.h"
#include "llerror.h"
#include "llevents.h"
#include "llsdutil.h"

LLAresListener::LLAresListener(LLAres* llares):
    LLEventAPI("LLAres",
               "LLAres listener to request DNS operations"),
    mAres(llares)
{
    // add() every method we want to be able to invoke via this event API.
    // Optional last parameter validates expected LLSD request structure.
    add("rewriteURI",
        "Given [\"uri\"], return on [\"reply\"] an array of alternative URIs.\n"
        "On failure, returns an array containing only the original URI, so\n"
        "failure case can be processed like success case.",
        &LLAresListener::rewriteURI,
        LLSD().with("uri", LLSD()).with("reply", LLSD()));
}

/// This UriRewriteResponder subclass packages returned URIs as an LLSD
/// array to send back to the requester.
class UriRewriteResponder: public LLAres::UriRewriteResponder
{
public:
    /**
     * Specify the request, containing the event pump name on which to send
     * the reply.
     */
    UriRewriteResponder(const LLSD& request):
        mReqID(request),
        mPumpName(request["reply"])
    {}

    /// Called by base class with results. This is called in both the
    /// success and error cases. On error, the calling logic passes the
    /// original URI.
    virtual void rewriteResult(const std::vector<std::string>& uris)
    {
        LLSD result;
        for (std::vector<std::string>::const_iterator ui(uris.begin()), uend(uris.end());
             ui != uend; ++ui)
        {
            result.append(*ui);
        }
        // This call knows enough to avoid trying to insert a map key into an
        // LLSD array. It's there so that if, for any reason, we ever decide
        // to change the response from array to map, it will Just Start Working.
        mReqID.stamp(result);
        LLEventPumps::instance().obtain(mPumpName).post(result);
    }

private:
    LLReqID mReqID;
    const std::string mPumpName;
};

void LLAresListener::rewriteURI(const LLSD& data)
{
    mAres->rewriteURI(data["uri"], new UriRewriteResponder(data));
}
