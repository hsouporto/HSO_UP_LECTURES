# Código em C: float P = -M * (N+B);
# Variáveis em C: float B = 7.8, M = 3.6, N = 7.1;
# Atribuição em C: P = -M * (N+B);
# Protótipo: float C (float B, float M, float N)

.data
B:  .float 1.2
M:  .float 1.5
N:  .float 1.8
P:  .float 0.0   # valor inicial de P é zero

.text
# Registos em RISC-V: f0-f31 (registos de ponto flutuante)

# Carrega as constantes B, M e N para os registos de ponto flutuante

la a0, B
flw f1, 0(a0)   # Carrega B em f1
la a0, M
flw f2, 0(a0)   # Carrega M em f2
la a0, N
flw f3, 0(a0)   # Carrega N em f3

fadd.s f4, f1, f3 # Executa a operação de soma (N + B) e armazena o resultado em f4
fmul.s f0, f2, f4 # Executa a operação de multiplicação (-M * (N + B)) e armazena o resultado em f0
fneg.s f0, f0 # Negativa o resultado da multiplicação (-M * (N + B)) e armazena o resultado em f0

# O valor final da expressão está agora armazenado no registrador de ponto flutuante f0