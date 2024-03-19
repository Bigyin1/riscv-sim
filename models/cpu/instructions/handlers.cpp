

#include "cpu/instruction.hpp"

namespace riscvModel
{

void IType::addi(Registers& r, AddrSpace&) const
{

    auto src = r.ReadRegVal(this->rs1);

    r.WriteAtReg(this->rd, src + this->imm);

    r.AdvancePC();
}

void IType::lb(Registers& r, AddrSpace& aspace) const
{

    auto addr = r.ReadRegVal(this->rs1) + this->imm;

    Registers::GPReg val = aspace.ReadByteFrom(addr);
    if (val >> 7)
    {
        val |= ~(Registers::GPReg)UINT8_MAX;
    }

    r.WriteAtReg(this->rd, val);

    r.AdvancePC();
}

void IType::lbu(Registers& r, AddrSpace& aspace) const
{

    auto addr = r.ReadRegVal(this->rs1) + this->imm;

    Registers::GPReg val = aspace.ReadByteFrom(addr);

    r.WriteAtReg(this->rd, val);

    r.AdvancePC();
}

void IType::lh(Registers& r, AddrSpace& aspace) const
{

    auto addr = r.ReadRegVal(this->rs1) + this->imm;

    Registers::GPReg val = aspace.ReadHWordFrom(addr);
    if (val >> 15)
    {
        val |= ~(Registers::GPReg)UINT16_MAX;
    }

    r.WriteAtReg(this->rd, val);

    r.AdvancePC();
}

void IType::lhu(Registers& r, AddrSpace& aspace) const
{

    auto addr = r.ReadRegVal(this->rs1) + this->imm;

    Registers::GPReg val = aspace.ReadHWordFrom(addr);

    r.WriteAtReg(this->rd, val);

    r.AdvancePC();
}

void IType::lw(Registers& r, AddrSpace& aspace) const
{

    auto addr = r.ReadRegVal(this->rs1) + this->imm;

    Registers::GPReg val = aspace.ReadWordFrom(addr);

    r.WriteAtReg(this->rd, val);

    r.AdvancePC();
}

void RType::add(Registers& r, AddrSpace&) const
{

    auto src1 = r.ReadRegVal(this->rs1);
    auto src2 = r.ReadRegVal(this->rs2);

    r.WriteAtReg(this->rd, src1 + src2);

    r.AdvancePC();
}

void RType::sub(Registers& r, AddrSpace&) const
{
    auto src1 = r.ReadRegVal(this->rs1);
    auto src2 = r.ReadRegVal(this->rs2);

    r.WriteAtReg(this->rd, src1 - src2);

    r.AdvancePC();
}

void SType::sb(Registers& r, AddrSpace& aspace) const
{
    auto addr = r.ReadRegVal(this->rs1) + this->imm;

    Registers::GPReg val = r.ReadRegVal(this->rs2);

    aspace.WriteByteAt(addr, (uint8_t)val);

    r.AdvancePC();
}

void SType::sh(Registers& r, AddrSpace& aspace) const
{
    auto addr = r.ReadRegVal(this->rs1) + this->imm;

    Registers::GPReg val = r.ReadRegVal(this->rs2);

    aspace.WriteHWordAt(addr, (uint16_t)val);

    r.AdvancePC();
}

void SType::sw(Registers& r, AddrSpace& aspace) const
{
    auto addr = r.ReadRegVal(this->rs1) + this->imm;

    Registers::GPReg val = r.ReadRegVal(this->rs2);

    aspace.WriteWordAt(addr, (uint32_t)val);

    r.AdvancePC();
}

void BType::beq(Registers& r, AddrSpace&) const
{
    auto src1 = r.ReadRegVal(this->rs1);
    auto src2 = r.ReadRegVal(this->rs2);

    if (src1 == src2)
    {
        r.PCRelJmp(this->imm);
    }
    else
    {
        r.AdvancePC();
    }
}

void BType::bne(Registers& r, AddrSpace&) const
{
    auto src1 = r.ReadRegVal(this->rs1);
    auto src2 = r.ReadRegVal(this->rs2);

    if (src1 != src2)
    {
        r.PCRelJmp(this->imm);
    }
    else
    {
        r.AdvancePC();
    }
}

void BType::blt(Registers& r, AddrSpace&) const
{
    auto src1 = (Registers::GPRegSigned)r.ReadRegVal(this->rs1);
    auto src2 = (Registers::GPRegSigned)r.ReadRegVal(this->rs2);

    if (src1 < src2)
    {
        r.PCRelJmp(this->imm);
    }
    else
    {
        r.AdvancePC();
    }
}

void BType::bltu(Registers& r, AddrSpace&) const
{
    auto src1 = r.ReadRegVal(this->rs1);
    auto src2 = r.ReadRegVal(this->rs2);

    if (src1 < src2)
    {
        r.PCRelJmp(this->imm);
    }
    else
    {
        r.AdvancePC();
    }
}

void BType::bge(Registers& r, AddrSpace&) const
{
    auto src1 = (Registers::GPRegSigned)r.ReadRegVal(this->rs1);
    auto src2 = (Registers::GPRegSigned)r.ReadRegVal(this->rs2);

    if (src1 > src2)
    {
        r.PCRelJmp(this->imm);
    }
    else
    {
        r.AdvancePC();
    }
}

void BType::bgeu(Registers& r, AddrSpace&) const
{
    auto src1 = r.ReadRegVal(this->rs1);
    auto src2 = r.ReadRegVal(this->rs2);

    if (src1 > src2)
    {
        r.PCRelJmp(this->imm);
    }
    else
    {
        r.AdvancePC();
    }
}

} // namespace riscvModel
