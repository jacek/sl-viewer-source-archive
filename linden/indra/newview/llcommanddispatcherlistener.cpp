/**
 * @file   llcommanddispatcherlistener.cpp
 * @author Nat Goodspeed
 * @date   2009-12-10
 * @brief  Implementation for llcommanddispatcherlistener.
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
#include "llviewerprecompiledheaders.h"
// associated header
#include "llcommanddispatcherlistener.h"
// STL headers
// std headers
// external library headers
// other Linden headers
#include "llcommandhandler.h"

LLCommandDispatcherListener::LLCommandDispatcherListener(/* LLCommandDispatcher* instance */):
    LLEventAPI("LLCommandDispatcher", "Access to LLCommandHandler commands") /* ,
    mDispatcher(instance) */
{
    add("dispatch",
        "Execute a command registered as an LLCommandHandler,\n"
        "passing any required parameters:\n"
        "[\"cmd\"] string command name\n"
        "[\"params\"] array of parameters, as if from components of URL path\n"
        "[\"query\"] map of parameters, as if from ?key1=val&key2=val\n"
        "[\"trusted\"] boolean indicating trusted browser [default true]",
        &LLCommandDispatcherListener::dispatch);
    add("enumerate",
        "Post to [\"reply\"] a map of registered LLCommandHandler instances, containing\n"
        "name key and (e.g.) untrusted flag",
        &LLCommandDispatcherListener::enumerate,
        LLSD().with("reply", LLSD()));
}

void LLCommandDispatcherListener::dispatch(const LLSD& params) const
{
    // For most purposes, we expect callers to want to be trusted.
    bool trusted_browser = true;
    if (params.has("trusted"))
    {
        // But for testing, allow a caller to specify untrusted.
        trusted_browser = params["trusted"].asBoolean();
    }
    LLCommandDispatcher::dispatch(params["cmd"], params["params"], params["query"], NULL,
                                  trusted_browser);
}

void LLCommandDispatcherListener::enumerate(const LLSD& params) const
{
    LLReqID reqID(params);
    LLSD response(LLCommandDispatcher::enumerate());
    reqID.stamp(response);
    LLEventPumps::instance().obtain(params["reply"]).post(response);
}
