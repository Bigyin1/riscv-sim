#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include "cpu/cpu.hpp"
#include "ram/ram.hpp"

TEST(Semihosting, helloworld)
{

    riscvModel::RAM<UINT16_MAX> ram = {0};

    std::ifstream hw("testdata/helloworld.bin");
    ram.LoadCode(hw, 0);
    hw.close();

    riscvModel::AddrSpace aspace = {&ram};
    riscvModel::Registers regs   = {0};

    std::ostringstream      output;
    riscvModel::Environment env(std::cin, output);

    riscvModel::CPU cpu(regs, aspace, env);

    while (!cpu.IsStopped())
    {
        auto ri = cpu.Fetch();

        auto instr = cpu.Decode(ri);
        ASSERT_NE(instr, nullptr);

        cpu.Execute(instr);
    }

    ASSERT_EQ(output.str(), "Hello World!\n");
}

int main(int argc, char** argv)
{

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
