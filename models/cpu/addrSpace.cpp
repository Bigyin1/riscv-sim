#include "addrSpace.hpp"

#include <stdexcept>

namespace riscvModel
{
AddrSpace::AddrSpace(Device* _dev) : dev(_dev) {}

static void checkBounds(uint64_t addr, std::pair<uint64_t, uint64_t> rng) // TODO
{
    if (addr >= rng.first && addr <= rng.second)
    {
        return;
    }

    throw std::runtime_error("ram bad address");
}

uint32_t AddrSpace::ReadWordFrom(uint64_t addr)
{

    checkBounds(addr, this->dev->GetAddrRange());

    return this->dev->ReadWordFrom(addr);
}
void AddrSpace::WriteWordAt(uint64_t addr, uint32_t w)
{

    checkBounds(addr, this->dev->GetAddrRange());

    return this->dev->WriteWordAt(addr, w);
}

uint16_t AddrSpace::ReadHWordFrom(uint64_t addr)
{
    checkBounds(addr, this->dev->GetAddrRange());

    return this->dev->ReadHWordFrom(addr);
}
void AddrSpace::WriteHWordAt(uint64_t addr, uint16_t hw)
{
    checkBounds(addr, this->dev->GetAddrRange());

    return this->dev->WriteHWordAt(addr, hw);
}

uint8_t AddrSpace::ReadByteFrom(uint64_t addr)
{
    checkBounds(addr, this->dev->GetAddrRange());

    return this->dev->ReadByteFrom(addr);
}
void AddrSpace::WriteByteAt(uint64_t addr, uint8_t b)
{

    checkBounds(addr, this->dev->GetAddrRange());

    return this->dev->WriteByteAt(addr, b);
}

} // namespace riscvModel
