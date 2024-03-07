# Código em C: int W = 7; double X = 7.1; double Y = sqrt(X) + W;
# Variáveis em C: int W = 7; double X = 7.1; double Y;
# Atribuição em C: Y = sqrt(X) + W;
# Protótipo double Y (int W, double X)
.data
W: .word 7
X: .double 0.49

.text

la a0, W
la a1, X
lw t0,0(a0)
fld f0,0(a1)

fsqrt.d f0,f0
fcvt.d.w f1,t0
fadd.d f0,f0,f1
