#include"kernel/types.h"
#include"kernel/stat.h"
#include"user/user.h"
#include "kernel/fs.h"

void find(char* path, char * file){
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) <0){
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if(fstat(fd,&st) < 0){
        fprintf(2,"find connot stat %s\n",path);
        close(fd);
        return;
    }

    if(st.type != T_DIR){
        fprintf(2,"find: %s is not a directory\n", path);
        close(fd);
        return;
    }


    switch (st.type)
    {
    case T_FILE:
        fprintf(2,"find: %s is not a dir", path);
        close(fd);
        return;
    case T_DIR:
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
            fprintf(2,"find: path too long\n");
            close(fd);
            return;
        }
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/';
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0)
                continue;
            if(!strcmp(de.name, ".") || !strcmp(de.name, ".."))
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            int fd1;
            if((fd1 = open(buf,0)) >= 0){
                if(fstat(fd1,&st) >= 0){
                    switch(st.type){
                    case T_FILE:
                        if(!strcmp(de.name, file)){
                            printf("%s\n",buf);
                        }
                        close(fd1);
                        break;
                    case T_DIR:
                        close(fd1);
                        find(buf,file);
                        break;
                    case T_DEVICE:
                        close(fd1);
                        break;
                    }
                }
            }
        }
        close(fd);
        break;
    case T_DEVICE:
        close(fd);
        break;
    }
   
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("error input");
        exit(1);
    }
    else{
        find(argv[1], argv[2]);
    }
    exit(0);
}