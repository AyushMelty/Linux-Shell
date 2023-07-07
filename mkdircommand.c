#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
int main(int argc, char const *argv[])
{
    int flagV=0;
    int flagP=0;
    char*dirname;
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"-p")==0){
            flagP=1;
        }
        if(strcmp(argv[i],"-v")==0){
            flagV=1;
        }
    }
    if(flagP==1 && flagV==1){
        printf("Invalid command");
        return 0;
    }
    if(flagP==0 && flagV==0){
        for(int i=1;i<argc;i++){
            dirname=(char *)argv[i];
            int check=mkdir(dirname,0777);
            if(check!=0){
                printf("mkdir: cannot create directory %s: File exists\n",dirname);
            }
            
        }
    }
    if(flagP==1){
        for(int i=2;i<argc;i++){
            dirname=(char *)argv[i];
            int check=mkdir(dirname,0777);
            
            
        }

    }
    if(flagV==1){
        for(int i=2;i<argc;i++){
            dirname=(char *)argv[i];
            int check=mkdir(dirname,0777);
            if(check!=0){
                printf("mkdir: cannot create directory %s: File exists\n",dirname);
            }
            else{
                printf("mkdir: created directory %s\n",dirname);
            }
            
        }

    }
    return 0;
}
