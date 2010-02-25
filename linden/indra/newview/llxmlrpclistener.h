/**
 * @file   llxmlrpclistener.h
 * @author Nat Goodspeed
 * @date   2009-03-18
 * @brief  LLEventPump API for LLXMLRPCTransaction. This header doesn't
 *         actually define the API; the API is defined by the pump name on
 *         which this class listens, and by the expected content of LLSD it
 *         receives.
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

#if ! defined(LL_LLXMLRPCLISTENER_H)
#define LL_LLXMLRPCLISTENER_H

#include "llevents.h"

/// Listen on an LLEventPump with specified name for LLXMLRPCTransaction
/// request events.
class LLXMLRPCListener
{
public:
    /// Specify the pump name on which to listen
    LLXMLRPCListener(const std::string& pumpname);

    /// Handle request events on the event pump specified at construction time
    bool process(const LLSD& command);

private:
    LLTempBoundListener mBoundListener;
};

#endif /* ! defined(LL_LLXMLRPCLISTENER_H) */
