# Introdução — Do código C ao processo em execução

Antes de começarmos a trabalhar com ponteiros, memória e processos, precisamos de perceber **como um programa em C passa de código escrito pelo programador a um programa que o sistema operativo consegue executar**.

## 1. O programa C

Consideremos:

```c
#include <stdio.h>

int main() {
    printf("Hello World!\n");
    return 0;
}
```

Guardamos o programa num ficheiro:

```text
hello.c
```

Este ficheiro contém **código-fonte** (*source code*).
É texto escrito numa linguagem que nós conseguimos compreender, mas que o processador não executa diretamente.

### Pergunta aos alunos

> O computador consegue executar diretamente o conteúdo de `hello.c`?

**Não.** É necessário transformar o código C num programa executável.

---

# 2. O processo de compilação

De forma simplificada:

```text
hello.c
   │
   ▼
Pré-processamento
   │
   ▼
Código C expandido
   │
   ▼
Compilação
   │
   ▼
Assembly
   │
   ▼
Assemblagem
   │
   ▼
Código máquina / object file
   │
   ▼
Linking
   │
   ▼
hello
   │
   ▼
Execução
   │
   ▼
Processo
```

É importante distinguir:

* **programa** → ficheiro executável armazenado no sistema de ficheiros;
* **processo** → programa em execução, com memória, estado, recursos, etc.

Esta distinção será importante mais tarde quando estudarmos processos.

---

# 3. O compilador

O compilador transforma código escrito numa linguagem de programação, como C, numa representação que pode ser executada pelo processador.

Por exemplo:

```bash
gcc -o hello hello.c
```

Aqui:

* `gcc` → compilador;
* `-o hello` → nome do executável produzido;
* `hello.c` → código-fonte.

Depois:

```bash
./hello
```

executa o programa.

### Pergunta

Qual é a diferença entre:

```bash
gcc -o hello hello.c
```

e

```bash
./hello
```

A primeira **produz** o executável.

A segunda **executa** o executável.

---

# 4. O que acontece dentro do `gcc`?

Quando fazemos:

```bash
gcc -o hello hello.c
```

há várias etapas envolvidas.

### 4.1 Pré-processamento

O pré-processador trata construções como:

```c
#include <stdio.h>
#define SIZE 10
```

Por exemplo:

```c
#include <stdio.h>
```

faz com que as declarações necessárias de `stdio.h` sejam disponibilizadas para o compilador.

---

### 4.2 Compilação

O compilador analisa o código C e produz código de baixo nível, normalmente **assembly** numa etapa intermédia.

Podemos pedir ao `gcc` para parar nessa fase:

```bash
gcc -S hello.c
```

Será produzido:

```text
hello.s
```

A ficha propõe precisamente esta experiência para observar o assembly produzido pelo compilador.

### Pergunta

> Porque é que existe uma linguagem assembly entre C e código máquina?

Porque o assembly representa de forma mais próxima as instruções que o processador executa, mas continua a ser uma representação textual que podemos inspecionar.

---

# 5. Assemblagem

O código assembly é transformado em código máquina.

De forma simplificada:

```text
hello.s
   │
   ▼
assembler
   │
   ▼
hello.o
```

O ficheiro `.o` é um **object file**.

Ainda não temos necessariamente um executável completo.

---

# 6. Linking

Um programa normalmente utiliza código que está noutros módulos ou bibliotecas.

Por exemplo:

```c
printf("Hello World!\n");
```

`printf` não foi implementada por nós.

É fornecida pela biblioteca standard de C.

O **linker** combina o nosso código com o código necessário das bibliotecas:

```text
hello.o
   +
bibliotecas
   │
   ▼
linker
   │
   ▼
hello
```

O resultado é o executável.

---

# 7. Compilar não é apenas "traduzir C"

Podemos portanto pensar:

```text
Código-fonte
     ↓
Pré-processamento
     ↓
Compilação
     ↓
Assembly
     ↓
Assemblagem
     ↓
Object files
     ↓
Linking
     ↓
Executável
```

Mas ainda falta uma coisa:

```text
Executável
     ↓
execução
     ↓
PROCESSO
```

Quando fazemos:

```bash
./hello
```

o sistema operativo cria um **processo** associado à execução daquele programa.

---

# 8. Avisos e erros

Vamos experimentar:

```bash
gcc -Wall -o hello hello.c
```

A opção:

```text
-Wall
```

ativa um conjunto importante de **warnings** do compilador.

A ficha recomenda explicitamente a utilização de `-Wall` e chama a atenção para o facto de warnings poderem indicar problemas que não impedem necessariamente a criação do executável.

### Pergunta aos alunos

> Se o compilador produz um executável, isso significa que o programa está correto?

**Não.**

É possível ter:

```text
código compila
      ↓
executável produzido
      ↓
programa executa
      ↓
resultado errado / erro durante execução
```

Por isso devemos distinguir:

### Erro de compilação

O compilador não consegue produzir o programa.

```text
source → X
```

### Warning

O compilador detectou algo potencialmente problemático, mas pode continuar.

```text
source → executable
          ↑
       warning
```

### Erro em runtime

O programa compila, mas ocorre um problema durante a execução.

```text
source → executable → process → ERROR
```

Os exemplos de ponteiros da ficha vão precisamente explorar esta última situação.

---

# 9. Debugging

Podemos pedir ao compilador para incluir informação adicional para debugging:

```bash
gcc -g -o hello hello.c
```

Depois podemos utilizar um debugger, por exemplo:

```bash
gdb hello
```

e executar:

```text
break main
run
next
```

A ficha introduz `gdb` desta forma e refere que, em sistemas que usam Clang/LLVM, como macOS, pode ser utilizado `lldb`.

O debugger permite observar o programa **enquanto ele está a executar**.

Por exemplo:

```text
Código C

int x = 10;
int y = 20;

        ↓

Debugger

x = 10
y = 20
```

Podemos avançar instrução a instrução e observar como o estado da memória se altera.

Isto será especialmente útil quando começarmos a estudar:

* variáveis;
* endereços;
* ponteiros;
* arrays;
* stack;
* heap;
* chamadas de funções.

---

# 10. Programa vs processo

Esta é uma distinção fundamental para Sistemas Operativos.

### Programa

É um ficheiro:

```text
hello
```

armazenado no disco.

### Processo

É uma instância desse programa em execução.

```text
                 DISCO
                  │
              executable
                  │
                  │ execução
                  ▼
              PROCESSO
                  │
       ┌──────────┼──────────┐
       ▼          ▼          ▼
     código     dados      stack
                            ...
```

Podemos ter o mesmo programa associado a vários processos.

Por exemplo:

```bash
./hello
```

cria um processo.

Se o programa permanecer a executar e fizermos:

```bash
./hello
```

novamente, podemos ter outra instância/processo.

---

# 11. Ligação com a ficha

A partir daqui, a ficha começa a explorar o que acontece **dentro do processo**.

Por exemplo, no exercício dos ponteiros:

```c
int i, j, *p, *q;

i = 5;
p = &i;
*p = 7;
```

já não estamos apenas interessados em saber se o programa compila.

Queremos compreender:

```text
Processo
┌─────────────────────────────┐
│                             │
│   i = 7                     │
│   j = ?                     │
│                             │
│   p ────────────────┐       │
│                    │       │
│                    ▼       │
│                   i       │
│                             │
└─────────────────────────────┘
```

Ou seja:

> **Como é que o código C que escrevemos se transforma num processo com memória e estado?**

Esta é a ponte entre **programação C** e **Sistemas Operativos**.

---

# 12. Perguntas rápidas para a aula

Antes de avançar para os ponteiros:

1. O que é um código-fonte?
2. O que faz o compilador?
3. O que significa compilar um programa?
4. Para que serve `gcc`?
5. Para que serve `-o`?
6. Para que serve `-Wall`?
7. Para que serve `-g`?
8. Qual é a diferença entre `gcc hello.c` e `./hello`?
9. O que é assembly?
10. O que é um object file?
11. Para que serve o linker?
12. O que é uma biblioteca?
13. O que é um executável?
14. O que é um processo?
15. Qual é a diferença entre programa e processo?
16. Um programa que compila está necessariamente correto?
17. Qual é a diferença entre um warning e um erro de compilação?
18. Em que momento pode ocorrer um segmentation fault?
19. Para que serve um debugger?
20. Porque é que um debugger será útil quando estudarmos ponteiros?

---

## Ideia-chave para os alunos

A mensagem que eu deixaria no quadro é:

```text
C source
   │
   │ gcc
   ▼
executable
   │
   │ execute
   ▼
process
   │
   ├── code
   ├── data
   ├── stack
   ├── heap
   └── resources
```

E depois:

> **A partir daqui, vamos abrir a "caixa" do processo e perceber onde vivem as variáveis, os ponteiros e os arrays.**

Isso cria uma transição natural para os exercícios `pointers1.c`, `char_array.c`, `int_array.c` e, posteriormente, para os erros de memória e `segmentation fault` apresentados na ficha.
