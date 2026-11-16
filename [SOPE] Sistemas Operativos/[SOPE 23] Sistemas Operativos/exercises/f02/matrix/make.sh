gcc -c -Wall -fPIC -o matrix.o matrix.c
gcc -shared -o libmatrix.so matrix.o

gcc -Wall use_matrix.c -o use_matrix -L. -lmatrix
./use_matrix
