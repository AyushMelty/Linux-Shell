#include <stdio.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    int flag1=0;
    int flag2=0;
    int flag3=0;
    FILE *fptr;
    char filedata[100];
    if(argc>3){
        printf("Invalid command\n");
    }
    if(argc==2){
        fptr=fopen(argv[1],"r");
        if(fptr==NULL){
            printf("NO SUCH FILE\n");
            return 0;
        }
        while(fgets(filedata,100,fptr)!=NULL){
            printf("%s",filedata);
        }
        fclose(fptr);
        flag1=1;

    }
    if(strcmp(argv[1],"-n")==0){
        int count=1;
        fptr=fopen(argv[2],"r");
        if(fptr==NULL){
            printf("NO SUCH FILE\n");
            return 0;
        }
        while(fgets(filedata,100,fptr)!=NULL){
            printf("%d ",count);
            printf("%s",filedata);
	    count++;

        }
        flag2=1;
        fclose(fptr);
    }
    if(strcmp(argv[1],"-s")==0){
        int flag=0;
        fptr=fopen(argv[2],"r");
        if(fptr==NULL){
            printf("NO SUCH FILE\n");
            return 0;
        }
        while(fgets(filedata,100,fptr)!=NULL){
            if(strcmp(filedata,"\n")==0){
                if(flag==0){
                    printf("%s",filedata);
                    flag=1;
                }
                else{
                    continue;
                }
            }
            else{
                printf("%s",filedata);
                flag=0;
            }
        }
        flag3=1;
        fclose(fptr);
    }
    if(flag1==0 && flag2==0 && flag3==0){
        printf("Invalid Command\n");
    }
    
    return 0;
}
