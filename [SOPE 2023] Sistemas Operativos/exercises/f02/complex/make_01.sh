clang -Wall -c complex.c
ar -rc libcomplex.a complex.o
ar -t libcomplex.a

clang -Wall use_complex.c -o use_complex -L. -libcomplex -lm
./use-use_complex
