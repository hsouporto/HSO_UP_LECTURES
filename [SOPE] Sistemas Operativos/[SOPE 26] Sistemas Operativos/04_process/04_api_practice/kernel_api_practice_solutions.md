# Practice Sheet — Solutions

Every program below was compiled with `gcc -Wall -Wextra`, with no warnings, and run. The sample output shown comes from real runs; the PIDs will be different on your machine.

---

## Part A — Process management

### 1. Counting processes with `&&`

The program creates **4 processes**, counting the original one. Call the original process **P**.

1. P runs the first `fork()` and creates **A**. In A, the first `fork()` returned 0, so `0 && ...` is false. A skips the second `fork()` and the `if` body.
2. In P, the first `fork()` returned A's PID, which is true, so P runs the second `fork()` and creates **B**. In B, that second `fork()` returned 0, so the condition is false and B skips the `if` body.
3. In P, both calls returned true, so P enters the `if` body and runs the third `fork()`, creating **C**.

```
P ─┬─ A   (1st fork = 0  -> stops)
   ├─ B   (2nd fork = 0  -> stops)
   └─ C   (created inside the if)
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    if (fork() && fork())
        fork();
        
    printf("pid=%d ppid=%d\n", getpid(), getppid());
    exit(EXIT_SUCCESS);
}
```

### 2. Why is "hello" printed twice?

`printf` doesn't write to the terminal straight away: it puts the text in a **buffer** inside the process's memory. A line-buffered `stdout` only sends its buffer out when it sees `\n`. So when `fork()` runs, `"hello "` is still waiting in the buffer.

`fork()` copies the whole memory of the process, and the buffer is part of it. Both processes therefore hold `"hello "`, and each prints it when it flushes its buffer.

To fix it, add `fflush(stdout);` before the `fork()`. Writing `"hello\n"` instead also works when the output goes to a terminal, but not when it goes to a pipe or a file, which are fully buffered.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    printf("hello ");          /* no '\n': stays in the stdio buffer */
    /* fflush(stdout); */      /* uncomment to print "hello" only once */
    if (fork() == 0) {
        printf("from child\n");
        exit(EXIT_SUCCESS);
    }
    wait(NULL);
    printf("from parent\n");
    exit(EXIT_SUCCESS);
}
```

### 3. Reading the exit status

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* Usage: ./ex03 N   -> child exits with N; ./ex03 abort -> child crashes */
int main(int argc, char *argv[])
{
    if (argc != 2) { fprintf(stderr, "Usage: %s N|abort\n", argv[0]); return 1; }

    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) {
        if (strcmp(argv[1], "abort") == 0)
            abort();                       /* killed by SIGABRT */
        exit(atoi(argv[1]));
    }

    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        printf("child %d exited with code %d\n", pid, WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("child %d killed by signal %d (%s)\n",
               pid, WTERMSIG(status), strsignal(WTERMSIG(status)));
    return 0;
}
```

```
$ ./ex03 7
child 219 exited with code 7
$ ./ex03 abort
child 221 killed by signal 6 (Aborted)
$ ./ex03 300
child 288 exited with code 44
```

The status only stores the **low 8 bits** of the exit code, so the value is always between 0 and 255, and 300 & 255 = 44. That is why programs use small exit codes, with 0 meaning success.

`abort()` doesn't exit normally, so `WIFEXITED` is false. The child was killed by `SIGABRT` (signal 6), so `WIFSIGNALED` is true.

### 4. Zombies and orphans

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    /* Part A: zombie */
    pid_t z = fork();
    if (z == 0)
        exit(0);                            /* child ends immediately */
    printf("zombie child: %d -- run: ps -o pid,stat,cmd -p %d\n", z, z);
    fflush(stdout);
    sleep(10);                              /* parent has not waited yet */
    waitpid(z, NULL, 0);                    /* now the zombie disappears */
    printf("zombie reaped\n");
    fflush(stdout);                         /* don't copy the buffer into the next child */

    /* Part B: orphan */
    pid_t o = fork();
    if (o == 0) {
        printf("orphan: my parent is %d\n", getppid());
        sleep(2);                           /* parent exits meanwhile */
        printf("orphan: my parent is now %d\n", getppid());
        exit(0);
    }
    sleep(1);
    printf("parent %d exits without waiting\n", getpid());
    return 0;
}
```

```
  PID STAT CMD
  273 S    ./ex04
  275 Z    [ex04] <defunct>
...
orphan: my parent is 273
orphan: my parent is now 1
```

- **(a) Zombie (state `Z`, `<defunct>`).** The child has ended, but the kernel keeps a small entry for it, holding its PID and exit status. The parent may still call `wait` to read that status. The entry disappears once the parent waits. A parent that never waits leaves zombies behind, and these use up PIDs.
- **(b) Orphan.** When the parent ends first, the child is **adopted** by `init`, PID 1, or by a designated "subreaper" process, so `getppid()` changes. The new parent will call `wait` for the child when it ends, so the orphan doesn't stay a zombie forever.

The `fflush(stdout)` calls in the solution matter. Without them, when the output is sent to a pipe or a file, the second child inherits the text still in the buffer and prints it again. This is exercise 2 happening for real.

### 5. `timeit`

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

/* Usage: ./timeit cmd [args...] */
int main(int argc, char *argv[])
{
    if (argc < 2) { fprintf(stderr, "Usage: %s cmd [args...]\n", argv[0]); return 1; }

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) {
        execvp(argv[1], &argv[1]);          /* argv[1..] is already NULL-terminated */
        perror("execvp");
        exit(127);
    }

    int status;
    waitpid(pid, &status, 0);
    clock_gettime(CLOCK_MONOTONIC, &t1);

    double secs = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
    fprintf(stderr, "[timeit] %s: %.3f s, exit code %d\n",
            argv[1], secs, WIFEXITED(status) ? WEXITSTATUS(status) : -1);
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}
```

```
$ ./timeit sleep 1
[timeit] sleep: 1.002 s, exit code 0
$ ./timeit ls /nonexistent
ls: cannot access '/nonexistent': No such file or directory
[timeit] ls: 0.010 s, exit code 2
```

`argv` always ends with `NULL`, so `&argv[1]` is already a valid argument array for `execvp`. `CLOCK_MONOTONIC` is used rather than the wall clock because it doesn't jump if the system time is changed while the command runs. Exit code 127 is the usual convention for "command not found".

### 6. Race of processes

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* Usage: ./race 3 1 2  -> each child sleeps N seconds; print finishing order */
int main(int argc, char *argv[])
{
    int n = argc - 1;
    pid_t pids[n];

    for (int i = 0; i < n; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            sleep(atoi(argv[i + 1]));
            exit(i + 1);                    /* exit code = position in argv */
        }
    }

    for (int place = 1; place <= n; place++) {
        int status;
        pid_t who = wait(&status);          /* returns whichever child ends first */
        int idx = WEXITSTATUS(status);
        printf("%d. child %d (slept %s s)\n", place, who, argv[idx]);
    }
    return 0;
}
```

```
$ ./race 3 1 2
1. child 238 (slept 1 s)
2. child 239 (slept 2 s)
3. child 237 (slept 3 s)
```

`wait()` returns **whichever** child ends first, so the results come out in the order the children finish. Calling `waitpid(pids[i], ...)` in a loop would report them in the order they were created. Each child's exit code tells the parent which argument it was given.

---

## Part B — Inter-process communication

### 7. Two-way communication with two pipes

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* Usage: ./sumpipe N  -> parent sends 1..N to the child, child returns the sum */
int main(int argc, char *argv[])
{
    if (argc != 2) { fprintf(stderr, "Usage: %s N\n", argv[0]); return 1; }
    int n = atoi(argv[1]);

    int down[2], up[2];                     /* down: parent->child, up: child->parent */
    if (pipe(down) == -1 || pipe(up) == -1) { perror("pipe"); return 1; }

    if (fork() == 0) {                      /* child */
        close(down[1]);
        close(up[0]);
        long sum = 0;
        int x;
        while (read(down[0], &x, sizeof x) == sizeof x)
            sum += x;
        write(up[1], &sum, sizeof sum);
        close(down[0]);
        close(up[1]);
        exit(0);
    }

    close(down[0]);                         /* parent */
    close(up[1]);
    for (int i = 1; i <= n; i++)
        write(down[1], &i, sizeof i);
    close(down[1]);                         /* child's read() returns 0 -> loop ends */

    long sum;
    read(up[0], &sum, sizeof sum);
    close(up[0]);
    wait(NULL);
    printf("sum 1..%d = %ld (expected %ld)\n", n, sum, (long)n * (n + 1) / 2);
    return 0;
}
```

```
$ ./sumpipe 1000
sum 1..1000 = 500500 (expected 500500)
```

- **Two pipes are needed** because a pipe only goes **one way**. With a single pipe, the parent could even read back its own numbers. A `socketpair` would work with just one channel, because it is bidirectional.
- **If the parent never closes `down[1]`,** the child's `read` never returns 0, because a write end is still open. The child waits forever, the parent waits forever for the total, and the program is stuck: a **deadlock**.
- Each side also closes the ends it doesn't use, for the same reason.

### 8. Output redirection

```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

/* Usage: ./redir out.txt cmd [args...]   (same as: cmd args > out.txt) */
int main(int argc, char *argv[])
{
    if (argc < 3) { fprintf(stderr, "Usage: %s file cmd [args...]\n", argv[0]); return 1; }

    pid_t pid = fork();
    if (pid == 0) {
        int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) { perror("open"); exit(1); }
        dup2(fd, STDOUT_FILENO);            /* fd 1 now points to the file */
        close(fd);
        execvp(argv[2], &argv[2]);
        perror("execvp");
        exit(127);
    }
    int status;
    waitpid(pid, &status, 0);
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}
```

`dup2(fd, 1)` makes file descriptor 1 (`stdout`) point to the open file. `exec` keeps the file descriptors, so `echo` writes to file descriptor 1 as usual and the text ends up in the file. `echo` never knows. This is how the shell implements `>`.

The redirection is done **in the child**, so the parent's own `stdout` stays the same.

### 9*. A three-stage pipeline

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* Runs:  ls /usr/bin | sort -r | head -5 */
char *cmd1[] = { "ls", "/usr/bin", NULL };
char *cmd2[] = { "sort", "-r", NULL };
char *cmd3[] = { "head", "-5", NULL };

/* start cmd with stdin from 'in' and stdout to 'out' (-1 = leave as is) */
static void start(char **cmd, int in, int out, int p1[2], int p2[2])
{
    if (fork() == 0) {
        if (in != -1)  dup2(in, STDIN_FILENO);
        if (out != -1) dup2(out, STDOUT_FILENO);
        /* close ALL pipe ends, or the readers never see EOF */
        close(p1[0]); close(p1[1]);
        close(p2[0]); close(p2[1]);
        execvp(cmd[0], cmd);
        perror("execvp");
        exit(127);
    }
}

int main(void)
{
    int p1[2], p2[2];
    if (pipe(p1) == -1 || pipe(p2) == -1) { perror("pipe"); return 1; }

    start(cmd1, -1,    p1[1], p1, p2);      /* ls   -> p1          */
    start(cmd2, p1[0], p2[1], p1, p2);      /* p1   -> sort -> p2  */
    start(cmd3, p2[0], -1,    p1, p2);      /* p2   -> head        */

    close(p1[0]); close(p1[1]);             /* parent uses no pipe end */
    close(p2[0]); close(p2[1]);
    for (int i = 0; i < 3; i++)
        wait(NULL);
    return 0;
}
```

Its output is identical to the output of `ls /usr/bin | sort -r | head -5` in the shell.

How the pipes are connected:

- `ls` writes into the first pipe.
- `sort` reads from the first pipe and writes into the second.
- `head` reads from the second pipe.

**What happens if you remove a `close()`:** for example, if the parent doesn't close `p1[1]`, the program **hangs**. A reader only sees EOF once **every** copy of the pipe's write end is closed. After `fork`, each process holds its own copy of each end. `sort` needs EOF before it can print anything, and it never gets it while the parent still holds `p1[1]`, so `head` never receives any lines and everyone waits forever. When I tested this, the program had to be stopped after 3 seconds and printed nothing.

---

## Part C — Signals

### 10. `timeout`

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

/* Usage: ./timeout SECS cmd [args...] */
static pid_t child;

static void on_alarm(int sig)
{
    (void)sig;
    kill(child, SIGKILL);                   /* time is up */
}

int main(int argc, char *argv[])
{
    if (argc < 3) { fprintf(stderr, "Usage: %s secs cmd [args...]\n", argv[0]); return 1; }

    child = fork();
    if (child == 0) {
        execvp(argv[2], &argv[2]);
        perror("execvp");
        exit(127);
    }

    signal(SIGALRM, on_alarm);
    alarm(atoi(argv[1]));                   /* SIGALRM after SECS seconds */

    int status;
    while (waitpid(child, &status, 0) == -1)
        ;                                   /* retry if interrupted by the signal */
    alarm(0);                               /* cancel alarm if child ended in time */

    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGKILL) {
        printf("timeout: '%s' killed after %s s\n", argv[2], argv[1]);
        return 124;
    }
    printf("timeout: '%s' finished, exit code %d\n", argv[2], WEXITSTATUS(status));
    return WEXITSTATUS(status);
}
```

```
$ ./timeout 1 sleep 5
timeout: 'sleep' killed after 1 s          (exit code 124)
$ ./timeout 3 sleep 1
timeout: 'sleep' finished, exit code 0
```

- `alarm(n)` asks the kernel to send `SIGALRM` to the process after `n` seconds. The handler then kills the child.
- **Why `waitpid` can return -1:** when a signal arrives during a blocking system call, the call may be **interrupted** and return -1 with `errno == EINTR`. Nothing really went wrong, so the loop just calls `waitpid` again.
- `alarm(0)` cancels the alarm if the child finished in time.

### 11. Three Ctrl-C to quit

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

static volatile sig_atomic_t count = 0;

static void on_int(int sig) { (void)sig; count++; }

int main(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    sa.sa_handler = on_int;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    printf("PID %d: press Ctrl-C three times to quit\n", getpid());
    int seen = 0;
    while (count < 3) {
        pause();
        if (count != seen) {
            seen = count;
            printf("Ctrl-C #%d%s\n", seen, seen < 3 ? " (ignored)" : " -> bye");
        }
    }
    return 0;
}
```

```
PID 256: press Ctrl-C three times to quit
Ctrl-C #1 (ignored)
Ctrl-C #2 (ignored)
Ctrl-C #3 -> bye
```

- **Why not `printf` in the handler:** `printf` is **not async-signal-safe**. If the signal arrives while `main` is itself in the middle of a `printf`, the stdio buffer can be corrupted, or the program can deadlock.
- **Doing it safely:** the handler only changes a `volatile sig_atomic_t` counter, and `main` does the printing after `pause()` returns.
- **Why `sigaction`:** it behaves the same on every Unix system, and it lets you control which signals are blocked while the handler runs (`sa_mask`) and what happens to interrupted calls (`sa_flags`).

### 12*. Ping-pong

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

/* Parent and child take turns printing, synchronised with SIGUSR1 */
#define ROUNDS 5

static void on_usr1(int sig) { (void)sig; }

int main(void)
{
    /* Block SIGUSR1 first, so a signal sent "too early" is kept pending
       instead of being lost; sigsuspend() unblocks it while waiting. */
    sigset_t block, old;
    sigemptyset(&block);
    sigaddset(&block, SIGUSR1);
    sigprocmask(SIG_BLOCK, &block, &old);
    signal(SIGUSR1, on_usr1);

    pid_t child = fork();
    if (child == 0) {
        pid_t parent = getppid();
        for (int i = 1; i <= ROUNDS; i++) {
            sigsuspend(&old);               /* wait for the parent's turn to end */
            printf("  pong %d (child %d)\n", i, getpid());
            fflush(stdout);
            kill(parent, SIGUSR1);
        }
        exit(0);
    }

    for (int i = 1; i <= ROUNDS; i++) {
        printf("ping %d (parent %d)\n", i, getpid());
        fflush(stdout);
        kill(child, SIGUSR1);
        sigsuspend(&old);                   /* wait for the child's answer */
    }
    wait(NULL);
    return 0;
}
```

```
ping 1 (parent 261)
  pong 1 (child 262)
ping 2 (parent 261)
  pong 2 (child 262)
...
ping 5 (parent 261)
  pong 5 (child 262)
```

**Why the `pause()` version can hang:** this is a **race condition**. Suppose the parent sends `SIGUSR1` before the child has reached `pause()`. The handler runs immediately and the signal is used up. The child then calls `pause()` and waits for a signal that has already come and gone, so both processes end up waiting for each other forever.

**The fix:**

1. **Block** `SIGUSR1` with `sigprocmask` **before** calling `fork()`. A blocked signal isn't lost: it stays *pending*.
2. Wait with `sigsuspend(&old)`. In a single atomic step, it unblocks the signal and waits for it, so a signal that arrived early is delivered at once and the wait ends.
3. The mask is inherited by the child through `fork()`, so the child is protected from the start too.
