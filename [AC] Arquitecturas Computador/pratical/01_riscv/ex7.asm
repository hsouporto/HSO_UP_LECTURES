# Ok a) Determinar o comprimento de uma cadeia de carateres.

.data
str:    .asciz "hello, world"

.text
START:
	la      a0, str
	jal     ra, COUNT_CHARS
	li      a7, 10
	ecall

COUNT_CHARS:
    mv      t1, zero            # 32 bit reg counter set to zero

LOOP:
    lbu     t0, 0(a0)           # load next char 
    beq     t0, zero, FIM       # if null, end
    
    addi    t1, t1, 1           # increment the counter 
    addi    a0, a0, 1           # iterate again, moving addres pinter by 1 byte (char)
    j       LOOP

FIM:
    mv      a0, t1              # moving temporary register to a0 (return registers)
    ret













# Ok b) Determinar o número de ocorrências de um caráter numa cadeia de carateres.
.data
str:    .asciz "hello, world"

.text
START:
	la      a0, str
    li      a1, 'l'
	jal     ra, COUNT_OCCURS
	li      a7, 10
	ecall

COUNT_OCCURS:
    mv      t2, zero               # contador de caracteres

LOOP:
    lbu     t0, 0(a0)           # load the char
    beq     t0, zero, FIM       # if null, ends
    bne     a1, t0, NEXT        # diferent, next
    addi    t2, t2, 1           # increment count


NEXT:    
    //addi    t1, t1, 1           # increment count
    addi    a0, a0, 1           # next char
    j       LOOP

FIM:
    mv      a0, t2              # final move, t2 to a0
    ret

# Ok d) Determinar o número de vogais de uma cadeia de carateres utilizando a sub-rotina da alínea anterior.  

.data
str:    .asciz "hello, world"
str_vogal .asciz "aeiouAEIOU"

.text
START:
	la      a0, str
    la      a1, str_vogal
	jal     ra, COUNT_VOGALS
	li      a7, 10
	ecall

COUNT_VOGALS:
    mv      t2, zero             # contador de caracteres/vogals
    mv      t3, a1              # save temp vogals begin

LOOP:
    lbu     t0, 0(a0)           # load next char
    beq     t0, zero, FIM       # if null , ends

###

LOOP_VOG:
    lbu     t1, 0(a1)           # load vogal
    beq     t1, zero, RELOAD    # reload vogals and nex char
    bne     t1, t0, NEXT_VOGAL  # different, next vogal

    addi    t2, t2, 1           # increment count found vogal
    j RELOAD                    # interrupt search, I found somethings

NEXT_VOGAL:
    addi    a1, a1, 1           # next vogal
    j       LOOP_VOG

### 


RELOAD:
    mv      a1, t3             # realod vector array vogals from begin address


NEXT_CHAR:    
    addi    a0, a0, 1           # next character
    j       LOOP

FIM:
    mv      a0, t2
    ret


# OK c) Contar quantas palavras tem uma cadeia de carateres, assumindo que há um único espaço entre
# palavras consecutivas. Utilizar a sub-rotina da alínea b)

.data
str:    .asciz "hello, world, hello"

.text
START:
	la      a0, str
    li      a1, ' '
	jal     ra, COUNT_WORDS
	li      a7, 10
	ecall

COUNT_WORDS:
    mv      t2, zero               # contador de caracteres

LOOP:
    lbu     t0, 0(a0)           # load char 
    beq     t0, zero, FIM       # if null, ends
    bne     a1, t0, NEXT        # different, next
    addi    t2, t2, 1           # increment counter


NEXT:    
    addi    t1, t1, 1           # increment number of chars
    addi    a0, a0, 1           # move pointer next char
    j       LOOP

FIM:
    addi    t2, t1, 1           # two split, three words
    mv      a0, t2
    ret


# OK e) Determinar o número de letras maiúsculas de uma cadeia de carateres.
.data
str:    .asciz "hello, AAworld"

.text
START:
	la      a0, str
    li      a1, 'A'
    li      a2, 'Z'   
	jal     ra, COUNT_CAPS
	li      a7, 10
	ecall

COUNT_CAPS:
        mv      t1, zero                   # set counter on items 

LOOP:   
        lbu     t0, 0(a0)           # carrega o próximo caractere
        beq     t0, zero, FIM       # se for nulo, termina
        bge     t0, a1, UP              # brach greater or equal  Se x5 for maior ou igual a x3, up
        j       NEXT

UP:
        blt     t0, a2, COUNT           # lower than, count, otherwise next nne
        j       NEXT

COUNT:
        addi     t1, t1, 1               # add to counter and proceed

NEXT:
        addi     a0, a0, 1               # add one to next char
        j       LOOP                    # loop again

FIM:
        mv      a0, t1                  # final move to aling with return registers
        ret 

# f) Palíndromo é uma palavra, grupo de palavras ou verso em que o sentido é o mesmo, quer se
# leia da esquerda para a direita quer da direita para a esquerda (ex.: "ANOTARAM A DATA DA
# MARATONA").
# Determinar se uma cadeia de carateres é palíndromo. Assumir que a cadeia de carateres não in-
# clui espaços nem sinais de pontuação e que é indiferente o uso de letras maiúsculas e minúsculas.
# A sub-rotina devolve 1 em caso afirmativo ou 0 no caso contrário.

# ps pode usar a stack

.data
str:    .asciz "hellolleh"

.text
START:
	la      a0, str
	jal     ra, PALINDROME
	li      a7, 10
	ecall

PALINDROME:
        mv      t2, zero                # set counter on items 
        mv      t3, a0                  # save temporary
        mv      t5, zero                 # palindrome false

STR_LEN:
        lbu     t0, 0(t2)               # carrega o próximo caractere
        beq     t0, zero, START_LOOP    # se for nulo, termina
        addi    t2, t2, 1               # add to counter
        j       STR_LEN                 # loop again len



START_LOOP:
        add     t4, t2, t3              # 
        srli    t0, t0, 2               # decive by 2



LOOP:   
        beq     t2, zero, FIM           
        lbu     t0, 0(t3)               # carrega o próximo caractere
        lbu     t1, 0(t4)               # carrega o próximo caractere
        beq     t0, t1, NEXT            # next char
        mv      t5, zero
        j       FIM


NEXT:   
        addi     t5, zero, 1                   # palindrome 1
        addi     t2, t2, -1              # subtract

        addi     t3, t3, 1               # move pointers
        addi     t4, t4, -1              # move pointers
        j       LOOP                


             
FIM:
        mv      a0, t5                  # final move to aling with return registers
        ret 