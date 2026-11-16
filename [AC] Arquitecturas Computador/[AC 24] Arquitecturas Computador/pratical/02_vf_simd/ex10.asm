/*
10. Considerar um vetor V com n números inteiros de 8 bits (tipo char em C/C++) com dimensão
favorável ao paralelismo do processamento a realizar. */


.data
V: 	.byte 3, 5, -3, 6, 0, -6, 6, 100
n: 	.word 8
lim: .byte 1

.text
	la		a0, V 
	lw		a1, n 
	lb 		a2, lim 
	jal 	ra, contaInf 
	li 		a7, 10 
	ecall 

# 01 02 03 04 "
contaInf:

	srli 	a1, a1, 2		# n/4  

	slli	t0, a2, 8		# replicate the lim in the reg t0 in two lower bytes     |0x00 00 02 00| = t2 
	add		t0, t0, a2		# add in the two lower bytes							 |0x00 00 00 02| + T2   =  |0x00 00 02 02|	
	
	slli	t1, t0, 16		# bytes of t1											 |0x00 00 02 02| 16 = 0x02 02 00 00| 
	add		t1, t1, t0		# t1 = (lim, lim, lim, lim)								 |0x00 00 02 02|	= |0x02 02 02 02|
	
	mv 		t2, zero		# counter of numbers bellow lim

LOOP:
	lw		t0, 0(a0)
	scmplt8 t1, t0. t1		# (t0.B[3], t0.B[2], t0.B[1], t0.B[0]) < (lim, lim, lim, lim) ?

	add8 	t2, t2, t1      # if yes, t0.B[i]=0xFF, otherwise, t0.B[i] = 0x00    | coun byte3, count byte2,  0)

	addi 	a0, a0, 4
	addi	a1, a1, -1
	bne		a1, zero, LOOP

	mv		a0, zero

LO:
	andi	t0, t2, 0x0ff	# keep only lower bytes values (mask) |BYTE3| BYTE2| BYTE1| BYTE0|  & |0x00| 0x000| 0x00| 0xFF|
	add		a0, a0, t0		# accum  value is <=0
	srli	t2, t2, 8		# n3xt byte of t2			|BYTE3| BYTE2| BYTE1| BYTE0| > |0x00|BYTE3| BYTE2| BYTE1| 
	bne		t2, zero, LO 	# unrool

	neg 	a0, a0
	ret



.data
V:   .byte   5, -3, 32, 0, 1, 127, -1, -3
n:   .word   8
lim: .byte   1

.text
     la      a0, V
     lw      a1, n
     lb      a2, lim
     jal     contaInf     # Resultado em a0
     li      a7, 10   
     ecall
     
contaInf:
     srli    a1, a1, 2    # N. itera��es = n/4
							# a0 = |0x00 | 0x00 | 0x00 |0x01
     slli    t0, a2, 8    # Replica lim     |0x00 | 0x00 | 0x01 |0x00
     add     t0, t0, a2   # nos 4			 |0x00 | 0x00 | 0x01 |0x01

     slli    t1, t0, 16   # bytes de t1 |0x01 | 0x01 | 0x00 |0x00
     add     t1, t1, t0   # t1 = (lim, lim, lim, lim)  |0x01 | 0x01 | 0x01 |0x01
     
	 mv      t2, zero   	# counter set to rero    


prox:
	 lw  t0, 0(a0)    # As duas instru��es seguintes n�o s�o suportadas por RARS
     scmplt8 t3, t0, t1   # (t0.B[3], t0.B[2], t0.B[1], t0.B[0]) < (lim, lim, lim, lim)?
                          # Se sim t1.B[i]=0xff, caso contr�rio t1.B[i]=0x00 (i=0,...,3)
     add8    t2, t2, t3   # CORRE��O: usar t3 nesta instru��o e na anterior (n�o alterar t1)
     
	 addi    a0, a0, 4	  # proceed address nex address (4 bytes ahead)
     addi    a1, a1, -1		# decrement counter
     bne     a1, zero, prox


     mv      a0, zero    

L0:  
	 andi    t0, t2, 0x0FF	# |0x00 | 0x000 |   |    | 
     slli     t0, t0, 24   # expandir (extens�o de sinal)  [CORRE��O]
     srai     t0, t0, 24   #

     add     a0, a0, t0   # Valor acumulado � <= 0
     srli    t2, t2, 8    # Pr�ximo byte de t2

     bne     t2, zero, L0

     neg     a0, a0

     ret	
	
	 	

	






































########################################################
a) Desenvolver a sub-rotina conta_inf que determina quantos elementos do vetor V são inferiores a um valor lim. Considerar que o protótipo da função a invocar em C é:
int conta_inf(char *V, int n, char lim)
 */

.data
V: .byte 1,2,3,4,5,6,7,8,9,10,11,12
n: .word 12
lim: .byte 6	

.text
la 		a0,V			# load address
lw 		a1,n			# load word
lbu 	a2,lim			# load byte unsigned
jal     conta_inf     	# Resultado em a0
li      a7, 10   		# exit clean
ecall


# loop until the end 
conta_inf:
	slli 	t0,a2,8			# rotate 8 bytes, 
	or   	a2,t0,a2		# duplicate lim (along the bytes)   now two bytes have same value
	PKBB16 	a2,a2,a2		# Pack -> rd = CONCAT(rs1.H[0],rs2.H[0]); put lim 4 times in the register to compare with 4 elements at a time
							# Pack bottom half-words of 2 regs
							# this makes as single 
	add 	t0,zero,zero	# parallel negative counter




# set the labe to iterate among 
prox:	
	beq 	a1,zero,fim		# test if we reach end
	addi  	a1,a1,-4		# decrement 4 units (4 bytes at once)
	lw 		t1,0(a0)		# load the contest
	addi 	a0,a0,4			# set pointer to next integer (4 bytes ahead)
	SCMPLT8 t1,t1,a2		# 4 element compare less than (T = 0xFF, F = 0x00), in the a2 pack
	ADD8 	t0,t0,t1		# Add the -1's (only the signals bits)
	j prox


# set the final unpacking 
fim:	
	SUNPKD810 	t2,t0			# Unpack -> rd.H[1] = rs1.B[1]; rd.H[0] = rs1.B[0]
	SUNPKD832 	t3,t0			# Unpack -> rd.H[1] = rs1.B[3]; rd.H[0] = rs1.B[2]
	ADD16 		t1,t2,t3			# ADD the 16 bit parts
	CRAS16 		t1,t1,t1			# Cross add 16 bit parts (upper bits), cross sub (lower bits, will be discarded)
									# CRAS16 rd,ra,rb Cross add and sub rd.H[0] = ra.H[0] + rb.H[0]
	srai 		t0,t1,16			# Shift arithmetical, keeps sign (each true is "-1")
	sub 		a0,zero,t0			# change signal
	ret

# https://github.com/riscv/riscv-p-spec/blob/master/P-ext-proposal.adoc


########################################################
/*
b) Desenvolver a sub-rotina conta_ocorr que determina o número de ocorrências de um elemento
val no vetor V . O protótipo da função a invocar em C é:
int conta_ocorr(char *V, int n, char val)

 */


.data
V: .byte 1,2,3,4,5,6,7,8,9,10,11,12
n: .word 12
val: .byte 6	

.text
la 		a0,V			# load address
lw 		a1,n			# load word
lbu 	a2,val			# load byte unsigned
jal     conta_inf     	# Resultado em a0
li      a7, 10   		# exit clean
ecall


# loop until the end 
conta_equal:
	slli 	t0,a2,8			# load 0x000010
	or   	a2,t0,a2		# duplicate lim (along the bytes)
	PKBB16 	a2,a2,a2		# Pack -> rd = CONCAT(rs1.H[0],rs2.H[0]); put lim 4 times in the register to compare with 4 elements at a time
							# Pack bottom half-words of 2 regs
							# this makes as single 
	add 	t0,zero,zero	# parallel negative counter




# set the label to iterate among 
prox:	
	beq 	a1,zero,fim		# test if we reach end
	addi  	a1,a1,-4		# decrement 4 units (4 bytes at once)
	lw 		t1,0(a0)		# load the contest
	addi 	a0,a0,4			# set pointer to next integer (4 bytes ahead)
	SCMPLT8 t1,t1,a2		# 4 element compare less than (T = 0xFF, F = 0x00), in the a2 pack
	ADD8 	t0,t0,t1		# Add the -1's (only the signals bits)
	j prox


# set the final unpacking 
fim:	
	SUNPKD810 	t2,t0			# Unpack -> rd.H[1] = rs1.B[1]; rd.H[0] = rs1.B[0]
	SUNPKD832 	t3,t0			# Unpack -> rd.H[1] = rs1.B[3]; rd.H[0] = rs1.B[2]
	ADD16 		t1,t2,t3			# ADD the 16 bit parts
	CRAS16 		t1,t1,t1			# Cross add 16 bit parts (upper bits), cross sub (lower bits, will be discarded)
									# CRAS16 rd,ra,rb Cross add and sub rd.H[0] = ra.H[0] + rb.H[0]
	srai 		t0,t1,16			# Shift arithmetical, keeps sign (each true is "-1")
	sub 		a0,zero,t0			# change signal
	ret