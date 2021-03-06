/***************************************************************************
 * Gens: Timer functions.                                                  *
 *                                                                         *
 * Copyright (c) 1999-2002 by Stéphane Dallongeville                       *
 * Copyright (c) 2003-2004 by Stéphane Akhoun                              *
 * Copyright (c) 2008 by David Korth                                       *
 *                                                                         *
 * Several functions were taken from Wine 1.1.6.                           *
 * Copyright 1999 Juergen Schmied                                          *
 * Copyright 2007 Dmitry Timoshkov                                         *
 *                                                                         *
 * This program is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU General Public License as published by the   *
 * Free Software Foundation; either version 2 of the License, or (at your  *
 * option) any later version.                                              *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License along *
 * with this program; if not, write to the Free Software Foundation, Inc., *
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.           *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "timer.h"

#include <unistd.h>
#ifdef HAVE_LIBRT
#include <time.h>
#else
#include <sys/time.h>
#endif
#include <stddef.h>

// Time #defines from Wine's dlls/ntdll/time.c
#define TICKSPERSEC        10000000
#define SECSPERDAY         86400
#define SECS_1601_TO_1970  ((369 * 365 + 89) * (uint64_t)SECSPERDAY)
#define TICKS_1601_TO_1970 (SECS_1601_TO_1970 * TICKSPERSEC)

static int64_t start_time;


/**
 * NtQuerySystemTime(): Retrieves the current system time.
 * @param pTime Pointer to 64-bit variable to store the time in.
 */
static void NtQuerySystemTime(int64_t* pTime)
{
	// Originally from Wine 1.1.6
	// dlls/ntdll/time.c
	
	if (!pTime)
		return;
	
#ifdef HAVE_LIBRT
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	*pTime = now.tv_sec * (int64_t)TICKSPERSEC + TICKS_1601_TO_1970;
	*pTime += (now.tv_nsec / 1000) * 10;
#else
	struct timeval now;
	gettimeofday(&now, NULL);
	*pTime = now.tv_sec * (int64_t)TICKSPERSEC + TICKS_1601_TO_1970;
	*pTime += now.tv_usec * 10;
#endif
}


/**
 * init_timer(): Initialize the Wine timer functions.
 */
void init_timer(void)
{
	NtQuerySystemTime(&start_time);
}


/**
 * GetTickCount() Get the number of milliseconds that have elapsed since Gens was started.
 * @return Milliseconds since Gens was started.
 */
unsigned int GetTickCount(void)
{
	// Originally from Wine 1.1.6
	// dlls/ntdll/time.c
	
	int64_t now;
	NtQuerySystemTime(&now);
	return (now - start_time) / 10000;
}


/**
 * QueryPerformanceFrequency(): Get the frequency of the high-resolution performance counter.
 * @param freq Pointer to 64-bit variable to store the frequency in.
 */
void QueryPerformanceFrequency(int64_t *frequency)
{
	// Originally from Wine 1.1.6
	// dlls/ntdll/time.c
	
	// The frequency is always reported as 1,193,182 Hz.
	// My XP Pro VM reports the frequency as 3,579,545 Hz (NTSC color subcarrier),
	// but it doesn't really make a difference.
	*frequency = 1193182;
}


/**
 * QueryPerformanceCounter(): Get the high-resolution performance counter value.
 * @param counter Pointer to 64-bit variable to store the counter in.
 */
void QueryPerformanceCounter(int64_t *counter)
{
	// Originally from Wine 1.1.6
	// dlls/ntdll/time.c
	
	if (!counter)
		return;
	
	int64_t now;
	NtQuerySystemTime(&now);
	*counter = ((now - start_time) * 21) / 176;
}
