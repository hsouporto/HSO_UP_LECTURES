# Explicação dos exercícios

## Exercício 1 — `hello.c`

### O que pretende mostrar

Introduzir o **processo de compilação** e debugging.

```bash
gcc -S hello.c
gcc hello.c
gcc -o hello hello.c
gcc -Wall -o hello hello.c
gcc -g -o hello hello.c
```

* `-S` → produz assembly (`hello.s`)
* `-o hello` → define o nome do executável
* `-Wall` → ativa warnings
* `-g` → inclui informação para debugging

Depois:

```bash
./hello
```

executa o programa.

### Pergunta

> Qual é a diferença entre `hello.c`, `hello.s` e `hello`?

**C source → Assembly → Executável.**

O `gdb`/`lldb` permite executar o programa passo a passo e observar o seu estado.

---

## Exercício 2 — `trig.c`

### O que pretende mostrar

**Erros de compilação, warnings e bibliotecas.**

O programa utiliza:

```c
sin(...)
cos(...)
M_PI
```

Primeiro:

```bash
gcc -Wall -o trig trig.c
```

O compilador apresenta erros.

### Perguntas

> O que diz exatamente o erro?

> Que biblioteca contém `sin()` e `cos()`?

Consultar:

```bash
man sin
man cos
```

Depois de corrigir o código, pode surgir outro problema durante o **linking**.

A ideia principal é perceber:

```text
código → compilação → linking → executável
```

e que utilizar uma função de uma biblioteca pode exigir informação adicional ao linker.

---

## Exercício 3 — `pointers1.c`

### O que pretende mostrar

**Ponteiros = endereços de memória.**

```c
int i, j, *p, *q;

i = 5;
p = &i;
*p = 7;
```

Aqui:

```text
p = endereço de i
*p = conteúdo existente nesse endereço
```

Portanto:

```text
i = 5
p = &i
*p = 7
```

faz:

```text
i = 7
```

Depois:

```c
j = 3;
p = &j;
q = p;
p = &i;
*q = 2;
```

O ponto importante é que **`q` continua a apontar para `j`**, mesmo depois de `p` mudar.

### Pergunta

> Se `q = p` e depois `p = &i`, para onde aponta `q`?

Para `j`.

A ficha pede precisamente uma representação da memória para acompanhar estas alterações.

---

## Exercício 4 — `char_array.c`

### O que pretende mostrar

**Arrays e aritmética de ponteiros.**

```c
char msg[] = "Hello World";
```

A expressão:

```c
msg + i
```

representa o endereço do elemento `i`.

E:

```c
*(msg + i)
```

é o conteúdo desse endereço.

Portanto:

```c
msg[i]
```

e

```c
*(msg + i)
```

representam o mesmo elemento.

### Pergunta

> Quantos bytes avança `msg + 1`?

Como `msg` é um array de `char`, avança **1 byte**.

A ficha pede também que se observe a correspondência entre endereço e conteúdo.

---

## Exercício 5 — `int_array.c`

É o mesmo conceito do exercício anterior, mas agora com:

```c
int primes[] = {2, 3, 5, 7, 11};
```

Temos:

```c
primes[i]
```

equivalente a:

```c
*(primes + i)
```

### Diferença importante

Se:

```text
sizeof(int) = 4 bytes
```

então:

```text
primes + 1
```

avança **4 bytes**, não 1.

Isto acontece porque a aritmética de ponteiros depende do **tipo apontado**.

### Pergunta

> `p + 1` significa endereço + 1 byte?

**Não.** Significa avançar uma unidade do tipo apontado.

---

## Exercício 6 — `call_by_value.c` vs `call_by_reference.c`

### O que pretende mostrar

**Passagem de argumentos e ponteiros.**

No primeiro:

```c
swap(n1, n2);
```

a função recebe **cópias** dos valores.

Alterar:

```c
n1
n2
```

dentro de `swap()` não altera as variáveis originais.

No segundo:

```c
swap(&n1, &n2);
```

passamos os **endereços**.

A função recebe:

```c
int *p1
int *p2
```

e pode alterar os valores através de:

```c
*p1
*p2
```

### Pergunta

> Porque é que o segundo `swap()` consegue alterar `n1` e `n2`?

Porque recebe os **endereços das variáveis**, e não cópias dos seus valores.

---

## Exercício 7 — `bad_pointer.c` vs `good_pointer.c`

### O que pretende mostrar

**Stack, heap e ponteiros inválidos.**

No `bad_pointer.c`:

```c
int* get_int() {
    int i = 2;
    return &i;
}
```

`i` é uma variável local.

Quando `get_int()` termina, essa variável deixa de ser válida.

Estamos a devolver o endereço de uma variável que já não deve ser utilizada.

### No `good_pointer.c`

```c
int* p = malloc(sizeof(int));
```

A memória é obtida no **heap**.

Essa memória continua válida depois de a função terminar, até ser libertada com:

```c
free(p);
```

### Pergunta

> Qual é a diferença fundamental?

```text
bad_pointer:
local variable → stack → deixa de existir ao terminar a função

good_pointer:
malloc → heap → permanece válida até free()
```

A ficha utiliza este exemplo para introduzir erros de acesso à memória e `segmentation fault`.

---

## Exercício 8 — Ponteiros inválidos

### O que pretende mostrar

Reconhecer situações perigosas com ponteiros.

### 1. Null pointer

```c
char *p1 = NULL;
*p1;
```

Não existe um endereço válido para aceder.

---

### 2. Wild pointer

```c
char *p2;
*p2;
```

`p2` não foi inicializado.

O endereço contém um valor indeterminado.

---

### 3. Dangling pointer

```c
char *p3 = malloc(sizeof(char));
free(p3);

*p3;
```

A memória já foi libertada, mas o ponteiro continua a conter o endereço antigo.

### Pergunta final

> O que têm estas três situações em comum?

Tentamos utilizar um endereço que **não é válido para aquela operação**.

O sistema operativo pode terminar o processo com, por exemplo:

```text
Segmentation fault
```

A ficha termina pedindo ainda a análise de diferentes formas de utilização de ponteiros e das zonas do espaço de endereçamento envolvidas.

---

# Resumo para o quadro

```text
1. Compilação
       ↓
2. Programa executável
       ↓
3. Processo
       ↓
4. Memória
       ├── Stack
       ├── Heap
       ├── Data
       └── Code
              ↓
5. Ponteiros
       ↓
6. Endereços
       ↓
7. Acesso válido / inválido
```

**Mensagem principal da aula:**

> Um ponteiro não é o valor: é um endereço que permite chegar ao valor.
