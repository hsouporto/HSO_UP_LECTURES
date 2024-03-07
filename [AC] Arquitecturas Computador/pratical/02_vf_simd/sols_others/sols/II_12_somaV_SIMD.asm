# Implementar a sub-rotina somaV que calcula o vetor soma, P + Q, e armazena-o em R
# void somaV(short int *P, short int *Q, short int *R, int n)

.data
P: .half 1,2,3,4,5,6,7,8,9,10,11,12
Q: .half 1,2,3,4,5,6,7,8,9,10,11,12
R: .space 24
n: .word 12

.text
la a0,P
la a1,Q
la a2,R
la a3,n
lw a3,0(a3)

somaV:
	ble a3,zero,fim
	lw t0,0(a0)
	lw t1,0(a1)
	ADD16 t0,t0,t1
	sw t0,0(a2)
	addi a0,a0,4
	addi a1,a1,4
	addi a2,a2,4
	addi a3,a3,-2				
	j somaV
fim:	
	ret
