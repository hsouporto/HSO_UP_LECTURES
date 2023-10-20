#include <unistd.h>
#include <stdio.h>

// STATUS: TESTED
int main() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
    
}