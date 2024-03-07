.data
V:   .byte   5, -3, 32, 0, 1, 127, -1, -3
n:   .word   8
lim: .byte   1

.text
     la      a0, V
     lw      a1, n
     lw      a2, lim
     jal     contaInf     # Resultado em a0
     li      a7, 10   
     ecall
     
contaInf:
     srli    a1, a1, 2    # N. itera��es = n/4
     slli    t0, a2, 8    # Replica lim
     add     t0, t0, a2   # nos 4
     slli    t1, t0, 16   # bytes de t1
     add     t1, t1, t0   # t1 = (lim, lim, lim, lim)
     mv      t2, zero  

prox:
     lw      t0, 0(a0)
     scmplt8 t1, t0, t1   # (s0.B[3], s0.B[2], s0.B[1], s0.B[0]) < (lim, lim, lim, lim)?
     add8    t2, t2, t1   # Se sim s0.B[i]=0xff, caso contr�rio s0.B[i]=0x00 (i=0,...,3)
     addi    a0, a0, 4
     addi    a1, a1, -1
     bne     a1, zero, prox
     mv      a0, zero       
L0:  
     andi    t0, t2, 0x0FF
     add     a0, a0, t0   # Valor acumulado � <= 0
     srli    t2, t2, 8    # Pr�ximo byte de t2
     bne     t2, zero, L0
     
     neg     a0, a0
     ret

