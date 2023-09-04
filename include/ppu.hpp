#pragma once

#include "common.hpp"


/*
 Bit7   BG and Window over OBJ (0=No, 1=BG and Window colors 1-3 over the OBJ)
 Bit6   Y flip          (0=Normal, 1=Vertically mirrored)
 Bit5   X flip          (0=Normal, 1=Horizontally mirrored)
 Bit4   Palette number  **Non CGB Mode Only** (0=OBP0, 1=OBP1)
 Bit3   Tile VRAM-Bank  **CGB Mode Only**     (0=Bank 0, 1=Bank 1)
 Bit2-0 Palette number  **CGB Mode Only**     (OBP0-7)
 */

enum class FetchState {
    FS_TILE,
    FS_DATA0,
    FS_DATA1,
    FS_IDLE,
    FS_PUSH
};

enum class PPUMode {
    OAM,
    XFER,
    VBLANK,
    HBLANK
};

class FIFOEntry {
public:
    FIFOEntry();

    void setValue(u32 value);
    u32 getValue() const;

    void setNext(FIFOEntry* next);
    FIFOEntry* getNext() const;

private:
    u32 value; // 32-bit color value.
    FIFOEntry* next;
};

class FIFO {
public:
    FIFO();

    void push(u32 value);
    u32 pop();
    bool isEmpty() const;
    u32 getSize() const;

    void setHead(FIFOEntry* head);
    FIFOEntry* getHead() const;

    void setTail(FIFOEntry* tail);
    FIFOEntry* getTail() const;

    void setSize(u32 size);
    u32 getSize() const;

private:
    FIFOEntry* head;
    FIFOEntry* tail;
    u32 size;
};

struct PixelFIFOContext {
    FetchState curFetchState;
    FIFO pixelFIFO;
    u8 lineX;
    u8 pushedX;
    u8 fetchX;
    u8 bgwFetchData[3];
    u8 fetchEntryData[6]; // OAM data..
    u8 mapY;
    u8 mapX;
    u8 tileY;
    u8 fifoX;
};

struct OAMEntry {
    u8 y;
    u8 x;
    u8 tile;
    u8 fCgbPn : 3;
    u8 fCgbVramBank : 1;
    u8 fPn : 1;
    u8 fXFlip : 1;
    u8 fYFlip : 1;
    u8 fBgp : 1;
};

class OAMLineEntry {
public:
    OAMLineEntry();

    void setEntry(OAMEntry entry);
    OAMEntry getEntry() const;

    void setNext(OAMLineEntry* next);
    OAMLineEntry* getNext() const;

private:
    OAMEntry entry;
    OAMLineEntry* next;
};

class PPU {
public:
    PPU();

    void init();
    void tick();

    void oamWrite(u16 address, u8 value);
    u8 oamRead(u16 address);

    void vramWrite(u16 address, u8 value);
    u8 vramRead(u16 address);

    void setCurrentFrame(u32 frame);
    u32 getCurrentFrame() const;

    void setLineTicks(u32 ticks);
    u32 getLineTicks() const;

    void setVideoBuffer(u32* buffer);
    u32* getVideoBuffer() const;

    void setWindowLine(u8 line);
    u8 getWindowLine() const;

    void modeOAM();
    void modeXfer();
    void modeVBlank();
    void modeHBlank();

private:
    OAMEntry oamRam[40];
    u8 vram[0x2000];

    PixelFIFOContext pfc;

    u8 lineSpriteCount; // 0 to 10 sprites.
    OAMLineEntry* lineSprites; // Linked list of current sprites on line.
    OAMLineEntry lineEntryArray[10]; // Memory to use for the list.

    u8 fetchedEntryCount;
    OAMEntry fetchedEntries[3]; // Entries fetched during pipeline.
    u8 windowLine;

    u32 currentFrame;
    u32 lineTicks;
    u32* videoBuffer;
    
};