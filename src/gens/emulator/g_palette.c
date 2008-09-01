/**
 * GENS: Palette handler.
 */


#include "g_palette.h"
#include "g_main.h"
#include "gens_core/vdp/vdp_rend.h"
#include "gens_core/vdp/vdp_32x.h"


int RMax_Level;
int GMax_Level;
int BMax_Level;
int Contrast_Level;
int Brightness_Level;
int Greyscale;
int Invert_Color;


/**
 * Constrain_Color_Component(): Constrains a color component.
 * @param c Color component.
 * @return Constrained color component.
 */
inline int Constrain_Color_Component(int c)
{
	if (c < 0)
		return 0;
	else if (c > 0x3F)
		return 0x3F;
	return c;
}


/**
 * CalculateGrayScale(): Calculates grayscale color values.
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 * @return Grayscale value.
 */
inline int CalculateGrayScale(int r, int g, int b)
{
	// Standard grayscale computation: Y = R*0.30 + G*0.59 + B*0.11
	r = (r * (unsigned int) (0.30 * 65536.0)) >> 16;
	g = (g * (unsigned int) (0.59 * 65536.0)) >> 16;
	b = (b * (unsigned int) (0.11 * 65536.0)) >> 16;
	return (r + g + b);
}


/**
 * Recalculate_Palettes(): Recalculates the MD and 32X palettes for brightness, contrast, and various effects.
 */
void Recalculate_Palettes(void)
{
	int i;
	int r, g, b;
	int rf, gf, bf;
	int bright, cont;
	unsigned short color;
	
	// Calculate the MD palette.
	for (r = 0; r < 0x10; r++)
	{
		for (g = 0; g < 0x10; g++)
		{
			for (b = 0; b < 0x10; b++)
			{
				color = (b << 8) | (g << 4) | r;
				
				rf = (r & 0xE) << 2;
				gf = (g & 0xE) << 2;
				bf = (b & 0xE) << 2;
				
				rf = (int) (double) (rf) * (int) ((double) (RMax_Level) / 224.0);
				gf = (int) (double) (gf) * (int) ((double) (GMax_Level) / 224.0);
				bf = (int) (double) (bf) * (int) ((double) (BMax_Level) / 224.0);
				
				// Compute colors here (64 levels)
				
				bright = Brightness_Level;
				bright -= 100;
				bright *= 32;
				bright /= 100;
				
				rf += bright;
				gf += bright;
				bf += bright;
				
				rf = Constrain_Color_Component(rf);
				gf = Constrain_Color_Component(gf);
				bf = Constrain_Color_Component(bf);
				
				cont = Contrast_Level;
				
				rf = (rf * cont) / 100;
				gf = (gf * cont) / 100;
				bf = (bf * cont) / 100;
				
				rf = Constrain_Color_Component(rf);
				gf = Constrain_Color_Component(gf);
				bf = Constrain_Color_Component(bf);
				
				// 32-bit palette
				Palette32[color] = (rf << 18) | (gf << 10) | (bf << 2);
				
				// 16-bit palette
				if (bpp == 15)
				{
					rf = (rf >> 1) << 10;
					gf = (gf >> 1) << 5;
				}
				else
				{
					rf = (rf >> 1) << 11;
					gf = (gf >> 0) << 5;
				}
				bf = (bf >> 1) << 0;
				
				Palette[color] = rf | gf | bf;
			}
		}
	}
	
	// Calculate the 32X palette.
	for (i = 0; i < 0x10000; i++)
	{
		bf = ((i >> 10) & 0x1F) << 1;
		gf = ((i >> 5) & 0x1F) << 1;
		rf = ((i >> 0) & 0x1F) << 1;
		
		rf = (int) (double) (rf) * (int) ((double) (RMax_Level) / 248.0);
		gf = (int) (double) (gf) * (int) ((double) (GMax_Level) / 248.0);
		bf = (int) (double) (bf) * (int) ((double) (BMax_Level) / 248.0);
		
		// Compute colors here (64 levels)
		
		bright = Brightness_Level;
		bright -= 100;
		bright *= 32;
		bright /= 100;
		
		rf += bright;
		gf += bright;
		bf += bright;
		
		rf = Constrain_Color_Component(rf);
		gf = Constrain_Color_Component(gf);
		bf = Constrain_Color_Component(bf);
		
		cont = Contrast_Level;
		
		rf = (rf * cont) / 100;
		gf = (gf * cont) / 100;
		bf = (bf * cont) / 100;
		
		rf = Constrain_Color_Component(rf);
		gf = Constrain_Color_Component(gf);
		bf = Constrain_Color_Component(bf);
		
		// 32-bit palette
		_32X_Palette_32B[i] = (rf << 18) | (gf << 10) | (bf << 2);
		
		// 16-bit palette
		if (bpp == 15)
		{
			rf = (rf >> 1) << 10;
			gf = (gf >> 1) << 5;
		}
		else
		{
			rf = (rf >> 1) << 11;
			gf = (gf >> 0) << 5;
		}
		bf = (bf >> 1) << 0;
		
		_32X_Palette_16B[i] = rf | gf | bf;
	}
	
	// Convert colors to grayscale, if necessary.
	if (Greyscale)
	{
		// MD palette.
		for (i = 0; i < 0x1000; i++)
		{
			r = (Palette32[i] >> 16) & 0xFF;
			g = (Palette32[i] >> 8) & 0xFF;
			b = Palette32[i] & 0xFF;
			
			r = g = b = CalculateGrayScale(r, g, b);
			
			// 32-bit color
			Palette32[i] = (r << 16) | (g << 8) | b;
			
			// 15/16-bit color
			if (bpp == 15)
			{
				r = ((r >> 3) & 0x1F) << 10;
				g = ((g >> 3) & 0x1F) << 5;
			}
			else
			{
				r = ((r >> 3) & 0x1F) << 11;
				g = ((g >> 2) & 0x3F) << 5;
			}
			b = (b >> 3) & 0x1F;
			
			Palette[i] = r | g | b;
		}
		
		// 32X palette.
		for (i = 0; i < 0x10000; i++)
		{
			r = (_32X_Palette_32B[i] >> 16) & 0xFF;
			g = (_32X_Palette_32B[i] >> 8) & 0xFF;
			b = _32X_Palette_32B[i] & 0xFF;
			
			r = g = b = CalculateGrayScale(r, g, b);
			
			// 32-bit color
			_32X_Palette_32B[i] = (r << 16) | (g << 8) | b;
			
			// 15/16-bit color
			if (bpp == 15)
			{
				r = ((r >> 3) & 0x1F) << 10;
				g = ((g >> 3) & 0x1F) << 5;
			}
			else
			{
				r = ((r >> 3) & 0x1F) << 11;
				g = ((g >> 2) & 0x3F) << 5;
			}
			b = (b >> 3) & 0x1F;
			
			_32X_Palette_16B[i] = r | g | b;
		}
	}
	
	// Invert colors, if necessary.
	if (Invert_Color)
	{
		// MD palette.
		for (i = 0; i < 0x1000; i++)
		{
			Palette[i] ^= 0xFFFF;
			Palette32[i] ^= 0xFFFFFF;
		}
		
		// 32X palette.
		for (i = 0; i < 0x10000; i++)
		{
			_32X_Palette_16B[i] ^= 0xFFFF;
			_32X_Palette_32B[i] ^= 0xFFFFFF;
		}
	}
	
	// Adjust 32X VDP CRAM.
	for (i = 0; i < 0x100; i++)
	{
		_32X_VDP_CRam_Ajusted[i] = _32X_Palette_16B[_32X_VDP_CRam[i]];
		_32X_VDP_CRam_Ajusted32[i] = _32X_Palette_32B[_32X_VDP_CRam[i]];
	}
}
