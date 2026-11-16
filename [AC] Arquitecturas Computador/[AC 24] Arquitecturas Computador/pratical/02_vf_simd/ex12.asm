/*
12. Considerar os vetores P , Q e R, contendo n valores representados em 16 bits. Assumir o protótipo
da função a chamar em C para executar as sub-rotinas seguintes. Assumir a não ocorrência de overflow.


########################################################
a) Implementar a sub-rotina somaV que calcula o vetor soma, P + Q, e armazena-o em R.
void somaV(short int *P, short int *Q, short int *R, int n)
 */



# ou
.data
P: .half 1,2,3,4,5,6,7,8,9,10,11,12
Q: .half 1,2,3,4,5,6,7,8,9,10,11,12
R: .space 24
n: .word 12

.text
	la a0,P         # load address
	la a1,Q         # load address
	la a2,R         # load address
	la a3,n         # load address
	lw a3,0(a3)     # load word from address pointer


somaV:
	ble a3,zero,fim     # test ie we reach end numbers
	lw t0,0(a0)         # load word /consireing half word
	lw t1,0(a1)         # load other half 2 part word

	ADD16 t0,t0,t1      # add 16 the two halfs
	sw t0,0(a2)         # store resulntin word , 

	addi a0,a0,4        # next int (two short word)    
	addi a1,a1,4        # same
	addi a2,a2,4        # same

	addi a3,a3,-2		# we hanlde two halfs at once (4 bytes chunk since)	    	
	j somaV
fim:





# using a single cicle
somaV_single:
    ble     a3, zero, fim
    lw      t0, 0(a0)
    lw      t1, 0(a1)

    addi    t2, t1, t0
    sw      t2, 0(a2)
    addi    a0, a0, 2
    addi    a1, a1, 2
    addi    a2, a2, 4
    addi    a3, a3, -1
    j       somaV_sigle
       

########################################################
/* 
b) Implementar a sub-rotina altV que multiplica cada elemento de P pelo escalar k.
void altV(short int *P, int n, short int k)
*/



 # ou
 .data
P: .half 1,2,3,4,5,6,7,8,9,10,11,12
R: .space 24
K: .half 6
n: .word 12

.text
la a0,P         # load address
la a1,K         # load address
la a2,R         # load address
la a3,n         # load address
lw a3,0(a3)     # load word from address pointer


altV:
# replicate the value
	slli	t0, a2, 8		# replicate the lim in the reg t0 4 bytes
	add		t0, t0, a2		# add in the 4
	slli	t1, t0, 16		# bytes of t1
	add		t1, t1, t0		# t1 = (lim, lim, lim, lim)


LOOP:
	ble a3,zero,fim     # test ie we reach end numbers
	lw t0,0(a0)         # load word /consireing half word

	MUL16 t0,t0,t1      # add 16 the two halfs
	sw t0,0(a2)         # store resulntin word , 

	addi a0,a0,4        # next int (two word)    
	addi a1,a1,4        # same
	addi a2,a2,4        # same

	addi a3,a3,-2		# we hanlde two halfs at once (4 bytes chunk since)	    	
	j LOOP
fim:




    


########################################################
/* 
c) Implementar a sub-rotina msubV que, utilizando as sub-rotinas anteriores (somaV e altV), calcula
P − k Q e armazena o resultado em R.
void msubV(short int *P, short int *Q, short int *R, int n, short int k)
*/

