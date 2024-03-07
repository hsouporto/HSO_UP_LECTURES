.data
P:   .float  2.0, 5.3  # P(x; y)
Q:   .float  5.0, 1.3  # Q(x; y)

.text
     la      a0, P
     la      a1, Q
     flw     ft0, (a0)  
     flw     ft1, 4(a0)
     flw     ft2, (a1)  
     flw     ft3, 4(a1)
     fsub.s  ft0, ft0, ft2
     fmul.s  ft0, ft0, ft0
     fsub.s  ft2, ft1, ft3
     fmul.s  ft2, ft2, ft2
     fadd.s  fa0, ft0, ft2
     fsqrt.s fa0, fa0        # Resultado em fa0
     li      a7, 10   
     ecall   
