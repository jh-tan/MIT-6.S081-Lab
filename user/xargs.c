#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../kernel/param.h"
#include "user.h"

#define MAX 1024
int main(int argc, char *argv[])
{
    //example echo hello too | xargs echo bye
    char line[MAX];
    char* params[MAXARG];
    int n, args_index = 0;
    int i;
    //argv[0] = xargs
    //argv[1] = echo
    //argv[2] = bye
    //argv[3] = null
    //cmd = echo
    char* cmd = argv[1];
    for (i = 1; i < argc; i++) params[args_index++] = argv[i];

    //params[0] = echo
    //params[1] = bye

    // Read stand input
    while ((n = read(0, line, MAX)) > 0)
    {
        //read : hello too
        if (fork() == 0) // child process
        {
            int index = 0;
            char *p;
            for (p = line; *p !='\0' ;p++)
            {
                if (*p == ' ' || *p == '\n')
                {
                    *p = '\0';
                    params[args_index++] = p-index;
                    index = 0;
                    //params[2] = hello
                    //params[3] = too
                }
                else
                    index++;
            }
            params[args_index] = 0;
            exec(cmd, params);
        }
        else wait((int*)0);
    }
    exit(0);
}
