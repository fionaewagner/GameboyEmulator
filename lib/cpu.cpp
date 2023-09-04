#include "../include/common.hpp"
#include "../include/cpu.hpp"
#include "../include/emu.hpp"
#include "../include/bus.hpp"
#include "../include/instructions.hpp"
#include "../include/interrupts.hpp"
#include "../include/dbg.hpp"
#include "../include/common.hpp"
#include <iostream>
#include <iomanip>


#define CPU_DEBUG 0

void emuCycles(int numCycle) {
    std::cout << "emuCycles called with numCycle: " << numCycle << std::endl;
}

CPU::CPU() {
    registers.pc = 0x100;
    registers.sp = 0xFFFE;
    *((u16 *)&registers.a) = 0xB001;
    *((u16 *)&registers.b) = 0x1300;
    *((u16 *)&registers.d) = 0xD800;
    *((u16 *)&registers.h) = 0x4D01;
    ieRegister = 0;
    flags = 0;
    intMasterEnabled = false;
    enablingIME = false;

    // fix this
    timer_get_context()->div = 0xABCC;
}

void CPU::fetchInstruction() {
    u8 opcode = bus.read(registers.pc++);
    curOpcode = opcode;
    curInst = &InstructionManager::instructionByOpcode(opcode);
}

void fetch_data();


bool CPU::step() {
    if (!isHalted()) {
        u16 pc = registers.pc;

        fetchData();
        emuCycles(1);
        fetchInstruction();
        fetchData();  // Fetch data after instruction fetch

#if CPU_DEBUG == 1
        std::string flags = "";
        flags += registers.f & (1 << static_cast<int>(Flag::Z)) ? 'Z' : '-';
        flags += registers.f & (1 << static_cast<int>(Flag::N)) ? 'N' : '-';
        flags += registers.f & (1 << static_cast<int>(Flag::H)) ? 'H' : '-';
        flags += registers.f & (1 << static_cast<int>(Flag::C)) ? 'C' : '-';

        std::string inst = "inst"; // Replace with actual inst_to_str function if available

        std::cout << std::hex << std::setfill('0') << std::setw(8) << emu_get_context()->ticks
                  << " - " << std::setw(4) << pc << ": " << std::setw(12) << inst
                  << " (" << std::setw(2) << curOpcode << " " << std::setw(2) << bus_read(pc + 1)
                  << " " << std::setw(2) << bus_read(pc + 2) << ") A: " << std::setw(2) << std::hex
                  << static_cast<int>(registers.a) << " F: " << flags << " BC: " << std::hex
                  << std::setw(4) << static_cast<int>(registers.b << 8 | registers.c)
                  << " DE: " << std::setw(4) << static_cast<int>(registers.d << 8 | registers.e)
                  << " HL: " << std::setw(4) << static_cast<int>(registers.h << 8 | registers.l) << std::endl;
#endif

        if (curInst == nullptr) {
            std::cout << "Unknown Instruction! " << std::hex << static_cast<int>(curOpcode) << std::endl;
            exit(-7);
        }

        //dbg_update();
        //dbg_print();

        // Call the execute function of the current instruction
        curInst->execute(); // No need to pass 'this'
    } else {
        // CPU is halted...
        emuCycles(1);

        // Check if any interrupt flags are set and unhalt if necessary
        if (isIntMasterEnabled() && (getIERegister() & registers.f)) {
            setHalted(false);
        }
    }

    if (isIntMasterEnabled()) {
        handleInterrupts();
        setEnablingIME(false);
    }

    if (isEnablingIME()) {
        setIntMasterEnabled(true);
    }

    return true;
}
u8 CPU::getIERegister() const {
    return ieRegister;
}

void CPU::setIERegister(u8 n) {
    ieRegister = n;
}

void CPU::requestInterrupt(InterruptType t) {
    setFlag(static_cast<Flag>(static_cast<u8>(t)), true);
}
