#include "cpu/cpu.hpp"

#include <iostream>

#include "cpu/instruction.hpp"
#include "decoder.hpp"

namespace riscvModel
{

CPU::CPU(Registers& _regs, AddrSpace& aspace) : regs(_regs), addrSpace(aspace) {}

RawInstr CPU::Fetch()
{
    return this->addrSpace.ReadWordFrom(this->regs.GetPC());
}

const Instruction* CPU::Decode(RawInstr iraw)
{
    return this->idecoder.Decode(iraw);
}

void CPU::Execute(const Instruction* instr)
{

#define ExecCase(iid, itype, iname)                                                                \
    case iid:                                                                                      \
        static_cast<const itype##Type*>(instr)->iname(this->regs, this->addrSpace);                \
        break;

    switch (instr->id)
    {
        ExecCase(0b000'0010011, I, addi);
        ExecCase(0b000'0000011, I, lb);
        ExecCase(0b001'0000011, I, lh);
        ExecCase(0b010'0000011, I, lw);

        ExecCase(0b0000000'000'0110011, R, add);
        ExecCase(0b0100000'000'0110011, R, sub);

        ExecCase(0b000'0100011, S, sb);
        ExecCase(0b001'0100011, S, sh);
        ExecCase(0b010'0100011, S, sw);

        ExecCase(0b000'1100011, B, beq);
        ExecCase(0b001'1100011, B, bne);
        ExecCase(0b100'1100011, B, blt);
        ExecCase(0b101'1100011, B, bge);

        default:

            std::cout << "unknown iid:" << instr->id << std::endl;

            std::abort();
            break;
    }

#undef ExecCase
}

} // namespace riscvModel
