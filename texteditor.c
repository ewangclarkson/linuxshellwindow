/*the following headers allows the inclusion of certain functions to this program*/
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>
#include<signal.h>
#include"library.h"
#include<assert.h>
#include<iso646.h>
#include<errno.h>
#include<ctype.h>
//macro definitions
#define MAX_LEN 10000000
#define MAX_NUM 100
#define FILE_LEN 20
#define T 10
#define E 11
#define X 12
#define Y 13
#define Z 14
#define F 15
#define D 16
#define handle_err(msg)\
          do{perror(msg);exit(0);}\
              while(0);
#define KEY '&' 
#define EXTEN ".ept"
#define EXTENSION ".rle"
#define FILE_L 100
#define MAX_L 100000
#define FILE_LE 90
#define MAX_LE 10000
#define DIRNAME_MAXLEN 200
/******************************************
 * typedefinition allows the user to use  *
 * an alias in place of  a keyword        *
 ******************************************/
typedef char* INSTRUCT_R;

//global variable
  char filecontent[MAX_NUM];
  char buffer[MAX_LEN];

//function definitions
 int paste(char*dir,char*filename,int depth,char*directory);
 inline void copy(char*file);
 inline void cut(char*file);
 inline void makelink(char*M_link);
 void copy_to(char*text,char*code);
 void move_to(char*text,char*code);
 static inline void Rename(char*new_name,char*file);
 static inline void move_to_trash(char*file);
 static inline void delete(char*filedelete);
void destination(char*dir,char*filename,int depth,char*buf,char*file_N,int readD);
void handler(int sig);
int rle_compression(char*file_compress,int arg);
int rle_uncompression(char*file_uncompress,int arg);
int encryption(char*file_encrypt,int argc);
int decryption(char*file_decrypt,int argc);

//the main function of the program
 int main(int argc,char*argv[])
 {
  INSTRUCT_R code;
   strcpy(code,argv[1]);
   switch(*code){
    case '1':
             libreoffice();
              signal(SIGINT,handler);
              raise(SIGINT);
             break;
    case '2':
             cut(argv[2]);
             signal(SIGINT,handler);
              raise(SIGINT);
              break;
    case '3':
             copy(argv[2]);
             signal(SIGINT,handler);
              raise(SIGINT); 
             break;
    case '4':
             makelink(argv[2]);
             signal(SIGINT,handler);
              raise(SIGINT);
             break;
    case '5':
             paste("/home","DIRECTORY",0,argv[2]);
             signal(SIGINT,handler);
              raise(SIGINT);
             break;
    case '6':
          
             copy_to(argv[2],argv[3]);
             signal(SIGINT,handler);
              raise(SIGINT);
              break;
    case '7':
             move_to(argv[2],argv[3]);
             signal(SIGINT,handler);
              raise(SIGINT);
             break;
    case '8':
             move_to_trash(argv[2]);
             signal(SIGINT,handler);
              raise(SIGINT);
             break;
    case '9':
             delete(argv[2]);
             signal(SIGINT,handler);
              raise(SIGINT);
             break;
    case 'T':
             file();
             signal(SIGINT,handler);
              raise(SIGINT);
              break;
    case 'E':
             folder();
             signal(SIGINT,handler);
              raise(SIGINT); 
             break;
    case 'X':
    case 'x':
             Rename(argv[2],argv[3]);
             signal(SIGINT,handler);
              raise(SIGINT);
              break;
    case 'Y':
    case 'y':
             encryption(argv[2],argc);
             signal(SIGINT,handler);
             raise(SIGINT);
             break;
   case 'Z':
   case 'z':
            decryption(argv[2],argc);
             signal(SIGINT,handler);
             raise(SIGINT);
             break;
   case 'F':
   case 'f':
            rle_compression(argv[2],argc);
            signal(SIGINT,handler);
             raise(SIGINT);
            break;
   case 'D':
            rle_uncompression(argv[2],argc);
            signal(SIGINT,handler);
             raise(SIGINT);
            break;
    default:
             unlink(argv[0]);
            return 0;
  }
  unlink(argv[0]);
  return 0;
 }

 //the signal handler function
 void handler(int sig){
   printf("signal %d occured\n",sig);
 }
            
/***********************************************************
 * the function copy copy a file in to the queue and store *
 * until the paste function is called                      *
 ***********************************************************/   
 extern inline void copy( char*file)
 {
      FILE*fp,*fp1,*fp2;
    DIR*dp;
    char*shortcut;
   shortcut=file;
   int readD;
   mkdir("DIRECTORY",S_IRUSR|S_IWUSR|S_IXUSR);
   if((fp=fopen(file,"r"))==NULL){
       fprintf(stderr,"FAILED TO OPEN COPYFILE %s\n",file);
       exit(0);
    }
   readD=fread(buffer,sizeof(char),sizeof(buffer)/sizeof(buffer[0]),fp);
   
  if((dp=opendir("DIRECTORY"))==NULL){
      fprintf(stderr,"FAILED TO OPEN DIRECTORY\n");
      exit(0);
    }
   chdir("DIRECTORY");
   if((fp1=fopen(shortcut,"a+"))==NULL){
      fprintf(stderr,"OPEN ERROR!\n");
      exit(EXIT_FAILURE);
   }
    assert(readD>0&&readD<=MAX_LEN);
     fwrite(buffer,sizeof(char),readD,fp1);
     fclose(fp);
     fclose(fp1);
    if((fp2=fopen("filepaste","a+"))==NULL){
        perror("ERROR USAGE!\n");
        exit(0);
     }
     fputs(shortcut,fp2);
     fclose(fp2);
     chdir("..");
     closedir(dp);
   return;
  
 }
/******************************************************************
 * the function cut below copies a file to a location and removes *
 * the older version                                              * 
 ******************************************************************/  
 extern inline void cut(char*file){
    FILE*fp,*fp1,*fp2;
    DIR*dp;
    char*shortcut;
   shortcut=file;
   int readD;
   mkdir("DIRECTORY",S_IRUSR|S_IWUSR|S_IXUSR);
   if((fp=fopen(file,"r"))==NULL){
       fprintf(stderr,"FAILED TO OPEN COPYFILE %s\n",file);
       exit(0);
    }
   readD=fread(buffer,sizeof(char),sizeof(buffer)/sizeof(buffer[0]),fp);
   
  if((dp=opendir("DIRECTORY"))==NULL){
      fprintf(stderr,"FAILED TO OPEN DIRECTORY\n");
      exit(0);
    }
   chdir("DIRECTORY");
   if((fp1=fopen(shortcut,"a+"))==NULL){
      fprintf(stderr,"OPEN ERROR!\n");
      exit(EXIT_FAILURE);
   }
    assert(readD>0&&readD<=MAX_LEN);
     fwrite(buffer,sizeof(char),readD,fp1);
     fclose(fp);
     fclose(fp1);
    if((fp2=fopen("filepaste","a+"))==NULL){
        perror("ERROR USAGE!\n");
        exit(0);
     }
     fputs(shortcut,fp2);
     fclose(fp2);
     chdir("..");
     closedir(dp);
     unlink(file);

   return;
 }

/********************************************************************
 * the function below makes a link of the parameter file in the     *
 * same directory where the file is situated                        *
 ********************************************************************/ 
 inline void makelink(char*M_link){
   char*linkage;
    linkage=M_link;
    link(linkage,"linkedfile");
   return ;
 }

/****************************************************************************
 * the function copy to prompts the user to choose the location where he    *
 * to copy the file to                                                      *
 *88888888888888888888888888888888888888888888888888888888888888888888888888*/
 void copy_to(char*text,char*code){


   FILE*fp,*fptr;
   char buffe[MAX_L];
   char buf[20];
   int readD;
   int register i=0;
   fp=fopen(text,"r");
    assert(fp!=NULL);
    if((readD=fread(buffe,sizeof(char),sizeof(buffe)/sizeof(buffe[0]),fp))<=0){
       fprintf(stderr,"ERROR USAGE!\n");
       exit(0);
     }
  
 switch(*code){
    case '1':
             chdir("/home");
             chdir("ewang");
             if((fptr=fopen(text,"a+"))==NULL){
                 perror("ERROR USAGE!\n");
                 exit(EXIT_FAILURE);
                }
                chmod(text,S_IRUSR);
               fwrite(buffe,sizeof(char),readD,fptr);
               fclose(fptr);
               fclose(fp);
             break;
    case '2':
               chdir("/home");
               chdir("ewang");
               chdir("Desktop");
              if((fptr=fopen(text,"a+"))==NULL){
                 perror("ERROR USAGE!\n");
                 exit(EXIT_FAILURE);
                }
                chmod(text,S_IRUSR);
               fwrite(buffe,sizeof(char),readD,fptr);
               fclose(fptr);
               fclose(fp);
               while(i!=2){
                 chdir("..");
                  i++;
              }
             break;
                  
     case '3':
               chdir("/home");
               chdir("ewang");
               chdir("Documents");
               if((fptr=fopen(text,"a+"))==NULL){
                 perror("ERROR USAGE!\n");
                 exit(EXIT_FAILURE);
                }
                chmod(text,S_IRUSR);
               fwrite(buffe,sizeof(char),readD,fptr);
               fclose(fptr);
               fclose(fp);
               while(i!=2){
                 chdir("..");
                  i++;
              }
             break;
     case '4':
               chdir("/home");
               chdir("ewang");
               chdir("Music");
               if((fptr=fopen(text,"a+"))==NULL){
                 perror("ERROR USAGE!\n");
                 exit(EXIT_FAILURE);
                }
               chmod(text,S_IRUSR);
               fwrite(buffe,sizeof(char),readD,fptr);
               fclose(fptr);
               fclose(fp);
             break;
      case '5':
               chdir("/home");
               chdir("ewang");
               chdir("Videos");
               if((fptr=fopen(text,"a+"))==NULL){
                 perror("ERROR USAGE!\n");
                 exit(EXIT_FAILURE);
                }
               chmod(text,S_IRUSR);
               fwrite(buffe,sizeof(char),readD,fptr);
               fclose(fptr);
               fclose(fp);
               while(i!=2){
                 chdir("..");
                  i++;
              }
             break;
      case '6':
               chdir("/home");
               chdir("ewang");
               chdir("Pictures");
               if((fptr=fopen(text,"a+"))==NULL){
                 perror("ERROR USAGE!\n");
                 exit(EXIT_FAILURE);
                }
                chmod(text,S_IRUSR);
               fwrite(buffe,sizeof(char),readD,fptr);
               fclose(fptr);
               fclose(fp);
               while(i!=2){
                 chdir("..");
                  i++;
              }
             break;
      case '7':
               chdir("/home");
               chdir("ewang");
               chdir("Downloads");
               if((fptr=fopen(text,"a+"))==NULL){
                 perror("ERROR USAGE!\n");
                 exit(EXIT_FAILURE);
                }
                chmod(text,S_IRUSR);
               fwrite(buffe,sizeof(char),readD,fptr);
               fclose(fptr);
               fclose(fp);
               while(i!=2){
                 chdir("..");
                  i++;
              }
             break;        
      default:
              fclose(fp);
              return ;
 }
}
  
/*((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))){
 { the function copy to prompts the user to choose the location where he    }
 { to copy the file to                                                      }
 }(((((((((((((((((((((((((()))))))))))))))))))))))))))))))))))))))))))))))){*/     
 void move_to(char*text,char*code){

   FILE*fp,*fptr;
   char buffe[MAX_L];
   char buf[20];
   int readD;
   int register i=0;
   fp=fopen(text,"r");
    assert(fp!=NULL);
    if((readD=fread(buffe,sizeof(char),sizeof(buffe)/sizeof(buffe[0]),fp))<=0){
       fprintf(stderr,"ERROR USAGE!\n");
       exit(0);
     }
   remove(text);
 switch(*code){
    case '1':
             chdir("/home");
             chdir("ewang");
             if((fptr=fopen(text,"a+"))==NULL){
                 perror("ERROR USAGE!\n");
                 exit(EXIT_FAILURE);
                }
                chmod(text,S_IRUSR);
               fwrite(buffe,sizeof(char),readD,fptr);
               fclose(fptr);
               fclose(fp);
             break;
    case '2':
               chdir("/home");
               chdir("ewang");
               chdir("Desktop");
              if((fptr=fopen(text,"a+"))==NULL){
                 perror("ERROR USAGE!\n");
                 exit(EXIT_FAILURE);
                }
                chmod(text,S_IRUSR);
               fwrite(buffe,sizeof(char),readD,fptr);
               fclose(fptr);
               fclose(fp);
               while(i!=2){
                 chdir("..");
                  i++;
              }
             break;
                  
     case '3':
               chdir("/home");
               chdir("ewang");
               chdir("Documents");
               if((fptr=fopen(text,"a+"))==NULL){
                 perror("ERROR USAGE!\n");
                 exit(EXIT_FAILURE);
                }
                chmod(text,S_IRUSR);
               fwrite(buffe,sizeof(char),readD,fptr);
               fclose(fptr);
               fclose(fp);
               while(i!=2){
                 chdir("..");
                  i++;
              }
             break;
     case '4':
               chdir("/home");
               chdir("ewang");
               chdir("Music");
               if((fptr=fopen(text,"a+"))==NULL){
                 perror("ERROR USAGE!\n");
                 exit(EXIT_FAILURE);
                }
               chmod(text,S_IRUSR);
               fwrite(buffe,sizeof(char),readD,fptr);
               fclose(fptr);
               fclose(fp);
             break;
      case '5':
               chdir("/home");
               chdir("ewang");
               chdir("Videos");
               if((fptr=fopen(text,"a+"))==NULL){
                 perror("ERROR USAGE!\n");
                 exit(EXIT_FAILURE);
                }
               chmod(text,S_IRUSR);
               fwrite(buffe,sizeof(char),readD,fptr);
               fclose(fptr);
               fclose(fp);
               while(i!=2){
                 chdir("..");
                  i++;
              }
             break;
      case '6':
               chdir("/home");
               chdir("ewang");
               chdir("Pictures");
               if((fptr=fopen(text,"a+"))==NULL){
                 perror("ERROR USAGE!\n");
                 exit(EXIT_FAILURE);
                }
                chmod(text,S_IRUSR);
               fwrite(buffe,sizeof(char),readD,fptr);
               fclose(fptr);
               fclose(fp);
               while(i!=2){
                 chdir("..");
                  i++;
              }
             break;
      case '7':
               chdir("/home");
               chdir("ewang");
               chdir("Downloads");
               if((fptr=fopen(text,"a+"))==NULL){
                 perror("ERROR USAGE!\n");
                 exit(EXIT_FAILURE);
                }
                chmod(text,S_IRUSR);
               fwrite(buffe,sizeof(char),readD,fptr);
               fclose(fptr);
               fclose(fp);
               while(i!=2){
                 chdir("..");
                  i++;
              }
             break;        
      default:
              fclose(fp);
              return ;
 }

}
/*NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  N This function rename the file it takes                                N
  NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN*/
 static inline void Rename(char*new_name,char*file){
   rename(new_name,file);
 }
//the following function deletes the file specified and move it to the trash
 static inline void move_to_trash(char*file){
     remove(file);
 }
/********************the function delete unlinks the file*****************/
 static inline void delete(char*filedelete){
  unlink(filedelete);
 } 
/****************************************************************************
 * the function paste below paste the recent copied file                    *
 ****************************************************************************/
int paste(char*dir,char*filename,int depth,char*directory){
 DIR*dp,*dptr;
 char*des;
 struct dirent*entry;
 struct stat statbuf;
  FILE*fp,*fp1,*fp2;
  struct dirent*enter;
  char file_N[FILE_LE]={"ta\0"};
  char buf[MAX_LE];
  int readD;
   
 
  if((dp=opendir(dir))==NULL){
      perror("");
      exit(EXIT_FAILURE);
  }
  chdir(dir);
  while((entry=readdir(dp))!=NULL)
  {
   lstat(entry->d_name,&statbuf);
   if(S_ISDIR(statbuf.st_mode)){
     if(strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name)==0)
         continue;
  /*if is the current or parent directory continue and call the subdirectory by recursion*/
         paste(entry->d_name,filename,depth+4,directory);
     
          if(strcmp(filename,entry->d_name)==0){
             if((dptr=opendir("DIRECTORY"))==NULL){
                  printf("cannot open directory\n");
                  exit(0);
              }
  
            chdir("DIRECTORY");
            if((enter=readdir(dp))==NULL){
                exit(0);
             }
           if((fp=fopen("filepaste","r"))==NULL){
               perror("FATAL ERROR!\n");
               exit(0);
           }
           fgets(file_N,FILE_LE,fp);
           fclose(fp);
           if((fp1=fopen(file_N,"r"))==NULL){
              perror("FATAL ERROR!\n");
                exit(0);
           }
  
          readD=fread(buf,sizeof(char),sizeof(buf)/sizeof(buf[0]),fp1);
          remove("filepaste");
          remove(file_N);
          chdir("..");
          rmdir(filename);
          
          
          rmdir("DIRECTORY");
          fclose(fp1);
           closedir(dptr);
          
          destination("/home",directory,0,buf,file_N,readD);
         
          
       }
      }
     }
     chdir("..");
     closedir(dp);
   }
/***************************************************************************
 * this function paste the copied or cut file to the destination precise by*
 * the user                                                                *
 ***************************************************************************/
void destination(char*dir,char*filename,int depth,char*buf,char*file_N,int readD)
{
  DIR*dp;
  FILE*fp;
 struct dirent*entry;
 struct stat statbuf;
 
  if((dp=opendir(dir))==NULL){
      perror("");
      exit(EXIT_FAILURE);
  }
  chdir(dir);
  while((entry=readdir(dp))!=NULL)
  {
   lstat(entry->d_name,&statbuf);
   if(S_ISDIR(statbuf.st_mode)){
     if(strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name)==0)
         continue;
  /*if is the current or parent directory continue and call the subdirectory by recursion*/
         destination(entry->d_name,filename,depth+4,buf,file_N,readD);
     
          if(strcmp(filename,entry->d_name)==0){
            assert(readD>0&&readD<MAX_LE);
         chdir(filename);
         if((fp=fopen(file_N,"a+"))==NULL){
           fprintf(stderr,"ERROR USAGE IN PASTE FUNCTION\n");
            exit(0);
         }
         fwrite(buf,sizeof(char),readD,fp);
  
         fclose(fp);
     chdir("..");
     }
    }
   }
   chdir("..");
   closedir(dp);
 }

/*****************************************************************
 * the following compresses a file using the run length encoding *
 *****************************************************************/
int rle_compression(char*file_compress,int arg)
{
  FILE*fp,*fp1;
  char FILENAME[25];
  int ch,chcopy,i=1,j=0;
   if(arg<2){
       handle_err("NO INPUT FILE FROM COMMANDLINE");
    }
  strcpy(FILENAME,file_compress);
  strcat(FILENAME,EXTENSION);
 if((fp=fopen(file_compress,"r"))==NULL)
   {
     fprintf(stderr,"ERROR USAGE!FAILED TO OPEN INTPUT FILE\n");
     exit(EXIT_FAILURE);
   }
   
 if((fp1=fopen(FILENAME,"a+"))==NULL)
   {
     fprintf(stderr,"ERROR USAGE!FAILED TO OPEN OUTPUT FILE\n");
     exit(EXIT_FAILURE);
   }
  
 chcopy=getc(fp);
 while((ch=getc(fp)) not_eq EOF)
 {
     if(ch==chcopy){
        while(ch == chcopy){
             i++;
            ch=getc(fp);
        }
         ungetc(ch,fp);
     }    
          
          fprintf(fp1,"%.2d %X ",i,chcopy);
          chcopy=ch;
     i=0;
   }
  remove(file_compress);   
 fclose(fp);
 fclose(fp1);

 return 0;
}
/*******************************************************************
 * the following uncompresses a file using the run length encoding *
 *******************************************************************/
int rle_uncompression(char*file_uncompress,int arg)
{
   FILE*fp,*fp1;
  int ch,i=1,n,loop,j=0;
  char*ptr,FILENAME[sizeof(file_uncompress)],CH,str[100];
   if(arg<2){
       handle_err("NO INPUT FILE FROM COMMANDLINE");
    }
 
   if((strstr(file_uncompress,EXTENSION))==NULL)
     {
      fprintf(stderr,"FILE EXTENSION NOT .rle\n");
      exit(EXIT_FAILURE);
     }
 if((fp=fopen(file_uncompress,"rb"))==NULL)
   {
     fprintf(stderr,"ERROR USAGE!FAILED TO OPEN INTPUT FILE\n");
     exit(EXIT_FAILURE);
   }
 strcpy(str,file_uncompress);
   ptr=str;
  while(j!=(strlen(file_uncompress)-4))
  {
   sscanf(ptr,"%c",&CH);
   FILENAME[j++]=CH;
   ptr=&str[j];
  }
  FILENAME[j]='\0';
 if((fp1=fopen(FILENAME,"a+"))==NULL)
   {
     fprintf(stderr,"ERROR USAGE!FAILED TO OPEN OUTPUT FILE\n");
     exit(EXIT_FAILURE);
   }
 while((n=fscanf(fp,"%d",&i))==1)
     {
      fscanf(fp,"%X",&ch);
      for(loop=0;loop<i;loop++)
        fprintf(fp1,"%c",ch); 
      }
  remove(file_uncompress);         
 fclose(fp);
 fclose(fp1);
 
 return 0;
}
//the encryption function encrypts a file passed through the cmdline
int encryption(char*file_encrypt,int argc)
{
  FILE*fp,*fp1;
  int ch,size;
  size=(int)(sizeof(file_encrypt)+5);
  char FILENAME[size];
 if(argc<2){
    handle_err("NO COMMAND LINE ARGUMENT");
 }
  
  if((fp=fopen(file_encrypt,"rb"))==NULL){
      fprintf(stderr,"ERROR USAGE!FAILED TO OPEN INPUT FILE\n");
      exit(EXIT_FAILURE);
  }
 
 strcpy(FILENAME,file_encrypt);
 strcat(FILENAME,EXTEN);

 if((fp1=fopen(FILENAME,"ab"))==NULL){
    fprintf(stderr,"ERROR FAILED TO OPEN INPUT FILE\n");
    exit(EXIT_FAILURE);
 }
 
 ch=fgetc(fp);
 while(ch not_eq EOF)
  {
    fprintf(fp1,"%c",ch xor KEY);
    ch=getc(fp);
  }
  
  fclose(fp);
  fclose(fp1);
  remove(file_encrypt);
 return 0;
}
//definning the decripting function
int decryption(char*file_decrypt,int argc)
{
 FILE*fp,*fp1;
  int ch,j=0;
  char FILENAME[sizeof(file_decrypt)];
  char CH,str[100],*ptr;
 if(argc<2){
    handle_err("NO COMMAND LINE ARGUMENT");
 }
  if((strstr(file_decrypt,EXTEN))==NULL)
     {
      fprintf(stderr,"FILE EXTENSION NOT .ept\n");
      exit(EXIT_FAILURE);
     }
  if((fp=fopen(file_decrypt,"rb"))==NULL){
      fprintf(stderr,"ERROR USAGE!FAILED TO OPEN INPUT FILE\n");
      exit(EXIT_FAILURE);
  }
 
 strcpy(str,file_decrypt);
  ptr=str;
  while(j<(strlen(file_decrypt)-4))
  {
   sscanf(ptr,"%c",&CH);
   FILENAME[j++]=CH;
   ptr=&str[j];
  }
  FILENAME[j]='\0';
 
 if((fp1=fopen(FILENAME,"ab+"))==NULL){
    fprintf(stderr,"ERROR FAILED TO OPEN INPUT FILE\n");
    exit(EXIT_FAILURE);
 }
 ch=fgetc(fp);
 while(ch not_eq EOF)
  {
    fprintf(fp1,"%c",ch xor KEY);//exclusive or each char with the & key
    ch=getc(fp);
  }
  remove(file_decrypt);
  fclose(fp);
  fclose(fp1);

 return 0;
}
  


              
  


