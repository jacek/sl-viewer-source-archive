/**
 * @file   llappviewerlistener.h
 * @author Nat Goodspeed
 * @date   2009-06-18
 * @brief  Wrap subset of LLAppViewer API in event API
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

#if ! defined(LL_LLAPPVIEWERLISTENER_H)
#define LL_LLAPPVIEWERLISTENER_H

#include "lleventapi.h"
#include <boost/function.hpp>

class LLAppViewer;
class LLSD;

/// Listen on an LLEventPump with specified name for LLAppViewer request events.
class LLAppViewerListener: public LLEventAPI
{
public:
    typedef boost::function<LLAppViewer*(void)> LLAppViewerGetter;
    /// Bind the LLAppViewer instance to use (e.g. LLAppViewer::instance()).
    LLAppViewerListener(const LLAppViewerGetter& getter);

private:
    void requestQuit(const LLSD& event);
    void forceQuit(const LLSD& event);

    LLAppViewerGetter mAppViewerGetter;
};

#endif /* ! defined(LL_LLAPPVIEWERLISTENER_H) */
