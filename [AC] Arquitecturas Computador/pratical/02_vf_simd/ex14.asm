/*
14. Uma sequência de n pontos (xi, yi) do plano está guardada em memória como um vetor de 2n
números inteiros com 8 bits {x1, y1, x2, y2, . . . , xn, yn}. Escrever a sub-rotina mirrorSeq que troca as
coordenadas horizontal e vertical de cada ponto. O protótipo desta sub-rotina em C é:
void mirrorSeq(char *pt, int n)
 */


# void mirrorSeq(char *pt, int n);


.data
pt: .byte 1,2,3,4,5,6,7,8,9,10,11,12
n: .word 6

.text
la a0   ,pt                 # load address
lw a1   ,0(a1)              # load word from address pointer

mirrorSeq:
	ble     a1,zero,fim     # test if we reach end
	lw      t0,0(a0)        # load the word

	SWAP8   t0,t0,t1        # swap bytes from int (4 bytes)
	sw      t0,0(a0)        # store it
	
    addi    a0,a0,4         # net int (4 bytes)
	addi    a1,a1,-2        # next set of bytes (two pairs)
	j       mirrorSeq       # jump to label

fim:	
	ret


    



    