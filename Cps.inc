/*


 ######  ########  ######## ########  #### ########  ######
##    ## ##     ## ##       ##     ##  ##     ##    ##    ##
##       ##     ## ##       ##     ##  ##     ##    ##
##       ########  ######   ##     ##  ##     ##     ######
##       ##   ##   ##       ##     ##  ##     ##          ##
##    ## ##    ##  ##       ##     ##  ##     ##    ##    ##
 ######  ##     ## ######## ########  ####    ##     ######
 
 
SA-MP Team for SA-MP
Incognito for Streamer
KJason for making this include

*/
#if !defined _samp_included
	#error You need to include a_samp.inc before this include
#endif

#if !defined _streamer_included
	#error You need to include streamer.inc before this include
#endif

#if defined _MCP_included
	#endinput
#endif

#define _MCP_included

#if !defined INVALID_DYNAMIC_AREA
	#define INVALID_DYNAMIC_AREA -1
#endif

#define INVALID_CP_ID -1
#define MAX_CPS 100

static 
	CP@MIUsed[MAX_PLAYERS][MAX_CPS],
	CP@Cylinder[MAX_PLAYERS][MAX_CPS];

stock cp_SetPlayerMapIcon(playerid, iconid, Float:x, Float:y, Float:z, markertype, color, style = MAPICON_LOCAL)
{
	CP@MIUsed[playerid][iconid] = true;
	return SetPlayerMapIcon(playerid, iconid, Float:x, Float:y, Float:z, markertype, color, style);
}
#if defined _ALS_SetPlayerMapIcon
	#undef SetPlayerMapIcon
#else
	#define _ALS_SetPlayerMapIcon
#endif

#define SetPlayerMapIcon cp_SetPlayerMapIcon

stock cp_RemovePlayerMapIcon(playerid, iconid)
{
	CP@MIUsed[playerid][iconid] = false;
	if(CP@Cylinder[playerid][iconid] != INVALID_DYNAMIC_AREA)
	{
		DestroyDynamicArea(CP@Cylinder[playerid][iconid]);
		CP@Cylinder[playerid][iconid] = INVALID_DYNAMIC_AREA;
	}
	return RemovePlayerMapIcon(playerid, iconid);
}
#if defined _ALS_RemovePlayerMapIcon
	#undef RemovePlayerMapIcon
#else
	#define _ALS_RemovePlayerMapIcon
#endif

#define RemovePlayerMapIcon cp_RemovePlayerMapIcon

public OnPlayerConnect(playerid)
{
	for(new i; i < MAX_CPS; i++)
	{
		CP@MIUsed[playerid][i] = false;
		CP@Cylinder[playerid][i] = INVALID_DYNAMIC_AREA;
	}
	#if defined cp_OnPlayerConnect
		return cp_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect cp_OnPlayerConnect
#if defined cp_OnPlayerConnect
	forward cp_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	for(new i; i < MAX_CPS; i++)
	{
		if(CP@Cylinder[playerid][i] == INVALID_DYNAMIC_AREA)continue;
		DestroyCP(playerid, i);
	}
	#if defined cp_OnPlayerDisconnect
		return cp_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect cp_OnPlayerDisconnect
#if defined cp_OnPlayerDisconnect
	forward cp_OnPlayerDisconnect(playerid, reason);
#endif

forward OnPlayerEnterCP(playerid, cpid);
forward OnPlayerLeaveCP(playerid, cpid);

stock ShowCP(playerid, Float:x, Float:y, Float:z)
{
	if(!IsPlayerConnected(playerid))
	{
		printf("Tried to create a checkpoint for an offline player: X: %f, Y: %f, Z: %f, playerid: %i", x, y, z, playerid);
		return 0;
	}
	new cpid = -1;
	for(new i; i < MAX_CPS; i++)
	{
		if(CP@MIUsed[playerid][i])continue;
		cpid = i;
		break;
	}
	if(cpid == -1)
	{
		printf("Failed to create a checkpoint: No free mapicon slot available. X: %f, Y: %f, Z: %f, playerid: %i", x, y, z, playerid);
		return INVALID_CP_ID;
	}
	SetPlayerMapIcon(playerid, cpid, x, y, z, 0, 0xAA00000FF, MAPICON_GLOBAL_CHECKPOINT);
	CP@Cylinder[playerid][cpid] = CreateDynamicCylinder(x, y, z - 0.5, z + 0.5, 1.3, .playerid = playerid);
	return cpid;
}

stock DestroyCP(playerid, cpid)
{
	if(!IsPlayerConnected(playerid))
	{
		printf("Tried to delete a checkpoint for an offline player: CPID %i, playerid %i", cpid, playerid);
		return 0;
	}
	if(!(0 <= cpid <= 99) || CP@Cylinder[playerid][cpid] == INVALID_DYNAMIC_AREA)
	{
		printf("Tried to delete a non-existing checkpoint: CPID %i, playerid %i", cpid, playerid);
		return 0;
	}
	DestroyDynamicArea(CP@Cylinder[playerid][cpid]);
	CP@Cylinder[playerid][cpid] = INVALID_DYNAMIC_AREA;
	RemovePlayerMapIcon(playerid, cpid);
	return 1;
}

public OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA: areaid)
{
	for(new i; i < MAX_CPS; i++)
	{
		if(areaid == CP@Cylinder[playerid][i])
		{
			#if defined FILTERSCRIPT
				CallRemoteFunction("OnPlayerEnterCP", "ii", playerid, i);
			#else
				CallLocalFunction("OnPlayerEnterCP", "ii", playerid, i);
			#endif
			break;
		}
	}
	#if defined cp_OnPlayerEnterDynamicArea
		return cp_OnPlayerEnterDynamicArea(playerid, areaid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif

#define OnPlayerEnterDynamicArea cp_OnPlayerEnterDynamicArea
#if defined cp_OnPlayerEnterDynamicArea
	forward cp_OnPlayerEnterDynamicArea(playerid, areaid);
#endif

public OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA: areaid)
{
	for(new i; i < MAX_CPS; i++)
	{
		if(areaid == CP@Cylinder[playerid][i])
		{
			#if defined FILTERSCRIPT
				CallRemoteFunction("OnPlayerLeaveCP", "ii", playerid, i);
			#else
				CallLocalFunction("OnPlayerLeaveCP", "ii", playerid, i);
			#endif
			break;
		}
	}
	#if defined cp_OnPlayerLeaveDynamicArea
		return cp_OnPlayerLeaveDynamicArea(playerid, areaid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerLeaveDynamicArea
	#undef OnPlayerLeaveDynamicArea
#else
	#define _ALS_OnPlayerLeaveDynamicArea
#endif

#define OnPlayerLeaveDynamicArea cp_OnPlayerLeaveDynamicArea
#if defined cp_OnPlayerLeaveDynamicArea
	forward cp_OnPlayerLeaveDynamicArea(playerid, areaid);
#endif
