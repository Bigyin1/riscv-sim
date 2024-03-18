#include "ram/ram.hpp"

namespace riscvModel
{

template class RAM<512>;
template class RAM<UINT16_MAX>;

template <std::size_t RamSz>
RAM<RamSz>::RAM(uint64_t _start) : start(_start)
{
}

template <std::size_t RamSz>
std::pair<uint64_t, uint64_t> RAM<RamSz>::GetAddrRange()
{

    return {this->start, this->start + this->storage.size() * sizeof(this->storage[0])};
}

template <std::size_t RamSz>
uint32_t RAM<RamSz>::ReadWordFrom(uint64_t addr)
{
    size_t storageIdx = addr / 4;
    return this->storage[storageIdx];
}

template <std::size_t RamSz>
void RAM<RamSz>::WriteWordAt(uint64_t addr, uint32_t w)
{
    size_t storageIdx         = addr / 4;
    this->storage[storageIdx] = w;
}

template <std::size_t RamSz>
uint16_t RAM<RamSz>::ReadHWordFrom(uint64_t addr)
{
    size_t storageIdx = addr / 4;
    size_t bucketIdx  = addr % 2;

    uint32_t word = storage[storageIdx];

    uint16_t* bucket = (uint16_t*)&word;

    return bucket[bucketIdx];
}

template <std::size_t RamSz>
void RAM<RamSz>::WriteHWordAt(uint64_t addr, uint16_t hw)
{
    size_t storageIdx = addr / 4;
    size_t bucketIdx  = addr % 2;

    uint32_t word = storage[storageIdx];

    uint16_t* bucket  = (uint16_t*)&word;
    bucket[bucketIdx] = hw;

    storage[storageIdx] = word;
}

template <std::size_t RamSz>
uint8_t RAM<RamSz>::ReadByteFrom(uint64_t addr)
{
    size_t storageIdx = addr / 4;
    size_t bucketIdx  = addr % 4;

    uint32_t word = storage[storageIdx];

    uint8_t* bucket = (uint8_t*)&word;

    return bucket[bucketIdx];
}

template <std::size_t RamSz>
void RAM<RamSz>::WriteByteAt(uint64_t addr, uint8_t b)
{
    size_t storageIdx = addr / 4;
    size_t bucketIdx  = addr % 4;

    uint32_t word = storage[storageIdx];

    uint8_t* bucket   = (uint8_t*)&word;
    bucket[bucketIdx] = b;

    storage[storageIdx] = word;
}

template <std::size_t RamSz>
void RAM<RamSz>::LoadCode(std::ifstream& f, size_t at)
{

    while (!f.eof())
    {
        uint32_t val = 0;
        f.read((char*)&val, sizeof(val));

        this->storage[at] = val;
        at++;
    }
}

} // namespace riscvModel
