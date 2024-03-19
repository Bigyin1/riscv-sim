#pragma once

#include <stdint.h>

#include <array>

namespace riscvModel
{

class Registers
{
public:
    using GPReg       = uint32_t;
    using GPRegSigned = int32_t;

    using RegIdx = uint8_t;

private:
    std::array<GPReg, 32> gpRegs = {};
    uint64_t              pc;

public:
    Registers(uint64_t pc);

    void     AdvancePC();
    void     PCRelJmp(uint64_t offset);
    uint64_t GetPC();

    GPReg ReadRegVal(RegIdx idx) const;
    void  WriteAtReg(RegIdx idx, GPReg w);
};
} // namespace riscvModel
