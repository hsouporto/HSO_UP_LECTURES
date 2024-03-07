.data
pontos: .byte   5, -3, 32, 0, 1, 127, -1, -3
n:      .word   4
 
.text
     la     a0, pontos
     lw     a1, n
     jal    mirrorSeq     # Não retorna nada
     li     a7, 10   
     ecall
     
mirrorSeq:
     srli   a1, a1, 1    # N. iterações = n/2 (processa 2 pontos por iteração)    
prox:
     lw     t0, 0(a0)
     swap8  t0, t0       # troca coordenadas de cada ponto
     sw     t0, 0(a0)
     addi   a0, a0, 4
     addi   a1, a1, -1
     bne    a1, zero, prox
     ret
