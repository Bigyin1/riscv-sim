#include "cpu/cpu.hpp"

#include <iostream>

#include "ram/ram.hpp"

static const riscvModel::Instruction* nextInstr(riscvModel::CPU& cpu, riscvModel::RAM& ram)
{
    static size_t loadAddr = 0;

    auto ri    = ram.ReadWordFrom(loadAddr);
    auto instr = cpu.Decode(ri);
    if (instr == nullptr)
    {
        std::cout << "failed to decode" << std::endl;
        return nullptr;
    }

    loadAddr += sizeof(riscvModel::RawInstr);

    return instr;
}

int main()
{

    uint64_t              loadAddr = 0;
    riscvModel::RAM       ram(loadAddr);
    riscvModel::Registers regs(loadAddr);

    std::ifstream bin("arithm.bin");
    ram.LoadCode(bin, loadAddr);

    riscvModel::AddrSpace aspace(&ram);

    riscvModel::CPU cpu(regs, aspace);

    std::cout << "testing: "
              << "addi  x10, x0, 1" << std::endl;
    auto instr = nextInstr(cpu, ram);
    if (instr == nullptr)
        return 1;

    cpu.Execute(instr);

    if (regs.ReadRegVal(10) != 1)
    {
        std::cout << "got: " << regs.ReadRegVal(10) << "wanted: 1" << std::endl;
    }

    std::cout << "testing: "
              << "addi  x10, x10, -2" << std::endl;
    instr = nextInstr(cpu, ram);
    if (instr == nullptr)
        return 1;

    cpu.Execute(instr);

    if (regs.ReadRegVal(10) != (uint32_t)-1)
    {
        std::cout << "got: " << (int32_t)regs.ReadRegVal(10) << "wanted: -1" << std::endl;
    }

    std::cout << "testing: "
              << "add x12, x0, x10" << std::endl;
    instr = nextInstr(cpu, ram);
    if (instr == nullptr)
        return 1;

    cpu.Execute(instr);

    if (regs.ReadRegVal(12) != (uint32_t)-1)
    {
        std::cout << "got: " << (int32_t)regs.ReadRegVal(12) << "wanted: -1" << std::endl;
    }

    std::cout << "testing: "
              << "sub x12, x12, x10" << std::endl;
    instr = nextInstr(cpu, ram);
    if (instr == nullptr)
        return 1;

    cpu.Execute(instr);

    if (regs.ReadRegVal(12) != 0)
    {
        std::cout << "got: " << regs.ReadRegVal(12) << "wanted: 0" << std::endl;
    }

    return 0;
}
