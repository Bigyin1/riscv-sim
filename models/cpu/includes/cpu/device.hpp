#pragma once

#include <stdint.h>

#include <utility>

namespace riscvModel
{
class Device
{

public:
    virtual std::pair<uint64_t, uint64_t> GetAddrRange() = 0;

    virtual uint32_t ReadWordFrom(uint64_t addr)            = 0;
    virtual void     WriteWordAt(uint64_t addr, uint32_t w) = 0;

    virtual uint16_t ReadHWordFrom(uint64_t addr)            = 0;
    virtual void     WriteHWordAt(uint64_t addr, uint16_t w) = 0;

    virtual uint8_t ReadByteFrom(uint64_t addr)           = 0;
    virtual void    WriteByteAt(uint64_t addr, uint8_t w) = 0;

    virtual ~Device() = default;
};

} // namespace riscvModel
