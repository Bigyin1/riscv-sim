#include "cpu/cpu.hpp"

#include <gtest/gtest.h>

#include <iostream>

#include "ram/ram.hpp"

class TestCPU : public testing::Test
{
protected:
    TestCPU() : aspace(&ram), cpu(regs, aspace) {}

    static void SetUpTestSuite() { input.open("testdata/rv32i.bin"); }

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

TEST_F(TestCPU, sb)
{
    ASSERT_NE(currInstr, nullptr);

    regs.WriteAtReg(1, (riscvModel::Registers::GPReg)INT8_MIN);

    cpu.Execute(currInstr);
    ASSERT_EQ(aspace.ReadByteFrom(54), (uint8_t)INT8_MIN);
}

TEST_F(TestCPU, lb)
{
    ASSERT_NE(currInstr, nullptr);

    regs.WriteAtReg(2, (riscvModel::Registers::GPReg)500);

    aspace.WriteByteAt(500 - 27, INT8_MAX);

    cpu.Execute(currInstr);
    ASSERT_EQ(regs.ReadRegVal(3), INT8_MAX);
}

TEST_F(TestCPU, sh)
{
    ASSERT_NE(currInstr, nullptr);

    regs.WriteAtReg(1, (riscvModel::Registers::GPReg)INT16_MIN);

    cpu.Execute(currInstr);
    ASSERT_EQ(aspace.ReadHWordFrom(128), (uint16_t)INT16_MIN);
}

TEST_F(TestCPU, lh)
{
    ASSERT_NE(currInstr, nullptr);

    regs.WriteAtReg(5, (riscvModel::Registers::GPReg)610);

    aspace.WriteHWordAt(610 - 100, (uint16_t)-101);

    cpu.Execute(currInstr);
    ASSERT_EQ(regs.ReadRegVal(2), -101);
}

TEST_F(TestCPU, sw)
{
    ASSERT_NE(currInstr, nullptr);

    regs.WriteAtReg(1, (riscvModel::Registers::GPReg)INT32_MIN + 1);

    regs.WriteAtReg(6, (riscvModel::Registers::GPReg)512 + 128 - 4);

    cpu.Execute(currInstr);
    ASSERT_EQ(aspace.ReadWordFrom(512 - 4), (uint32_t)INT32_MIN + 1);
}

TEST_F(TestCPU, lw)
{
    ASSERT_NE(currInstr, nullptr);

    regs.WriteAtReg(5, (riscvModel::Registers::GPReg)-4);

    aspace.WriteWordAt(-4 + 104, (uint32_t)-101);

    cpu.Execute(currInstr);
    ASSERT_EQ(regs.ReadRegVal(2), -101);
}

TEST_F(TestCPU, beq)
{
    ASSERT_NE(currInstr, nullptr);

    regs.PCRelJmp(32);
    regs.WriteAtReg(1, (riscvModel::Registers::GPReg)-1);
    regs.WriteAtReg(2, (riscvModel::Registers::GPReg)-1);

    cpu.Execute(currInstr);
    ASSERT_EQ(regs.GetPC(), 32 - 16);
}

TEST_F(TestCPU, bne)
{
    ASSERT_NE(currInstr, nullptr);

    regs.PCRelJmp(32);
    regs.WriteAtReg(1, (riscvModel::Registers::GPReg)1);
    regs.WriteAtReg(2, (riscvModel::Registers::GPReg)1);

    cpu.Execute(currInstr);
    ASSERT_EQ(regs.GetPC(), 36);
}

TEST_F(TestCPU, blt)
{
    ASSERT_NE(currInstr, nullptr);

    regs.PCRelJmp(32);
    regs.WriteAtReg(3, (riscvModel::Registers::GPReg)-2);
    regs.WriteAtReg(4, (riscvModel::Registers::GPReg)-1);

    cpu.Execute(currInstr);
    ASSERT_EQ(regs.GetPC(), 32 - 24);
}

TEST_F(TestCPU, bge)
{
    ASSERT_NE(currInstr, nullptr);

    regs.PCRelJmp(32);
    regs.WriteAtReg(1, (riscvModel::Registers::GPReg)1);
    regs.WriteAtReg(2, (riscvModel::Registers::GPReg)0);

    cpu.Execute(currInstr);
    ASSERT_EQ(regs.GetPC(), 32 - 20);
}

int main(int argc, char** argv)
{

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
