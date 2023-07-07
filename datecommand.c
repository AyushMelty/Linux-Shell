#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
char Months[12][50]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
char Days[7][50]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
char *giveMonth(int monthnum){
    return Months[monthnum];
}
char *giveDay(int daynum){
    return Days[daynum];
}
void main(int argc, char *argv[])
{       
    time_t cur_t;
    cur_t = time(NULL);
    struct tm *local = localtime(&cur_t);    
    if(argc==1){
    printf("%s %s %d  %02d:%02d:%02d IST %d\n",giveDay(local->tm_wday), giveMonth(local->tm_mon),local->tm_mday, local->tm_hour,
           local->tm_min, local->tm_sec,1900+local->tm_year);
    }

    if(strcmp(argv[1],"-R")==0){
        struct tm *global = gmtime(&cur_t);
        printf("%s, %s %d  %02d:%02d:%02d UTC %d\n",giveDay(global->tm_wday), giveMonth(global->tm_mon),global->tm_mday, global->tm_hour,
           global->tm_min, global->tm_sec,1900+global->tm_year);  
    }
    if(strcmp(argv[1],"-u")==0){
         printf("%s, %s %d  %02d:%02d:%02d IST %d +0530\n",giveDay(local->tm_wday), giveMonth(local->tm_mon),local->tm_mday, local->tm_hour,
           local->tm_min, local->tm_sec,1900+local->tm_year); 
    }

}
