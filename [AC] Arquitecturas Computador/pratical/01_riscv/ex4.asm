3. Considerar o seguinte programa, onde são invocadas duas sub-rotinas (POLI e QUAD).

.data
    num : .word 7

.text
    la t0 , num
    lw a0 , 0( t0 )
    jal ra , poli
    li a7 , 10
    ecall # termina

POLI : 
    ... # ***

    addi    sp, sp, -16         # alocar espaço na pilha (deve ser múltiplo de 16)
    sw    ra, 12(sp)            # guardar ra (return address) na pilha (vai ser alterado por jal ra, QUAD)
    sw    s0, 8 (sp)            # guardar s0  (registo não deve ser alterado por POLI)

    ... # ***
    mv t0 , a0 # <1 >           # ok, we may need to save t0, if routine uses it
    
    jal ra , QUAD               // call QUAD
    mv s0 , a0                  // save return a0 to s0 (x^2)
    mv a0 , 3                   // put 3 in a0
    mul t0 , t0 , a0            // multuply t0 (x) with 3
    add a0 , s0 , t0            // add s0(x^2) with 3x
    addi a0 , a0 , 1            // sum to the expression 1

    # restore things back  
    lw    s0, 8(sp)            //recuperar valor de s0
    lw    ra, 12(sp)           # recuperar valor de ra
    addi    add, sp, 16        # deallocathe the reserved space

    ret # <2 > a0

QUAD : 
    mul a0 , a0 , a0            // square a0
    ret

# a) Analise o programa e descreva o que calcula a sub-rotina POLI.
# x^2+3x+1
# valor calculado= 71 7^2 + 3x7 +1 

# b) Completar o código com as instruções que ache necessárias nos locais assinalados por ***.

# c) Indique o conteúdo da pilha do sistema imediatamente antes da execução das instruções assi-
# naladas com <1> e <2>.



