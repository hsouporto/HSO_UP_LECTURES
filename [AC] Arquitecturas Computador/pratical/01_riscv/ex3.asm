.data
num: .word 4



.text
     la   t0, num
     lw   a0, 0(t0)
     jal  ra, sumSquare   
     li   a7, 10       # Ver resultado em a0 !
     ecall             # Termina 

     
          
sumSquare:
     addi sp, sp, -16  # reserve space for 4 word in the stack
     sw   ra, 12(sp)   # save return address (mandatory)
     sw   s0, 8(sp)    # Save s0, 
     sw   s1, 4(sp)    # saved (s0 e s1)

     add  s0, a0, x0   # Copy value of n into s0 (equal add with zero - x0)
     add  s1, x0, x0   # set caccumulator s1  to zero (x0 = 0) =0

loop:

     bge  x0, s0, FIM  # Jumo if s0 n�o � positivo
     add  a0, s0, x0   # Copia s0 para a0 para invocar 'square' (sum with x0 =0)
     jal  ra, square   # Call the sub-rotina 'square'

     add  s1, s1, a0   # update s1 with return value a0
     addi s0, s0, -1   # decrement s0 in 1
     jal  x0, loop     # iterate again 
     
FIM: 

     add  a0, s1, x0   # Copy to a0 the accumulated sum holded in s1

     lw   ra, 12(sp)   # recover ra
     lw   s0, 8(sp)    # recover s0
     lw   s1, 4(sp)    # recover s1
     
     addi sp, sp, 16   # release the allocated stack space 
     jr   ra           # final return
		
square:                  # our subroutine
     mul  a0, a0, a0
     ret
     
