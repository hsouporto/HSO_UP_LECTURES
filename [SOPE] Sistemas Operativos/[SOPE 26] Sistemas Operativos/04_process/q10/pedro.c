#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <errno.h>


int main(int argc, char *argv[]) {
    pid_t pid;

    for (int i = 1; i < argc ; i++){
        char fl[100];
        strcpy(fl,argv[i]);

        char *endf = strtok(fl, "."); // Mudei aqui para a copia, argv apos prmeira execucao exec é modificado
        //endf = realloc(endf, (strlen(endf)+ 10) * sizeof (char));
        strcat (endf,".epub");


        //strcat(zipargs,fl);
        //strcat(zipargs," ");
        pid = fork();
        if (pid < 0) {
            perror("txt fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0){
            printf("ori: %s - dest %s \n", fl, endf);

            printf("process %d is converting file %s\n", getpid(),argv[i]);
            execlp("pandoc","pandoc", argv[i] ,"-o", endf, (char*)NULL);

            exit(0);
        }

    }


    for (int i = 1; i < argc ;i++)
        wait(NULL);


    printf("process %d is creating the zip file\n", getpid());

    execlp("zip", "zip", "-R", "livros", "*.epub", (char *)NULL); //tinha um caracter extranho nos tokens)



return 0;
}