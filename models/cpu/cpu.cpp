#include "cpu/cpu.hpp"

#include <iostream>

#include "cpu/instruction.hpp"
#include "decoder.hpp"

namespace riscvModel
{

CPU::CPU(Registers& _regs, AddrSpace& _aspace, Environment& _env)
    : regs(_regs), addrSpace(_aspace), env(_env)
{
}

RawInstr CPU::Fetch()
{
    return this->addrSpace.ReadWordFrom(this->regs.GetPC());
}

const Instruction* CPU::Decode(RawInstr iraw)
{
    return this->idecoder.Decode(iraw);
}

bool CPU::IsStopped()
{
    return this->regs.stopped;
}

void CPU::Execute(const Instruction* instr)
{

#define ExecCase(iid, itype, iname, ...)                                                           \
    case iid:                                                                                      \
        std::cout << "executing: " << #iname << std::endl;                                         \
        static_cast<const itype##Type*>(instr)->iname(this->regs, this->addrSpace __VA_ARGS__);    \
        break;

    switch (instr->id)
    {
        ExecCase(0b000'1100111, I, jalr);
        ExecCase(0b000'0010011, I, addi);
        ExecCase(0b000'0000011, I, lb);
        ExecCase(0b001'0000011, I, lh);
        ExecCase(0b010'0000011, I, lw);
        ExecCase(0b100'0000011, I, lbu);
        ExecCase(0b101'0000011, I, lhu);

        ExecCase(0b0000000'000'0110011, R, add);
        ExecCase(0b0100000'000'0110011, R, sub);

        ExecCase(0b000'0100011, S, sb);
        ExecCase(0b001'0100011, S, sh);
        ExecCase(0b010'0100011, S, sw);

        ExecCase(0b000'1100011, B, beq);
        ExecCase(0b001'1100011, B, bne);
        ExecCase(0b100'1100011, B, blt);
        ExecCase(0b101'1100011, B, bge);
        ExecCase(0b110'1100011, B, bltu);
        ExecCase(0b111'1100011, B, bgeu);

        ExecCase(0b1101111, J, jal);

        ExecCase(0b0110111, U, lui);
        ExecCase(0b0010111, U, auipc);

        ExecCase(0b0'000'0001111, I, fence);
        ExecCase(0b0'000'1110011, I, ecall, , this->env);
        ExecCase(0b1'000'1110011, I, ebreak);

        default:
            throw std::runtime_error("unknown iid");
    }

#undef ExecCase
}

} // namespace riscvModel
