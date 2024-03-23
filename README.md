# RISC-V simulator library

Supports basic rv32i

*ecall* is done with semihosting.

TODO: bitwise instructions of rv32i

## How to run tests
1. cmake -B ./build  -DCMAKE_BUILD_TYPE=Debug

2. cmake --build ./build -j 6 --config Debug

3. ctest --test-dir ./build --output-on-failure
