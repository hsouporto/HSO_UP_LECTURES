# OK int conta_intervalo (float *V, int n, float a, float b)

.data
n: .word 6
a: .float 0
b: .float 10
V: .float -15, 0, 2.75, 5.87, 5.65, 35.32

.text
    la      a0,     V       # load addressc
    la      a1,     n       # n intems
    
	la      t0,     a       # 
    la      t1,     b       # 
    
	lw      a1,     0(a1)   # load value    (numero de items)
    
	flw     fa0,    0(t0)   # load value    (carrga float para fa0)     (lower limit)
    flw     fa1,    0(t1)   # load value    (carrega float fa1)			( upper limit)

    jal conta_intervalo
    li a7,10                # rars clean exit  
    ecall

conta_intervalo:
	li 		t0, 	0				# count n items [a,b]

LOOP:	
    beq     a1,     zero,   FIM
	flw     ft0,    0(a0)           # load float value from vector pointer

	fle.s   t1,     fa0,    ft0	    # (a<V[i])?1:0 (result of test in register t1 (0 ou 1))
	beq     t1,     zero,   NEXT	# if 0, outside of the interval  (go to next)
	
	fle.s   t1,     ft0,    fa1	    # (V[i]<b)?1:0 (test result in t1)
	beq     t1,     zero,   NEXT	# if 0, also outside interval, next
	
	addi    a0,     a0,     1       # otherwise, value inside interval, add 1 to counter
	

NEXT
	addi    a0,     a0,     4       # prepare the next (4 bytes)
	addi    a1,     a1,     -1      # decrement item counter 
	
	j       LOOP					# jumo to next iteration

FIM:
	mov 	a0, t0                                # all done, return
	ret