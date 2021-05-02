//két csővezeték létrehozása
//a szülő procesz elküldi a saját pidjét a gyerek procesznek
//a gyerek procesz kiírja a képernyőre a szülő procesz pidjét
//a gyerek procesz vissza köldi az ő pidjét a másik pipeon
//a szülő megvárja a gyerek procesz megszünését és ő is megszünik

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <glob.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int fd1[2];
    int fd2[2];

    pid_t p_pid;
    pid_t c_pid;
    pid_t p;
  
    if (pipe(fd1)==-1)
    {
        printf(stderr, "Pipe hiba" );
        return 1;
    }
    if (pipe(fd2)==-1)
    {
        printf(stderr, "Pipe hiba" );
        return 1;
    }
  
    p = fork();
  
    if (p < 0)
    {
        fprintf(stderr, "fork hiba" );
        return 1;
    }
    else if (p > 0)
    {
        //szulo proces
  
        close(fd1[0]);

        p_pid = getpid();
        
        write(fd1[1], &p_pid, sizeof(p_pid));
        close(fd1[1]);
  
        wait(NULL);
  
        close(fd2[1]); 
        
        read(fd2[0], &c_pid, sizeof(c_pid));
        printf("A gyerek pid: %d \n", c_pid);
        close(fd2[0]);
    }
    else
    {
        //gyerek procesz

        close(fd1[1]);

        read(fd1[0], &p_pid, sizeof(p_pid));
        printf("A szulo pid: %d \n", p_pid);
  
        
        close(fd1[0]);
        close(fd2[0]);

        c_pid = getpid();
  
        write(fd2[1], &c_pid, sizeof(c_pid));

        close(fd2[1]);
  
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_SUCCESS);
}