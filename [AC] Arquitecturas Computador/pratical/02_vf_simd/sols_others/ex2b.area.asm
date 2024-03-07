.data
raio:.float 2.0
PI:  .float 3.14159

.text
     la     a0, raio
     la     a1, PI
     flw    fa0, (a0)  
     flw    ft0, (a1)
     fmul.s fa0, fa0, fa0
     fmul.s fa0, fa0, ft0   # Resultado em fa0
     li     a7, 10   
     ecall   
