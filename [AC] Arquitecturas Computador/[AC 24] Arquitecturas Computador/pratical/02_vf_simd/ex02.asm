# 2  Escrever e testar programas, envolvendo dados em vírgula flutuante com precisão simples, para
# calcular:


########################################################
# a) expression value (A−B)×C / D+A−3 

# Define as variáveis A, B, C, D e resultado
.section .data
A: .float 2.1
B: .float 1.2
C: .float 3.3
D: .float 4.4
resultado: .float 0

.section .text
.globl main
main:
    # Carrega as variáveis A, B, C e D nos registradores f0, f1, f2 e f3, respectivamente
    la  a0, A
     la   a1, B
     la   a2, C
     la   a3, D
     la   a4, resultado
    
    flw f0, 0(a0)
    flw f1, 0(a1)
    flw f2, 0(a2)
    flw f3, 0(a3)
    
    # Executa as operações matemáticas para calcular o resultado da expressão
    fsub.s f4, f0, f1   # f4 = A - B
    fmul.s f5, f4, f2   # f5 = (A - B) * C
    fadd.s f6, f0, f3   # f6 = A + D
    li    a0, 3
    fcvt.s.w   f1, a0
    fsub.s f7, f6, f1    # f7 = A + D - 3
    fdiv.s f8, f5, f7   # f8 = (A - B) * C / (D + A - 3)
    
    # Armazena o valor do resultado na memória
    fsw f8, 0(a4)
    
    # Encerra o programa
    li a0, 10
    ecall


########################################################
# b) Define as variáveis raio, pi e area

 .data
raio:.float 2.0
PI:  .float 3.14159

.text
     la     a0, raio        # load address and the the values into suitible registers
     la     a1, PI
     flw    fa0, (a0)  
     flw    ft0, (a1)


     fmul.s fa0, fa0, fa0   # do the r^2
     fmul.s fa0, fa0, ft0   # final result em fa0 ( pi*r^2)
     li     a7, 10   
     ecall   
   


########################################################
# c) Define the variables  x1, y1, x2, y2 and we whant the distance
.data
P:   .float  2.0, 5.3  # P(x; y)
Q:   .float  5.0, 1.3  # Q(x; y)

.text
     la      a0, P
     la      a1, Q
     flw     ft0, (a0)          # load firsr
     flw     ft1, 4(a0)         # load second displacement 4 bytes
     
     flw     ft2, (a1)          # again
     flw     ft3, 4(a1)

     fsub.s  ft0, ft0, ft2      # subtract, single precison
     fmul.s  ft0, ft0, ft0

     fsub.s  ft2, ft1, ft3
     fmul.s  ft2, ft2, ft2
     
     fadd.s  fa0, ft0, ft2
     fsqrt.s fa0, fa0        # Result in fa0 (.s single precision)
     li      a7, 10   
     ecall   

    