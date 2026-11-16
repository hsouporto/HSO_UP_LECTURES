# Aula — Unix/Linux Command Shell

## 1. Objetivos

Nesta aula vamos aprender a utilizar a shell para:

* navegar no sistema de ficheiros;
* criar, copiar, mover e remover ficheiros e diretórios;
* utilizar caminhos absolutos e relativos;
* utilizar wildcards/globs;
* compreender permissões;
* redirecionar entrada e saída;
* combinar comandos através de pipes;
* procurar e processar informação em ficheiros;
* pesquisar ficheiros;
* consultar processos;
* executar processos em background;
* terminar processos;
* compreender o funcionamento de `xargs`.

A ficha apresenta estes temas através de exercícios práticos e recomenda uma abordagem importante:

> **Antes de executar um comando, devemos tentar prever o resultado. Depois executamos o comando e verificamos a nossa previsão.**

Esta será a metodologia da aula.

---

# 2. Shell: o que estamos realmente a utilizar?

## Explicação

Uma shell é um **interpretador de comandos**.

O utilizador escreve:

```text
comando
```

e a shell interpreta essa linha.

A shell permite manipular ficheiros, executar programas, controlar processos e combinar comandos.

Existem várias shells:

```text
sh
csh
bash
zsh
```

A ficha destaca `bash` e refere que o `zsh` é a shell por omissão do macOS. Também salienta que existe uma grande sobreposição entre as diferentes shells.

### Pergunta

**Professor:**

> "Se eu aprender `bash`, os conhecimentos deixam de servir quando encontrar `zsh`?"

### Resposta esperada

Não.

Os conceitos fundamentais e muitos dos comandos são comuns.

A ficha salienta precisamente que aprender `bash` facilita a compreensão e utilização de outras shells.

---

# 3. Metodologia: prever antes de executar

Antes de cada exercício:

1. ler o comando;
2. explicar o que cada parte significa;
3. perguntar qual será o resultado;
4. pedir aos alunos para prever;
5. executar;
6. comparar com a previsão;
7. explicar eventuais diferenças.

### Pergunta

> "É melhor executar primeiro e tentar perceber depois, ou prever primeiro?"

O objetivo é criar o hábito:

```text
comando
   ↓
previsão
   ↓
execução
   ↓
observação
   ↓
explicação
```

Este método é particularmente importante em shell porque pequenos símbolos podem alterar completamente o resultado.

---

# 4. Exercício 1 — `cd`, `~` e o diretório pessoal

A ficha começa com:

```bash
cd ~
cd
```

e pede para determinar em que diretório ficamos depois de cada comando.

## Explicação

`~` representa o diretório pessoal do utilizador.

Portanto:

```bash
cd ~
```

significa:

> mudar para o diretório pessoal.

O comando:

```bash
cd
```

sem argumentos também leva normalmente para o diretório pessoal.

### Perguntas

> "Qual é o resultado de `cd ~`?"

> "E de `cd`?"

> "São diferentes?"

### Verificação

```bash
pwd
```

### Conceitos

```text
~
```

é uma expansão da shell para o diretório pessoal.

E:

```text
pwd
```

mostra o diretório de trabalho atual.

---

# 5. Caminhos absolutos e relativos

A ficha introduz explicitamente **absolute and relative paths**.

## Caminho absoluto

Começa na raiz:

```text
/
```

Por exemplo:

```text
/tmp
```

ou:

```text
/home/aluno
```

num sistema Linux.

No macOS podemos ter:

```text
/Users/aluno
```

## Caminho relativo

É interpretado relativamente ao diretório atual.

Por exemplo:

```text
dir1/dir2
```

### Pergunta

Se estamos em:

```text
/home/aluno
```

onde ficamos depois de:

```bash
cd dir1
```

?

E depois:

```bash
cd ..
```

?

### Conceitos

```text
.   → atual
..  → pai
~   → home
/   → raiz
```

---

# 6. Exercício 2 — Construir uma árvore de diretórios

A ficha pede para construir:

```text
dir1
├── dir2
│   ├── dir4
│   │   └── dir6
│   └── dir5
└── dir3
```

## Explicação

Queremos transformar uma representação textual numa estrutura real do sistema de ficheiros.

Uma solução possível é:

```bash
mkdir dir1
mkdir dir1/dir2
mkdir dir1/dir2/dir4
mkdir dir1/dir2/dir4/dir6
mkdir dir1/dir2/dir5
mkdir dir1/dir3
```

Ou utilizar `mkdir -p`:

```bash
mkdir -p dir1/dir2/dir4/dir6
mkdir -p dir1/dir2/dir5
mkdir -p dir1/dir3
```

### Pergunta

> "Qual é a vantagem de `mkdir -p`?"

Permite criar os diretórios intermédios necessários.

---

# 7. `tree`

Depois podemos observar a estrutura:

```bash
tree dir1
```

A ficha utiliza `tree` para visualizar a árvore de diretórios.

### Pergunta

> "Qual é a diferença entre `ls` e `tree`?"

`ls` mostra o conteúdo de um diretório.

`tree` mostra a estrutura hierárquica.

### Nota

Se `tree` não estiver instalado, pode ser necessário instalá-lo no ambiente utilizado.

---

# 8. Exercício 3 — `..` dentro de um caminho

A ficha apresenta:

```bash
cd dir1/dir2/dir4/dir6/../..
```

## Pergunta antes de executar

> "Em que diretório vamos ficar?"

Vamos simplificar passo a passo.

Partimos de:

```text
dir1
└── dir2
    └── dir4
        └── dir6
```

Estamos em:

```text
dir6
```

Primeiro:

```text
..
```

leva para:

```text
dir4
```

Segundo:

```text
..
```

leva para:

```text
dir2
```

Portanto terminamos em:

```text
dir1/dir2
```

### Conceito importante

Um caminho pode conter componentes intermédios que fazem a navegação subir ou descer na árvore.

---

# 9. Exercício 4 — `touch`

A ficha pede para criar vários ficheiros utilizando `touch`.

Por exemplo:

```bash
touch dir1/dir2/f1.txt
touch dir1/dir2/h22.txt
touch dir1/dir2/dir4/g22.doc
touch dir1/g368.pdf
touch dir1/dir3/f3a.txt
touch dir1/dir3/g56.doc
touch dir1/dir3/g3x.pdf
```

## Explicação

`touch` pode criar um ficheiro vazio se este ainda não existir.

### Pergunta

> "O `touch` cria um diretório?"

Não.

Para diretórios usamos:

```bash
mkdir
```

### Pergunta

> "E se o ficheiro já existir?"

O comportamento principal do `touch` é atualizar os timestamps do ficheiro.

---

# 10. Globs / Wildcards

A ficha introduz os **globs**:

```text
^
?
*
[]
{}
```

## Explicação

Globs são padrões interpretados pela shell para selecionar nomes de ficheiros.

Os mais importantes para esta aula são:

```text
*
?
[...]
```

### `*`

Representa zero ou mais caracteres.

Por exemplo:

```bash
ls *.txt
```

seleciona ficheiros terminados em `.txt`.

### `?`

Representa exatamente um carácter.

Por exemplo:

```bash
ls g?.pdf
```

pode corresponder a:

```text
g3.pdf
g5.pdf
```

mas não:

```text
g35.pdf
```

### `[ ]`

Permite especificar um conjunto ou intervalo de caracteres.

Por exemplo:

```text
[fg]
```

significa:

```text
f ou g
```

E:

```text
[4-7a-z]
```

significa um carácter entre `4` e `7` ou entre `a` e `z`.

---

# 11. Exercício 5 — `find` e padrões

A ficha apresenta:

```bash
find dir1/dir2 -name "[fg][35][4-7a-z].txt" -print
```

e:

```bash
find dir1/dir3 -name "[fg][35][4-7a-z].txt" -print
```

## Vamos decompor

```text
[fg]
```

primeiro carácter:

```text
f ou g
```

Depois:

```text
[35]
```

segundo carácter:

```text
3 ou 5
```

Depois:

```text
[4-7a-z]
```

terceiro carácter:

```text
4,5,6,7,a,b,c,...,z
```

Finalmente:

```text
.txt
```

### Pergunta

Qual destes nomes corresponde ao padrão?

```text
f35.txt
g56.txt
g3x.pdf
f3a.txt
```

### Resposta

```text
g56.txt
f3a.txt
```

dependendo do diretório onde procuramos.

### Conceito

`find` percorre uma árvore e procura ficheiros que satisfaçam determinadas condições.

---

# 12. `rm -rf`

A ficha apresenta:

```bash
rm -rf dir1/dir2
```

## Explicação

`rm` remove ficheiros.

A opção:

```text
-r
```

significa recursivamente.

A opção:

```text
-f
```

força a operação sem pedir determinadas confirmações.

Assim:

```bash
rm -rf dir1/dir2
```

remove `dir2` e o seu conteúdo.

### Pergunta importante

> "Porque é que `rm -rf` deve ser utilizado com cuidado?"

Porque uma árvore inteira pode ser removida recursivamente.

### Regra prática

Antes de executar:

```bash
rm -rf ...
```

devemos sempre verificar:

```bash
pwd
ls
```

e confirmar exatamente o caminho.

---

# 13. Permissões — `ls -l`

A ficha apresenta:

```bash
ls -l
```

e um resultado semelhante a:

```text
-rw-r--r-- 1 lblopes staff 1412 Dec 29 15:43 f3a.txt
```

## Explicação

Vamos separar:

```text
-rw-r--r--
```

em:

```text
-
rw-
r--
r--
```

Temos:

```text
tipo | user | group | others
```

Neste caso:

```text
-      → ficheiro normal
rw-    → utilizador pode ler e escrever
r--    → grupo pode ler
r--    → outros podem ler
```

### Os três tipos de permissão

```text
r → read
w → write
x → execute
```

---

# 14. Permissões em octal

A ficha pede explicitamente a representação das permissões em octal.

Temos:

```text
r = 4
w = 2
x = 1
```

Portanto:

```text
rwx = 4 + 2 + 1 = 7
rw- = 4 + 2 = 6
r-x = 4 + 1 = 5
r-- = 4
--- = 0
```

Por exemplo:

```text
rwxr-xr-x
```

é:

```text
7 5 5
```

ou:

```text
755
```

---

# 15. Exercício 8 — `chmod`

A ficha utiliza:

```bash
chmod 755 doit
chmod u-wx doit
chmod go-rx doit
chmod 644 doit
```

## Explicação

`chmod` altera permissões.

Temos três grupos:

```text
u → user
g → group
o → others
```

E três operações:

```text
+ → adicionar
- → remover
= → definir
```

### Exemplo

```bash
chmod u-wx doit
```

significa:

> remover `write` e `execute` do utilizador.

Já:

```bash
chmod go-rx doit
```

significa:

> remover `read` e `execute` do grupo e dos outros.

---

# 16. Redirecionamento com `cat`

A ficha utiliza:

```bash
cat > trees.txt
```

e depois introduz linhas de texto.

## Explicação

Normalmente:

```bash
cat
```

recebe informação através do `stdin` e escreve no `stdout`.

Quando fazemos:

```bash
cat > trees.txt
```

estamos a dizer:

```text
stdin → cat → stdout → trees.txt
```

O utilizador escreve:

```text
pine:253:221:1.2
oak:144:123:0.9
birch:92:83:1.6
yew:65:63:4.3
alder:12:5:9.6
```

E termina a entrada com:

```text
Ctrl-D
```

### Pergunta

> "O que faz `Ctrl-D` neste contexto?"

Indica **EOF — End Of File** no terminal, terminando a entrada para o `cat`.

---

# 17. `cut`

Depois temos:

```bash
cat trees.txt | cut -d ':' -f 1,4
```

## Explicação

Cada linha tem campos separados por `:`.

Por exemplo:

```text
pine:253:221:1.2
```

tem:

```text
campo 1 → pine
campo 2 → 253
campo 3 → 221
campo 4 → 1.2
```

A opção:

```text
-d ':'
```

define o delimitador.

A opção:

```text
-f 1,4
```

seleciona os campos 1 e 4.

Portanto obtemos:

```text
pine:1.2
oak:0.9
birch:1.6
yew:4.3
alder:9.6
```

---

# 18. `sort`

Depois:

```bash
cat trees.txt | cut -d ':' -f 1,4 | sort
```

## Explicação

O resultado de `cut` passa para `sort`.

Temos:

```text
cat
 ↓
cut
 ↓
sort
```

### Pergunta

> "Qual é a vantagem de fazer isto em três comandos?"

Cada programa tem uma tarefa simples.

Podemos combiná-los através de pipes.

Esta é uma ideia central do Unix:

> **programas pequenos podem ser combinados para realizar tarefas mais complexas.**

---

# 19. `sed`

A ficha introduz:

```bash
sed 's/Ring/Sword/g'
```

## Explicação

`sed` é um editor/processador de texto orientado a streams.

Neste caso:

```text
s/Ring/Sword/g
```

significa:

```text
s       → substitute
Ring    → texto procurado
Sword   → substituição
g       → todas as ocorrências da linha
```

Assim:

```text
One Ring to rule them all
```

passa para:

```text
One Sword to rule them all
```

---

# 20. `grep -v`

A ficha utiliza:

```bash
cat q2.txt | grep -v Mordor
```

## Explicação

`grep` procura linhas que correspondem a um padrão.

Por exemplo:

```bash
grep Mordor q2.txt
```

seleciona linhas que contêm `Mordor`.

Com:

```bash
grep -v Mordor q2.txt
```

o `-v` inverte a seleção.

Portanto:

> mostrar linhas que **não** contêm `Mordor`.

### Pergunta

Qual é a diferença entre:

```bash
grep Mordor
```

e:

```bash
grep -v Mordor
```

---

# 21. `wc`

A ficha utiliza:

```bash
wc -l q2.txt
```

`wc` conta informação.

A opção:

```text
-l
```

conta linhas.

### Pergunta

Se o ficheiro tem 7 linhas, o que esperamos de:

```bash
wc -l q2.txt
```

?

---

# 22. `diff`

A ficha introduz:

```bash
diff f1.txt f2.txt
```

## Explicação

`diff` compara ficheiros.

Primeiro:

```bash
sed 's/half/two thirds/g' < f1.txt > f2.txt
```

Aqui temos:

```text
f1.txt
  ↓
sed
  ↓
f2.txt
```

Depois:

```bash
diff f1.txt f2.txt
```

### Pergunta

> "Os ficheiros são iguais?"

Não.

O `sed` substituiu ocorrências de `half`.

Depois:

```bash
sed 's/like/do not like/g' < f1.txt > f2.txt
```

E fazemos novamente:

```bash
diff f1.txt f2.txt
```

### Conceito

`diff` permite verificar diferenças entre duas versões de um ficheiro.

---

# 23. Redirecionamento de entrada `<`

Aqui aparece um conceito novo:

```bash
sed '...' < f1.txt > f2.txt
```

Temos:

```text
f1.txt
   │
   │ stdin
   ▼
  sed
   │
   │ stdout
   ▼
f2.txt
```

Portanto:

```text
<
```

redireciona a entrada standard.

Enquanto:

```text
>
```

redireciona a saída standard.

---

# 24. `sort -n`

A ficha utiliza:

```bash
sort -n < numbers1.txt > numbers2.txt
```

## Explicação

Sem opções, `sort` faz ordenação lexicográfica.

Com:

```text
-n
```

faz ordenação numérica.

### Pergunta

Qual seria a diferença entre ordenar:

```text
2
10
100
20
```

como texto e como números?

Como texto:

```text
10
100
2
20
```

Como números:

```text
2
10
20
100
```

Este é um bom exemplo de como uma opção pode alterar significativamente o comportamento de um comando.

---

# 25. Processos

A ficha pergunta:

```bash
ps -A | wc -l
```

e pergunta o que podemos calcular aproximadamente com este comando.

## Explicação

`ps` mostra informação sobre processos.

A opção:

```text
-A
```

seleciona todos os processos.

Depois:

```text
|
```

envia a saída para:

```text
wc -l
```

que conta linhas.

Portanto:

```text
ps -A
   ↓
todos os processos
   ↓
wc -l
   ↓
número aproximado de linhas/processos apresentados
```

### Pergunta

> "O que representa cada linha?"

Em termos gerais, cada linha corresponde a uma entrada de processo apresentada pelo `ps`.

### Conceito

O sistema operativo gere muitos processos simultaneamente.

---

# 26. Background — `&`

A ficha apresenta:

```bash
emacs &
emacs &
emacs &
```

## Explicação

Normalmente, quando executamos:

```bash
programa
```

a shell fica à espera que o programa termine.

Com:

```bash
programa &
```

pedimos à shell para iniciar o processo em **background**.

Por exemplo:

```bash
emacs &
```

permite continuar a utilizar a shell.

Podemos visualizar os processos:

```bash
ps -A | grep emacs
```

A ficha mostra três processos `emacs` e também o próprio processo `grep`.

### Pergunta

> "Porque aparece `grep emacs` no resultado?"

Porque o comando:

```bash
ps -A | grep emacs
```

também cria um processo `grep` cujo comando contém a palavra `emacs`.

---

# 27. `kill`

A ficha termina os processos com:

```bash
kill -9 3577 3578 3579
```

## Explicação

`kill` envia um **sinal** a um processo.

O:

```text
-9
```

corresponde a:

```text
SIGKILL
```

que força a terminação do processo.

O número:

```text
3577
```

é o PID — Process ID.

### Pergunta

> "O que é o PID?"

É o identificador do processo.

---

# 28. `xargs`

A ficha introduz agora uma ferramenta muito importante:

```bash
xargs
```

Temos:

```bash
cat vtext.txt | xargs
```

e obtemos:

```text
um dois tres quatro cinco
```

## Explicação

`xargs` pega na informação recebida através do `stdin` e constrói argumentos para outro comando.

É útil quando temos:

```text
lista de dados
      ↓
xargs
      ↓
argumentos de um comando
```

### Pergunta

> "Qual é a diferença entre um pipe e `xargs`?"

Um pipe liga:

```text
stdout → stdin
```

Enquanto `xargs` transforma a entrada em **argumentos de um comando**.

---

# 29. Exemplo conceptual de `xargs`

Imagine:

```text
a
b
c
```

Se fizermos:

```bash
cat ficheiro | xargs echo
```

podemos obter:

```text
a b c
```

Conceptualmente:

```text
echo a b c
```

Ou seja, `xargs` construiu uma lista de argumentos.

---

# 30. Processos em loop infinito

A ficha termina com um programa C:

```c
int main(int argc, char* argv[]) {
    for( ; ; )
        ;
}
```

## Explicação

O ciclo:

```c
for( ; ; )
```

não possui condição de terminação.

Portanto:

```text
programa
   ↓
loop infinito
```

O processo continua a executar até receber um sinal que o termine.

Compilar:

```bash
gcc infinity.c -o infinity
```

Executar em background:

```bash
./infinity &
```

A ficha pede para criar vários processos desse programa.

---

# 31. Pipeline final

A ficha apresenta:

```bash
ps -A | grep infinity | sed 's/^[[:space:]]*//' | cut -d ' ' -f 1 | xargs kill -9
```

Este é provavelmente o exercício mais importante para consolidar a aula.

Não devemos executá-lo imediatamente.

Primeiro devemos desmontá-lo.

---

## Passo 1

```bash
ps -A
```

Lista processos.

---

## Passo 2

```bash
ps -A | grep infinity
```

Seleciona processos cujo texto contém `infinity`.

---

## Passo 3

```bash
... | sed 's/^[[:space:]]*//'
```

Remove espaços no início das linhas.

---

## Passo 4

```bash
... | cut -d ' ' -f 1
```

Tenta extrair o primeiro campo separado por espaços.

---

## Passo 5

```bash
... | xargs kill -9
```

Transforma os PIDs em argumentos de:

```bash
kill -9
```

Portanto temos:

```text
ps
 ↓
grep
 ↓
sed
 ↓
cut
 ↓
xargs
 ↓
kill
```

Cada programa faz uma tarefa pequena.

---

# 32. Grande ideia da aula

Este último exemplo mostra uma das ideias fundamentais das ferramentas Unix:

```text
programa simples
      +
programa simples
      +
programa simples
      +
pipe
      ↓
operação complexa
```

Em vez de criar um único programa que faz tudo, podemos construir uma sequência de pequenas ferramentas.

---

# 33. Perguntas de consolidação

## Navegação

1. O que representa `~`?
2. Qual é a diferença entre `.` e `..`?
3. Qual é a diferença entre caminho absoluto e relativo?
4. O que faz `pwd`?
5. Qual é a diferença entre `cd` e `pwd`?

## Ficheiros

6. Para que serve `touch`?
7. Qual é a diferença entre `cp` e `mv`?
8. Qual é a diferença entre `rm` e `rmdir`?
9. O que faz `rm -rf`?
10. Por que devemos ter cuidado com `rm -rf`?

## Globs

11. O que significa `*`?
12. O que significa `?`?
13. O que significa `[fg]`?
14. O que significa `[4-7a-z]`?

## `find`

15. O que faz `find`?
16. Qual é o papel de `-name`?
17. O que significa o padrão:

```text
[fg][35][4-7a-z].txt
```

## Permissões

18. O que significam `r`, `w` e `x`?
19. O que significa `755`?
20. Qual é a diferença entre `chmod 755 file` e `chmod u-wx file`?
21. O que significam `u`, `g` e `o`?

## Redirecionamento

22. O que faz `>`?
23. O que faz `>>`?
24. O que faz `<`?
25. Qual é a diferença entre:

```bash
command > file
```

e:

```bash
command < file
```

## Pipes

26. O que faz `|`?
27. O que significa:

```text
stdout → stdin
```

28. Qual é a vantagem de combinar comandos com pipes?

## Texto

29. Para que serve `grep`?
30. O que faz `grep -v`?
31. Para que serve `cut`?
32. O que significa `cut -d ':' -f 1,4`?
33. Para que serve `sort`?
34. Qual é a diferença entre `sort` e `sort -n`?
35. Para que serve `sed`?
36. O que significa:

```text
s/X/Y/g
```

37. Para que serve `diff`?
38. Para que serve `wc -l`?

## Processos

39. O que mostra `ps`?
40. O que é um PID?
41. O que faz `&`?
42. Qual é a diferença entre foreground e background?
43. O que faz `kill`?
44. O que significa `SIGKILL`?

## `xargs`

45. Qual é a função de `xargs`?
46. Qual é a diferença entre um pipe e `xargs`?
47. Porque é que `xargs` é útil em pipelines?

---

# 34. Perguntas de Revisão

Estas perguntas são particularmente importantes para conduzir a aula.

Antes de executar:

```bash
cd ~
cd
```

perguntar:

> "Onde estamos?"

Antes de:

```bash
cd dir1/dir2/dir4/dir6/../..
```

perguntar:

> "Qual é o diretório final?"

Antes de:

```bash
find dir1/dir3 -name "[fg][35][4-7a-z].txt"
```

perguntar:

> "Quais dos ficheiros vão aparecer?"

Antes de:

```bash
chmod 755 doit
```

perguntar:

> "Que permissões ficam para user, group e others?"

Antes de:

```bash
cat trees.txt | cut -d ':' -f 1,4 | sort
```

perguntar:

> "Qual será exatamente a saída?"

Antes de:

```bash
ps -A | wc -l
```

perguntar:

> "O que estamos a contar?"

Antes de:

```bash
ps -A | grep emacs
```

perguntar:

> "O `grep` também vai aparecer?"

Antes de:

```bash
cat vtext.txt | xargs
```

perguntar:

> "Como será transformada a lista de linhas?"

Antes do pipeline final:

```bash
ps -A | grep infinity | sed ... | cut ... | xargs kill -9
```

perguntar:

> "Conseguem explicar o que cada processo do pipeline recebe e produz?"

---

# 35. Modelo mental final

No final da aula, os alunos devem conseguir interpretar:

```text
                    SHELL
                      │
              ┌───────┴───────┐
              │               │
          comandos          globbing
              │
              ▼
          processos
              │
       ┌──────┼──────┐
       │      │      │
     stdin  stdout  stderr
       │      │
       │      └───────┐
       │              │
       ▼              ▼
    processo        ficheiro
       │
       └── pipe ──→ processo
                       │
                       ▼
                     xargs
                       │
                       ▼
                    comando
```

A grande mensagem da ficha é:

> **Uma shell não é apenas uma calculadora de comandos. É um ambiente para combinar programas, ficheiros, processos e streams de entrada e saída.**

Os símbolos:

```text
>
>>
<
|
&
```

não são simples caracteres. São operadores que permitem controlar a forma como os processos comunicam com o ambiente.

E comandos como:

```text
find
grep
cut
sort
sed
xargs
ps
kill
```

tornam-se muito mais poderosos quando são combinados.

A competência que queremos desenvolver é, portanto:

```text
COMPREENDER
     ↓
PREVER
     ↓
EXECUTAR
     ↓
OBSERVAR
     ↓
EXPLICAR
     ↓
COMBINAR
```
