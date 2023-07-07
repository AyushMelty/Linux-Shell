#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    int flag1=0;
    int flag2=0;
    int flag3=0;
    char path[100];
    // chdir("..");
    getcwd(path,sizeof(path));    
    DIR *dir=opendir(path);
    struct dirent *sd;
   // printf("working");
    if(argc>2){
        printf("Invalid Command\n");
    }
    if(dir==NULL){
        printf("Error! Unable to opend directory");
        return 0;
    }
    if(strcmp(argv[1],"ola")==0){
        while((sd=readdir(dir))!=NULL){
            if(sd->d_name[0]!='.'){
                printf("%s ",sd->d_name);
            }
        }
        flag1=1;
    }
    if(strcmp(argv[1],"-a")==0){
        while((sd=readdir(dir))!=NULL){
            printf("%s ",sd->d_name);
            
        }
        flag2=1;
        
    }
    if(strcmp(argv[1],"-m")==0){
        while((sd=readdir(dir))!=NULL){
            if(sd->d_name[0]!='.'){
                printf("%s, ",sd->d_name);
            }

        }
        flag3=1;
    }
    if(flag1==0 && flag2==0 && flag3==0){
        printf("Invalid Command\n");
    }
    printf("\n");
    closedir(dir);

    return 0;
}
