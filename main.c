#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>
#include<pthread.h>      

#define MAX_COMMAND_SIZE 256
#define MAX_ARG_SIZE 16
pid_t pid;
int flagt;
char commandPath[100];
char command[MAX_COMMAND_SIZE];
char *args_arr[MAX_ARG_SIZE];
void runInter(char *command);//handles internal commands
void runLS();
void runCAT();
void runpwd();
void runEcho();
void runDate();
void runMkdir();
void runrm();
void runnewLS();
void* sysLS();
void runnewCat();
void* sysCAT();
void runnewDATE();
void* sysDATE();
void runnewMKDIR();
void* sysMKDIR();
void runnewRM();
void* sysRM();
void get_command()
{
    printf("LinuxShell$  ");
    fgets(command, MAX_COMMAND_SIZE, stdin);
    if (((command[strlen(command)-1]=='\n') && strlen(command) > 0)){
        command[strlen(command)-1] = '\0';
    }
    
}
char cur_path[256];
void change_dir(char *pth) {
	int ret;
	if (pth[0] == '.') {
		getcwd(cur_path, sizeof(cur_path));
		strcat(cur_path,"/");
		strcat(cur_path,pth);
		ret = chdir(cur_path);	
	}
	else if (pth[0] == '~') {
		pth++;
		char *cur_path = getenv("HOME");
		strcat(cur_path, pth);
		ret = chdir(cur_path);
	}
	else {
		ret = chdir(pth);
	}
	if (ret == -1) {
		printf("Invalid Path\n");
	}
	else {
		char present[10001];
		getcwd(present, sizeof(present));
		printf("%s\n", present);
	}
}

int cnt;
void parse_command()
{
    cnt = 0;
    char *p = command;
    while(*p != '\0')
    {
        if(*p == ' ')
        {
            *p = '\0';
            p++;
            continue;
        }
        args_arr[cnt++] = p;
        while(*p != '\0' && *p != ' ')
            p++;
    }
    args_arr[cnt] = NULL;
}

// pid_t pid;
int main()
{
    getcwd(commandPath,sizeof(commandPath));
    while(1==1)
    {
        flagt=0;
        get_command();
        
        if (strcmp(command, "exit") == 0){
            return 0;
        }

        if (strcmp("", command) == 0){
            continue;
        }
        
        parse_command();
        

        if (strcmp(args_arr[0], "cd") == 0) {
            change_dir(args_arr[1]);
            continue;
        }
        if(strcmp(args_arr[0],"ls")==0){
            if(strcmp(args_arr[cnt-1],"&t")==0){
                flagt=1;
                runnewLS();
            }
            else{
                runLS();
            }
        }
        if(strcmp(args_arr[0],"cat")==0){
            if(strcmp(args_arr[cnt-1],"&t")==0){
                runnewCat();
            }
            else{
                runCAT();
                continue;

            }
            
        }
        if(strcmp(args_arr[0],"pwd")==0){
            runpwd();
            continue;
        }
        if(strcmp(args_arr[0],"echo")==0){
            runEcho();
            continue;
        }
        if(strcmp(args_arr[0],"date")==0){
            if(strcmp(args_arr[cnt-1],"&t")==0){
                runnewDATE();
                
            }
            else{
                runDate();
            }
        }
        if(strcmp(args_arr[0],"mkdir")==0){
            if(strcmp(args_arr[cnt-1],"&t")==0){
                runnewMKDIR();
            }
            else{
                runMkdir();
            }
        }
        if(strcmp(args_arr[0],"rm")==0){
            if(strcmp(args_arr[cnt-1],"&t")==0){
                runnewRM();
            }
            else{
                runrm();
            }
        }


        // pid = fork();

        
    }
    return 0;
}
void* sysLS(){
    char path[100];
    char temp[100];
    strcpy(path,commandPath);
    strcat(path,"/./ls");
    if(cnt==2){
        strcat(path," ola");
        int ret= system(path);
        
    }
    else{
        for(int i=1;i<cnt-1;i++){
            sprintf(temp," %s",args_arr[i]);
            strcat(path,temp);
        }
       
        int ret= system(path);
       
    }
}
void runnewLS(){
    pthread_t t1;
    pthread_create(&t1,NULL,&sysLS,NULL);
    pthread_join(t1,NULL);
    return;
    

}
void* sysCAT(){
    char path[100];
    char temp[100];
    strcpy(path,commandPath);
    strcat(path,"/./cat");
    
    
    for(int i=1;i<cnt-1;i++){
        sprintf(temp," %s",args_arr[i]);
        strcat(path,temp);
    }
   // printf("%s\n",path);
    int ret= system(path);
       
    

    
}
void runnewCat(){
    pthread_t t1;
    pthread_create(&t1,NULL,&sysCAT,NULL);
    pthread_join(t1,NULL);
    return;

}

void runLS(){
    char path[100];
    int a=0;
    int m=0;
    strcpy(path,commandPath);
    strcat(path,"/ls");
   // printf("reached\n");
    if(cnt==1){
       // printf("reached further");
        char *const argv[]={path,"ola",NULL};
        pid=fork();
        if(pid==0){
            execv(argv[0],argv);
        }
        else{
            wait(NULL);
            return;
        }
    }
    if(strcmp(args_arr[1],"-a")==0){
        a=1;
    }
    if(strcmp(args_arr[1],"-m")==0){
        m=1;
    }
    
    if(a==1){
        char *const argv[]={path,"-a",NULL};
        pid=fork();
        if(pid==0){
            execv(argv[0],argv);
        }
        else{
            wait(NULL);
            return;
        }

    }
    if(m==1){
        char *const argv[]={path,"-m",NULL};
        pid=fork();
        if(pid==0){
            execv(argv[0],argv);
        }
        else{
            wait(NULL);
            return;
        }

    }
}
void runCAT(){
    char path[100];
    strcpy(path,commandPath);
    strcat(path,"/cat");
    int n=0;
    int s=0;
    if(strcmp(args_arr[1],"-n")==0){
        n=1;
    }
    if(strcmp(args_arr[1],"-s")==0){
        s=1;
    }
    if(s==0 && n==0){
        char *const argv[]={path,args_arr[1],NULL};
        pid=fork();
        if(pid==0){
            execv(argv[0],argv);
        }
        else{
            wait(NULL);
            return;
        }
    }
    if(s==1 && n==0){
        char *const argv[]={path,"-s",args_arr[2],NULL};
        pid=fork();
        if(pid==0){
            execv(argv[0],argv);
        }
        else{
            wait(NULL);
            return;
        }
    }
    if(s==0 && n==1){
        char *const argv[]={path,"-n",args_arr[2],NULL};
        pid=fork();
        if(pid==0){
            execv(argv[0],argv);
        }
        else{
            wait(NULL);
            return;
        }
    }
}

void runpwd(){
    char ans[100];
    int flag1=0;
    int flag2=0;
    int flag3=0;
    if(cnt>2){
        printf("Invalid Command\n");
        return;
    }

    if((int)cnt==1){
        puts(getcwd(ans,100));
        return;
    }
    if(strcmp(args_arr[1],"-L")==0){
        flag2=1;
    }
    if(strcmp(args_arr[1],"-P")==0){
        flag3=1;
    }
    if(flag2==1 && flag3==1){
        printf("Invalid Input");
        return;
    }
    if(flag2==1 && flag3==1){
        printf("Invalid Command\n");
        return;
    }
    if(flag2==0 && flag3==0){
        printf("Invalid Command\n");
        return;
    }
    if(flag2==1 || flag3==1){
        puts(getcwd(ans,100));
        return;
        
    }
}
void runEcho(){
    if((int)cnt==1){
        return;
    }
    if(strcmp(args_arr[1],"-n")==0){
        for(int i=2;i<(int)cnt;i++){
            printf("%s ",args_arr[i]);
        }
        return;
    }
    if(strcmp(args_arr[1],"--help")==0){
        printf("Echo the STRING(s) to standard output.\n-n do not output the trailing newline\n--help display this help and exit");
        return;
    }
    for(int i=1;i<(int)cnt;i++){
        printf("%s ",args_arr[i]);
    }
    printf("\n");
    return;
}
void* sysDATE(){
    char path[100];
    char temp[100];
    strcpy(path,commandPath);
    strcat(path,"/./date");
    
    
    for(int i=1;i<cnt-1;i++){
        sprintf(temp," %s",args_arr[i]);
        strcat(path,temp);
    }
   // printf("%s\n",path);
    int ret= system(path);


}
void runnewDATE(){
    pthread_t t1;
    pthread_create(&t1,NULL,&sysDATE,NULL);
    pthread_join(t1,NULL);
    return;

}
void runDate(){
    char path[100];
    strcpy(path,commandPath);
    strcat(path,"/date");
    if((int)cnt==1){
        char *const argv[]={path,NULL};
        pid=fork();
        if(pid==0){
            execv(argv[0],argv);
        }
        else{
            wait(NULL);
            return;
        }


    }
    if((int)cnt==3){
        printf("Invalid Input");
        return;
    }
    if(strcmp(args_arr[1],"-R")){
        char *const argv[]={path,"-R",NULL};
        pid=fork();
        if(pid==0){
            execv(argv[0],argv);
        }
        else{
            wait(NULL);
            return;
        }

        
    }
    if(strcmp(args_arr[1],"-u")){
        char *const argv[]={path,"-u",NULL};
        pid=fork();
        if(pid==0){
            execv(argv[0],argv);
            return;
        }
        else{
            wait(NULL);
            return;
        }

        
    }

}
void* sysMKDIR(){
    char path[100];
    char temp[100];
    strcpy(path,commandPath);
    strcat(path,"/./mkdir");
    
    
    for(int i=1;i<cnt-1;i++){
        sprintf(temp," %s",args_arr[i]);
        strcat(path,temp);
    }
   // printf("%s\n",path);
    int ret= system(path);

}
void runnewMKDIR(){
    pthread_t t1;
    pthread_create(&t1,NULL,&sysMKDIR,NULL);
    pthread_join(t1,NULL);
    return;
}
void runMkdir(){
    char path[100];
    char *argv[10];
    strcpy(path,commandPath);
    strcat(path,"/mkdir");
    for(int i=0;i<10;i++){
        argv[i]=(char *)malloc(100 * sizeof(char));
    }
    strcpy(argv[0],path);
    for(int i=1;i<cnt;i++){
        strcpy(argv[i],args_arr[i]);
        
    }
    argv[cnt]=NULL;
    pid=fork();
    if(pid==0){
        execv(argv[0],argv);
        return;
    }
    else{
        wait(NULL);
        return;
    }


}
void* sysRM(){
    char path[100];
    char temp[100];
    strcpy(path,commandPath);
    strcat(path,"/./rm");
    
    
    for(int i=1;i<cnt-1;i++){
        sprintf(temp," %s",args_arr[i]);
        strcat(path,temp);
    }
   // printf("%s\n",path);
    int ret= system(path);

}
void runnewRM(){
    pthread_t t1;
    pthread_create(&t1,NULL,&sysRM,NULL);
    pthread_join(t1,NULL);
    return;

}
void runrm(){
    char path[100];
    char *argv[10];
    strcpy(path,commandPath);
    strcat(path,"/rm");
    for(int i=0;i<10;i++){
        argv[i]=(char *)malloc(100 * sizeof(char));
    }
    strcpy(argv[0],path);
    for(int i=1;i<cnt;i++){
        strcpy(argv[i],args_arr[i]);
        
    }
    argv[cnt]=NULL;
    pid=fork();
    if(pid==0){
        execv(argv[0],argv);
        return;
    }
    else{
        wait(NULL);
        return;
    }


}
