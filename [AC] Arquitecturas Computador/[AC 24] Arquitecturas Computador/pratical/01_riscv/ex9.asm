# a) Copiar um vetor com valores sem sinal do tipo byte para um vetor com valores sem sinal do tipo word

.data
array8: .byte 1, 2, 3, 4
array32: .space 16

.text
    lui a0, %hi(array8)
    addi a0, a0, %lo(array8)
    lui a1, %hi(array32)
    addi a1, a1, %lo(array32)
    
    li a2, 0
    li a3, 4
    
copy_loop:
    lb a4, 0(a0)
    addi a0, a0, 1
    andi a4, a4, 0xff
    slli a4, a4, 8*(a2%4)
    or a5, a5, a4
    addi a2, a2, 1
    bne a2, a3, copy_loop
    
    sw a5, 0(a1)
    addi a1, a1, 4
    li a5, 0


# b) Copiar um vetor com valores (com sinal) do tipo halfword para um vetor com valores do tipo word
.data
array16: .hword -1, 2, -3, 4
array32: .space 16

.text
    lui a0, %hi(array16)
    addi a0, a0, %lo(array16)
    lui a1, %hi(array32)
    addi a1, a1, %lo(array32)
    
    li a2, 0
    li a3, 4
    
copy_loop:
    lh a4, 0(a0)
    addi a0, a0, 2
    slli a4, a4, 16
    srai a4, a4, 16
    slli a4, a4, 8*(a2%4)
    or a5, a5, a4
    addi a2, a2, 1
    bne a2, a3, copy_loop
    sw a5, 0(a1)
    addi a1, a1, 4
    li a5, 0
