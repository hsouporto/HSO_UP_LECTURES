# parcc — parallel C compiler driver

    parcc -o prog prog1.c prog2.c ... progn.c

Each source file is compiled with `gcc -Wall -c file.c` in its own child
process (created with `fork` + `exec`). The parent waits for all of them
(`waitpid`) and, only if every compilation succeeded, links with
`gcc prog1.o ... progn.o -o prog`.

## Build

    make

## Try the examples

    cd examples/hello
    ../../parcc -o hello main.c greet.c farewell.c
    ./hello

    cd ../calc
    ../../parcc -o calc main.c add.c sub.c mul.c div.c
    ./calc 12 x 4

    cd ../stats
    ../../parcc -o stats main.c input.c mean.c minmax.c
    echo 3 1 4 1 5 9 2 6 | ./stats

    cd ../broken          # one file has a syntax error
    ../../parcc -o broken main.c helper.c    # -> errors reported, no linking

Tip: copy `parcc` into a directory on your PATH (e.g. `~/bin`) to type just
`parcc -o prog ...`. Clean everything with `make clean`.

The PIDs in the `[pid:N] compiling ...` lines and their order change from run
to run — that is the processes running in parallel.
