#pragma once

#include <stdint.h>

#include "addrSpace.hpp"
#include "registers.hpp"

namespace riscvModel
{

class Instruction
{

public:
    using InstrID = uint32_t;

    InstrID id;
};

struct IType : public Instruction
{
    Registers::GPReg  imm;
    Registers::RegIdx rs1;
    Registers::RegIdx rd;

    void addi(Registers& r, AddrSpace& aspace) const;

    void lb(Registers& r, AddrSpace& aspace) const;

    void lh(Registers& r, AddrSpace& aspace) const;

    void lw(Registers& r, AddrSpace& aspace) const;
};

struct RType : public Instruction
{
    Registers::RegIdx rs2;
    Registers::RegIdx rs1;
    Registers::RegIdx rd;

    void add(Registers& r, AddrSpace& aspace) const;

    void sub(Registers& r, AddrSpace& aspace) const;
};

struct SType : public Instruction
{
    Registers::GPReg  imm;
    Registers::RegIdx rs2;
    Registers::RegIdx rs1;
    Registers::RegIdx rd;

    void sb(Registers& r, AddrSpace& aspace) const;

    void sh(Registers& r, AddrSpace& aspace) const;

    void sw(Registers& r, AddrSpace& aspace) const;
};

struct BType : public Instruction
{
    Registers::GPReg  imm;
    Registers::RegIdx rs2;
    Registers::RegIdx rs1;

    void beq(Registers& r, AddrSpace& aspace) const;

    void bne(Registers& r, AddrSpace& aspace) const;

    void blt(Registers& r, AddrSpace& aspace) const;

    void bge(Registers& r, AddrSpace& aspace) const;
};

} // namespace riscvModel
