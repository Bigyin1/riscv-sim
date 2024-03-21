#pragma once

#include <iostream>
#include <istream>

#include "addrSpace.hpp"
#include "registers.hpp"

namespace riscvModel
{

class Environment // better be abstract
{
private:
    std::istream& input  = std::cin;
    std::ostream& output = std::cout;

public:
    Environment();
    Environment(std::istream& _i, std::ostream& _o);

    void EnvCall(Registers& regs, AddrSpace& aspace);
};

} // namespace riscvModel
