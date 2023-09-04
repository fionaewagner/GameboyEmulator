#include "../include/common.hpp"
#include "../include/cpu.hpp"
#include "../include/bus.hpp"
#include "../include/emu.hpp"
#include "../include/instructions.hpp"

//MAIN CHNAGE THAT NEEDS TO BE MADE IN THIS FILE:
//change the way we handle emu_cycles and bus_read
//right now we're passing them in as parameters to just get rid of the errors
//find a better way tho

//cpu needs to be able to run functions from: bus, emu
//bus needs to run fucntions from cpu, emu


void CPU::fetchData(std::function<u8(u16)> busRead , std::function<void(int)> emuCycles) {
    memDest = 0;
    destIsMem = false;

    if (curInst == nullptr) {
        return;
    }

    switch (curInst->getMode()) {
        case AddressMode::AM_IMP:
            return;

        case AddressMode::AM_R:
            fetchedData = cpuReadReg8(curInst->getReg1());
            return;

        case AddressMode::AM_R_R:
            fetchedData = cpuReadReg8(curInst->getReg2());
            return;

        case AddressMode::AM_R_D8:
            fetchedData = busRead(registers.pc); //fix ? 
            emuCycles(1); //also fix
            registers.pc++;
            return;

        case AddressMode::AM_R_D16:
        case AddressMode::AM_D16: {
            u16 lo = busRead(registers.pc);
            emuCycles(1);

            u16 hi = busRead(registers.pc + 1);
            emuCycles(1);

            fetchedData = lo | (hi << 8);

            registers.pc += 2;

            return;
        }

        case AddressMode::AM_MR_R:
            fetchedData = cpuReadReg8(curInst->getReg2());
            memDest = cpuReadReg16(curInst->getReg1());
            destIsMem = true;

            if (curInst->getReg1() == RegisterType::RT_C) {
                memDest |= 0xFF00;
            }

            return;

        case AddressMode::AM_R_MR: {
            u16 addr = cpuReadReg16(curInst->getReg2());

            if (curInst->getReg2() == RegisterType::RT_C) {
                addr |= 0xFF00;
            }

            fetchedData = busRead(addr);
            emuCycles(1);

        } return;

        case AddressMode::AM_R_HLI:
            fetchedData = busRead(cpuReadReg16(curInst->getReg2()));
            emuCycles(1);
            cpuSetReg16(RegisterType::RT_HL, cpuReadReg16(RegisterType::RT_HL) + 1);
            return;

        case AddressMode::AM_R_HLD:
            fetchedData = busRead(cpuReadReg16(curInst->getReg2()));
            emuCycles(1);
            cpuSetReg16(RegisterType::RT_HL, cpuReadReg16(RegisterType::RT_HL) - 1);
            return;

        case AddressMode::AM_HLI_R:
            fetchedData = cpuReadReg8(curInst->getReg2());
            memDest = cpuReadReg16(curInst->getReg1());
            destIsMem = true;
            cpuSetReg16(RegisterType::RT_HL, cpuReadReg16(RegisterType::RT_HL) + 1);
            return;

        case AddressMode::AM_HLD_R:
            fetchedData = cpuReadReg8(curInst->getReg2());
            memDest = cpuReadReg16(curInst->getReg1());
            destIsMem = true;
            cpuSetReg16(RegisterType::RT_HL, cpuReadReg16(RegisterType::RT_HL) - 1);
            return;

        case AddressMode::AM_R_A8:
            fetchedData = busRead(registers.pc);
            emuCycles(1);
            registers.pc++;
            return;

        case AddressMode::AM_A8_R:
            memDest = busRead(registers.pc) | 0xFF00;
            destIsMem = true;
            emuCycles(1);
            registers.pc++;
            return;

        case AddressMode::AM_HL_SPR:
            fetchedData = busRead(registers.pc);
            emuCycles(1);
            registers.pc++;
            return;

        case AddressMode::AM_D8:
            fetchedData = busRead(registers.pc);
            emuCycles(1);
            registers.pc++;
            return;

        case AddressMode::AM_A16_R:
        case AddressMode::AM_D16_R: {
            u16 lo = busRead(registers.pc);
            emuCycles(1);

            u16 hi = busRead(registers.pc + 1);
            emuCycles(1);

            memDest = lo | (hi << 8);
            destIsMem = true;

            registers.pc += 2;
            fetchedData = cpuReadReg8(curInst->getReg2());

        } return;

        case AddressMode::AM_MR_D8:
            fetchedData = busRead(registers.pc);
            emuCycles(1);
            registers.pc++;
            memDest = cpuReadReg16(curInst->getReg1());
            destIsMem = true;
            return;

        case AddressMode::AM_MR:
            memDest = cpuReadReg16(curInst->getReg1());
            destIsMem = true;
            fetchedData = busRead(cpuReadReg16(curInst->getReg1()));
            emuCycles(1);
            return;

        case AddressMode::AM_R_A16: {
            u16 lo = busRead(registers.pc);
            emuCycles(1);

            u16 hi = busRead(registers.pc + 1);
            emuCycles(1);

            u16 addr = lo | (hi << 8);

            registers.pc += 2;
            fetchedData = busRead(addr);
            emuCycles(1);

            return;
        }

        default:
            printf("Unknown Addressing Mode! %d (%02X)\n", static_cast<int>(curInst->getMode()), curOpcode);
            exit(-7);
            return;
    }
}