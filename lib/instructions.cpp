#include "../include/instructions.hpp"
#include "../include/cpu.hpp"
#include "../include/bus.hpp"

/**process for getting the instructions:
 * 1. get the value of the pc reg
 * 2. this is a u8 value
 * 3. this u8 value is an opcode
 * 4. each opcode has at least 1 instruction associated with it
 * 5. set the current instruction using the opcode value as read, then
 * 6. 
 * **/


Instruction::Instruction(InstructionType t = InstructionType::IN_NONE,
                         AddressMode m = AddressMode::AM_IMP,
                         RegisterType r1 = RegisterType::RT_NONE,
                         RegisterType r2 = RegisterType::RT_NONE,
                         ConditionType c = ConditionType::CT_NONE,
                         u8 p = 0)
    : type(t), mode(m), reg_1(r1), reg_2(r2), cond(c), param(p) {
}


const Instruction& instruction_by_opcode(Opcode opcode) {
    static Instruction instructions[0x100] = {
        // ... Instructions initialization here
    };
    
    return instructions[opcodeMap[opcode]];
}

instruction *instruction_by_opcode(u8 opcode){
    return &instructions[opcode];
}

char *inst_lookup[] = {
    "<NONE>",
    "NOP",
    "LD",
    "INC",
    "DEC",
    "RLCA",
    "ADD",
    "RRCA",
    "STOP",
    "RLA",
    "JR",
    "RRA",
    "DAA",
    "CPL",
    "SCF",
    "CCF",
    "HALT",
    "ADC",
    "SUB",
    "SBC",
    "AND",
    "XOR",
    "OR",
    "CP",
    "POP",
    "JP",
    "PUSH",
    "RET",
    "CB",
    "CALL",
    "RETI",
    "LDH",
    "JPHL",
    "DI",
    "EI",
    "RST",
    "IN_ERR",
    "IN_RLC", 
    "IN_RRC",
    "IN_RL", 
    "IN_RR",
    "IN_SLA", 
    "IN_SRA",
    "IN_SWAP", 
    "IN_SRL",
    "IN_BIT", 
    "IN_RES", 
    "IN_SET"
};

char *inst_name(in_type t) {
    return inst_lookup[t];
}

static char *rt_lookup[] = {
    "<NONE>",
    "A",
    "F",
    "B",
    "C",
    "D",
    "E",
    "H",
    "L",
    "AF",
    "BC",
    "DE",
    "HL",
    "SP",
    "PC"
};

void inst_to_str(cpu_context *ctx, char *str) {
    instruction *inst = ctx->cur_inst;
    sprintf(str, "%s ", inst_name(inst->type));

    switch(inst->mode) {
        case AM_IMP:
            return;

        case AM_R_D16:
        case AM_R_A16:
            sprintf(str, "%s %s,$%04X", inst_name(inst->type), 
                rt_lookup[inst->reg_1], ctx->fetched_data);
            return;

        case AM_R:
            sprintf(str, "%s %s", inst_name(inst->type), 
                rt_lookup[inst->reg_1]);
            return;

        case AM_R_R: 
            sprintf(str, "%s %s,%s", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_MR_R:
            sprintf(str, "%s (%s),%s", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_MR:
            sprintf(str, "%s (%s)", inst_name(inst->type), 
                rt_lookup[inst->reg_1]);
            return;

        case AM_R_MR:
            sprintf(str, "%s %s,(%s)", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_R_D8:
        case AM_R_A8:
            sprintf(str, "%s %s,$%02X", inst_name(inst->type), 
                rt_lookup[inst->reg_1], ctx->fetched_data & 0xFF);
            return;

        case AM_R_HLI:
            sprintf(str, "%s %s,(%s+)", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_R_HLD:
            sprintf(str, "%s %s,(%s-)", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_HLI_R:
            sprintf(str, "%s (%s+),%s", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_HLD_R:
            sprintf(str, "%s (%s-),%s", inst_name(inst->type), 
                rt_lookup[inst->reg_1], rt_lookup[inst->reg_2]);
            return;

        case AM_A8_R:
            sprintf(str, "%s $%02X,%s", inst_name(inst->type), 
                bus_read(ctx->regs.pc - 1), rt_lookup[inst->reg_2]);

            return;

        case AM_HL_SPR:
            sprintf(str, "%s (%s),SP+%d", inst_name(inst->type), 
                rt_lookup[inst->reg_1], ctx->fetched_data & 0xFF);
            return;

        case AM_D8:
            sprintf(str, "%s $%02X", inst_name(inst->type), 
                ctx->fetched_data & 0xFF);
            return;

        case AM_D16:
            sprintf(str, "%s $%04X", inst_name(inst->type), 
                ctx->fetched_data);
            return;

        case AM_MR_D8:
            sprintf(str, "%s (%s),$%02X", inst_name(inst->type), 
                rt_lookup[inst->reg_1], ctx->fetched_data & 0xFF);
            return;

        case AM_A16_R:
            sprintf(str, "%s ($%04X),%s", inst_name(inst->type), 
                ctx->fetched_data, rt_lookup[inst->reg_2]);
            return;

        default:
            fprintf(stderr, "INVALID AM: %d\n", inst->mode);
            NO_IMPL
    }
}