# Define o vetor de resultados com 101 elementos e o endereço de memória inicial
.section .data
vetor_resultados: .float 0:101
endereco_inicial: .int vetor_resultados

.section .text
.globl calc_poly
calc_poly:
    # Define os valores das constantes do polinômio
    li s0, 10650    # 1,5 * 10^3
    li s1, -125     # -12,5 * 10
    li s2, 700      # 7 * 100
    
    # Define as variáveis x e y
    flw f0, 0(a0)    # f0 é o valor de x
    flw f1, 0(scratch)    # f1 é o valor de y
    
    # Loop para calcular p(x) para cada valor de x
    li s3, 0         # s3 é o contador de loop
    li s4, 101       # s4 é o limite do loop

calc_loop:
    # Calcula o valor de p(x) e armazena no vetor de resultados
    fmadd.s f1, f0, f0, f0    # y = x^2
    fmadd.s f1, f0, f1, f1    # y = x^2 + x^2 = 2x^2
    fmul.s f1, f1, f0         # y = 2x^3
    fmadd.s f1, f1, s0, s2    # y = 1,5x^3 + 7
    fmadd.s f1, f0, s1, f1    # y = 1,5x^3 - 12,5x + 7
    
    swc1 f1, 0(a0)            # Armazena o valor de p(x) no vetor de resultados
    
    # Incrementa o contador de loop e verifica se atingiu o limite
    addi s3, s3, 1
    bne s3, s4, calc_loop
    
    # Encerra a sub-rotina
    jr ra




# Define o vetor de resultados com 101 elementos
.section .data
vetor_resultados: .float 0:101

.section .text
.globl main
main:
    # Chama a sub-rotina calc_poly
    la a0, vetor_resultados
    jal calc_poly
    
    # Imprime os valores do vetor de resultados
    flw f0, vetor_resultados
    li s0, 0
    li s1, 101
print_loop:
    # Imprime o valor atual do vetor de resultados
    la t0, vetor_resultados
    flw f0, (t0)(s0)
    fmv.s.x fa0, f0
    

 # ou
 # void calc_poly (float *results)

.data
results: 	.space 404		# 101*4
interval: 	.float 0.1
limit: 		.float 10

.text

la a0,results
jal calc_poly
li a7,10
ecall

calc_poly:
	addi sp,sp,-32
	sw ra,28(sp)
	sw s0,24(sp)
	fsw fs0,20(sp)
	fsw fs1,16(sp)
	fsw fs2,12(sp)

	mv s0,a0
	la t0,interval
	la t1,limit
	flw fs0,0(t0)		# fs0 = 0.1
	flw fs1,0(t1)		# fs1 = 10

	fcvt.s.w fs2,zero
	
set_input:
	fmv.s  fa0,fs2
	jal poly

	
	fsw fa0,0(s0)
	addi s0,s0,4
	fadd.s fs2,fs2,fs0
	flt.s t0,fs1,fs2 	# (fs1<fs0)?1:0
	beq  t0,zero,set_input

	flw fs2,12(sp)
	flw fs1,16(sp)
	flw fs0,20(sp)
	lw s0,24(sp)
	lw ra,28(sp)
	addi sp,sp,32
	ret

poly:
	li t0,3 	# 1,5*2
	li t1,25 	#12,5*2
	li t2,2
	li t3,7
	fcvt.s.w ft0,t0 
	fcvt.s.w ft1,t1
	fcvt.s.w ft2,t2
	fcvt.s.w ft3,t3
	fdiv.s ft0,ft0,ft2		# ft0 = 1,5
	fdiv.s ft1,ft1,ft2		# ft1 = 12,5
	fmadd.s ft1,fa0,ft1,ft3		# ft1 = 12,5x+7
	fmul.s ft4,fa0,fa0		# ft4 = x^2
	fmul.s fa0,fa0,ft4		# fa0 = x^3
	fmadd.s fa0, fa0,ft0,ft1	# fa0 = 1,5x^3+12,5x+7

	ret  