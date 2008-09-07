/***************************************************************************
 * Gens: Commodore 64 Character Set.                                       *
 *                                                                         *
 * Copyright (c) 1982 Commodore International                              *
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

/***************************************************
 * Format: 8 bytes per character, 8 bits per line. *
 * 1 == opaque dot; 0 == transparent dot           *
 * MSB == left-most dot; LSB == right-most dot     *
 *                                                 *
 * Character set is cp437                          *
 ***************************************************/

const unsigned char C64_charset[256][8] =
{
	// 0x00 - 0x0F
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// NULL
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ☺ [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ☻ [TODO]
	{0x36, 0x7F, 0x7F, 0x7F, 0x3E, 0x1C, 0x08, 0x00},	// ♥
	{0x08, 0x1C, 0x3E, 0x7F, 0x3E, 0x1C, 0x08, 0x00},	// ♦
	{0x18, 0x18, 0x66, 0x66, 0x18, 0x18, 0x3C, 0x00},	// ♣
	{0x08, 0x1C, 0x3E, 0x7F, 0x7F, 0x1C, 0x3E, 0x00},	// ♠
	{0x00, 0x3C, 0x7E, 0x7E, 0x7E, 0x7E, 0x3C, 0x00},	// •
	{0xFF, 0xC3, 0x81, 0x81, 0x81, 0x81, 0xC3, 0xFF},	// ◘
	{0x00, 0x3C, 0x7E, 0x66, 0x66, 0x7E, 0x3C, 0x00},	// ○
	{0xFF, 0xC3, 0x81, 0x99, 0x99, 0x81, 0xC3, 0xFF},	// ◙
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ♂ [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ♀ [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ♪ [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ♫ [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ☼ [TODO]
	
	// 0x10 - 0x1F
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ► [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ◄ [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ↕ [TODO]
	{0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x66, 0x00},	// ‼
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ¶ [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// § [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ▬ [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ↨ [TODO]
	{0x00, 0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x18},	// ↑
	{0x00, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x3C, 0x18},	// ↓
	{0x00, 0x04, 0x06, 0x7F, 0x7F, 0x06, 0x04, 0x00},	// →
	{0x00, 0x10, 0x30, 0x7F, 0x7F, 0x30, 0x10, 0x00},	// ←
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ∟ [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ↔ [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ▲ [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ▼ [TODO]
	
	// 0x20 - 0x2F
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// Space
	{0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00},	// !
	{0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00},	// "
	{0x66, 0x66, 0xFF, 0x66, 0xFF, 0x66, 0x66, 0x00},	// #
	{0x18, 0x3E, 0x60, 0x3C, 0x06, 0x7C, 0x18, 0x00},	// $
	{0x62, 0x66, 0x0C, 0x18, 0x30, 0x66, 0x46, 0x00},	// %
	{0x3C, 0x66, 0x3C, 0x38, 0x67, 0x66, 0x3F, 0x00},	// &
	{0x06, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},	// '
	{0x0C, 0x18, 0x30, 0x30, 0x30, 0x18, 0x0C, 0x00},	// (
	{0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x18, 0x30, 0x00},	// )
	{0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00},	// *
	{0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00},	// +
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1C, 0x30},	// ,
	{0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00},	// -
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00},	// .
	{0x00, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00},	// /
	
	// 0x30 - 0x3F
	{0x3C, 0x66, 0x6E, 0x76, 0x66, 0x66, 0x3C, 0x00},	// 0
	{0x18, 0x18, 0x38, 0x18, 0x18, 0x18, 0x7E, 0x00},	// 1
	{0x3C, 0x66, 0x06, 0x0C, 0x30, 0x60, 0x7E, 0x00},	// 2
	{0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C, 0x00},	// 3
	{0x06, 0x0E, 0x1E, 0x66, 0x7F, 0x06, 0x06, 0x00},	// 4
	{0x7E, 0x60, 0x7C, 0x06, 0x06, 0x66, 0x3C, 0x00},	// 5
	{0x3C, 0x66, 0x60, 0x7C, 0x66, 0x66, 0x3C, 0x00},	// 6
	{0x7E, 0x66, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x00},	// 7
	{0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C, 0x00},	// 8
	{0x3C, 0x66, 0x66, 0x3E, 0x06, 0x66, 0x3C, 0x00},	// 9
	{0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00},	// :
	{0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x30},	// ;
	{0x0E, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0E, 0x00},	// <
	{0x00, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x00, 0x00},	// =
	{0x70, 0x18, 0x0C, 0x06, 0x0C, 0x18, 0x70, 0x00},	// >
	{0x3C, 0x66, 0x06, 0x0C, 0x18, 0x00, 0x18, 0x00},	// ?
	
	// 0x40 - 0x4F
	{0x3C, 0x66, 0x6E, 0x6E, 0x60, 0x62, 0x3C, 0x00},	// @
	{0x18, 0x3C, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00},	// A
	{0x7C, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x7C, 0x00},	// B
	{0x3C, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3C, 0x00},	// C
	{0x78, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0x78, 0x00},	// D
	{0x7E, 0x60, 0x60, 0x78, 0x60, 0x60, 0x7E, 0x00},	// E
	{0x7E, 0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x00},	// F
	{0x3C, 0x66, 0x60, 0x6E, 0x66, 0x66, 0x3C, 0x00},	// G
	{0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00},	// H
	{0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00},	// I
	{0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x6C, 0x38, 0x00},	// J
	{0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x66, 0x00},	// K
	{0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x00},	// L
	{0x63, 0x77, 0x7F, 0x6B, 0x63, 0x63, 0x63, 0x00},	// M
	{0x66, 0x76, 0x7E, 0x7E, 0x6E, 0x66, 0x66, 0x00},	// N
	{0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00},	// O
	
	// 0x50 - 0x5F
	{0x7C, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x00},	// P
	{0x3C, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x0E, 0x00},	// Q
	{0x7C, 0x66, 0x66, 0x7C, 0x78, 0x6C, 0x66, 0x00},	// R
	{0x3C, 0x66, 0x60, 0x3C, 0x06, 0x66, 0x3C, 0x00},	// S
	{0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00},	// T
	{0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00},	// U
	{0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00},	// V
	{0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00},	// W
	{0x66, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x66, 0x00},	// X
	{0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x00},	// Y
	{0x7E, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x7E, 0x00},	// Z
	{0x3C, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3C, 0x00},	// [
	{0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x00},	// Backslash
	{0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x3C, 0x00},	// ]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ^ [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},	// _
	
	// 0x60 - 0x6F
	{0x60, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},	// `
	{0x00, 0x00, 0x3C, 0x06, 0x3E, 0x66, 0x3E, 0x00},	// a
	{0x00, 0x60, 0x60, 0x7C, 0x66, 0x66, 0x7C, 0x00},	// b
	{0x00, 0x00, 0x3C, 0x60, 0x60, 0x60, 0x3C, 0x00},	// c
	{0x00, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3E, 0x00},	// d
	{0x00, 0x00, 0x3C, 0x66, 0x7E, 0x60, 0x3C, 0x00},	// e
	{0x00, 0x0E, 0x18, 0x3E, 0x18, 0x18, 0x18, 0x00},	// f
	{0x00, 0x00, 0x3E, 0x66, 0x66, 0x3E, 0x06, 0x7C},	// g
	{0x00, 0x60, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x00},	// h
	{0x00, 0x18, 0x00, 0x38, 0x18, 0x18, 0x3C, 0x00},	// i
	{0x00, 0x06, 0x00, 0x06, 0x06, 0x06, 0x06, 0x3C},	// j
	{0x00, 0x60, 0x60, 0x6C, 0x78, 0x6C, 0x66, 0x00},	// k
	{0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00},	// l
	{0x00, 0x00, 0x66, 0x7F, 0x7F, 0x6B, 0x63, 0x00},	// m
	{0x00, 0x00, 0x7C, 0x66, 0x66, 0x66, 0x66, 0x00},	// n
	{0x00, 0x00, 0x3C, 0x66, 0x66, 0x66, 0x3C, 0x00},	// o
	
	// 0x70 - 0x7F
	{0x00, 0x00, 0x7C, 0x66, 0x66, 0x7C, 0x60, 0x60},	// p
	{0x00, 0x00, 0x3E, 0x66, 0x66, 0x3E, 0x06, 0x06},	// q
	{0x00, 0x00, 0x7C, 0x66, 0x60, 0x60, 0x60, 0x00},	// r
	{0x00, 0x00, 0x3E, 0x60, 0x3C, 0x06, 0x7C, 0x00},	// s
	{0x00, 0x18, 0x7E, 0x18, 0x18, 0x18, 0x0E, 0x00}, 	// t
	{0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3E, 0x00},	// u
	{0x00, 0x00, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00},	// v
	{0x00, 0x00, 0x63, 0x6B, 0x7F, 0x3E, 0x36, 0x00},	// w
	{0x00, 0x00, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x00},	// x
	{0x00, 0x00, 0x66, 0x66, 0x66, 0x3E, 0x0C, 0x78},	// y
	{0x00, 0x00, 0x7E, 0x0C, 0x18, 0x30, 0x7E, 0x00},	// z
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// { [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// | [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// } [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ~ [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// ⌂ [TODO]
	
	// 0x80 - 0x8F
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	
	// 0x90 - 0x9F
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	
	// 0xA0 - 0xAF
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	
	// 0xB0 - 0xBF
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	
	// 0xC0 - 0xCF
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	
	// 0xD0 - 0xDF
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	
	// 0xE0 - 0xEF
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	
	// 0xF0 - 0xFF
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	// [TODO]
};
