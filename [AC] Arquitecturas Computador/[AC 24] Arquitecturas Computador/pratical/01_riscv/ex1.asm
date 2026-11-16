.data
seq: .word   3, 5, -1, 19, 32

.text
      la   a0, seq    # Para efeitos de teste: endere�o de
      li   a1, 5      # seq em a0 e tamanho de seq em a1.
      jal  ra, soma   # Invoca sub-rotina.
      li   a7, 10     # Syscall para (exit status de forma limpa)
      ecall           # terminar programa.  ( a frente da subroutina nao tem dados, ra)



soma: 
      mv   t0, zero                 # set counter to zero


ciclo:

      beq  a1, zero, FIM            # test if we reach end of array 
      lw   t1, 0(a0)                # load value pointed by a0 to t1

      add  t0, t0, t1               # ad to the sum 
      addi a0, a0, 4                # next integer (4 bytes)
      addi a1, a1, -1               # decrement  number ofitems
      j    ciclo                    # jump to iterate again

FIM:  mv   a0, t0                   # final move, to return in 10 register (mandatory)
      ret


# a) Determine quantos bytes de memória são ocupados pela sequência de elementos.
20 = 4*5

# b) Indique o valor decimal do quarto elemento da sequência.
19

# c) Indique o endereço de memória do terceiro elemento da sequência.
0x10010008 - assuming x10010000 + 4*2 bytes
0x10010000 - 0x10010004  -  0x10010008 


# d) Indique o endereço de memória da instrução j ciclo
0x00400030

# e) Tendo em consideração os valores dos registos, determine quantas vezes já foi executada a ins- trução lw t1, 0(a0)
3

# f) Determine o valor de a0 após terminar a execução do código.
58

# g) Descreva o que faz a sub-rotina
A sub-rotina calcula a soma dos elementos da sequ�ncia.	     