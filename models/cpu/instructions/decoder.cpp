#include "decoder.hpp"

#include <iostream>

namespace riscvModel
{

const Instruction* Decoder::Decode(RawInstr instr)
{

    uint8_t opcode = (instr << 25) >> 25;

    switch (opcode)
    {
        case 0b0000011:
        case 0b0010011:
            return this->I.Decode(instr);

        case 0b0110011:
            return this->R.Decode(instr);

        case 0b1100011:
            return this->B.Decode(instr);

        case 0b0100011:
            return this->S.Decode(instr);

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

    this->instr.imm = (GPReg)map.imm4 << 2 | (GPReg)map.imm6 << 6 | (GPReg)map.imm1_1 << 12;

    if (map.imm1_2)
    {
        this->instr.imm |= ~(GPReg)0b111'111'111'111'1;
    }

    return static_cast<Instruction*>(&this->instr);
}

} // namespace riscvModel
