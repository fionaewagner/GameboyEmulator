#include "../include/dma.hpp"
#include "../include/ppu.hpp"
#include "../include/bus.hpp"

void DMA::start(u8 start) {
    isActive = true;
    dmaByte = 0;
    startDelay = 2;
    dmaValue = start;
}
void DMA::tick() {
        if (!isActive) {
            return;
        }

        if (startDelay) {
            startDelay--;
            return;
        }

        //fix this with the real ppu and bus
        PPU::oamWrite(dmaByte, Bus::busRead((dmaValue * 0x100) + dmaByte));

        dmaByte++;

        isActive = dmaByte < 0xA0;
}

bool DMA::isTransferring() const {
        return isActive;
}
