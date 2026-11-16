# A sub-rotina MEDIA calcula a média dos elementos de um vetor utilizando a sub-rotina SOMA.



.data
seq: .word   3, 5, -1, 19, 32

.text
      la   a0, seq    # Para efeitos de teste: endere�o de
      li   a1, 5      # seq em a0 e tamanho de seq em a1.
      jal  ra, MEDIA  # Invoca sub-rotina.
      li   a7, 10     # Syscall para (exit status de forma limpa)
      ecall           # terminar programa.  ( a frente da subroutina nao tem dados, ra)



MEDIA: 
      mv   t0, zero                 # set counter to zero
      mv   t2, a1                   # save counter (for mean)


ciclo:

      beq  a1, zero, FIM            # test if we reach end of array 
      lw   t1, 0(a0)                # load value pointed by a0 to t1

      add  t0, t0, t1               # ad to the sum 
      addi a0, a0, 4                # next integer (4 bytes)
      addi a1, a1, -1               # decrement  number ofitems
      j    ciclo                    # jump to iterate again

FIM:  
      div a0, t0, t2                # final division mean
      ret


# alternative is to use the subroutine



#  sub-rotina MAXMED calcula a média dos elementos de dois vetores, v1 e v2, com n elementos, e
# retorna a média com maior valor.


.data
v1:	.word 1, 2, 3, -3, 23
v2:	.word 46, 1, 1, 1, 1

#v2:	.word 1, 2, 3, 4, 5

.text
	la  a0, v1
	li  a1, 5
	jal SOMA     # resultado = 26
	
	la  a0, v1
	li  a1, 5
	jal MEDIA    # resultado = 5
	
	la  a0, v1
	la  a1, v2
	li  a2, 5
	jal MAXMED   # resultado = max(5; 10) = 10 
	             # se v2 alt. resultado = max(5; 3) = 5 
	li a7, 10    # termina
	ecall

# int SOMA(int *v, int n);
SOMA:
    li   t0, 0

prox:
     lw   t1, 0(a0)
	 add  t0, t0, t1

	 addi a0, a0, 4
	 addi a1, a1, -1

	 bne  a1, zero, prox

	 mv   a0, t0
	 ret
	

# int MEDIA(int *v, int n);
MEDIA:
     addi sp, sp, -16       # reserve space stack
	 sw   ra, 0(sp)         # save tge Return address
	 sw   a1, 4(sp)         # save the original numebr of elements

	 jal  SOMA              # call subroutine, compute teh sum, a0

	 lw   a1, 4(sp)         # retorre a1, original from the stack

	 div  a0, a0, a1        # camputing mean

	 lw   ra, 0(sp)         # Retore RA address
	 addi sp, sp, 16        # Deallocate stack space
	 ret
	
# int MAXMED(int *v1, int *v2, int n);
MAXMED:
     addi sp, sp, -16       # Reserve space stack
	 sw   ra, 0(sp)         # save return address
	 sw   a1, 4(sp)         # save addres v2
	 sw   a2, 8(sp)         # save numenr eleents

	 mv   a1, a2            # Move, a0, a1 number eleemnts

	 jal  MEDIA


	 sw   s0, 12(sp)        # store a0
	 mv   s0, a0            # save a0 (meean v1) into s0

	 lw   a0, 4(sp)         # Retore a0 pinter     (V2)
	 lw   a1, 8(sp)         # numer of element restore it


	 jal  MEDIA
     

	 blt  s0, a0, L         # test with is larger (branch lower than)

	 mv   a0, s0            # swap it fot the other

L:	 lw   s0, 12(sp)        # restore things back
	 lw   ra, 0(sp)         # Rstore the return address from stack
	 addi sp, sp, 16        # Put stack pointer in the same place :)

	 ret




.data
v1:	.word 1, 2, 3, -3, 23
v2:	.word 46, 1, 1, 1, 1
#v2:	.word 1, 2, 3, 4, 5

.text
	la  a0, v1
	li  a1, 5
	jal SOMA     # resultado = 26
	
	la  a0, v1
	li  a1, 5
	jal MEDIA    # resultado = 5
	
	la  a0, v1
	la  a1, v2
	li  a2, 5
	jal MAXMED   # resultado = max(5; 10) = 10 
	             # se v2 alt. resultado = max(5; 3) = 5 
	li a7, 10    # termina
	ecall

# int SOMA(int *v, int n);
SOMA:li   t0, 0

prox:

     lw   t1, 0(a0)
	 add  t0, t0, t1
	 addi a0, a0, 4
	 addi a1, a1, -1
	 bne  a1, zero, prox

	 mv   a0, t0
	 ret
	
# int MEDIA(int *v, int n);
MEDIA:
     addi sp, sp, -16
	 sw   ra, 0(sp)
	 sw   a1, 4(sp)

	 jal  SOMA

	 lw   a1, 4(sp)

	 div  a0, a0, a1

	 lw   ra, 0(sp)
	 addi sp, sp, 16
	 ret
	
# int MAXMED(int *v1, int *v2, int n);
MAXMED:
     addi sp, sp, -16
	 sw   ra, 0(sp)
	 sw   a1, 4(sp)
	 sw   a2, 8(sp)

	 mv   a1, a2        # micinf numebr of eleemnt to a1, a0 pointer array
	 jal  MEDIA

	 sw   s0, 12(sp)
	 mv   s0, a0
	 lw   a0, 4(sp)
	 lw   a1, 8(sp)

	 jal  MEDIA

	 blt  s0, a0, L
	 mv   a0, s0

L:	 lw   s0, 12(sp)
	 lw   ra, 0(sp)
	 addi sp, sp, 16
	 ret

