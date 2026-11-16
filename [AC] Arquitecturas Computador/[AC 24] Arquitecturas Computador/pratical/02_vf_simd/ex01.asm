


########################################################
# 1a) Escrever fragmentos de código assembly RISC-V que implementem o seguinte código em C.


# Operation : P = -M * (N+B);
# Prototipe: float C (float B, float M, float N)

.data
B:  .float 1.2
M:  .float 1.5
N:  .float 1.8
P:  .float 0.0   # valor inicial de P � zero

.text
# registers em RISC-V: f0-f31 (registers floating point)

# load the constants B, M e N into the floaring point registers

la      a0,     B
flw     f1,     0(a0)   # load B in f1 register

la      a0,     M
flw     f2,     0(a0)   # load M in f2 register

la      a0,     N
flw     f3,     0(a0)   # load N in f3 register


fadd.s  f4,      f1,     f3 # execute the sum operation ( N+ B) and store result in f4 (sigle precision.s)
fmul.s  f0,      f2,     f4 # execute the multiplication (-M * (N + B)) and store the rrsult in f0
fneg.s  f0,      f0         # invert the signal of the valur (x (-1)) (-M * (N + B)) and store in f0

# the final value in now stored in f0 floating point register


########################################################
 # 1b) 

# operation: Y = sqrt(X) + W;
# prototipe: double Y (int W, double X)
.data
W: .word 7          # set the variables
X: .double 0.49     # same

.text
la      a0,      W          # load address
la      a1,      X          # load value into a1

lw      t0,      0(a0)      # load address
fld     f0,      0(a1)      # load double into register

fsqrt.d     f0,     f0      # double precision d
fcvt.d.w    f1,     t0      # we need to convert the int into double for the operation
fadd.d      f0,     f0,     f1  # do the final operation and stroe in f0, 