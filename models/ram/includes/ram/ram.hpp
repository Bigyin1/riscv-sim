#pragma once
#include <array>
#include <fstream>

#include "cpu/device.hpp"

namespace riscvModel
{

template <std::size_t RamSz>
class RAM : public Device
{
private:
    std::array<uint32_t, RamSz / 4> storage = {};

    uint64_t start;

public:
    RAM(uint64_t start);

    std::pair<uint64_t, uint64_t> GetAddrRange() override;

    uint32_t ReadWordFrom(uint64_t addr) override;
    void     WriteWordAt(uint64_t addr, uint32_t w) override;

    uint16_t ReadHWordFrom(uint64_t addr) override;
    void     WriteHWordAt(uint64_t addr, uint16_t w) override;

    uint8_t ReadByteFrom(uint64_t addr) override;
    void    WriteByteAt(uint64_t addr, uint8_t w) override;

    void LoadCode(std::ifstream& f, size_t at);

    // ~RAM() {}
};

} // namespace riscvModel
