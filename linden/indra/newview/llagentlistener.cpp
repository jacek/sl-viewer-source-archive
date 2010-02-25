/**
 * @file   llagentlistener.cpp
 * @author Brad Kittenbrink
 * @date   2009-07-10
 * @brief  Implementation for llagentlistener.
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

#include "llviewerprecompiledheaders.h"

#include "llagentlistener.h"

#include "llagent.h"
#include "llcommandhandler.h"
#include "llslurl.h"
#include "llurldispatcher.h"
#include "llviewerobject.h"
#include "llviewerobjectlist.h"
#include "llviewerregion.h"

LLAgentListener::LLAgentListener(LLAgent &agent)
  : LLEventAPI("LLAgent",
               "LLAgent listener to (e.g.) teleport, sit, stand, etc."),
    mAgent(agent)
{
	add("requestTeleport",
        "Teleport: [\"regionname\"], [\"x\"], [\"y\"], [\"z\"]\n"
        "If [\"skip_confirmation\"] is true, use LLURLDispatcher rather than LLCommandDispatcher.",
        &LLAgentListener::requestTeleport);
	add("requestSit",
        "Ask to sit on the object specified in [\"obj_uuid\"]",
        &LLAgentListener::requestSit);
	add("requestStand",
        "Ask to stand up",
        &LLAgentListener::requestStand);
}

void LLAgentListener::requestTeleport(LLSD const & event_data) const
{
	if(event_data["skip_confirmation"].asBoolean())
	{
		LLSD params(LLSD::emptyArray());
		params.append(event_data["regionname"]);
		params.append(event_data["x"]);
		params.append(event_data["y"]);
		params.append(event_data["z"]);
		LLCommandDispatcher::dispatch("teleport", params, LLSD(), NULL, true);
		// *TODO - lookup other LLCommandHandlers for "agent", "classified", "event", "group", "floater", "parcel", "login", login_refresh", "balance", "chat"
		// should we just compose LLCommandHandler and LLDispatchListener?
	}
	else
	{
		std::string url = LLSLURL::buildSLURL(event_data["regionname"], event_data["x"], event_data["y"], event_data["z"]);
		LLURLDispatcher::dispatch(url, NULL, false);
	}
}

void LLAgentListener::requestSit(LLSD const & event_data) const
{
	//mAgent.getAvatarObject()->sitOnObject();
	// shamelessly ripped from llviewermenu.cpp:handle_sit_or_stand()
	// *TODO - find a permanent place to share this code properly.
	LLViewerObject *object = gObjectList.findObject(event_data["obj_uuid"]);

	if (object && object->getPCode() == LL_PCODE_VOLUME)
	{
		gMessageSystem->newMessageFast(_PREHASH_AgentRequestSit);
		gMessageSystem->nextBlockFast(_PREHASH_AgentData);
		gMessageSystem->addUUIDFast(_PREHASH_AgentID, mAgent.getID());
		gMessageSystem->addUUIDFast(_PREHASH_SessionID, mAgent.getSessionID());
		gMessageSystem->nextBlockFast(_PREHASH_TargetObject);
		gMessageSystem->addUUIDFast(_PREHASH_TargetID, object->mID);
		gMessageSystem->addVector3Fast(_PREHASH_Offset, LLVector3(0,0,0));

		object->getRegion()->sendReliableMessage();
	}
}

void LLAgentListener::requestStand(LLSD const & event_data) const
{
	mAgent.setControlFlags(AGENT_CONTROL_STAND_UP);
}

