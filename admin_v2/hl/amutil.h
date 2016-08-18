/*
 * $Id: amutil.h,v 1.2 2001/09/27 20:33:16 darope Exp $
 *
 *
 * Copyright (c) 1999-2001 Alfred Reynolds, Florian Zschocke, Magua
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
 * Description: This file declares various utility functions and macros.
 *              It should be safely included in all AM source files.
 *              I got sick and tired of getting endless errors when 
 *              including users.h or util.h due to unknown requirements
 *              and dependencies.
 *              I'm starting to move some functions over here from users.h
 *
 */

#ifndef _AMUTIL_H_
#define _AMUTIL_H_

#include <cvardef.h>
#include <errno.h>


//extern int errno;
extern cvar_t* ptAM_debug;
extern cvar_t* ptAM_devel;
extern cvar_t* ptAM_botProtection;
extern cvar_t* ptAM_autoban;


/*
 *  some macros to be used around
 */

#define DEBUG_LOG( level, args )   do{  if ( ptAM_debug && ptAM_debug->value >= level ) \
                 UTIL_LogPrintf( "[ADMIN] DEBUG: %s\n", UTIL_VarArgs args );} while(0)

#define DEVEL_LOG( level, args )   do{  if ( ptAM_devel && ptAM_devel->value >= level ) \
                 UTIL_LogPrintf( "[ADMIN] DEVEL(%i): %s\n", level, UTIL_VarArgs args );} while(0)

/* debugging and devel macros for conditional execution */
#define DEBUG_DO( level, commands ) do{ if ( ptAM_debug && ptAM_debug->value >= level ) \
                 { commands } } while(0)

#define DEVEL_DO( level, commands ) do{ if ( ptAM_devel && ptAM_devel->value >= level ) \
                 { commands } } while(0)




/*
 *  Functions defined in amutil.cpp
 */


// stop malformed names stuffing up checking 
//
int make_friendly(char* string, bool check);


// convert a string to all-lower 
//
void strtolower( char* string );


// a crude version of strstr() but ignoring case
//
char* stristr(const char* haystack, const char* needle );


// Formats the string-literals '\n' and '^n' into line feeds (ASCII 10)
//
void FormatLine(char* sLine);


// Formats a path so all the /s and \s are correct for that OS.
//
void FormatPath(char* sPath);


// Check a string for violations of maximum line length. 
// When a line is too long, if can fail, truncate or
// wrap the line. If the line cannot be handled, 0 is returned, 
// 1 otherwise
//
#define SW_NOWRAP 0
#define SW_WRAP 1
#define SW_TRUNC 2
int wrap_lines( char* String, int MaxLineLength, int WrapType );
 

#endif /* _AMUTIL_H_ */