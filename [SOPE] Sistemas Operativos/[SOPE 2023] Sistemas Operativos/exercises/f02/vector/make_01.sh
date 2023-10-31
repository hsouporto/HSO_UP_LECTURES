gcc -c -Wall -fPIC -o vector.o vector.c
gcc -shared -o libvector.so vector.o

gcc -Wall use_vector.c -o use_vector -L. -lvector
./use_vector

