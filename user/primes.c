#include"kernel/types.h"
#include"kernel/stat.h"
#include"user/user.h"

void primes(int p[]){
    close(p[1]);
    int new_p[2];
    int prime;
    if(read(p[0], &prime, 4)){
        printf("prime %d\n", prime);
        pipe(new_p);
        if(fork() == 0){
            primes(new_p);
        }
        else{
            close(new_p[0]);
            int num;
            while(read(p[0], &num, 4)){
                if(num % prime != 0)write(new_p[1], &num, 4);
            }
            close(p[0]);
            close(new_p[1]);
            wait(0);
        }
    }
    else{
        close(p[1]);
    }
    exit(0);
}

int main(){
    int p[2];
    pipe(p);
    if(fork() == 0){
        primes(p);
    }
    else{
        close(p[0]);
        for(int i = 2; i <= 35; ++i){
            if(write(p[1], &i, 4) != 4){
                printf("write error");
                exit(1);
            }
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}
