.global _start

_start: addi  x10, x0, 1     
        addi  x10, x10, -2

        add x12, x0, x10
        sub x12, x12, x10

        sb x1, 54(x0)
        lb x3, -27(x2)
lbl1:
        sh x1, 128(x0)
        lh x2, -100(x5)
lbl2:
        sw x1, -128(x6)
        lw x2, 104(x5)


        beq x1, x2, lbl1
        bne x1, x2, lbl2

        blt x3, x4, lbl1
        bge x1, x2, lbl2
lbl3:
        lbu x3, -27(x2)
        lhu x2, 100(x5)

        jalr x2, -28(x1)
        jal x8, loop
        jal x8, lbl3

loop:
        bltu x3, x4, loop
        bgeu x3, x4, lbl3

        lui x5, 1000
        auipc x5, 512






