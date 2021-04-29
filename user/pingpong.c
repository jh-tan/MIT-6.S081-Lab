#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "user.h"

int main(void){
    int p[2];
    char buf[512];
    pipe(p);

    int child = fork();
    if(child < 0){
        fprintf(2,"fork failed\n");
        exit(1);
    }
    else if(child == 0){
        fprintf(2,"%d: received ping\n",getpid());
        read(p[0], buf, 1);
        /*fprintf(2,"Send from parent: %s\n",buf);*/
        write(p[1],"C",1);
    }
    else{
        write(p[1],"P",1);
        wait((int *) 0);
        fprintf(2,"%d: received pong\n",getpid());
        read(p[0], buf, 1);
        /*fprintf(2,"Send from child: %s\n",buf);*/
    }
    exit(0);

}

