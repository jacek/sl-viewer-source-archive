/** 
 * @file lltexturerstats.cpp
 * @brief texture stats helper methods
 *
 * $LicenseInfo:firstyear=2002&license=viewergpl$
 * 
 * Copyright (c) 2002-2009, Linden Research, Inc.
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

#include "pipeline.h" 
#include "llagent.h"
#include "lltexturefetch.h" 
#include "lltexturestats.h"
#include "llviewerregion.h"


static LLSD averagesList;
void reset_texture_stats()
{
	llinfos << "Resetting texture download stats data" << llendl;
	averagesList.clear();
}

void capture_texture_stats_snapshot(U64 currentTime)
{
	static U32 monotonic_counter = 0;
	llinfos << "Taking texture snapshot" << llendl;
	if ( LLAppViewer::getTextureFetch() && LLAppViewer::getTextureFetch()->getTextureInfo())
	{
		std::stringstream time_string;
		time_string << currentTime;

		LLSD snapshot;
		snapshot["time"] = time_string.str();
		snapshot["texture_data"] = LLAppViewer::getTextureFetch()->getTextureInfo()->getAverages();

		std::stringstream message_number;
		message_number << "snapshot_" << ++monotonic_counter;
		averagesList[message_number.str()] = snapshot;
		llinfos << "Recorded snapshot " << monotonic_counter << llendl;
	}
}

void send_texture_stats_to_sim()
{
	LLSD texture_stats;
	// Only send stats if the agent is connected to a region.
	if (!gAgent.getRegion() || gNoRender)
	{
		return;
	}

	LLUUID agent_id = gAgent.getID();
	texture_stats["agent_id"] = agent_id;
	texture_stats["texture_details"] = averagesList;

	std::string texture_cap_url = gAgent.getRegion()->getCapability("TextureStats");
	if ( texture_cap_url != "" )
	{
		llinfos << "Sending texture stats to simulator" << llendl;
		LLHTTPClient::post(texture_cap_url, texture_stats, NULL);
	}
}

