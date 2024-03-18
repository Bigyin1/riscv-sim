#include "cpu/cpu.hpp"

#include <gtest/gtest.h>

#include <iostream>

#include "ram/ram.hpp"

class TestCPU : public testing::Test
{
protected:
    TestCPU() : aspace(&ram), cpu(regs, aspace) {}

    static void SetUpTestSuite() { input.open("testdata/arithm.bin"); }

    static void TearDownTestSuite() { input.close(); }

    virtual void SetUp() override
    {

        uint32_t rinstr = 0;
        input.read((char*)&rinstr, sizeof(rinstr));

        currInstr = cpu.Decode(rinstr);
    }

    const riscvModel::Instruction* currInstr = nullptr;

    riscvModel::RAM<512>  ram  = {0};
    riscvModel::Registers regs = {0};
    riscvModel::AddrSpace aspace;

    riscvModel::CPU cpu;

    static std::ifstream input;
};

std::ifstream TestCPU::input;

TEST_F(TestCPU, addi_1)
{
    std::cout << "testing: "
              << "addi  x10, x0, 1" << std::endl;
    ASSERT_NE(currInstr, nullptr);

    cpu.Execute(currInstr);
    ASSERT_EQ(regs.ReadRegVal(10), 1);
}

TEST_F(TestCPU, addi_2)
{
    std::cout << "testing: "
              << "addi  x10, x10, -2" << std::endl;
    ASSERT_NE(currInstr, nullptr);

    regs.WriteAtReg(10, 1);

    cpu.Execute(currInstr);
    ASSERT_EQ(regs.ReadRegVal(10), -1);
}

TEST_F(TestCPU, add)
{
    std::cout << "testing: "
              << "add x12, x0, x10" << std::endl;
    ASSERT_NE(currInstr, nullptr);

    regs.WriteAtReg(10, (riscvModel::Registers::GPReg)-1);

    cpu.Execute(currInstr);
    ASSERT_EQ(regs.ReadRegVal(12), -1);
}

TEST_F(TestCPU, sub)
{
    std::cout << "testing: "
              << "sub x12, x12, x10" << std::endl;
    ASSERT_NE(currInstr, nullptr);

    regs.WriteAtReg(12, (riscvModel::Registers::GPReg)-1);
    regs.WriteAtReg(10, (riscvModel::Registers::GPReg)-1);

    cpu.Execute(currInstr);
    ASSERT_EQ(regs.ReadRegVal(12), 0);
}

int main(int argc, char** argv)
{

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
