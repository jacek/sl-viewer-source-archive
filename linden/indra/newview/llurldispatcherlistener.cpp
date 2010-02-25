/**
 * @file   llurldispatcherlistener.cpp
 * @author Nat Goodspeed
 * @date   2009-12-10
 * @brief  Implementation for llurldispatcherlistener.
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
#include "llurldispatcherlistener.h"
// STL headers
// std headers
// external library headers
// other Linden headers
#include "llurldispatcher.h"

LLURLDispatcherListener::LLURLDispatcherListener(/* LLURLDispatcher* instance */):
    LLEventAPI("LLURLDispatcher", "Internal URL handling") /* ,
    mDispatcher(instance) */
{
    add("dispatch",
        "At startup time or on clicks in internal web browsers,\n"
        "teleport, open map, or run requested command.\n"
        "[\"url\"] string url to dispatch\n"
        "[\"trusted\"] boolean indicating trusted browser [default true]",
        &LLURLDispatcherListener::dispatch);
    add("dispatchRightClick", "Dispatch [\"url\"] as if from a right-click on a hot link.",
        &LLURLDispatcherListener::dispatchRightClick);
    add("dispatchFromTextEditor", "Dispatch [\"url\"] as if from an edit field.",
        &LLURLDispatcherListener::dispatchFromTextEditor);
}

void LLURLDispatcherListener::dispatch(const LLSD& params) const
{
    // For most purposes, we expect callers to want to be trusted.
    bool trusted_browser = true;
    if (params.has("trusted"))
    {
        // But for testing, allow a caller to specify untrusted.
        trusted_browser = params["trusted"].asBoolean();
    }
    LLURLDispatcher::dispatch(params["url"], NULL, trusted_browser);
}

void LLURLDispatcherListener::dispatchRightClick(const LLSD& params) const
{
    LLURLDispatcher::dispatchRightClick(params["url"]);
}

void LLURLDispatcherListener::dispatchFromTextEditor(const LLSD& params) const
{
    LLURLDispatcher::dispatchFromTextEditor(params["url"]);
}
