# b

.data
# Exemplo sem overflow:
#A:  .word -2, 4, 1, -5, 0
#B:  .word 8, 1, -1, -4, 3
#R:  .space 20  # Espaþo para o resultado (6, 5, 0, -9, 3)


.data
A: .word 4, 0x7ffffff0, -2, -2, 0
B: .word -1, 16, 0x80000001, 3, 0x80000000
R: .space 20        # space for the result

.text
    la      a0, A
    la      a1, B 
    la      a2, R
    li      a3, 5
    jal     somaVet_ovf
    li      a7, 10      # R IN MEMORY
    ecall 

somaVet_ovf:
    addi sp, sp, 32
    sw   ra, 20(sp)


 LOOP:
    beq a3, zero, FIM
    lw  t0, 0(a0)
    lw  t1, 0(a1)
    add t2, t0, t1              # sif sign(t0) = sign(t1) and sign(t2)!= sign(t0) we have overflow!!

    sw  a0, 16(sp)
    sw  a1, 12(sp)
    sw  a2, 8(sp)
    sw  a3, 4(sp)
    sw  t2, 0(sp)                   # sum t0 + t1


    jal ra, detOVF_ADD              # a0 ovefflow occurred or not

    lw  t2, 0(sp)

    beq a0, zero, NEXT
    bgt t2, zero, OVFneg

OVFpos:
    li  t2, 0x7ffffffff 
    j NEXT   


OVFneg:
    li  t2, 0x800000000


NEXT:
    lw  a0, 16(sp)
    lw  a1, 12(sp)
    lw  a2, 8(sp)
    lw  a3, 4(sp)
    

    sw  t2, 0(a2)       # store the sum in a2 (R)

    addi a0, a0, 4
    addi a1, a1, 4
    addi a2, a2, 4
    addi a3, a3, -1     # counter
    j   LOOP




FIM:
    lw ra, 20(sp)
    addi sp, sp, 32   # restore the stack again 
    ret


detOVF_ADD:
# a0= op1, a1=op2 and a2 = op1+ op2
# overflow only occirs inf operands have same signal and the sum has differnt singan that the operands
srli    a0, a0, 31      # keep the sign of tne op1
srli    a1, a1, 31      # keep the signal of op2
srli    a2, a2, 31      # keep the signal op + op2
xor     a0, a0, a1      # look have same signal or not
xor     a1, a1, a2      # same
xori    a0, a0. 1       # not ao
and     a0, a0, a1      # a0=0 no overflow occured / a0=1 we have overflow
ret














# a) Adição de vetores (R ← A + B) – assumir que a soma de cada par de elementos, Ai + Bi,
#é representável com o mesmo número de bits dos operandos, ou seja, assumir que não ocorre
# overflow.

.text
add_vectors:
    addi a5, a5, 0  # inicializa contador
    add a0, zero, a5  # inicializa endereço do vetor A
    add a1, zero, a5  # inicializa endereço do vetor B
    add a2, zero, a5  # inicializa endereço do vetor R

loop:
    lw a3, 0(a0)  # carrega Ai
    lw a4, 0(a1)  # carrega Bi

    add a3, a3, a4  # adiciona Ai e Bi
    sw a3, 0(a2)  # salva resultado em Ri

    addi a0, a0, 4  # avança para próximo elemento de A
    addi a1, a1, 4  # avança para próximo elemento de B
    addi a2, a2, 4  # avança para próximo elemento de R
    addi a5, a5, 1  # incrementa contador

    blt a5, a6, loop  # repetir enquanto contador for menor que tamanho do vetor
    ret


# b) Adição de vetores (R ← A+B) – se ocorrer overflow ao somar dois valores usar como resultado
# o maior ou o menor valor representável (saturação), conforme essa soma seja, respetivamente,
# positiva ou negativa  

.text
add_vectors_saturate:
    addi a5, a5, 0  # inicializa contador
    add a0, zero, a5  # inicializa endereço do vetor A
    add a1, zero, a5  # inicializa endereço do vetor B
    add a2, zero, a5  # inicializa endereço do vetor R

loop:
    lw a3, 0(a0)  # carrega Ai
    lw a4, 0(a1)  # carrega Bi
    add a3, a3, a4  # adiciona Ai e Bi
    blt a3, zero, set_min  # verifica se resultado é negativo
    
    bge a3, x30, set_max  # verifica se resultado é maior que máximo representável
    sw a3, 0(a2)  # salva resultado em Ri
    j next

set_min:
    sw x80000001, 0(a2)  # salva mínimo representável
    j next

set_max:
    sw x7fffffff, 0(a2)  # salva máximo representável

next:
    addi a0, a0, 4  # avança para próximo elemento de A
    addi a1, a1, 4  # avança para próximo elemento de B
    addi a2, a2, 4  # avança para próximo elemento de R
    addi a5, a5, 1  # incrementa contador
    blt a5, a6, loop  # repetir enquanto contador for menor que tamanho do vetor
    ret

# c) Multiplicação de um vetor por um inteiro ((R ← k ×A)) – assumir a não ocorrência de overflow.
.text

mult_vector_by_int:
    addi a5, a5, 0  # inicializa contador
    add a0, zero, a5  # inicializa endereço do vetor A
    add a2, zero, a5  # inicializa endereço do vetor R
    add a3, zero, a4  # guarda k em registrador a3

loop:
    lw a4, 0(a0)  # carrega Ai
    mul a4, a3, a4  # multiplica Ai por k
    sw a4, 0(a2)  # salva resultado em Ri
    addi a0, a0, 4  # avança para próximo elemento de A
    addi a2, a2, 4  # avança para próximo elemento de R
    addi a5, a5, 1  # incrementa contador
    blt a5, a6, loop  # repetir enquanto contador for menor que tamanho do vetor
    ret

# d) Produto interno (R ← A × B) – assumir que não ocorre overflow durante o cálculo.
.text
inner_product:
    addi a5, a5, 0  # inicializa contador
    add a0, zero, a5  # inicializa endereço do vetor A
    add a1, zero, a5  # inicializa endereço do vetor B
    add a3, zero, zero  # inicializa resultado

loop:
    lw a4, 0(a0)  # carrega Ai
    lw a6, 0(a1)  # carrega Bi
    mul a4, a4, a6  # multiplica Ai por Bi
    add a3, a3, a4  # soma resultado ao acumulador
    addi a0, a0, 4  # avança para próximo elemento de A
    addi a1, a1, 4  # avança para próximo elemento de B
    addi a5, a5, 1  # incrementa contador
    blt a5, a6, loop  # repetir enquanto contador for menor que tamanho do vetor
    ret

# e) Produto interno (R ← A × B) – caso ocorra overflow, na adição ou na multiplicação, a sub-
# rotina deve assinalar essa situação retornando o maior inteiro representável (assumir que este
# valor nunca decorre do cálculo do produto interno).


.text
inner_product:
    addi a5, a5, 0  # inicializa contador
    add a0, zero, a5  # inicializa endereço do vetor A
    add a1, zero, a5  # inicializa endereço do vetor B
    add a3, zero, zero  # inicializa resultado
    li a4, 2147483647  # carrega valor máximo representável
    li a6, -2147483648  # carrega valor mínimo representável
    
loop:
    lw a7, 0(a0)  # carrega Ai
    lw a8, 0(a1)  # carrega Bi
    mul a7, a7, a8  # multiplica Ai por Bi
    blt a7, a6, overflow  # verifica overflow negativo
    bgt a7, a4, overflow  # verifica overflow positivo
    add a3, a3, a7  # soma resultado ao acumulador
    addi a0, a0, 4  # avança para próximo elemento de A
    addi a1, a1, 4  # avança para próximo elemento de B
    addi a5, a5, 1  # incrementa contador
    blt a5, a6, loop  # repetir enquanto contador for menor que tamanho do vetor
    ret

overflow:
    bge a7, zero, overflow_positive  # verifica se é overflow positivo
    add a3, a6, zero  # retorna mínimo representável
    j end

overflow_positive:
    add a3, a4, zero  # retorna máximo representável

end:
    ret