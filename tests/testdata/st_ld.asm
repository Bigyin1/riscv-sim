.global _start

_start: 

    addi x1, x0, 100
    sb x1, 1000(x0)
    lb x2, 1000(x0)

    addi x1, x0, -1
    sh x1, 1000(x0)
    lh x2, 1000(x0)
