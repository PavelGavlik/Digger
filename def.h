#ifndef DEF_H
#define DEF_H

#include <QDebug>
#include <stdint.h>

#ifdef GNU32
#ifndef _WINDOWS
#define _WINDOWS
#endif
#ifndef __WIN32__
#define __WIN32__
#endif
#endif

#if defined(__FreeBSD__) || defined(__linux__) || defined(__APPLE__) || defined YOUR_UNIX_LIKE_ARCH_GOING_HERE
#define UNIX
#endif

#define DIR_NONE -1
#define DIR_RIGHT 0
#define DIR_UP 2
#define DIR_LEFT 4
#define DIR_DOWN 6

#define TYPES 5

#define BONUSES 1
#define BAGS 7
#define MONSTERS 6
#define FIREBALLS DIGGERS
#define DIGGERS 2
#define SPRITES (BONUSES+BAGS+MONSTERS+FIREBALLS+DIGGERS)

/* Sprite order is figured out here. By LAST I mean last+1. */

#define FIRSTBONUS 0
#define LASTBONUS (FIRSTBONUS+BONUSES)
#define FIRSTBAG LASTBONUS
#define LASTBAG (FIRSTBAG+BAGS)
#define FIRSTMONSTER LASTBAG
#define LASTMONSTER (FIRSTMONSTER+MONSTERS)
#define FIRSTFIREBALL LASTMONSTER
#define LASTFIREBALL (FIRSTFIREBALL+FIREBALLS)
#define FIRSTDIGGER LASTFIREBALL
#define LASTDIGGER (FIRSTDIGGER+DIGGERS)

/*#define DIGGERS 48
#define MONSTERS 12
#define EMERALDS 1
#define BAGS 7
#define COINS 3
#define BONUSES 1
#define STATICS 6
#define BACKGROUNDS 8
#define FONTCHARS 40

#define FIREBALLS 2
#define SPRITES (DIGGERS+MONSTERS+EMERALDS+BAGS+COINS+BONUSES+FIREBALLS-2+STATICS+BACKGROUNDS+FONTCHARS)

Sprite order is figured out here. By LAST I mean last+1.
#define FIRSTFIREBALL LASTBAG
#define LASTFIREBALL (FIRSTFIREBALL+FIREBALLS-2)

#define FIRSTDIGGER 1
#define LASTDIGGER (FIRSTDIGGER+DIGGERS)
#define FIRSTMONSTER LASTDIGGER
#define LASTMONSTER (FIRSTMONSTER+MONSTERS)
#define FIRSTEMERALD LASTMONSTER
#define LASTEMERALD (FIRSTEMERALD+EMERALDS)
#define FIRSTBAG LASTEMERALD
#define LASTBAG (FIRSTBAG+BAGS)
#define FIRSTBONUS LASTBAG
#define LASTBONUS (FIRSTBONUS+BONUSES)
#define FIRSTBACKGROUND LASTBONUS
#define LASTBACKGROUND (FIRSTBACKGROUND+BACKGROUNDS)
#define FIRSTSTATIC LASTBACKGROUND
#define LASTSTATIC (FIRSTSTATIC+STATICS)*/

#define MWIDTH 15
#define MHEIGHT 10
#define MSIZE MWIDTH*MHEIGHT

#define MAX_REC_BUFFER 262144l
           /* I reckon this is enough for about 36 hours of continuous play. */

#define INI_GAME_SETTINGS "Game"
#define INI_GRAPHICS_SETTINGS "Graphics"
#define INI_SOUND_SETTINGS "Sound"
#ifdef _WINDOWS
#define INI_KEY_SETTINGS "Win Keys"
#else
#define INI_KEY_SETTINGS "Keys"
#endif

/* using lesser buffer size will break ie. alsa on linux, no reason to use
 * lesser size anyways...
 */
#define DEFAULT_BUFFER 2048
#ifdef _WINDOWS
#define DEF_SND_DEV 1
#else
#ifdef ARM
#define DEF_SND_DEV 1
#else
#define DEF_SND_DEV 0
#endif
#endif

#if !defined (_MSVC) && defined (__WIN32__)
#define _int64 LARGE_INTEGER
#endif

#ifdef __WIN32__
 #if defined (RUNTIMEDYNAMICLINK) && !defined (DIRECTX)
  #define DIRECTX
 #endif
#else
 #ifdef DIRECTX
  #undef DIRECTX
 #endif
 #ifdef RUNTIMEDYNAMICLINK
  #undef RUNTIMEDYNAMICLINK
 #endif
 #if defined (_WINDOWS)
  #ifndef WIN16
   #define WIN16
  #endif
  #ifdef _MSVC
   #define farmalloc _fmalloc
   #define farfree _ffree
  #endif
 #endif 
#endif

#if defined ARM || defined(__WIN32__) || defined UNIX || defined(__MINGW32__)
#define FLATFILE
#endif

#ifdef FLATFILE
#define near
#define far
#define huge
#define farmalloc malloc
#define farfree free
#define farcoreleft coreleft
#endif

#ifdef ARM
#define ININAME "Digger:Settings"
#elif defined(__FreeBSD__) && defined _VGL
/* Applications using FreeBSD's console graphics running as root */
#define ININAME "/var/games/digger/digger.rc"
#elif defined UNIX && !defined _VGL
/* While SDL and other X11 related apps could be runned as ordinary user */
#ifdef __FreeBSD__
#include <sys/syslimits.h>
#elif !defined(__linux__) /* I donno what is analog of PATH_MAX for Linux :( */
#define PATH_MAX 1024
#endif
#define ININAME strncat(strncpy(malloc(PATH_MAX),getenv("HOME"),PATH_MAX),"/.digger.rc",PATH_MAX)
#else
#define ININAME "DIGGER.INI"
#endif

#if defined(__FreeBSD__) || defined(__linux__) || defined(__APPLE__)
//#include "fbsd_sup.h"
#endif

#ifdef UNIX
#define stricmp(x, y) strcasecmp(x, y)
#define strnicmp(x, y, z) strncasecmp(x, y, z)
#endif

#if defined _WINDOWS
#define DIGGER_VERSION "TD WIN 19990707"
#elif defined ARM
#define DIGGER_VERSION "JB ARM 19990320"
#elif defined _VGL
#define DIGGER_VERSION "MS FBSD 20000407"
#elif defined _SDL
#define DIGGER_VERSION "POK SDL 20110912"
#else
#define DIGGER_VERSION "AJ DOS 19990506"
#endif

/* Version string:
  First word: your initials if you have changed anything.
  Second word: platform.
  Third word: compilation date in yyyymmdd format. */

#endif /* DEF_H */
