#include "global.h"

#define BG_PALETTE_BUFFER_SIZE 512
#define BG_PALETTE_BUFFER_CHUNK_SIZE 16

extern u16 gBGPaletteBuffer[BG_PALETTE_BUFFER_SIZE];
extern bool8 gBGPaletteUsed[BG_PALETTE_BUFFER_SIZE / BG_PALETTE_BUFFER_CHUNK_SIZE];

extern void CpuCopy(void* src, void* dest, u32 size);

/*
void InitBGPaletteBuffer(void)
{
    u16 color = 0;
    u16* ptr;
    u32 i;
    bool8 paletteUsed;

    u8* p;

    ptr = gBGPaletteBuffer;

    i = 0x80;
    i <<= 2;

    do {
        *ptr++ = color;
        i--;
    } while (i);

    paletteUsed = TRUE;

    p = gBGPaletteUsed;
    p += 31;

    do
        *p-- = paletteUsed;
    while ((s32) p >= (s32) &gBGPaletteUsed);
}
void SetBGPaletteBufferColorRGB(s32 index, u8 *RGBArray, s32 a3, u8 *a4)
{
    if (a3 < 0) {
        a3 = 0;
    }
    if (a3 > 31) {
        a3 = 31;
    }
    gBGPaletteUsed[index / 16] = 1;
    if (!a4) {
        gBGPaletteBuffer[index] = ((RGBArray[2] * a3 / 256 & 0x1F) << 10) | ((RGBArray[1] * a3 / 256 & 0x1F) << 5) | (RGBArray[0] * a3 / 256 & 0x1F);
    }
    else
    {
        gBGPaletteBuffer[index] = ((a4[4 * RGBArray[2] + 2] * a3 / 256 & 0x1F) << 10) | ((a4[4 * RGBArray[1] + 1] * a3 / 256 & 0x1F) << 5) | (a4[4 * RGBArray[0]] * a3 / 256 & 0x1F);
    }
}
*/

void SetBGPaletteBufferColorArray(s32 index, u8 *colorArray)
{
    gBGPaletteUsed[index / BG_PALETTE_BUFFER_CHUNK_SIZE] = TRUE;
    gBGPaletteBuffer[index] = (colorArray[2] >> 3) << 10 | (colorArray[1] >> 3) << 5 | colorArray[0] >> 3;
}

void SetBGPaletteBufferColor(s32 index, u16 *color)
{
    gBGPaletteUsed[index / BG_PALETTE_BUFFER_CHUNK_SIZE] = TRUE;
    gBGPaletteBuffer[index] = *color;
}

void nullsub_4()
{

}
void nullsub_5(void)
{

}
void nullsub_143(void)
{

}

void TransferBGPaletteBuffer(void)
{
    u32 i;
    s32 paletteBufferIndex;
    u16 *dest;

    i = 0;
    paletteBufferIndex = 0;
    dest = (u16 *)PLTT;
    do
    {
        if (gBGPaletteUsed[i])
        {
            gBGPaletteUsed[i] = 0;
            CpuCopy(dest, &gBGPaletteBuffer[paletteBufferIndex], sizeof(u16) * 16);
        }
        ++i;
        dest += 16;
        paletteBufferIndex += 16;
    }
    while ( paletteBufferIndex < BG_PALETTE_BUFFER_SIZE );
}
