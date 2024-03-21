#pragma once

#include <stdint.h>

#include "addrSpace.hpp"
#include "decoder.hpp"
#include "environment.hpp"
#include "instruction.hpp"
#include "registers.hpp"

namespace riscvModel
{

class CPU
{
private:
    Registers&   regs;
    AddrSpace&   addrSpace;
    Environment& env;

    Decoder idecoder{};

public:
    CPU(Registers& _regs, AddrSpace& _aspace, Environment& _env);

    RawInstr           Fetch();
    const Instruction* Decode(RawInstr iraw);
    void               Execute(const Instruction* instr);

    bool IsStopped();
};

} // namespace riscvModel
