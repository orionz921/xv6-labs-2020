#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    if(argc !=2 )
    {
        printf("must 1 argument for sleep\n");
        exit(1);
    }
    int sleepnum = atoi(argv[1]);
    printf("nothing happens for a little while)\n");
    sleep(sleepnum);
    exit(0);
}
