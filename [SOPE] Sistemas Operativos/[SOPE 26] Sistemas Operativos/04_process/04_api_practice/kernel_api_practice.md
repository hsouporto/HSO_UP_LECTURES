# Practice Sheet — Processes and IPC (using the kernel API)

These exercises review `fork()`, `exec*()`, `wait()`/`waitpid()`, `exit()`, `pipe()`, `dup2()` and signals. Compile every program with:

```
gcc -Wall -Wextra prog.c -o prog
```

Check the return value of every system call, and use `perror()` when a call fails. Exercises marked with `*` are harder.

---

## Part A — Process management

**1. Counting processes with `&&`.** Without running it, predict how many processes the following program creates, counting the original one. Then run it to check your answer. *Hint:* remember that `&&` stops early when its left side is false (short-circuit evaluation), and that `fork()` returns 0 in the child.

```c
int main(void) {
    if (fork() && fork())
        fork();
    printf("pid=%d ppid=%d\n", getpid(), getppid());
    exit(EXIT_SUCCESS);
}
```

Draw the process tree, and label each process with the values that its `fork()` calls returned.

**2. Why is "hello" printed twice?** Run this program:

```c
int main(void) {
    printf("hello ");
    if (fork() == 0) {
        printf("from child\n");
        exit(EXIT_SUCCESS);
    }
    wait(NULL);
    printf("from parent\n");
    exit(EXIT_SUCCESS);
}
```

The word `hello` appears twice, even though `printf("hello ")` runs only once. Explain why. Change **one line** of the program so that `hello` is printed only once.

**3. Reading the exit status.** Write a program `ex03` that creates a child process:

- `./ex03 N` makes the child end with `exit(N)`.
- `./ex03 abort` makes the child call `abort()`.

The parent must say how the child ended, using `WIFEXITED`, `WEXITSTATUS`, `WIFSIGNALED` and `WTERMSIG`. For example:

```
$ ./ex03 7
child 219 exited with code 7
$ ./ex03 abort
child 221 killed by signal 6 (Aborted)
```

What happens to the exit code if you run `./ex03 300`? Why?

**4. Zombies and orphans.** Write a program with two parts:

- **(a) Zombie.** Create a child that ends immediately, while the parent sleeps for 10 seconds **before** calling `waitpid`. During those 10 seconds, run `ps -o pid,stat,cmd -C ex04` in another terminal. What is the child's state? Why does the kernel keep the child around?
- **(b) Orphan.** Create a child that prints `getppid()`, sleeps for 2 seconds, and prints `getppid()` again. Meanwhile, the parent ends after 1 second **without** waiting for the child. What value does the second `getppid()` print? Explain why.

**5. `timeit`.** Write `timeit cmd [args...]`. It runs the command in a child process using `execvp` and then prints how long the command took and its exit code. For example:

```
$ ./timeit sleep 1
[timeit] sleep: 1.002 s, exit code 0
```

*Hint:* use `clock_gettime(CLOCK_MONOTONIC, ...)`. You don't need to build a new argument array: `&argv[1]` already works, because it ends with `NULL`.

**6. Race of processes.** Write `race t1 t2 ... tn`. It creates one child per argument, and the child number `i` sleeps for `ti` seconds. The parent must print the children **in the order they finish**, not the order they were created:

```
$ ./race 3 1 2
1. child 238 (slept 1 s)
2. child 239 (slept 2 s)
3. child 237 (slept 3 s)
```

*Hint:* use `wait()` and not `waitpid(pid, ...)`. Use each child's exit code to find out which argument belongs to it.

---

## Part B — Inter-process communication

**7. Two-way communication with two pipes.** Write `sumpipe N`. The parent sends the integers `1..N` to its child through one pipe, as binary `int` values rather than text. The child adds them up and sends the total back through a **second** pipe. The parent prints the result and checks it against `N(N+1)/2`.

Why do you need two pipes? What would happen if the parent never closed the write end of the first pipe?

**8. Output redirection.** Write `redir file cmd [args...]`. It behaves like the shell command `cmd args > file`: the command's `stdout` goes to `file`, which is created or emptied first. Use `open`, `dup2` and `execvp`.

```
$ ./redir out.txt echo hello world
$ cat out.txt
hello world
```

**9*. A three-stage pipeline.** Write a program that runs the following, with three child processes and two pipes:

```
ls /usr/bin | sort -r | head -5
```

Check that your output is the same as the shell's. Then **remove** one of the `close()` calls on a pipe end and observe what happens. Explain why.

---

## Part C — Signals

**10. `timeout`.** Write `timeout secs cmd [args...]`. It runs the command, but if the command is still running after `secs` seconds, it kills it with `SIGKILL`. Use `alarm()` and a handler for `SIGALRM`. Print whether the command finished on time or was killed, and return 124 if it was killed. That is what the real `timeout` command returns.

```
$ ./timeout 1 sleep 5
timeout: 'sleep' killed after 1 s
$ ./timeout 3 sleep 1
timeout: 'sleep' finished, exit code 0
```

Why might `waitpid` return `-1` here, even though nothing actually went wrong?

**11. Three Ctrl-C to quit.** Write a program that ignores the first two `SIGINT` signals and quits cleanly on the third, printing a message each time:

```
Ctrl-C #1 (ignored)
Ctrl-C #2 (ignored)
Ctrl-C #3 -> bye
```

Use `sigaction()` instead of `signal()`. The handler must **only** increment a counter. Why should you avoid calling `printf` inside the handler?

**12*. Ping-pong.** A parent and its child take turns printing, 5 rounds each, and use `SIGUSR1` to tell each other it is their turn:

```
ping 1 (parent 261)
  pong 1 (child 262)
ping 2 (parent 261)
  ...
```

A first attempt using `pause()` sometimes hangs forever. Explain why. Then fix it with `sigprocmask()` and `sigsuspend()`.
