# int conta_intervalo (float *V, int n, float a, float b)

.data
n: .word 6
a: .float 0
b: .float 10
V: .float -15, 0, 2.75, 5.87, 5.65, 35.32

.text
la a0,V
la a1,n
la t0,a
la t1,b
lw a1,0(a1)
flw fa0,0(t0)
flw fa1,0(t1)
jal conta_intervalo
li a7,10
ecall

conta_intervalo:
	mv  t0,a0
	add a0, zero,zero
next:	beq a1,zero,end
	addi a1,a1,-1
	flw ft0,0(t0)
	addi t0,t0,4
	fle.s t1,fa0,ft0	# (a<V[i])?1:0
	beq t1,zero,next	# se 0, fora do intervalo
	fle.s t1,ft0,fa1	# (V[i]<b)?1:0
	beq t1,zero,next	# se 0, fora do intervalo
	addi a0,a0,1
	j next
end: 
	ret
	