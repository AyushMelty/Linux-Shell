#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
int main(int argc, char const *argv[])
{
    int flagI=0;
    int flagD=0;
    char*dirname;
    DIR *dir;
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"-i")==0){
            flagI=1;
        }
        if(strcmp(argv[i],"-d")==0){
            flagD=1;
        }
    }
    if(flagI==1 && flagD==1){
        printf("Invalid command\n");
        return 0;
    }
    if(flagI==0 && flagD==0){
        for(int i=1;i<argc;i++){
            dirname=(char *)argv[i];
            dir=opendir(dirname);
            if(dir!=NULL){
	        printf("rm: cannot remove %s: Is a directory\n",dirname);
                continue;
            }
            else{
                int check=remove(dirname);
                if(check!=0){
                    printf("rm: cannot remove %s: File does not exist\n",dirname);
                }
            
            }
        }
        
    }
    if(flagD==1){
        for(int i=2;i<argc;i++){
            dirname=(char *)argv[i];
            dir=opendir(dirname);
            if(dir!=NULL){

            
                int check=remove(dirname);
                if(check!=0){
                    check=rmdir(dirname);
                    if(check!=0){
                        printf("rm: failed to remove %s: Directory not empty   \n",dirname);
                    }
                }
            }
            else{
                int check=remove(dirname);
                if(check!=0){
                    printf("rm: failed to remove %s: file does not exist \n",dirname);
                }
            }    

            
            
        }

    }
    if(flagI==1){
        char choice;
        int check;        
        for(int i=2;i<argc;i++){
            
            dirname=(char *)argv[i];
            printf("rm: remove regular file %s?\n", dirname);
            scanf("%c",&choice);
            if(choice=='y'){
                dir=opendir(dirname);
                if(dir!=NULL){
	                printf("rm: cannot remove %s: Is a directory\n",dirname);
                    continue;
                }
                else{
                    int check=remove(dirname);
                    if(check!=0){
                        printf("rm: cannot remove %s: File does not exist\n",dirname);
                    }
            
                }
		    
            }
            else{
                continue;
            }
            
        }

    }
    closedir(dir);
    return 0;
}
