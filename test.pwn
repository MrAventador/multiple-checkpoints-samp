#include <a_samp>
#include <streamer>
#include <cps>
//==================================================================================
main()
{
	
}
//==================================================================================
public OnGameModeInit()
{
	return 1;
}
//==================================================================================
public OnPlayerEnterCP(playerid, cpid)
{
	new str[16];
	format(str, sizeof(str), "CPID: %i", cpid);
	SendClientMessage(playerid, -1, str);
	return 1;
}
//==================================================================================
public OnPlayerLeaveCP(playerid, cpid)
{
	new str[16];
	format(str, sizeof(str), "LCPID: %i", cpid);
	SendClientMessage(playerid, -1, str);
//	DestroyCP(playerid, cpid);
	return 1;
}
//==================================================================================
public OnPlayerCommandText(playerid, cmdtext[])
{
	if(!strcmp(cmdtext, "/test", true, 5))
	{
		new Float:x,Float:y,Float:z;
		GetPlayerPos(playerid, x, y, z);
		ShowCP(playerid, x, y, z);
	}
	else if(!strcmp(cmdtext, "/test2", true, 6))
	{
		DestroyAllCPs(playerid);
	}
	return 1;
}
