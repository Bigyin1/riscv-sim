#pragma once

#include "cpu/instruction.hpp"

namespace riscvModel
{

using RawInstr = uint32_t;

class Decoder
{

    using GPReg = Registers::GPReg;

    static Instruction::InstrID buildInstrID(uint8_t opcode, uint8_t funct3, uint8_t funct7);

    class ITypeDecoder
    {
    private:
        IType instr;

        union
        {
            RawInstr instr;
            struct
            {
                uint8_t  opcode : 7;
                uint8_t  rd : 5;
                uint8_t  funct3 : 3;
                uint8_t  rs1 : 5;
                uint32_t imm : 12;
            } __attribute__((packed));
        } map;

    public:
        Instruction* Decode(RawInstr instr);
    };

    class RTypeDecoder
    {
    private:
        RType instr;

        union
        {
            RawInstr instr;
            struct
            {
                uint8_t opcode : 7;
                uint8_t rd : 5;
                uint8_t funct3 : 3;
                uint8_t rs1 : 5;
                uint8_t rs2 : 5;
                uint8_t funct7 : 7;
            } __attribute__((packed));
        } map;

    public:
        Instruction* Decode(RawInstr instr);
    };

    class STypeDecoder
    {
    private:
        SType instr;

        union
        {
            RawInstr instr;
            struct
            {
                uint8_t  opcode : 7;
                uint32_t imm5 : 5;
                uint8_t  funct3 : 3;
                uint8_t  rs1 : 5;
                uint8_t  rs2 : 5;
                uint32_t imm7 : 7;
            } __attribute__((packed));
        } map;

    public:
        Instruction* Decode(RawInstr instr);
    };

    class BTypeDecoder
    {
    private:
        BType instr;

        union
        {
            RawInstr instr;
            struct
            {
                uint8_t  opcode : 7;
                uint32_t imm1_1 : 1;
                uint32_t imm4 : 4;
                uint8_t  funct3 : 3;
                uint8_t  rs1 : 5;
                uint8_t  rs2 : 5;
                uint32_t imm6 : 6;
                uint32_t imm1_2 : 1;
            } __attribute__((packed));
        } map;

    public:
        Instruction* Decode(RawInstr instr);
    };

    class JTypeDecoder
    {
    private:
        JType instr;

        union
        {
            RawInstr instr;
            struct
            {
                uint8_t  opcode : 7;
                uint8_t  rd : 5;
                uint32_t imm8 : 8;
                uint32_t imm1_1 : 1;
                uint32_t imm10 : 10;
                uint32_t imm1_2 : 1;
            } __attribute__((packed));
        } map;

    public:
        Instruction* Decode(RawInstr instr);
    };

    class UTypeDecoder
    {
    private:
        UType instr;

        union
        {
            RawInstr instr;
            struct
            {
                uint8_t  opcode : 7;
                uint8_t  rd : 5;
                uint32_t imm20 : 20;
            } __attribute__((packed));
        } map;

    public:
        Instruction* Decode(RawInstr instr);
    };

private:
    ITypeDecoder I;
    RTypeDecoder R;
    STypeDecoder S;
    BTypeDecoder B;
    JTypeDecoder J;
    UTypeDecoder U;

public:
    const Instruction* Decode(RawInstr instr);
};

} // namespace riscvModel
