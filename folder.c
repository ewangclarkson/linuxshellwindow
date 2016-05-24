#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>

void folder(){
 DIR*drp;
 mkdir("unknown folder",S_IRUSR|S_IWUSR|S_IXUSR|S_IXOTH);
 if((drp=opendir("unknown folder"))==NULL){
    perror("ERROR USAGE\n");
    exit(0);
 }
  closedir(drp);
 }

