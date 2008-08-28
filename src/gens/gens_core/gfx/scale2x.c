#include "vdp_rend.h"
#include "blit.h"
#include "byteswap.h"


extern unsigned char Bits32;


static void Blit_Scale2x_16(unsigned char *screen, int pitch, int x, int y, int offset);
static void Blit_Scale2x_32(unsigned char *screen, int pitch, int x, int y, int offset);


/**
 * Blit_Scale2x(): Blits the image to the screen, scaled to 2x its normal size (without filtering).
 * @param screen Screen buffer.
 * @param pitch Number of bytes per line.
 * @param x X coordinate for the image.
 * @param y Y coordinate for the image.
 * @param offset ???
 */
void Blit_Scale2x(unsigned char *screen, int pitch, int x, int y, int offset)
{
	if (Bits32)
		Blit_Scale2x_32(screen, pitch, x, y, offset);
	else
		Blit_Scale2x_16(screen, pitch, x, y, offset);
}


/**
 * Blit_Scale2x_16(): (16-bit) Blits the image to the screen, scaled to 2x its normal size (without filtering).
 * @param screen Screen buffer.
 * @param pitch Number of bytes per line.
 * @param x X coordinate for the image.
 * @param y Y coordinate for the image.
 * @param offset ???
 */
static void Blit_Scale2x_16(unsigned char *screen, int pitch, int x, int y, int offset)
{
	int i, j;
	unsigned short B, D, E, F, H;
	unsigned short E0, E1, E2, E3;
	
	// A B C
	// D E F
	// G H I
	
	int ScrWdth, ScrAdd;
	int SrcOffs, DstOffs;
	
	// Use an unsigned short* to make things easier.
	unsigned short *dst = (unsigned short*)screen;
	
	ScrAdd = offset >> 1;
	ScrWdth = x + ScrAdd;
	
	SrcOffs = 8;
	DstOffs = 0;
	
	for (i = 0; i < y; i++)
	{
		E = MD_Screen[SrcOffs - 1];
		F = MD_Screen[SrcOffs];
		
		DstOffs = i * pitch;
		
		for (j = 0; j < x; j++)
		{
			D = E; E = F;
			B = MD_Screen[SrcOffs - ScrWdth];
			H = MD_Screen[SrcOffs + ScrWdth];
			F = MD_Screen[++SrcOffs];
			E0 = D == B && B != F && D != H ? D : E;
			E1 = B == F && B != D && F != H ? F : E;
			E2 = D == H && D != B && H != F ? D : E;
			E3 = H == F && D != H && B != F ? F : E;
			
			// Copy the new pixels.
			dst[DstOffs + 0] = E0;
			dst[DstOffs + 1] = E1;
			dst[DstOffs + (pitch / 2) + 0] = E2;
			dst[DstOffs + (pitch / 2) + 1] = E3;
			
			// Next group of pixels.
			DstOffs += 2;
		}
		
		SrcOffs += ScrAdd;
	}
}


/**
 * Blit_Scale2x_32(): (32-bit) Blits the image to the screen, scaled to 2x its normal size (without filtering).
 * @param screen Screen buffer.
 * @param pitch Number of bytes per line.
 * @param x X coordinate for the image.
 * @param y Y coordinate for the image.
 * @param offset ???
 */
static void Blit_Scale2x_32(unsigned char *screen, int pitch, int x, int y, int offset)
{
	int i, j;
	unsigned int B, D, E, F, H;
	unsigned int E0, E1, E2, E3;
	
	// A B C
	// D E F
	// G H I
	
	int ScrWdth, ScrAdd;
	int SrcOffs, DstOffs;
	
	// Use an unsigned int* to make things easier.
	unsigned int *dst = (unsigned int*)screen;
	
	ScrAdd = offset >> 1;
	ScrWdth = x + ScrAdd;
	
	SrcOffs = 8;
	DstOffs = 0;
	
	for (i = 0; i < y; i++)
	{
		E = MD_Screen32[SrcOffs - 1];
		F = MD_Screen32[SrcOffs];
		
		DstOffs = i * (pitch / 2);
		
		for (j = 0; j < x; j++)
		{
			D = E; E = F;
			B = MD_Screen32[SrcOffs - ScrWdth];
			H = MD_Screen32[SrcOffs + ScrWdth];
			F = MD_Screen32[++SrcOffs];
			E0 = D == B && B != F && D != H ? D : E;
			E1 = B == F && B != D && F != H ? F : E;
			E2 = D == H && D != B && H != F ? D : E;
			E3 = H == F && D != H && B != F ? F : E;
			
			// Copy the new pixels.
			dst[DstOffs + 0] = E0;
			dst[DstOffs + 1] = E1;
			dst[DstOffs + (pitch / 4) + 0] = E2;
			dst[DstOffs + (pitch / 4) + 1] = E3;
			
			// Next group of pixels.
			DstOffs += 2;
		}
		
		SrcOffs += ScrAdd;
	}
}
