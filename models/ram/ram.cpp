#include "ram/ram.hpp"

namespace riscvModel
{

RAM::RAM(uint64_t _start) : start(_start) {}

std::pair<uint64_t, uint64_t> RAM::GetAddrRange()
{

    return {this->start, this->start + this->storage.size() * sizeof(this->storage[0])};
}

uint32_t RAM::ReadWordFrom(uint64_t addr)
{
    size_t storageIdx = addr / 4;
    return this->storage[storageIdx];
}
void RAM::WriteWordAt(uint64_t addr, uint32_t w)
{
    size_t storageIdx         = addr / 4;
    this->storage[storageIdx] = w;
}

uint16_t RAM::ReadHWordFrom(uint64_t addr)
{
    size_t storageIdx = addr / 4;
    size_t bucketIdx  = addr % 2;

    uint32_t word = storage[storageIdx];

    uint16_t* bucket = (uint16_t*)&word;

    return bucket[bucketIdx];
}
void RAM::WriteHWordAt(uint64_t addr, uint16_t hw)
{
    size_t storageIdx = addr / 4;
    size_t bucketIdx  = addr % 2;

    uint32_t word = storage[storageIdx];

    uint16_t* bucket  = (uint16_t*)&word;
    bucket[bucketIdx] = hw;

    storage[storageIdx] = word;
}

uint8_t RAM::ReadByteFrom(uint64_t addr)
{
    size_t storageIdx = addr / 4;
    size_t bucketIdx  = addr % 4;

    uint32_t word = storage[storageIdx];

    uint8_t* bucket = (uint8_t*)&word;

    return bucket[bucketIdx];
}
void RAM::WriteByteAt(uint64_t addr, uint8_t b)
{
    size_t storageIdx = addr / 4;
    size_t bucketIdx  = addr % 4;

    uint32_t word = storage[storageIdx];

    uint8_t* bucket   = (uint8_t*)&word;
    bucket[bucketIdx] = b;

    storage[storageIdx] = word;
}

void RAM::LoadCode(std::ifstream& f, size_t at)
{

    while (!f.eof())
    {
        uint32_t val = 0;
        f.read((char*)&val, sizeof(uint32_t));

        this->storage[at] = val;
        at++;
    }
}

} // namespace riscvModel
