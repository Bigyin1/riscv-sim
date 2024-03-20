#include "decoder.hpp"

#include <iostream>

namespace riscvModel
{

const Instruction* Decoder::Decode(RawInstr instr)
{

    uint8_t opcode = (instr << 25) >> 25;

    switch (opcode)
    {
        case 0b1100111: // jalr
        case 0b0000011: // loads
        case 0b0010011: // addi
            return this->I.Decode(instr);

        case 0b0110011:
            return this->R.Decode(instr);

        case 0b1100011:
            return this->B.Decode(instr);

        case 0b0100011:
            return this->S.Decode(instr);

        case 0b1101111:
            return this->J.Decode(instr);

        default:
            return nullptr;
    }
}

Instruction::InstrID Decoder::buildInstrID(uint8_t opcode, uint8_t funct3, uint8_t funct7)
{

    return ((uint32_t)opcode | (uint32_t)funct3 << 7 | (uint32_t)funct7 << 10);
}

Instruction* Decoder::ITypeDecoder::Decode(RawInstr rinstr)
{
    map.instr = rinstr;

    this->instr.id  = buildInstrID(map.opcode, map.funct3, 0);
    this->instr.rd  = map.rd;
    this->instr.rs1 = map.rs1;
    this->instr.imm = map.imm;

    if (this->instr.imm >> 11)
    {
        this->instr.imm |= ~(GPReg)0b111'111'111'111;
    }

    return static_cast<Instruction*>(&this->instr);
}

Instruction* Decoder::RTypeDecoder::Decode(RawInstr rinstr)
{
    map.instr = rinstr;

    this->instr.id  = buildInstrID(map.opcode, map.funct3, map.funct7);
    this->instr.rd  = map.rd;
    this->instr.rs1 = map.rs1;
    this->instr.rs2 = map.rs2;

    return static_cast<Instruction*>(&this->instr);
}

Instruction* Decoder::STypeDecoder::Decode(RawInstr rinstr)
{
    map.instr = rinstr;

    this->instr.id  = buildInstrID(map.opcode, map.funct3, 0);
    this->instr.rs1 = map.rs1;
    this->instr.rs2 = map.rs2;

    this->instr.imm = (GPReg)this->map.imm7 << 5 | (GPReg)this->map.imm5;

    if (this->instr.imm >> 11)
    {
        this->instr.imm |= ~(GPReg)0b111'111'111'111;
    }

    return static_cast<Instruction*>(&this->instr);
}

Instruction* Decoder::BTypeDecoder::Decode(RawInstr rinstr)
{
    map.instr = rinstr;

    this->instr.id  = buildInstrID(map.opcode, map.funct3, 0);
    this->instr.rs1 = map.rs1;
    this->instr.rs2 = map.rs2;

    this->instr.imm =
        (uint64_t)map.imm4 << 1 | (uint64_t)map.imm6 << 5 | (uint64_t)map.imm1_1 << 11;

    if (map.imm1_2)
    {
        this->instr.imm |= ~(uint64_t)0b111'111'111'111;
    }

    return static_cast<Instruction*>(&this->instr);
}

Instruction* Decoder::JTypeDecoder::Decode(RawInstr rinstr)
{
    map.instr = rinstr;

    this->instr.id = buildInstrID(map.opcode, 0, 0);
    this->instr.rd = map.rd;

    this->instr.imm =
        (uint64_t)map.imm10 << 1 | (uint64_t)map.imm1_1 << 11 | (uint64_t)map.imm8 << 12;

    if (map.imm1_2)
    {
        this->instr.imm |= ~(uint64_t)((1 << 20) - 1);
    }

    return static_cast<Instruction*>(&this->instr);
}

} // namespace riscvModel
