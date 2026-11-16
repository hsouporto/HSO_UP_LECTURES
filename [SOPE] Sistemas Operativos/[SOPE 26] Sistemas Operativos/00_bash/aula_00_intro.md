# Ficha #0 — Sistemas Operativos (Linux)

## 1. Ambiente

No Linux (Ubuntu, Fedora, Arch, etc.), abrir o **Terminal** (atalho comum: `Ctrl` + `Alt` + `T`).

Verificar o sistema:

```
uname -s
cat /etc/os-release
```

Verificar a shell (geralmente `bash` por omissão no Linux):

```
echo $SHELL
echo $0
```

Para definir bash expressamente como shell (se necessário):

```
chsh -s /bin/bash
```

## 2. Ferramentas de desenvolvimento

Verificar o compilador:

```
gcc --version
# ou clang --version
```

Se necessário (em distros baseadas em Debian/Ubuntu):

```
sudo apt update
sudo apt install build-essential
```

## 3. Shell: navegação

```
pwd
ls
ls -la
cd /tmp
cd ~
cd ..
```

* `.` → diretório atual

* `..` → diretório pai

* `~` → diretório pessoal

## 4. Ficheiros e diretórios

```
mkdir teste
cd teste
touch ficheiro.txt
cp ficheiro.txt copia.txt
mv copia.txt outro.txt
rm outro.txt
cd ..
rmdir teste
```

## 5. Variáveis de ambiente

```
echo $HOME
echo $USER
echo $SHELL
echo $PATH
env
```

Criar uma variável:

```
NOME="Aluno"
echo $NOME
```

Exportar para processos filhos:

```
export NOME
```

## 6. PATH

Ver o PATH:

```
echo $PATH
```

Descobrir onde está um comando:

```
which ls
command -v ls
```

Exemplo:

```
gcc hello.c -o hello
./hello
```

*(`hello` pode não funcionar porque o diretório atual não está necessariamente no PATH.)*

Adicionar temporariamente um diretório ao PATH:

```
export PATH="$HOME/bin:$PATH"
```

## 7. Primeiro programa C

Criar `hello.c`:

```
#include <stdio.h>

int main(void)
{
    printf("Hello, Operating Systems!\n");
    return 0;
}
```

Compilar:

```
gcc hello.c -o hello
```

Executar:

```
./hello
```

Verificar:

```
ls -l hello
```

## 8. Redirecionamento

```
./hello > output.txt
cat output.txt
```

* `>` → substitui o conteúdo

* `>>` → acrescenta ao ficheiro

Exemplo:

```
ls >> output.txt
```

## 9. Pipes

```
ls -la | less

ls -la | grep ".txt"

ps | grep bash
```

Um pipe liga:

> `stdout` do processo 1 $\rightarrow$ `stdin` do processo 2

## 10. Permissões

```
ls -l hello
```

Exemplo de saída: `-rwxr-xr-x`

* `r` → read

* `w` → write

* `x` → execute

Testar:

```
chmod u-x hello
./hello

chmod u+x hello
./hello
```

## 11. `man`

Consultar documentação:

```
man ls
man cp
man chmod
```

Prestar atenção a:

* `SYNOPSIS`

* `DESCRIPTION`

Pesquisar dentro do man:

* `/termo`

Sair:

* `q`

### Secções importantes

```
man 1 ls
man 2 fork
man 3 printf
```

* `1` → comandos

* `2` → system calls

* `3` → funções da biblioteca C

## 12. Comandos vs. executáveis

```
type ls
type cd
which ls
```

> Nem todos os comandos são executáveis. Alguns são *builtins* da shell, como `cd`.

## Objetivo da aula

Compreender a relação:

```
Terminal
   ↓
Shell
   ↓
comandos / variáveis
   ↓
PATH
   ↓
executáveis
   ↓
processos
   ↓
stdin / stdout / pipes
```

O objetivo principal é compreender o que cada comando faz e como as suas opções alteram o comportamento, e adquirir o hábito de consultar o `man` em vez de apenas memorizar comandos.