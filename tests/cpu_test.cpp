#include "cpu/cpu.hpp"

#include <gtest/gtest.h>

#include <iostream>

#include "ram/ram.hpp"

class TestArithm : public testing::Test
{
protected:
    const riscvModel::Instruction* getNextInstr()
    {

        auto ri    = ram.ReadWordFrom(loadAddr);
        auto instr = cpu->Decode(ri);
        if (instr == nullptr)
        {
            return nullptr;
        }

        loadAddr += sizeof(riscvModel::RawInstr);
        return instr;
    }

    virtual void SetUp() override
    {
        std::ifstream bin("arithm.bin");
        ram.LoadCode(bin, loadAddr);

        aspace = new riscvModel::AddrSpace(&ram);

        this->cpu = new riscvModel::CPU(regs, *aspace);
    }

    virtual void TearDown() override { delete cpu; }

    riscvModel::RAM       ram  = {0};
    riscvModel::Registers regs = {0};

    riscvModel::AddrSpace* aspace = nullptr;
    riscvModel::CPU*       cpu    = nullptr;

    uint64_t loadAddr = 0;
};

TEST_F(TestArithm, test1)
{

    std::cout << "testing: "
              << "addi  x10, x0, 1" << std::endl;
    auto instr = this->getNextInstr();
    ASSERT_NE(instr, nullptr);

    cpu->Execute(instr);
    ASSERT_EQ(regs.ReadRegVal(10), 1);

    std::cout << "testing: "
              << "addi  x10, x10, -2" << std::endl;
    instr = this->getNextInstr();
    ASSERT_NE(instr, nullptr);

    cpu->Execute(instr);
    ASSERT_EQ(regs.ReadRegVal(10), (uint32_t)-1);

    std::cout << "testing: "
              << "add x12, x0, x10" << std::endl;
    instr = this->getNextInstr();
    ASSERT_NE(instr, nullptr);

    cpu->Execute(instr);
    ASSERT_EQ(regs.ReadRegVal(12), (uint32_t)-1);

    std::cout << "testing: "
              << "sub x12, x12, x10" << std::endl;
    instr = this->getNextInstr();
    ASSERT_NE(instr, nullptr);

    cpu->Execute(instr);
    ASSERT_EQ(regs.ReadRegVal(12), 0);
}

int main(int argc, char** argv)
{

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
