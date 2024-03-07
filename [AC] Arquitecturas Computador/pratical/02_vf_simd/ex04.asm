# Definição da sub-rotina
# Entradas:
#   x: valor a ser usado como argumento do polinômio (double)
#   coefs: endereço base do vetor contendo os coeficientes do polinômio (double)
#   n: número de coeficientes do polinômio (byte)
# Saída:
#   f: valor do polinômio calculado para o valor x (double)
calc_poly:
  # Configuração de registradores
  # s0: endereço base de coefs
  # s1: valor de x
  # s2: valor do polinômio acumulado
  # s3: índice do coeficiente atual
  
  addi s0, a1, 0   # Endereço base de coefs
  fmv.d s1, a0     # Valor de x
  fadd.d s2, zero, zero  # Polinômio acumulado começa em zero
  addi s3, zero, 0  # Começa com o primeiro coeficiente

  # Cálculo do polinômio
  ble s3, a2, loop  # Verifica se já percorreu todos os coeficientes
  fld d0, 0(s0)    # Carrega coeficiente atual em d0
  fmadd.d s2, s1, d0, s2  # Multiplica x pelo acumulado e soma coeficiente atual
  addi s0, s0, 8   # Avança para o próximo coeficiente
  addi s3, s3, 1   # Incrementa o índice
  j loop

loop:
  # Loop para percorrer todos os coeficientes
  # Utiliza a instrução FMADD.D para realizar o cálculo
  # Adiciona o resultado parcial ao acumulado e avança para o próximo coeficiente
  ble s3, a2, fim
  fld d0, 0(s0)
  fmadd.d s2, s1, d0, s2
  addi s0, s0, 8
  addi s3, s3, 1
  j loop

fim:
  # Fim da sub-rotina
  # Coloca o resultado final no registrador f0 (registrador de retorno)
  fmv.x.d a0, s2
  jr ra
  