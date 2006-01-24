/* File:      thread_defs_xsb.h
** Author(s): Marques
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
*/


#ifndef __THREAD_DEFS_XSB_H__

#define __THREAD_DEFS_XSB_H__

 
/* THREAD PRIMITIVES */

#define XSB_THREAD_CREATE	 1
#define XSB_THREAD_EXIT		 2
#define XSB_THREAD_JOIN		 3
#define XSB_THREAD_DETACH	 4
#define XSB_THREAD_SELF		 5

#define XSB_MUTEX_INIT		 6
#define XSB_MUTEX_LOCK		 7
#define XSB_MUTEX_TRYLOCK	 8
#define XSB_MUTEX_UNLOCK 	 9
#define XSB_MUTEX_DESTROY       10

#define XSB_SYS_MUTEX_LOCK	11
#define XSB_SYS_MUTEX_UNLOCK	12

#define XSB_ENSURE_ONE_THREAD	13
#define XSB_THREAD_YIELD	14

#define XSB_SHOW_MUTEXES        15

#define MAX_THREADS		1024


/* MUTEX KINDS (under LINUX) */

#define XSB_FAST_MUTEX		1
#define XSB_RECURSIVE_MUTEX	2
#define XSB_ERRORCHECK_MUTEX	3



/* Mutexes to protect execution of critical system stuff */

#define MAX_SYS_MUTEXES		40

/* Be sure to update this if you add a recusive mutex */
#define LAST_REC_MUTEX		8

/* If you add a mutex, also update mutex_names[] in thread_xsb.c */
/* first mutexes are recursive */
#define MUTEX_DYNAMIC		0

/* Use this one only for the stream_table itself: see I/O code for 
   locking the streams themselves. */
#define MUTEX_IO		1	/* Must be recursive */
#define MUTEX_TABLE		2
#define MUTEX_TRIE		3
#define MUTEX_SYMBOL		4
#define MUTEX_FLAGS		5
#define MUTEX_LOAD_UNDEF	6	/* Must be recursive */
#define MUTEX_DELAY		7
#define MUTEX_SYS_SYSTEM	8      /* recursive prob. not necess */

/* Non-recursive */
#define MUTEX_STRING		15
#define MUTEX_ATOM_BUF		16
#define MUTEX_SM		17
#define MUTEX_STACKS		18
#define MUTEX_SOCKETS		19
#define MUTEX_MEM		20
#define MUTEX_ODBC		21
#define MUTEX_GENTAG		22
#define MUTEX_DISPBLKHDR        23

/* Some mutexes available to users */
#define MUTEX_CONSOLE		30
#define MUTEX_USER1		31
#define MUTEX_USER2		32
#define MUTEX_USER3		33
#define MUTEX_USER4		34
#define MUTEX_USER5		35
#define MUTEX_USER6		36
#define MUTEX_USER7		37
#define MUTEX_USER8		38
#define MUTEX_USER9		39

/* Used for random number generation in testing modules */

#define INIT_MT_RANDOM          0
#define MT_RANDOM               1
#define MT_RANDOM_INTERVAL      2

#endif /* __THREAD_DEFS_XSB_H__ */
