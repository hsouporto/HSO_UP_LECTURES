.data
X:  .float -2.0, 4.0, -3.0003, -4.8, 1.0
Y:  .float 10.2, 4.7, -4.94, -1.0, 2.0
n:  .word  5

.text
    la  a0, X
    la  a1, Y
    lw  a2, n
    jal ra, prodInt
    li  a7, 10      # have the result in fa0
    ecall


prodInt:
    fcvt.s.w    ft7, zero

LOOP:
    beq         a2, zero, FIM
    flw         ft0, 0(a0)
    flw         ft1, 0(a1)
    fmadd.s     ft7, ft0, ft1, ft7      # this updfates the accumulator with xi*yi


NEXT:
    addi        a0, a0, 4
    addi        a1, a1, 4
    addi        a2, a2, -1
    j           LOOP

FIM:
    fcvt.d.s    fa0, ft7
    ret 

    
