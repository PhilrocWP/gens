;
; Gens: [MDP] Interpolated Scanline renderer. [16-bit color] (x86 asm version)
;
; Copyright (c) 1999-2002 by Stéphane Dallongeville
; Copyright (c) 2003-2004 by Stéphane Akhoun
; Copyright (c) 2008-2009 by David Korth
;
; This program is free software; you can redistribute it and/or modify it
; under the terms of the GNU General Public License as published by the
; Free Software Foundation; either version 2 of the License, or (at your
; option) any later version.
;
; This program is distributed in the hope that it will be useful, but
; WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License along
; with this program; if not, write to the Free Software Foundation, Inc.,
; 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
;

; MDP NASM (x86) macros.
%include "mdp/mdp_nasm_x86.inc"

arg_destScreen	equ 28+8
arg_mdScreen	equ 28+12
arg_destPitch	equ 28+16
arg_srcPitch	equ 28+20
arg_width	equ 28+24
arg_height	equ 28+28
arg_mask	equ 28+32
arg_vmodeFlags	equ 28+32

; Symbol redefines for ELF.
%ifdef __OBJ_ELF
	%define	_mdp_render_interpolated_scanline_16_x86	mdp_render_interpolated_scanline_16_x86
	%define	_mdp_render_interpolated_scanline_16_x86_mmx	mdp_render_interpolated_scanline_16_x86_mmx
%endif

section .rodata align=64
	
	; 64-bit masks used for the mmx version.
	MASK_DIV2_15_MMX:	dd 0x3DEF3DEF, 0x3DEF3DEF
	MASK_DIV2_16_MMX:	dd 0x7BEF7BEF, 0x7BEF7BEF
	
section .text align=64
	
	align 64
	
	;************************************************************************
	; void mdp_render_interpolated_scanline_16_x86(uint16_t *destScreen, uint16_t *mdScreen,
	;					       int destPitch, int srcPitch,
	;					       int width, int height, uint32_t mask);
	global _mdp_render_interpolated_scanline_16_x86
	_mdp_render_interpolated_scanline_16_x86:
		
		; Save registers.
		pushad
		
		mov	ecx, [esp + arg_width]		; ecx = Number of pixels per line
		mov	ebp, [esp + arg_destPitch]	; ebp = Pitch of destination surface (bytes per line)
		mov	esi, [esp + arg_mdScreen]	; esi = Source
		add	ecx, ecx
		sub	[esp + arg_srcPitch], ecx	; arg_srcPitch = offset
		add	ecx, ecx			; ecx = Number of bytes per line
		sub	ebp, ecx			; ebp = Difference between dest pitch and src pitch
		mov	edi, [esp + arg_destScreen]	; edi = Destination
		shr	ecx, 2				; Transfer 4 bytes per cycle. (2 16-bit pixels)
		mov	[esp + arg_width], ecx		; Initialize the X counter.
		jmp	short .Loop_Y
	
	align 64
	
	.Loop_Y:
	.Loop_X1:
				mov	ax, [esi]
				mov	dx, [esi + 2]
				add	esi, byte 2
				
				shr	ax, 1
				shr	dx, 1
				and	ax, [esp + arg_mask]
				and	dx, [esp + arg_mask]
				
				add	ax, dx
				mov	dx, [esi]
				mov	[edi], ax
				mov	[edi + 2], dx
				add	edi, byte 4
				
				dec	ecx
				jnz	short .Loop_X1
			
			mov	ecx, [esp + arg_width]	; ecx = Number of pixels per line
			shr	ecx, 2			; Black out 16 bytes (8 16-bit pixels) per cycle.
			add	edi, ebp		; Add the destination pitch difference.
			xor	edx, edx		; Scanlines are all black.
			jmp	short .Loop_X2
	
	align 64
	
	.Loop_X2:
				mov	[edi], edx
				mov	[edi + 4], edx
				mov	[edi + 8], edx
				mov	[edi + 12], edx
				add	edi, 16
				
				dec ecx
				jnz short .Loop_X2
			
			add	esi, [esp + arg_srcPitch]	; Add the source pitch difference.
			add	edi, ebp			; Add the destination pitch difference.
			mov	ecx, [esp + arg_width]		; Reset the X conuter.
			dec	dword [esp + arg_height]	; Decrement the Y counter.
			jnz	near .Loop_Y
		
		; Restore registers.
		popad
		ret
	
	align 64
	
	;************************************************************************
	; void mdp_render_interpolated_scanline_16_x86_mmx(uint16_t *destScreen, uint16_t *mdScreen,
	;						   int destPitch, int srcPitch,
	;						   int width, int height, uint32_t vmodeFlags);
	global _mdp_render_interpolated_scanline_16_x86_mmx
	_mdp_render_interpolated_scanline_16_x86_mmx:
		
		; Save registers.
		pushad
		
		; (PIC) Get the Global Offset Table.
		get_GOT
		
		mov	ecx, [esp + arg_width]		; ecx = Number of pixels per line
		mov	ebp, [esp + arg_destPitch]	; ebp = Pitch of destination surface (bytes per line)
		mov	esi, [esp + arg_mdScreen]	; esi = Source
		add	ecx, ecx
		sub	[esp + arg_srcPitch], ecx	; arg_srcPitch = offset
		add	ecx, ecx			; ecx = Number of bytes per line
		sub	ebp, ecx			; ebp = Difference between dest pitch and src pitch
		mov	edi, [esp + arg_destScreen]	; edi = Destination
		shr	ecx, 4				; Transfer 16 bytes per cycle. (8 16-bit pixels)
		mov	[esp + arg_width], ecx		; Initialize the X counter.
		
		; Initialize the mask.
		
		; Default to 16-bit color. (Mode 565)
		get_movq_localvar	mm7, MASK_DIV2_16_MMX
		test	byte [esp + arg_vmodeFlags], 1
		jnz	short .Loop_Y
		
		; 15-bit color is specified. (Mode 555)
		get_movq_localvar	mm7, MASK_DIV2_15_MMX
		jmp	short .Loop_Y
	
	align 64
	
	.Loop_Y:
	.Loop_X1:
				; Get source pixels.
				movq		mm0, [esi]
				movq		mm2, mm0
				movq		mm1, [esi + 2]
				add		esi, byte 8
				
				; Interpolate the pixels.
				psrlw		mm0, 1
				psrlw		mm1, 1
				pand		mm0, mm7
				pand		mm1, mm7
				movq		mm3, mm2
				paddw		mm0, mm1
				punpcklwd	mm2, mm0
				punpckhwd	mm3, mm0
				
				; Put destination pixels.
				movq		[edi], mm2
				movq		[edi + 8], mm3
				add		edi, byte 16
				
				; Next group of pixels.
				dec		ecx
				jnz		short .Loop_X1
			
			mov	ecx, [esp + arg_width]	; Reset the X counter.
			add	edi, ebp		; Add the destination pitch difference.
			shr	ecx, 2			; Black out 64 bytes (32 16-bit pixels) per cycle.
			pxor	mm0, mm0		; Scanlines are all black.
			jmp	short .Loop_X2
	
	align 64
	
	.Loop_X2:
				; Black out the scanline.
				movq	[edi], mm0
				movq	[edi + 8], mm0
				movq	[edi + 16], mm0
				movq	[edi + 24], mm0
				movq	[edi + 32], mm0
				movq	[edi + 40], mm0
				movq	[edi + 48], mm0
				movq	[edi + 56], mm0
				add	edi, byte 64
				
				; Next group of pixels.
				dec	ecx
				jnz	short .Loop_X2
			
			add	esi, [esp + arg_srcPitch]	; Add the source pitch difference.
			add	edi, ebp			; Add the destination pitch difference.
			mov	ecx, [esp + arg_width]		; Reset the X conuter.
			dec	dword [esp + arg_height]	; Decrement the Y counter.
			jnz	near .Loop_Y
		
		; Restore registers.
		emms
		popad
		ret
