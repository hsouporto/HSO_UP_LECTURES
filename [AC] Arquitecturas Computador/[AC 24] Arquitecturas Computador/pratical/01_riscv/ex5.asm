# OK a) Determinar o valor máximo de um vetor com dados do tipo byte

.data
array:
    .byte 1, 2, 3, 13, 5, 6, 7, 20, 9, 10


.text
BEGIN:
	la   a0, array          # load array
	li   a1, 10             # number of items
	jal  ra, MAX_VALUE_BYTE
	li   a7, 10
	ecall
	


MAX_VALUE_BYTE:	
	li   t0, -128			# t0 holds the temporary maximum

LOOP:
    beq  a1, zero, FIM      # test if we reach end of array(items)
	lbu  t1, 0(a0)			# load t1 with the new value to be checked
	bge  t0, t1, NEXT       # try to compare, if not jump, else proceed
	mv   t0, t1				# a new maximum was found save it to t0

NEXT:
	addi a0, a0, 1			# update pointer to next byte
	addi a1, a1, -1			# decr number of bytes to check
	J    LOOP               # loop again

FIM:        
	mv   a0, t0				# move temporary t0 value to return register a0
	ret

# Alternative Solution




 
        
        


# OK b) Determinar o valor máximo de um vetor com dados do tipo unsigned word
.data
array:
    .word 1, 2, 3, 13, 5, 6, 7, 20, 9, 10

.text
BEGIN:
	la   a0, array          # load array
	li   a1, 10             # number of items
	jal  ra, MAX_VALUE_WORD
	li   a7, 10
	ecall
	
MAX_VALUE_WORD:	
	li   t0, 0		# t0 holds the temporary maximum

LOOP:
    beq  a1, zero, FIM      # test if we reach end of array(items)
	lw  t1, 0(a0)		    # load t1 with the new value to be checked
	bgeu  t0, t1, NEXT      # try to compare, if not jump, else proceed
	mv   t0, t1		# a new maximum was found

NEXT:
	addi a0, a0, 4		# update pointer to next word
	addi a1, a1, -1		# decr number of bytes to check
	J    LOOP               # loop again

FIM:        
	mv   a0, t0
	ret


# OK c) Determinar o valor mínimo de um vetor com dados do tipo halfword
.data
array:
    .half 1, 2, 3, 13, 5, 6, 7, 20, 9, 10

.text
BEGIN:
	la   a0, array          # load array
	li   a1, 10             # number of items
	jal  ra, MAX_VALUE_HALF
	li   a7, 10
	ecall
	
MAX_VALUE_HALF:	
	li   t0, 32767		    # t0 holds the temporary maximum

LOOP:
    beq  a1, zero, FIM      # test if we reach end of array(items)
	lh  t1, 0(a0)		    # load t1 with the new value to be checked (half word)
	bge  t0, t1, NEXT       # try to compare, if not jump, else proceed
	mv   t0, t1		# a new maximum was found

NEXT:
	addi a0, a0, 2		# update pointer to nex thalf  word
	addi a1, a1, -1		# decr number of bytes to check
	J    LOOP               # loop again

FIM:        
	mv   a0, t0
	ret


# OK d) Determinar o número de valores de um vetor que pertencem ao intervalo [a; b] assumindo dados do tipo word.
.data
array:
    .word 1, 2, 3, 13, 5, 6, 7, 20, 9, 10

.text
Start:
	la   a0, array
	li   a1, 10

	li   a2, 4 		# lower limit of interval [a;b]
	li   a3, 13		# upper limit of interval [a;b]
	jal  ra, CountValues
	li   a7, 10
	ecall
	
CountValues:	
	li   t1, 0		# set counter to zero

Loop:
	lw   t0, 0(a0)		# load t0 with the new value to be checked



	lw   t0, 0(a0)		# load t0 with the new value to be checked

	bgt  t0, a3, NEXT		# larger than upper bound
	blt  t0, a2, NEXT		# smaller than lower bound
	addi t1, t1, 1		# incr counter (new value is within [a;b])

NEXT:
	addi a0, a0, 4		# update pointer
	addi a1, a1, -1		# decr number of words to check
	bne  a1, zero, Loop

	mv   a0, t1
	ret 


# New solution
.data
array:
    .word 1, 2, 3, 13, 5, 6, 7, 20, 9, 10

.text
Start:
	la   a0, array
	li   a1, 10

	li   a2, 4 		# lower limit of interval [a;b]
	li   a3, 13		# upper limit of interval [a;b]
	jal  ra, CountValues
	li   a7, 10
	ecall
	
CountValues:	
	li   t1, 0		# set counter to zero

Loop:
	lw   t0, 0(a0)		# load t0 with the new value to be checked

	bgt  t0, a3, NEXT		# larger than upper bound
	blt  t0, a2, NEXT		# smaller than lower bound
	addi t1, t1, 1		# incr counter (new value is within [a;b])

NEXT:
	addi a0, a0, 4		# update pointer
	addi a1, a1, -1		# decr number of words to check
	bne  a1, zero, Loop

	mv   a0, t1
	ret 




# OK e) Contar quantos números pares existem num vetor de inteiros de 32 bits.

.data
array:
    .word 1, 2, 3, 13, 5, 6, 7, 20, 9, 10

.text
Start:
	la   a0, array
	li   a1, 10
	jal  ra, CountEvens
	li   a7, 10
	ecall
	
CountEvens:	
	li   t1, 0		# set counter to zero
	li   t2, 2		# remainder(X/t2) will be 0 if X is even

LOOP:
	bne  a1, zero, LOOP # one loop again
	lw   t0, 0(a0)		# load t0 with the new value to be checked
	rem  t0, t0, t2		# devide by two and keep reminder
	bne  t0, zero, L1	# look at reminder
	addi t1, t1, 1		# incr counter (new value is even)

L1:
	addi a0, a0, 4		# update pointer
	addi a1, a1, -1		# decr number of words to check

	j	LOOP


	mv   a0, t1			# final move
	ret




# OK f) Inverter a ordem dos elementos de um vetor com inteiros de 32 bits.

.data
array_in:
    .word 1, 2, 3, 13, 5, 6, 7, 20, 9, 10
array_out:
    .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

.text
Start:
	la   a0, array_in
	la   a1, array_out
	li   a2, 10
	jal  ra, INVERT_ORDER
	li   a7, 10
	ecall
	
INVERT_ORDER:	
	addi a1, a1, 36		# set 2nd ptr to last position (4*10-4)

LOOP:
	lw   t1, 0(a0)		# load t1 with the new value 
	sw   t1, 0(a1)		# store it in reverse order
	addi a0, a0, 4		# move to the...
	addi a1, a1, -4		# ...the next element
	addi a2, a2, -1		# decrement number of elements to reverse
	bne  a2, zero, LOOP
	ret
