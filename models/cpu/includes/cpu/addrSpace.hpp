#pragma once

#include <vector>

#include "cpu/device.hpp"

namespace riscvModel
{

class AddrSpace
{
private:
    Device* dev; // only one device for now(ram)

public:
    uint32_t ReadWordFrom(uint64_t addr);
    void     WriteWordAt(uint64_t addr, uint32_t w);

    uint16_t ReadHWordFrom(uint64_t addr);
    void     WriteHWordAt(uint64_t addr, uint16_t w);

    uint8_t ReadByteFrom(uint64_t addr);
    void    WriteByteAt(uint64_t addr, uint8_t w);

    AddrSpace(Device* d);
};
} // namespace riscvModel
