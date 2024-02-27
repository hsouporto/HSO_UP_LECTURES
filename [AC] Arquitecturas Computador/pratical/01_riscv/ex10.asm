# a) Determinar a posição do bit 1 mais significativo da representação binária de um número inteiro.
.text
MSB:
    li a0, 0
    li a1, 31
    bge a2, a0, FIM

    xori a2, a2, -1     # FFFFFFFFFFFFFFFFFFFFFFF         
    srli a2, a2,  1     # shift right
    addi a1, a1, -1     # add i
    bne a2, a0, MSB     # while no equal, jump

FIM:
    add a0, zero, a1
    ret


# ou

.data
# Assume-se que o n�mero � n�o nulo
num1: .word 1   # Res=0

#num2: .word 38   # Res=5
#num3: .word 0x80000000  # Res=31

.text
      lw   a0, num1
      jal  ra, pos1MSB   
      li   a7, 10       # Resultado em a0     
      ecall           

pos1MSB:
      li   t0, 31       # �ndice do MSB
      li   t1, 1
      slli t1, t1, 31   # 0x80 00 00 00

L1:   
      and  t2, a0, t1
      bne  t2, zero, fim

      addi t0, t0, -1
      slli a0, a0, 1

      bne  a0, zero, L1

fim:  mv   a0, t0
      ret