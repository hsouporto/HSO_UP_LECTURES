# Desenvolver a sub-rotina conta_inf que determina quantos elementos do vetor V s�o inferiores a um valor lim.
# int conta_inf(char *V, int n, char lim)
.data
V: .byte 1,2,3,4,5,6,7,8,9,10,11,12
n: .word 12
lim: .byte 6	

.text
la a0,V
lw a1,n
lbu a2,lim
jal     conta_inf     # Resultado em a0
li      a7, 10   
ecall

conta_inf:
	slli t0,a2,8
	or   a2,t0,a2		# duplicate lim
	PKBB16 a2,a2,a2		# Pack -> rd = CONCAT(rs1.H[0],rs2.H[0]); put lim 4 times in the register to compare with 4 elements at a time
	add t0,zero,zero	# parallel negative counter

prox:	

	beq a1,zero,fim
	addi, a1,a1,-4
	lw t1,0(a0)
	addi a0,a0,4
	SCMPLT8 t1,t1,a2		# 4 element compare less than (T = 0xFF, F = 0x00)
	ADD8 t0,t0,t1			# Add the -1's
	j prox

	
fim:	
	SUNPKD810 t2,t0			# Unpack -> rd.H[1] = rs1.B[1]; rd.H[0] = rs1.B[0]
	SUNPKD832 t3,t0			# Unpack -> rd.H[1] = rs1.B[3]; rd.H[0] = rs1.B[2]
	ADD16 t1,t2,t3			# ADD the 16 bit parts
	CRAS16 t1,t1,t1			# Cross add 16 bit parts (upper bits), cross sub (lower bits, will be discarded)
	srai t0,t1,16			# Shift arithmetical, keeps sign (each true is "-1")
	sub a0,zero,t0			# change signal
	ret
