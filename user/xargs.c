#include"kernel/types.h"
#include"kernel/stat.h"
#include"user/user.h"
#include"kernel/param.h"

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("inpur error");
        exit(1);
    }
    char* argvs[MAXARG];
    int idx = 0;
    for(int i = 0; i < argc-1; ++i){
        argvs[idx++] = argv[i+1];
    }

    char buf[512];
    while(read(0,buf,sizeof(buf))>0){
        char temp[MAXARG] = {"\0"};
        int cur = 0;
        for(int i = 0; i < strlen(buf); ++i){
            if(buf[i] == '\n' || buf[i] == ' '){
                if(fork() == 0){
                    temp[cur] = 0;
                    argvs[idx] = temp;
                    exec(argv[1],argvs);
                    exit(0);
                }
                wait(0);
                memset(temp,0,sizeof(temp));
                cur = 0;
            }
            else{
                temp[cur++] = buf[i];
            }
            
        }
    }

    exit(0);
}