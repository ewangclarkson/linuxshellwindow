#include<stdio.h>
#include<stdlib.h>

void file(){
 FILE*fp;
 if((fp=fopen("file.dat","a+"))==NULL){
    perror("ERROR USAGE\n");
    exit(0);
 }
  fclose(fp);
 }
