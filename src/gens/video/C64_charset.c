/***************************************************************************
 * Gens: Commodore 64 Character Set.                                       *
 *                                                                         *
 * Copyright (c) 1982 Commodore International                              *
 ***************************************************************************/

/***************************************************
 * Format: 8 bytes per character, 8 bits per line. *
 * 1 == opaque dot; 0 == transparent dot           *
 * MSB == left-most dot; LSB == right-most dot     *
 ***************************************************/

#include "C64_charset.h"

const osd_char_t C64_charset[] =
{
	// cp1252: 0x00 - 0x0F (TODO: 0x01, 0x02, 0x0B-0x0F)
	{0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{L'♥', {0x36, 0x7F, 0x7F, 0x7F, 0x3E, 0x1C, 0x08, 0x00}},
	{L'♦', {0x08, 0x1C, 0x3E, 0x7F, 0x3E, 0x1C, 0x08, 0x00}},
	{L'♣', {0x18, 0x18, 0x66, 0x66, 0x18, 0x18, 0x3C, 0x00}},
	{L'♠', {0x08, 0x1C, 0x3E, 0x7F, 0x7F, 0x1C, 0x3E, 0x00}},
	{L'•', {0x00, 0x3C, 0x7E, 0x7E, 0x7E, 0x7E, 0x3C, 0x00}},
	{L'◘', {0xFF, 0xC3, 0x81, 0x81, 0x81, 0x81, 0xC3, 0xFF}},
	{L'○', {0x00, 0x3C, 0x7E, 0x66, 0x66, 0x7E, 0x3C, 0x00}},
	{L'◙', {0xFF, 0xC3, 0x81, 0x99, 0x99, 0x81, 0xC3, 0xFF}},
	
	// cp1252: 0x10 - 0x1F (TODO: 0x10, 0x11, 0x12, 0x14, 0x15, 0x16, 0x17, 0x1C, 0x1D, 0x1E, 0x1F)
	{L'‼', {0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x66, 0x00}},
	{L'↑', {0x00, 0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x18}},
	{L'↓', {0x00, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x3C, 0x18}},
	{L'→', {0x00, 0x04, 0x06, 0x7F, 0x7F, 0x06, 0x04, 0x00}},
	{L'←', {0x00, 0x10, 0x30, 0x7F, 0x7F, 0x30, 0x10, 0x00}},
	
	// cp1252: 0x20 - 0x2F
	{L' ', {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{L'!', {0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00}},
	{L'"', {0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{L'#', {0x66, 0x66, 0xFF, 0x66, 0xFF, 0x66, 0x66, 0x00}},
	{L'$', {0x18, 0x3E, 0x60, 0x3C, 0x06, 0x7C, 0x18, 0x00}},
	{L'%', {0x62, 0x66, 0x0C, 0x18, 0x30, 0x66, 0x46, 0x00}},
	{L'&', {0x3C, 0x66, 0x3C, 0x38, 0x67, 0x66, 0x3F, 0x00}},
	{L'\'', {0x06, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{L'(', {0x0C, 0x18, 0x30, 0x30, 0x30, 0x18, 0x0C, 0x00}},
	{L')', {0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x18, 0x30, 0x00}},
	{L'*', {0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00}},
	{L'+', {0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00}},
	{L',', {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30}},
	{L'-', {0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00}},
	{L'.', {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00}},
	{L'/', {0x00, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00}},
	
	// cp1252: 0x30 - 0x3F
	{L'0', {0x3C, 0x66, 0x6E, 0x76, 0x66, 0x66, 0x3C, 0x00}},
	{L'1', {0x18, 0x18, 0x38, 0x18, 0x18, 0x18, 0x7E, 0x00}},
	{L'2', {0x3C, 0x66, 0x06, 0x0C, 0x30, 0x60, 0x7E, 0x00}},
	{L'3', {0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C, 0x00}},
	{L'4', {0x06, 0x0E, 0x1E, 0x66, 0x7F, 0x06, 0x06, 0x00}},
	{L'5', {0x7E, 0x60, 0x7C, 0x06, 0x06, 0x66, 0x3C, 0x00}},
	{L'6', {0x3C, 0x66, 0x60, 0x7C, 0x66, 0x66, 0x3C, 0x00}},
	{L'7', {0x7E, 0x66, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x00}},
	{L'8', {0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C, 0x00}},
	{L'9', {0x3C, 0x66, 0x66, 0x3E, 0x06, 0x66, 0x3C, 0x00}},
	{L':', {0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00}},
	{L';', {0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x30}},
	{L'<', {0x0E, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0E, 0x00}},
	{L'=', {0x00, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x00, 0x00}},
	{L'>', {0x70, 0x18, 0x0C, 0x06, 0x0C, 0x18, 0x70, 0x00}},
	{L'?', {0x3C, 0x66, 0x06, 0x0C, 0x18, 0x00, 0x18, 0x00}},
	
	// cp1252: 0x40 - 0x4F
	{L'@', {0x3C, 0x66, 0x6E, 0x6E, 0x60, 0x62, 0x3C, 0x00}},
	{L'A', {0x18, 0x3C, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00}},
	{L'B', {0x7C, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x7C, 0x00}},
	{L'C', {0x3C, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3C, 0x00}},
	{L'D', {0x78, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0x78, 0x00}},
	{L'E', {0x7E, 0x60, 0x60, 0x78, 0x60, 0x60, 0x7E, 0x00}},
	{L'F', {0x7E, 0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x00}},
	{L'G', {0x3C, 0x66, 0x60, 0x6E, 0x66, 0x66, 0x3C, 0x00}},
	{L'H', {0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00}},
	{L'I', {0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00}},
	{L'J', {0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x6C, 0x38, 0x00}},
	{L'K', {0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x66, 0x00}},
	{L'L', {0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x00}},
	{L'M', {0x63, 0x77, 0x7F, 0x6B, 0x63, 0x63, 0x63, 0x00}},
	{L'N', {0x66, 0x76, 0x7E, 0x7E, 0x6E, 0x66, 0x66, 0x00}},
	{L'O', {0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}},
	
	// cp1252: 0x50 - 0x5F
	{L'P', {0x7C, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x00}},
	{L'Q', {0x3C, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x0E, 0x00}},
	{L'R', {0x7C, 0x66, 0x66, 0x7C, 0x78, 0x6C, 0x66, 0x00}},
	{L'S', {0x3C, 0x66, 0x60, 0x3C, 0x06, 0x66, 0x3C, 0x00}},
	{L'T', {0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00}},
	{L'U', {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}},
	{L'V', {0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00}},
	{L'W', {0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00}},
	{L'X', {0x66, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x66, 0x00}},
	{L'Y', {0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x00}},
	{L'Z', {0x7E, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x7E, 0x00}},
	{L'[', {0x3C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3C, 0x00}},
	{L'\\', {0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x00}},
	{L']', {0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x00}},
	{L'^', {0x00, 0x18, 0x24, 0x42, 0x00, 0x00, 0x00, 0x00}}, // (based on C64 "↑")
	{L'_', {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF}},
	
	// 0x60 - 0x6F
	{L'`', {0x60, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{L'a', {0x00, 0x00, 0x3C, 0x06, 0x3E, 0x66, 0x3E, 0x00}},
	{L'b', {0x00, 0x60, 0x60, 0x7C, 0x66, 0x66, 0x7C, 0x00}},
	{L'c', {0x00, 0x00, 0x3C, 0x60, 0x60, 0x60, 0x3C, 0x00}},
	{L'd', {0x00, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3E, 0x00}},
	{L'e', {0x00, 0x00, 0x3C, 0x66, 0x7E, 0x60, 0x3C, 0x00}},
	{L'f', {0x00, 0x0E, 0x18, 0x3E, 0x18, 0x18, 0x18, 0x00}},
	{L'g', {0x00, 0x00, 0x3E, 0x66, 0x66, 0x3E, 0x06, 0x7C}},
	{L'h', {0x00, 0x60, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x00}},
	{L'i', {0x00, 0x18, 0x00, 0x38, 0x18, 0x18, 0x3C, 0x00}},
	{L'j', {0x00, 0x06, 0x00, 0x06, 0x06, 0x06, 0x06, 0x3C}},
	{L'k', {0x00, 0x60, 0x60, 0x6C, 0x78, 0x6C, 0x66, 0x00}},
	{L'l', {0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00}},
	{L'm', {0x00, 0x00, 0x66, 0x7F, 0x7F, 0x6B, 0x63, 0x00}},
	{L'n', {0x00, 0x00, 0x7C, 0x66, 0x66, 0x66, 0x66, 0x00}},
	{L'o', {0x00, 0x00, 0x3C, 0x66, 0x66, 0x66, 0x3C, 0x00}},
	
	// 0x70 - 0x7F (TODO: 0x7F)
	{L'p', {0x00, 0x00, 0x7C, 0x66, 0x66, 0x7C, 0x60, 0x60}},
	{L'q', {0x00, 0x00, 0x3E, 0x66, 0x66, 0x3E, 0x06, 0x06}},
	{L'r', {0x00, 0x00, 0x7C, 0x66, 0x60, 0x60, 0x60, 0x00}},
	{L's', {0x00, 0x00, 0x3E, 0x60, 0x3C, 0x06, 0x7C, 0x00}},
	{L't', {0x00, 0x18, 0x7E, 0x18, 0x18, 0x18, 0x0E, 0x00}},
	{L'u', {0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3E, 0x00}},
	{L'v', {0x00, 0x00, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00}},
	{L'w', {0x00, 0x00, 0x63, 0x6B, 0x7F, 0x3E, 0x36, 0x00}},
	{L'x', {0x00, 0x00, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x00}},
	{L'y', {0x00, 0x00, 0x66, 0x66, 0x66, 0x3E, 0x0C, 0x78}},
	{L'z', {0x00, 0x00, 0x7E, 0x0C, 0x18, 0x30, 0x7E, 0x00}},
	{L'{', {0x1C, 0x30, 0x30, 0x60, 0x30, 0x30, 0x1C, 0x00}}, // (based on C64 "[")
	{L'|', {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18}}, // (custom)
	{L'}', {0x38, 0x0C, 0x0C, 0x06, 0x0C, 0x0C, 0x38, 0x00}}, // (based on C64 "]")
	{L'~', {0x00, 0x00, 0x20, 0x5A, 0x04, 0x00, 0x00, 0x00}}, // (based on C64 "-") [TODO: Needs improvement.]
	
	// End of character set.
	{-1, {0}}
};
