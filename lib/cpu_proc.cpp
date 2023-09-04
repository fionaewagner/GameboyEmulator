#include "../include/common.hpp"
#include "../include/cpu.hpp"
#include "../include/emu.hpp"
#include "../include/bus.hpp"
#include "../include/stack.hpp"
#include "../include/instructions.hpp"

//processes CPU instructions...

//possibly move this 
void Instruction::execute() {
        switch (type) {
            case InstructionType::IN_NONE:
                procNone();
                break;
            case InstructionType::IN_NOP:
                procNop();
                break;
            case InstructionType::IN_LD:
                procLd();
                break;
            case InstructionType::IN_LDH:
                procLdh();
                break;
            case InstructionType::IN_JP:
                procJp();
                break;
            case InstructionType::IN_DI:
                procDi();
                break;
            case InstructionType::IN_POP:
                procPop();
                break;
            case InstructionType::IN_PUSH:
                procPush();
                break;
            case InstructionType::IN_JR:
                procJr();
                break;
            case InstructionType::IN_CALL:
                procCall();
                break;
            case InstructionType::IN_RET:
                procRet();
                break;
            case InstructionType::IN_RST:
                procRst();
                break;
            case InstructionType::IN_DEC:
                procDec();
                break;
            case InstructionType::IN_INC:
                procInc();
                break;
            case InstructionType::IN_ADD:
                procAdd();
                break;
            case InstructionType::IN_ADC:
                procAdc();
                break;
            case InstructionType::IN_SUB:
                procSub();
                break;
            case InstructionType::IN_SBC:
                procSbc();
                break;
            case InstructionType::IN_AND:
                procAnd();
                break;
            case InstructionType::IN_XOR:
                procXor();
                break;
            case InstructionType::IN_OR:
                procOr();
                break;
            case InstructionType::IN_CP:
                procCp();
                break;
            case InstructionType::IN_CB:
                procCb();
                break;
            case InstructionType::IN_RRCA:
                procRrca();
                break;
            case InstructionType::IN_RLCA:
                procRlca();
                break;
            case InstructionType::IN_RRA:
                procRra();
                break;
            case InstructionType::IN_RLA:
                procRla();
                break;
            case InstructionType::IN_STOP:
                procStop();
                break;
            case InstructionType::IN_HALT:
                procHalt();
                break;
            case InstructionType::IN_DAA:
                procDaa();
                break;
            case InstructionType::IN_CPL:
                procCpl();
                break;
            case InstructionType::IN_SCF:
                procScf();
                break;
            case InstructionType::IN_CCF:
                procCcf();
                break;
            case InstructionType::IN_EI:
                procEi();
                break;
            case InstructionType::IN_RETI:
                procReti();
                break;
            default:
                // Handle unknown opcode or error (if desired)
                NO_IMPL;
                break;
        }
}

void CPU::setFlag(Flag flag, bool value) {
        if (value) {
            flags |= (1 << static_cast<uint8_t>(flag));
        } else {
            flags &= ~(1 << static_cast<uint8_t>(flag));
        }
}

void CPU::setFlags(bool z, bool n, bool h, bool c) {
        setFlag(Flag::Z, z);
        setFlag(Flag::N, n);
        setFlag(Flag::H, h);
        setFlag(Flag::C, c);
}


static void procNone() {
    printf("INVALID INSTRUCTION!\n");
    exit(-7);
}

static void procNop() {
    //do nothing
}



RegisterType decodeReg(u8 reg) {
    if (reg > 0b111) {
        return RegisterType::RT_NONE;
    }

    return static_cast<RegisterType>(reg);
}

void procCb(CPU& cpu) {
    u8 op = cpu.getFetchedData();
    RegisterType reg = decodeReg(op & 0b111);
    u8 bit = (op >> 3) & 0b111;
    u8 bitOp = (op >> 6) & 0b11;
    u8 regVal = cpu.cpuReadReg8(reg);

    cpu.emuCycles(1);

    if (reg == RT_HL) {
        cpu.emuCycles(2);
    }

    switch (bitOp) {
        case 1:
            // BIT
            cpu.setFlags(!((regVal & (1 << bit))), false, true, cpu.isCarryFlagSet());
            return;

        case 2:
            // RST
            regVal &= ~(1 << bit);
            cpu.cpuSetReg8(reg, regVal);
            return;

        case 3:
            // SET
            regVal |= (1 << bit);
            cpu.cpuSetReg8(reg, regVal);
            return;
    }

    switch (bit) {
        case 0: {
            // RLC
            bool setC = false;
            u8 result = (regVal << 1) & 0xFF;

            if ((regVal & (1 << 7)) != 0) {
                result |= 1;
                setC = true;
            }

            cpu.cpuSetReg8(reg, result);
            cpu.setFlags(result == 0, false, false, setC);
        } return;

        // Implement other cases for the rest of the instructions...

        default:
            fprintf(stderr, "ERROR: INVALID CB: %02X", op);
            NO_IMPL;
    }
}

void procRlca(CPU &cpu) {
    u8 regVal = cpu.cpuReadReg8(RegisterType::RT_A);
    bool setC = false;
    u8 result = (regVal << 1) & 0xFF;

    if ((regVal & (1 << 7)) != 0) {
        result |= 1;
        setC = true;
    }

    cpu.cpuSetReg8(RegisterType::RT_A, result);
    cpu.setFlags(result == 0, false, false, setC);
}

void procRrca(CPU &cpu) {
        uint8_t regVal = cpu.cpuReadReg8(RegisterType::RT_A);
        bool setC = regVal & 1;
        regVal = (regVal >> 1) | (setC << 7);
        cpu.cpuSetReg8(RegisterType::RT_A, regVal);
        cpu.setFlags(regVal == 0, false, false, setC);
}


void procRla(CPU &cpu) {
    uint8_t regVal = cpu.cpuReadReg8(RegisterType::RT_A);
    uint8_t cf = cpu.isCarryFlagSet() ? 1 : 0;
    uint8_t c = (regVal >> 7) & 1;

    regVal = (regVal << 1) | cf;
    cpu.cpuSetReg8(RegisterType::RT_A, regVal);
    cpu.setFlags(regVal == 0, false, false, c);
}

void procStop(CPU &cpu) {
    std::cerr << "STOPPING!" << std::endl;
}



void procDaa(CPU &cpu) {
    u8 u = 0;  // Assuming you have a custom u8 type
    int fc = 0;

    if (cpu.isHalfCarryFlagSet() || (!cpu.isSubtractFlagSet() && (cpu.cpuReadReg8(RegisterType::RT_A) & 0xF) > 9)) {
        u = 6;
    }

    if (cpu.isCarryFlagSet() || (!cpu.isSubtractFlagSet() && cpu.cpuReadReg8(RegisterType::RT_A) > 0x99)) {
        u |= 0x60;
        fc = 1;
    }

    cpu.cpuSetReg8(RegisterType::RT_A, cpu.isSubtractFlagSet() ? cpu.cpuReadReg8(RegisterType::RT_A) - u : cpu.cpuReadReg8(RegisterType::RT_A) + u);

    cpu.setFlags(cpu.cpuReadReg8(RegisterType::RT_A) == 0, false, false, fc);
}

void procCpl(CPU &cpu) {
    cpu.cpuSetReg8(RegisterType::RT_A, ~cpu.cpuReadReg8(RegisterType::RT_A));
    cpu.setFlags(-1, true, true, -1);
}

void procScf(CPU &cpu) {
    cpu.setFlags(-1, false, false, true);
}

void procCcf(CPU &cpu) {
    cpu.setFlags(-1, false, false, cpu.isCarryFlagSet() ? 0 : 1);
}

void procHalt(CPU &cpu) {
    cpu.setHalted(true);
}

void procRra(CPU &cpu) {
    u8 carry = cpu.isCarryFlagSet() ? 1 : 0;
    u8 new_c = cpu.cpuReadReg8(RegisterType::RT_A) & 1;

    cpu.cpuSetReg8(RegisterType::RT_A, (cpu.cpuReadReg8(RegisterType::RT_A) >> 1) | (carry << 7));

    cpu.setFlags(0, false, false, new_c);
}

void procAnd(CPU &cpu) {
    cpu.cpuSetReg8(RegisterType::RT_A, cpu.cpuReadReg8(RegisterType::RT_A) & cpu.getFetchedData());
    cpu.setFlags(cpu.cpuReadReg8(RegisterType::RT_A) == 0, false, true, false);
}

void procXor(CPU &cpu) {
    cpu.cpuSetReg8(RegisterType::RT_A, cpu.cpuReadReg8(RegisterType::RT_A) ^ (cpu.getFetchedData() & 0xFF));
    cpu.setFlags(cpu.cpuReadReg8(RegisterType::RT_A) == 0, false, false, false);
}

void procOr(CPU &cpu) {
    cpu.cpuSetReg8(RegisterType::RT_A, cpu.cpuReadReg8(RegisterType::RT_A) | (cpu.getFetchedData() & 0xFF));
    cpu.setFlags(cpu.cpuReadReg8(RegisterType::RT_A) == 0, false, false, false);
}

void procCp(CPU &cpu) {
    int n = static_cast<int>(cpu.cpuReadReg8(RegisterType::RT_A)) - static_cast<int>(cpu.getFetchedData());

    cpu.setFlags(n == 0, true, (static_cast<int>(cpu.cpuReadReg8(RegisterType::RT_A)) & 0x0F) - (static_cast<int>(cpu.getFetchedData()) & 0x0F) < 0, n < 0);
}

void procDi(CPU &cpu) {
    cpu.setIntMasterEnabled(false);
}

void procEi(CPU &cpu) {
    cpu.setEnablingIME(true);
}

bool is16Bit(RegisterType rt) {
    return rt >= RegisterType::RT_AF;
}

void procLd(CPU &cpu) {
    const Instruction *inst = cpu.getCurInst();
    if (cpu.isDestMem()) {
        if (is16Bit(inst->getReg2())) {
            emuCycles(1);
            busWrite16(cpu.getMemDest(), cpu.getFetchedData());
        } else {
            busWrite(cpu.getMemDest(), cpu.getFetchedData());
        }
        emuCycles(1);
        return;
    }

    if (inst->getMode() == AddressMode::AM_HL_SPR) {
        u8 hFlag = (cpu.cpuReadReg8(inst->getReg2()) & 0xF) +
                   (cpu.getFetchedData() & 0xF) >= 0x10;
        u8 cFlag = (cpu.cpuReadReg8(inst->getReg2()) & 0xFF) +
                   (cpu.getFetchedData() & 0xFF) >= 0x100;

        cpu.setFlags(false, false, hFlag, cFlag);
        cpu.cpuSetReg8(inst->getReg1(),
                      cpu.cpuReadReg8(inst->getReg2()) + static_cast<int8_t>(cpu.getFetchedData()));
        return;
    }

    cpu.cpuSetReg8(inst->getReg1(), cpu.getFetchedData());
}

void procLdh(CPU &cpu) {
    const Instruction *inst = cpu.getCurInst();
    if (inst->getReg1() == RegisterType::RT_A) {
        cpu.cpuSetReg8(inst->getReg1(), busRead(0xFF00 | cpu.getFetchedData()));
    } else {
        busWrite(cpu.getMemDest(), cpu.cpuReadReg8(RegisterType::RT_A));
    }
    emuCycles(1);
}

bool CPU::checkCond(ConditionType cond) {
    bool z = isZeroFlagSet();
    bool c = isCarryFlagSet();

    switch (cond) {
        case ConditionType::CT_NONE: return true;
        case ConditionType::CT_C: return c;
        case ConditionType::CT_NC: return !c;
        case ConditionType::CT_Z: return z;
        case ConditionType::CT_NZ: return !z;
    }

    return false;
}

void CPU::gotoAddr(u16 addr, bool pushPC) {
    if (checkCond(getCurInst()->getCond())) {
        if (pushPC) {
            emuCycles(2);
            stackPush16(cpuReadReg16(RegisterType::RT_PC));
        }

        cpuSetReg16(RegisterType::RT_PC, addr);
        emuCycles(1);
    }
}

void procJp(CPU &cpu) {
    cpu.setCurInst(&cpu.getCurInst()[1]);  // Assuming getCurInst() is an array of instructions
    u16 address = cpu.getFetchedData();
    gotoAddr(cpu, address, false);
}

void procJr(CPU &cpu) {
    cpu.setCurInst(&cpu.getCurInst()[1]);  // Assuming getCurInst() is an array of instructions
    int8_t rel = static_cast<int8_t>(cpu.getFetchedData() & 0xFF);
    u16 addr = cpu.cpuReadReg16(RegisterType::RT_PC) + rel;
    gotoAddr(cpu, addr, false);
}

void procCall(CPU &cpu) {
    cpu.setCurInst(&cpu.getCurInst()[1]);  // Assuming getCurInst() is an array of instructions
    u16 address = cpu.getFetchedData();
    gotoAddr(cpu, address, true);
}

void procRst(CPU &cpu) {
    cpu.setCurInst(&cpu.getCurInst()[1]);  // Assuming getCurInst() is an array of instructions
    u16 address = cpu.getCurInst()->getParam();
    gotoAddr(cpu, address, true);
}

void procRet(CPU &cpu) {
    if (cpu.getCurInst()->getCond() != ConditionType::CT_NONE) {
        cpu.emuCycles(1);
    }

    if (checkCond(cpu)) {
        u16 lo = stackPop(cpu);
        cpu.emuCycles(1);
        u16 hi = stackPop(cpu);
        cpu.emuCycles(1);

        u16 n = (hi << 8) | lo;
        cpu.cpuSetReg16(RegisterType::RT_PC, n);

        cpu.emuCycles(1);
    }
}

void procReti(CPU &cpu) {
    cpu.setIntMasterEnabled(true);
    procRet(cpu);
}

void procPop(CPU &cpu) {
    u16 lo = stackPop(cpu);
    cpu.emuCycles(1);
    u16 hi = stackPop(cpu);
    cpu.emuCycles(1);

    u16 n = (hi << 8) | lo;

    cpu.cpuSetReg16(cpu.getCurInst()->getReg1(), n);

    if (cpu.getCurInst()->getReg1() == RegisterType::RT_AF) {
        cpu.cpuSetReg16(cpu.getCurInst()->getReg1(), n & 0xFFF0);
    }
}

void procPush(CPU &cpu) {
    u16 hi = (cpu.cpuReadReg16(cpu.getCurInst()->getReg1()) >> 8) & 0xFF;
    cpu.emuCycles(1);
    stackPush(cpu, hi);

    u16 lo = cpu.cpuReadReg16(cpu.getCurInst()->getReg1()) & 0xFF;
    cpu.emuCycles(1);
    stackPush(cpu, lo);
    
    cpu.emuCycles(1);
}



void procInc(CPU &cpu) {
    u16 val = cpu.cpuReadReg16(cpu.getCurInst()->getReg1()) + 1;

    if (is16Bit(cpu.getCurInst()->getReg1())) {
        cpu.emuCycles(1);
    }

    if (cpu.getCurInst()->getReg1() == RegisterType::RT_HL && cpu.getCurInst()->getMode() == AddressMode::AM_MR) {
        val = busRead(cpu.cpuReadReg16(RegisterType::RT_HL)) + 1;
        val &= 0xFF;
        busWrite(cpu.cpuReadReg16(RegisterType::RT_HL), val);
    } else {
        cpu.cpuSetReg16(cpu.getCurInst()->getReg1(), val);
        val = cpu.cpuReadReg16(cpu.getCurInst()->getReg1());
    }

    if ((cpu.getCurOpcode() & 0x03) == 0x03) {
        return;
    }

    cpu.setFlags(val == 0, false, (val & 0x0F) == 0, true);
}

void procDec(CPU &cpu) {
    u16 val = cpu.cpuReadReg16(cpu.getCurInst()->getReg1()) - 1;

    if (is16Bit(cpu.getCurInst()->getReg1())) {
        cpu.emuCycles(1);
    }

    if (cpu.getCurInst()->getReg1() == RegisterType::RT_HL && cpu.getCurInst()->getMode() == AddressMode::AM_MR) {
        val = busRead(cpu.cpuReadReg16(RegisterType::RT_HL)) - 1;
        busWrite(cpu.cpuReadReg16(RegisterType::RT_HL), val);
    } else {
        cpu.cpuSetReg16(cpu.getCurInst()->getReg1(), val);
        val = cpu.cpuReadReg16(cpu.getCurInst()->getReg1());
    }

    if ((cpu.getCurOpcode() & 0x0B) == 0x0B) {
        return;
    }

    cpu.setFlags(val == 0, true, (val & 0x0F) == 0x0F, true);
}

void procSub(CPU &cpu) {
    u16 val = cpu.cpuReadReg16(cpu.getCurInst()->getReg1()) - cpu.getFetchedData();

    int z = val == 0;
    int h = ((int)cpu.cpuReadReg16(cpu.getCurInst()->getReg1()) & 0xF) - ((int)cpu.getFetchedData() & 0xF) < 0;
    int c = ((int)cpu.cpuReadReg16(cpu.getCurInst()->getReg1())) - ((int)cpu.getFetchedData()) < 0;

    cpu.cpuSetReg16(cpu.getCurInst()->getReg1(), val);
    cpu.setFlags(z, true, h, c);
}

//here

void procSbc(CPU &cpu) {
    u8 val = cpu.getFetchedData() + cpu.isCarryFlagSet();

    int z = cpu.cpuReadReg8(cpu.getCurInst()->getReg1()) - val == 0;

    int h = ((int)cpu.cpuReadReg8(cpu.getCurInst()->getReg1()) & 0xF) 
        - ((int)cpu.getFetchedData() & 0xF) - ((int)cpu.isCarryFlagSet()) < 0;
    int c = ((int)cpu.cpuReadReg8(cpu.getCurInst()->getReg1())) 
        - ((int)cpu.getFetchedData()) - ((int)cpu.isCarryFlagSet()) < 0;

    cpu.cpuSetReg8(cpu.getCurInst()->getReg1(), cpu.cpuReadReg8(cpu.getCurInst()->getReg1()) - val);
    cpu.setFlags(z, true, h, c);
}

void procAdc(CPU &cpu) {
    u16 u = cpu.getFetchedData();
    u16 a = cpu.cpuReadReg8(RegisterType::RT_A);
    u16 c = cpu.isCarryFlagSet();

    cpu.cpuSetReg8(RegisterType::RT_A, (a + u + c) & 0xFF);

    cpu.setFlags(cpu.cpuReadReg8(RegisterType::RT_A) == 0, false, 
        (a & 0xF) + (u & 0xF) + c > 0xF,
        a + u + c > 0xFF);
}

void procAdd(CPU &cpu) {
    u32 val = cpu.cpuReadReg8(cpu.getCurInst()->getReg1()) + cpu.getFetchedData();

    bool is16Bit = cpu.is16Bit(cpu.getCurInst()->getReg1());

    if (is16Bit) {
        cpu.emuCycles(1);
    }

    if (cpu.getCurInst()->getReg1() == RegisterType::RT_SP) {
        val = cpu.cpuReadReg16(RegisterType::RT_SP) + static_cast<int8_t>(cpu.getFetchedData());
    }

    int z = (val & 0xFF) == 0;
    int h = (cpu.cpuReadReg8(cpu.getCurInst()->getReg1()) & 0xF) + (cpu.getFetchedData() & 0xF) >= 0x10;
    int c = (int)(cpu.cpuReadReg8(cpu.getCurInst()->getReg1()) & 0xFF) + (int)(cpu.getFetchedData() & 0xFF) >= 0x100;

    if (is16Bit) {
        z = -1;
        h = (cpu.cpuReadReg16(cpu.getCurInst()->getReg1()) & 0xFFF) + (cpu.getFetchedData() & 0xFFF) >= 0x1000;
        u32 n = static_cast<u32>(cpu.cpuReadReg16(cpu.getCurInst()->getReg1())) + static_cast<u32>(cpu.getFetchedData());
        c = n >= 0x10000;
    }

    if (cpu.getCurInst()->getReg1() == RegisterType::RT_SP) {
        z = 0;
        h = (cpu.cpuReadReg16(RegisterType::RT_SP) & 0xF) + (cpu.getFetchedData() & 0xF) >= 0x10;
        c = (int)(cpu.cpuReadReg16(RegisterType::RT_SP) & 0xFF) + (int)(cpu.getFetchedData() & 0xFF) >= 0x100;
    }

    cpu.cpuSetReg16(cpu.getCurInst()->getReg1(), val & 0xFFFF);
    cpu.setFlags(z, false, h, c);
}

