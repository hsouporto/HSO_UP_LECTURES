
# a) Contar o número de bits a 1 na representação binária de um valor do tipo word.


.data
num: .word 38   # Res=3

#num: .word 32  # Res=1
#num: .word 0   # Res=0
#num: .word 1   # Res=1
#num: .word 0x80000000  # Res=1

.text
      la   t0, num
      lw   a0, 0(t0)
      jal  ra, nbits1   
      li   a7, 10     
      ecall   

nbits1:
      mv   t0, zero                 # Init counter register (zero)
           
ciclo:
      beq  a0, zero, fim            # while  not zero, proceeed
      andi t1, a0, 1                # x & 0000000000000001 = 0, 1
      add  t0, t0, t1               # add resulting value (accumulator ' result mask')
      srli a0, a0, 1                # rotate right the bit
      j    ciclo
      
fim:  mv   a0, t0                   # moving t0 temp register, a0
      ret


# b) Determinar o número de bits iguais em posições correspondentes de dois valores do tipo word

.data
num1: .word 38   # Res=3
num2: .word 38  # Res=1

#num: .word 0   # Res=0
#num: .word 1   # Res=1
#num: .word 0x80000000  # Res=1

.text
      la   t0, num1
      la   t1, num2
      lw   a0, 0(t0)
      lw   a1, 0(t1)

      jal  ra, NBITS_2WORD   
      li   a7, 10     
      ecall   

NBITS_2WORD:
      mv   t0, zero                 # set counter to zero
      addi t3, t3, 32               # staing 32 bits to be compared
           
LOOP:
      beq  t3, zero, FIM            

      andi t1, a0, 1                # mask number 0 . 0 or 1
      andi t2, a1, 1                # mask number 1 . 0 or 1

      bge  t2, t1, COUNT            # compare, if true count ans proceed
      j    NEXT                     # else, go net bit


COUNT:     
      addi t0, t0, 1

NEXT:
      addi t3, t3, -1               # decrement counter
      srli a0, a0, 1                # rotate right both numbers
      srli a1, a1, 1
      j    LOOP

      
FIM:  
      mv   a0, t0                   # final move
      ret