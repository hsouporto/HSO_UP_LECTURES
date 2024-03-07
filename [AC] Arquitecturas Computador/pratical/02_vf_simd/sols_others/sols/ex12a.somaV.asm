.data
P:   .half  512, -3, -32, 0, 1, 127, -1, 4
P:   .half  -513, 13, 32, 0, 1, 127, 2, -3
R:   .space 16
n:   .word  8
 
.text
     la     a0, P
     la     a1, Q
     la     a2, R
     lw     a3, n
     jal    somaV     # Não retorna nada
     li     a7, 10   
     ecall
     
somaV:
     srli   a3, a3, 1    # N. iterações = n/2 (processa 2 halfwords por iteração)    
prox:beq    a3, zero, fim
     lw     t0, 0(a0)
     lw     t1, 0(a1)
     add16  t2, t0, t1
     sw     t2, 0(a2)
     addi   a0, a0, 4
     addi   a1, a1, 4
     addi   a2, a2, 4
     addi   a3, a3, -1
     j      prox
fim: ret