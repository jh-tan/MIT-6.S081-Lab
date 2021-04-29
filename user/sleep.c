#include "../kernel/types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if(argc == 1 ){
         fprintf(2, "Please enter the duration\n");
         exit(1);
    }
    else if(argc > 2){
         fprintf(2, "Please do not enter argument other than the duration\n");
         exit(1);
    }
    else{
        int sec = atoi(argv[1]);
        sleep(sec);
        exit(1);
    }
}
