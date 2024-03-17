.global _start

_start: addi  x10, x0, 1     
        addi  x10, x10, -2

        add x12, x0, x10
        sub x12, x12, x10
