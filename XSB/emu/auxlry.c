/* File:      auxlry.c
** Author(s): Warren, Sagonas, Xu
** Contact:   xsb-contact@cs.sunysb.edu
** 
** Copyright (C) The Research Foundation of SUNY, 1986, 1993-1998
** 
** XSB is free software; you can redistribute it and/or modify it under the
** terms of the GNU Library General Public License as published by the Free
** Software Foundation; either version 2 of the License, or (at your option)
** any later version.
** 
** XSB is distributed in the hope that it will be useful, but WITHOUT ANY
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License for
** more details.
** 
** You should have received a copy of the GNU Library General Public License
** along with XSB; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**
** $Id: auxlry.c,v 1.14 2003-03-10 16:18:11 lfcastro Exp $
** 
*/


#include "xsb_config.h"

#include <stdio.h>

/* take care of the time.h problems */
#include "xsb_time.h"

#ifndef WIN_NT
#include <sys/resource.h>

#ifdef SOLARIS
/*--- Include the following to bypass header file inconcistencies ---*/
extern int getrusage();
extern int gettimeofday();
#endif

#ifdef HP700
#include <sys/syscall.h>
extern int syscall();
#define getrusage(T, USAGE)	syscall(SYS_getrusage, T, USAGE);
#endif

#endif

#ifdef WIN_NT
#include "windows.h"
#endif

/*----------------------------------------------------------------------*/

double cpu_time(void)
{
  float time_sec;

#if defined(WIN_NT)
  static int win_version = -1;

  if (win_version == -1) {
    OSVERSIONINFO winv;
    winv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&winv);
    win_version = winv.dwPlatformId;
  }

  if (win_version == VER_PLATFORM_WIN32_NT) {
    HANDLE thisproc;
    FILETIME creation, exit, kernel, user;
    unsigned long long lkernel, luser;
    double stime, utime;

    thisproc = GetCurrentProcess();
    GetProcessTimes(thisproc,&creation,&exit,&kernel,&user);
    /* unfinished -- how to convert kernel+user (two 64-bit unsigned
       integers) into an appropriate float?              --lfcastro */
    /* the code below assumes sizeof(long long) == 8 */
    
    lkernel = ((unsigned long long) kernel.dwHighDateTime << 32) + 
      kernel.dwLowDateTime;
    luser = ((unsigned long long) kernel.dwHighDateTime << 32) + 
      kernel.dwLowDateTime;

    stime = lkernel / 1.0e7;
    utime = luser / 1.0e7;

    time_sec = (float) stime + utime;

  } else {
    time_sec = ((float) clock() / CLOCKS_PER_SEC);
  }

#else
  struct rusage usage;

  getrusage(RUSAGE_SELF, &usage);
  time_sec = (float)usage.ru_utime.tv_sec +
	     (float)usage.ru_utime.tv_usec / 1000000.0;
#endif

  return time_sec;
}

/*----------------------------------------------------------------------*/

void get_date(int *year, int *month, int *day,
	     int *hour, int *minute, int *second)
{
#ifdef WIN_NT
    SYSTEMTIME SystemTime;
    TIME_ZONE_INFORMATION tz;
    GetLocalTime(&SystemTime);
    *year = SystemTime.wYear;
    *month = SystemTime.wMonth;
    *day = SystemTime.wDay;
    *hour = SystemTime.wHour;
    *minute = SystemTime.wMinute;
    *second = SystemTime.wSecond;
    GetTimeZoneInformation(&tz);
    *hour = *hour + tz.Bias/60;
    *minute = *minute + tz.Bias % 60;
#else
#ifdef HAVE_GETTIMEOFDAY
    struct timeval tv;
    struct tm *tm;

    gettimeofday(&tv,NULL);
    tm = gmtime(&tv.tv_sec);
    *year = tm->tm_year;
    if (*year < 1900)
      *year += 1900;
    *month = tm->tm_mon + 1;
    *day = tm->tm_mday;
    *hour = tm->tm_hour;
    *minute = tm->tm_min;
    *second = tm->tm_sec;
#endif
#endif
}

/*----------------------------------------------------------------------*/

double real_time(void)
{
#if defined(WIN_NT)
  double value = ((float) clock() / CLOCKS_PER_SEC);
#else
  double value;
  struct timeval tvs;

  gettimeofday(&tvs, 0);
  value = tvs.tv_sec + 0.000001 * tvs.tv_usec;
#endif
  return value;
}

/*----------------------------------------------------------------------*/
