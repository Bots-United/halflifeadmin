/*
 * ===========================================================================
 *
 * $Id: CPlugin.h,v 1.8 2003/08/19 23:43:29 bugblatter Exp $
 *
 *
 * Copyright (c) 2002-2003 Alfred Reynolds, Florian Zschocke, Magua
 *
 *   This file is part of Admin Mod.
 *
 *   Admin Mod is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   Admin Mod is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Admin Mod; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *   In addition, as a special exception, the author gives permission to
 *   link the code of this program with the Half-Life Game Engine ("HL 
 *   Engine") and Modified Game Libraries ("MODs") developed by VALVe, 
 *   L.L.C ("Valve") and Modified Game Libraries developed by Gearbox 
 *   Software ("Gearbox").  You must obey the GNU General Public License 
 *   in all respects for all of the code used other than the HL Engine and 
 *   MODs from Valve or Gearbox. If you modify this file, you may extend 
 *   this exception to your version of the file, but you are not obligated 
 *   to do so.  If you do not wish to do so, delete this exception statement
 *   from your version.
 *
 * ===========================================================================
 *
 * Comments:
 *
 * A class for handling the plugins.  Each instance
 * of CPlugin represents one actual Small plugin; includes
 * the filename, an AMX virtual machine, a list of exported
 * commands, etc. 
 *
 */

#define BUF_SIZE 100 // general buffer size
#define PLUGIN_CMD_SIZE 100
#define PLUGIN_HELP_SIZE 150

#define INVALID_INDEX -1
#define INT_MAX_PLAYERS 32

const int ACCESS_ALL = 0;
const int ACCESS_IMMUNITY = 4096;
const int ACCESS_RESERVE_NICK = 16384;
const int ACCESS_RESERVE_SPOT = 32768;

#include <string.h>
#include "extdll.h"
#include "amx.h"
#include "CLinkList.cpp"
#include "commandhandler.h"

int GetUserAccess(edict_t* pEntity);
void System_Response(char *str,edict_t *);

/* Yeah, it's kludgy to redefine this stuff here, but I
didn't feel like messing with users.h. */

#ifdef _WIN32
	typedef int (FAR *AMXINIT)(AMX *,void *);
	typedef int (FAR *AMXREGISTER)(AMX *,AMX_NATIVE_INFO *,int);
	typedef int (FAR *AMXFINDPUBLIC)(AMX *,char *,int *);
	typedef int (FAR *AMXEXEC)(AMX *,cell *,int, int,...);
	typedef int (FAR *AMXGETADDR)(AMX *,cell,cell **);
	typedef int (FAR *AMXSTRLEN)(cell *,int *);
	typedef int (FAR *AMXRAISEERROR)(AMX *,int);
	typedef int (FAR *AMXGETSTRING)(char *,cell *);
	typedef int (FAR *AMXSETSTRING)(cell *,char *,int);
#else
	typedef int (*AMXINIT)(AMX *,void *);
	typedef int (*AMXREGISTER)(AMX *,AMX_NATIVE_INFO *,int);
	typedef int (*AMXFINDPUBLIC)(AMX *,char *,int *);
	typedef int (*AMXEXEC)(AMX *,cell *,int, int,...);
	typedef int (*AMXGETADDR)(AMX *,cell,cell **);
	typedef int (*AMXSTRLEN)(cell *,int *);
	typedef int (*AMXRAISEERROR)(AMX *,int);
	typedef int (*AMXGETSTRING)(char *,cell *);
	typedef int (*AMXSETSTRING)(cell *,char *,int);
#endif

void UTIL_LogPrintf( char *fmt, ... );

typedef struct {
	char sCmd[PLUGIN_CMD_SIZE];
	int iAccess;
	int iIndex;
} command_struct;

typedef struct {
	char sCmd[PLUGIN_CMD_SIZE];
	char sHelp[PLUGIN_HELP_SIZE];
	int iAccess;
} help_struct;

class CAMXCommandHandler;

class CPlugin {

public:
	// see cevent.h for comments on this
	enum { EVENT_SIZE = 64 };

public:
	CPlugin::CPlugin();
	CPlugin::~CPlugin();
	
	AMX* amx();
	BOOL AddCommand(char* Cmd, char* Function, int iAccess);
	bool AddEvent(char *event, char *function );

	plugin_result HandleCommand(const CAMXCommandHandler* pHandler, edict_t* pEntity, char* sCmd, char* sData);
	plugin_result HandleEvent(const CAMXCommandHandler* pHandler, edict_t* pEntity);
	plugin_result HandleConnect(edict_t* pEntity, char* sName, char* IPAddress);
	plugin_result HandleDisconnect(edict_t* pEntity);
	plugin_result HandleInfo(edict_t* pentity, char* sNewName);
	plugin_result HandleLog(char* sLog);
	BOOL LoadPlugin(char* filename, int iPriority);
	plugin_result StartPlugin();
	char* File();
	char* Name();
	void SetName(char* sName);
	char* Desc();
	void SetDesc(char* sDesc);
	char* Version();
	void SetVersion(char* sVersion);
	int Priority() const { return m_iPriority; }
	
private :
	void Cleanup();
	void InitValues();
	int LoadFile(char* filename);

	int m_iEventCommandIndex;
	int m_iEventConnectIndex;
	int m_iEventDisconnectIndex;
	int m_iEventInfoIndex;
	int m_iEventLogIndex;
	int m_iInitIndex;
	int m_iPriority;
	char m_sFile[BUF_SIZE];
	char m_sName[BUF_SIZE];
	char m_sDesc[BUF_SIZE];
	char m_sVersion[BUF_SIZE];
	AMX* m_pAmx;
	void* m_pProgram;
	CLinkList<command_struct>* m_pCommands;

	struct event_struct
	{
		char event[EVENT_SIZE];
		char function[EVENT_SIZE];
	};

	CLinkList<struct event_struct>* m_pEvents;
};