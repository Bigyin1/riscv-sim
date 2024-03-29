#include "cpu/registers.hpp"

#include "decoder.hpp"

namespace riscvModel
{

Registers::Registers(uint64_t _pc) : pc(_pc) {}

void Registers::AdvancePC()
{
    this->pc += sizeof(RawInstr);
}

void Registers::PCRelJmp(uint64_t offset)
{
    this->pc += offset;
}

void Registers::PCAbsJmp(uint64_t target)
{
    this->pc = target;
}

Registers::GPReg Registers::ReadRegVal(RegIdx idx) const
{
    return this->gpRegs[idx];
}

void Registers::WriteAtReg(RegIdx idx, GPReg w)
{
    this->gpRegs[idx] = w;
}

uint64_t Registers::GetPC()
{
    return this->pc;
}

} // namespace riscvModel
