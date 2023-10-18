gcc -c -Wall -fPIC -o complex.o complex.c
gcc -shared -o libcomplex.so complex.o

gcc -Wall use_complex.c -o use_complex -L. -lcomplex
./use_complex
#export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH