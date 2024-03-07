.data
#item a) Y = (A-B)*C/(D+A-3)
# float Y (float A, float B, float C, float D)
A: .float 2.0
B: .float 1.0
C: .float 1.0
D: .float 1.0
#item b) Area = pi*r^2
# float circle_area (float R)
R: .float 1.0
pi: .float 3.14159
#item c) sqrt((p1-p2)^2+(y1-y2)^2)
# float distance (float p1, float p2, float y1, float y2)
p1: .float 0.0
p2: .float 3.0
y1: .float 0.0
y2: .float 4.0

.text
main:

la t0, A
la t1, B
la t2, C
la t3, D
flw fa0,0(t0)
flw fa1,0(t1)
flw fa2,0(t2)
flw fa3,0(t3)
jal equation

la t0, R
flw fa0,0(t0)
jal circle_area

la t0, p1
la t1, p2
la t2, y1
la t3, y2
flw fa0,0(t0)
flw fa1,0(t1)
flw fa2,0(t2)
flw fa3,0(t3)
jal distance

addi a7, zero,10
ecall

equation:
fsub.s ft0,fa0,fa1
fmul.s ft0,ft0,fa2
fadd.s ft1,fa2,fa0
li t0, 3
fcvt.s.w ft2,t0
fsub.s ft1,ft1,ft2
fmv.s fa0,ft1
ret

circle_area:
la t1, pi
flw fa1,0(t1)
fmul.s fa0,fa0,fa0
fmul.s fa0,fa0,fa1
ret

distance:
fsub.s fa0,fa0,fa1
fsub.s fa1,fa2,fa3
fmul.s fa0,fa0,fa0
fmadd.s fa1,fa1,fa1,fa0
fsqrt.s fa0,fa1
ret