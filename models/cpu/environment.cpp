#include "cpu/environment.hpp"

namespace riscvModel
{

Environment::Environment() {}

Environment::Environment(std::istream& _i, std::ostream& _o) : input(_i), output(_o) {}

void Environment::EnvCall(Registers& r, AddrSpace& aspace)
{

    if (r.ReadRegVal(17) == 93) // exit
    {
        r.stopped = true;
        return;
    }

    if (r.ReadRegVal(17) == 64) // write
    {
        int fd = (int)r.ReadRegVal(10);
        if (fd != 1)
        {
            return;
        }

        uint64_t addr = r.ReadRegVal(11);
        uint64_t len  = r.ReadRegVal(12);

        for (size_t i = 0; i < len; i++)
        {
            char c = (char)aspace.ReadByteFrom(addr + i);
            this->output.write(&c, 1);
        }

        return;
    }
}

} // namespace riscvModel
