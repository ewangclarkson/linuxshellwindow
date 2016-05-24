#include<stdio.h>
#include<stdlib.h>

void libreoffice(){
 FILE*fp;
 if((fp=fopen("unknown file.odt","a+"))==NULL){
    perror("ERROR USAGE\n");
    exit(0);
 }
  fclose(fp);
 }

