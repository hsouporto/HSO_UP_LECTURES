# a) double erfpos (double x)
# b) double erf (double x)

.data
n1: .double 0.278393
n2: .double 0.230389
n3: .double 0.000972
n4: .double 0.078108
x: .double -1.0

.text
la t0,x
fld fa0,0(t0)
jal ra,erf
li a7,10
ecall

erf:
	addi sp, sp, -16
	sw   ra, 12(sp)
	fsd  fs0, 4(sp)
	fcvt.d.w fs0,zero
	fle.d t0,fs0,fa0		# (a>=0)?1:0
	beq t0,zero,neg
	jal erfpos
	j end
neg:
	fsub.d fa0,fs0,fa0
	jal erfpos
	fsub.d fa0,fs0,fa0
	j end
end:
	lw   ra, 12(sp)
	fld  fs0, 4(sp)
	addi sp, sp, 16
	ret

erfpos:
	addi t0,zero,1
	la t1,n1
	la t2,n2
	la t3,n3
	la t4,n4
	fcvt.d.w fa1,t0
	fld ft1,0(t1)
	fld ft2,0(t2)
	fld ft3,0(t3)
	fld ft4,0(t4)
	fmadd.d ft0,fa0,ft1,fa1		# ft0 = n1*x+1
	fmul.d ft5, fa0,fa0		# ft5 = x^2
	fmadd.d ft0,ft5,ft2,ft0		# ft0 = n2*x^2+n1*x+1
	fmul.d ft5, ft5,fa0		# ft5 = x^3
	fmadd.d ft0,ft5,ft3,ft0		# ft0 = n3*x^3+n2*x^2+n1*x+1
	fmul.d ft5, ft5,fa0		# ft5 = x^4
	fmadd.d ft0,ft5,ft4,ft0		# ft0 = n4*x^4+n3*x^3+n2*x^2+n1*x+1
	fmul.d ft0,ft0,ft0		# ft0 = (n4*x^4+n3*x^3+n2*x^2+n1*x+1)^2
	fmul.d ft0,ft0,ft0		# ft0 = (n4*x^4+n3*x^3+n2*x^2+n1*x+1)^4
	fdiv.d fa0,fa1,ft0		# fa0 = 1/(n4*x^4+n3*x^3+n2*x^2+n1*x+1)^4
	fsub.d fa0,fa1,fa0		# fa0 = 1-1/(n4*x^4+n3*x^3+n2*x^2+n1*x+1)^4
	ret

		