.text
.global CheckABS
# a0 = valor " limite " X
# a1 = tamanho do vetor
# a2 = endereço do vetor
CheckABS:

    li t0 , 0               # Contador de ocorrências

LOOP:
    beq a1, zero, FIM       # Test if reach zero
    lw t1 , 0(a2)           # Lê elemento do vetor

    bge t1 , zero , POS    # Test if positve or negative (full word)
    neg t1 , t1             # Valor absoluto do elemento lido (complement value)

POS: 
    bleu t1 , a0 , NEXT     # test if (unsigned)
    sw zero , 0(a2)         # Como | elemento |> a0 então elemento torna - se 0
    addi t0, t0, 1          # increment counter

NEXT: 
    addi a2 , a2 , 4        # Atualiza endereço
    addi a1 , a1 , -1       # Atualiza iterações em falta
    j   LOOP

 FIM:   
    mv a0 , t0              # Coloca resultado em a0
    ret