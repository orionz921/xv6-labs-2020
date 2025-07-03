#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    int fp[2];
    int cp[2];
    pipe(fp);
    pipe(cp);
    char readtxt[10];
    int pid = fork();
    if(pid == 0)
    {
        close(fp[1]);
        close(cp[0]);
        if(read(fp[0],readtxt,10)){
            printf("%d: received %s\n",getpid(),readtxt);
        }
        write(cp[1],"pong",10);
        close(cp[1]);
        close(fp[0]);
        exit(0);
    }
    else{
        close(cp[1]);
        close(fp[0]);
        write(fp[1],"ping",10);
        if(read(cp[0],readtxt,10)){
            printf("%d: received %s\n",getpid(),readtxt);
        }
        close(fp[1]);
        close(cp[0]);
    }
    exit(0);
}
