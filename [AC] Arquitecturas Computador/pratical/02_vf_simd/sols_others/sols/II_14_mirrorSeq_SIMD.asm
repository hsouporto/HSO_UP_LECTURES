# Uma sequência de n pontos (xi, yi) do plano está guardada em memória como um vetor de 2n números inteiros com 8 bits {x1, y1, x2, y2, . . . , xn, yn}. 
# Escrever a sub-rotina mirrorSeq que troca as coordenadas horizontal e vertical de cada ponto. 
# void mirrorSeq(char *pt, int n)

.data
pt: .byte 1,2,3,4,5,6,7,8,9,10,11,12
n: .word 6

.text
la a0,pt
lw a1,0(a1)

mirrorSeq:
	ble a1,zero,fim
	lw t0,0(a0)
	SWAP8 t0,t0,t1
	sw t0,0(a0)
	addi a0,a0,4
	addi a1,a1,-2
	j mirrorSeq
fim:	
	ret
