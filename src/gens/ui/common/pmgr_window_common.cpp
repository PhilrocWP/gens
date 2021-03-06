/***************************************************************************
 * Gens: Plugin Manager Window. (Common Functions)                         *
 *                                                                         *
 * Copyright (c) 1999-2002 by Stéphane Dallongeville                       *
 * Copyright (c) 2003-2004 by Stéphane Akhoun                              *
 * Copyright (c) 2008-2009 by David Korth                                  *
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

#include "pmgr_window_common.hpp"
#include "libgsft/gsft_unused.h"

#include <stdint.h>

// C++ includes
#include <string>
#include <sstream>
using std::string;
using std::stringstream;
using std::endl;


/**
 * GetCPUFlags_string(): Convert required and supported CPU flags into a string.
 * @param cpuFlagsRequired Required CPU flags.
 * @param cpuFlagsSupported Supported CPU flags.
 * @param formatting If true, uses "<b></b>" to indicate required flags; if false, uses "[flag]*".
 */
string GetCPUFlags_string(const uint32_t cpuFlagsRequired,
			  const uint32_t cpuFlagsSupported,
			  const bool formatting)
{
	stringstream ssFlags;
	ssFlags << "CPU Flags: ";
	
	if (!cpuFlagsRequired && !cpuFlagsSupported)
	{
		// No CPU flags required or supported.
		ssFlags << "(none)";
		return ssFlags.str();
	}
	
	// Check all CPU flags.
	static const char* cpuFlagNames[] =
	{
		"MMX", "MMXEXT", "3DNOW", "3DNOWEXT",
		"SSE", "SSE2", "SSE3", "SSSE3",
		"SSE4.1", "SSE4.2", "SSE4A",
		
		NULL
	};
	
	int curFlag = 0;
	bool firstFlag = true;
	while (cpuFlagNames[curFlag])
	{
		uint32_t flagBit = (1 << curFlag);
		
		if (cpuFlagsRequired & flagBit)
		{
			// This CPU flag is required.
			if (!firstFlag)
				ssFlags << " ";
			
			if (formatting)
				ssFlags << "<b>" << cpuFlagNames[curFlag] << "</b>";
			else
				ssFlags << cpuFlagNames[curFlag] << "*";
			
			firstFlag = false;
		}
		else if (cpuFlagsSupported & flagBit)
		{
			// This CPU flag is supported, but not required.
			if (!firstFlag)
				ssFlags << " ";
			ssFlags << cpuFlagNames[curFlag];
			firstFlag = false;
		}
		
		// Next CPU flag.
		curFlag++;
	}
	
	// Return the CPU flag string.
	return ssFlags.str();
}


/**
 * numToHex(): Convert a numbr to a hexadecimal character.
 * @param num Number.
 * @return Hexadecimal character.
 */
static inline char numToHex(unsigned char num)
{
	return ((num <= 9) ? (num + '0') : ((num >= 10 && num <= 15) ? (num - 10 + 'a') : 0x00));
}


/**
 * UUIDtoString(): Convert a 16-byte UUID to a string.
 * @param uuid Pointer to UUID.
 * @return UUID as a string.
 */
string UUIDtoString(const unsigned char *uuid)
{
	char sUUID[48];
	char *pUUIDChar = sUUID;
	for (unsigned int i = 0; i < 16; i++)
	{
		*pUUIDChar++ = numToHex(uuid[i] >> 4);
		*pUUIDChar++ = numToHex(uuid[i] & 0x0F);
		
		if (i == 3 || i == 5 || i == 7 || i == 9)
			*pUUIDChar++ = '-';
	}
	*pUUIDChar = 0x00;
	
	return string(sUUID);
}
