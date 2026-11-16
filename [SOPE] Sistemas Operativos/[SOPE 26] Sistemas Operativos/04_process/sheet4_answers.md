# Process Management — Sheet 4: Brief Answers

---

## 1. Three consecutive `fork()` calls

**8 processes** in total, counting the parent.

Each `fork()` duplicates **every** process that reaches it, so the number of processes doubles each time: 1 → 2 → 4 → 8, which is 2³.

To check, print the PIDs before `exit`:

```c
fork(); fork(); fork();
printf("pid=%d ppid=%d\n", getpid(), getppid());
```

The program prints 8 lines with 8 different PIDs.

---

## 2. `fork()` inside a loop that runs 4 times

**16 processes** (2⁴).

Every child continues the loop from the iteration where it was created. So on each iteration, every process that exists forks again, and the count doubles: 1 → 2 → 4 → 8 → 16.

You can check it the same way, by adding `printf("%d\n", getpid());` before `exit`.

---

## 3. `value` in the parent and in the child

- The child prints `value = 1`.
- The parent prints `value = 0`.
- Both print the **same address**.

`fork()` gives the child a **copy** of the parent's address space. The two processes then have separate memories, and the copy is made lazily with copy-on-write. When the child writes `value = 1`, it changes only its own copy, and the parent's copy stays 0.

The addresses are equal because they are **virtual** addresses. The same virtual address is mapped to different physical pages in each process.

```
before fork:  parent [value=0 @0x7ff..]
after  fork:  parent [value=0 @0x7ff..]   child [value=0 @0x7ff..]
child writes: parent [value=0 @0x7ff..]   child [value=1 @0x7ff..]
```

---

## 4. How the child signals its end after `execlp`

If `execlp` succeeds, it **never returns**. The child's code is replaced by the program it executes, such as `ls`.

When that program finishes, it calls `exit()`, or returns from its `main`. The kernel then:

- ends the process,
- stores its exit status,
- sends `SIGCHLD` to the parent.

The parent's `waitpid()` then returns, and it can read the status with `WEXITSTATUS`.

The child does not do anything explicit itself: the end of the exec'd program is the signal.

### The `exec` family: `execl`, `execlp`, `execv`, `execvp`, …

All of these do the same thing: they **replace the current program** with a new one in the same process, which keeps its PID and its open files. If they succeed, they never return; on error they return `-1`.

They differ only in **how you pass the arguments** and **how the program is found**. The letters after `exec` tell you which variant you have:

| Letter | Meaning | Example |
|---|---|---|
| `l` (list) | arguments are written one by one, ending with `NULL` | `execl("/bin/ls", "ls", "-l", NULL)` |
| `v` (vector) | arguments are in an array, ending with `NULL` | `execv("/bin/ls", args)` |
| `p` (path) | the program is searched for in `$PATH`, so a bare name such as `"ls"` is enough | `execlp("ls", "ls", "-l", NULL)` |
| `e` (environment) | you also pass the environment (`envp`) explicitly | `execle(path, "ls", NULL, envp)` |

So:

| Function | Arguments | Searches `$PATH`? | Environment |
|---|---|---|---|
| `execl`  | list   | no  | inherited |
| `execlp` | list   | yes | inherited |
| `execle` | list   | no  | given |
| `execv`  | array  | no  | inherited |
| `execvp` | array  | yes | inherited |
| `execve` | array  | no  | given (this is the real system call; the others are library wrappers around it) |

Two common confusions:

- The **first argument** is the program to run. The **second** becomes `argv[0]`, the name the new program sees for itself. That is why the name is written twice in `execlp("gcc", "gcc", "-Wall", ...)`.
- Use an **`l`** variant when the number of arguments is fixed when you write the code. Use a **`v`** variant when the arguments are only known at run time, such as a command typed by the user. That is why question 6 switches from `execlp` to `execvp`.

---

## 5. Simple shell: why `ls -l` fails, and an `exit` command

The whole line, for example `"ls -l"`, is passed to `execlp` as the **program name**. No program is called `ls -l`, so exec fails with *No such file or directory*. Also, `execlp(command, command, NULL)` never passes any arguments.

To add an `exit` command, test the line before calling `fork()`:

```c
if (strcmp(command, "exit") == 0)
    break;
```

---

## 6. Commands with arguments (`execvp` + `strtok`)

Split the line into words and build an `argv` array that ends with `NULL`:

```c
char *args[64];
int n = 0;
char *tok = strtok(command, " \t");
while (tok != NULL && n < 63) {
    args[n++] = tok;
    tok = strtok(NULL, " \t");
}
args[n] = NULL;
if (n == 0) continue;                       /* empty line */
if (strcmp(args[0], "exit") == 0) break;

pid_t pid = fork();
if (pid == 0) {
    execvp(args[0], args);                  /* e.g. {"ls","-l",NULL} */
    perror("execvp");
    exit(EXIT_FAILURE);
}
waitpid(pid, NULL, 0);
```

`execvp` takes the arguments as an array, so it can handle any number of them. With `execlp`, the number of arguments must be fixed when you write the code. The `exec` table in question 4 compares all the variants.

---

## 7. History and `myhistory n`

1. Append each command line to a file, for example `.myhistory`, before running it.
2. To handle `myhistory n`, run `tail -n <n> .myhistory` in a child process.

```c
/* save the line BEFORE strtok modifies it */
FILE *h = fopen(".myhistory", "a");
if (h) { fprintf(h, "%s\n", command); fclose(h); }

/* ... tokenize into args ... */

if (strcmp(args[0], "myhistory") == 0 && args[1] != NULL) {
    char *t[] = { "tail", "-n", args[1], ".myhistory", NULL };
    if (fork() == 0) {
        execvp("tail", t);
        perror("execvp");
        exit(1);
    }
    wait(NULL);
    continue;
}
```

---

## 8. Template program `par`

The missing includes are:

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
```

How it works:

- The first loop forks one child per argument. Each child prints its PID and its word, then calls `exit`. The `exit` is essential: without it, the child would go on forking in the loop.
- The second loop calls `wait(NULL)` once per child, so the parent does not finish before its children and does not leave zombies.

The children run **in parallel**, so the order of the output lines can change from one run to the next.

---

## 9. `parcc`

This is the `par` pattern with `exec` added:

1. Fork one child per `.c` file. Each child prints `[pid:N] compiling f.c ...` and then runs `execlp("gcc","gcc","-Wall","-c",f,NULL)`.
2. Call `wait()` once per child, checking `WIFEXITED(status) && WEXITSTATUS(status)==0`.
3. If every compilation succeeded, build `{"gcc","f1.o",...,"fn.o","-o",prog,NULL}`, fork once more, run it with `execvp`, and wait for it.

The compile step uses `execlp` because each command always has exactly four words. The link step uses `execvp` because the number of `.o` files is only known at run time (see the `exec` table in question 4).

The full program and the test examples are in `parcc.zip`.

---

## 10. `txt2epub`

This is the same structure as `parcc`, but it runs `pandoc` and then `zip`:

```c
int main(int argc, char *argv[]) {
    /* convert every .txt file in parallel */
    for (int i = 1; i < argc; i++) {
        if (fork() == 0) {
            char out[256];
            snprintf(out, sizeof out, "%s", argv[i]);
            strcpy(strrchr(out, '.'), ".epub");          /* x.txt -> x.epub */
            printf("[pid:%d] converting %s ...\n", getpid(), argv[i]);
            fflush(stdout);
            execlp("pandoc", "pandoc", argv[i], "-o", out, NULL);
            perror("execlp");
            exit(1);
        }
    }
    for (int i = 1; i < argc; i++)
        wait(NULL);

    /* zip ebooks.zip b1.epub ... bn.epub */
    char *cmd[argc + 2];
    cmd[0] = "zip";
    cmd[1] = "ebooks.zip";
    for (int i = 1; i < argc; i++) {
        cmd[i + 1] = malloc(strlen(argv[i]) + 2);        /* ".epub" is 1 char longer */
        strcpy(cmd[i + 1], argv[i]);
        strcpy(strrchr(cmd[i + 1], '.'), ".epub");
    }
    cmd[argc + 1] = NULL;

    if (fork() == 0) {
        execvp("zip", cmd);
        perror("execvp");
        exit(1);
    }
    wait(NULL);
    return 0;
}
```

The program also needs `<string.h>` for `strcpy`, `strrchr` and `strlen`.

The order of the `converting` lines changes from run to run because the conversions run in parallel.
