#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char rootfs[1024];
int nocolor = 0;
// run command 
void set_rootfs(char* dir){
    strcpy(rootfs,dir);
}
void disable_color(){
  nocolor = 1;
}
int run(char* cmd){
  char* ncmd;
  if (strlen(cmd)<1){
    return 0;
  }if(strstr(cmd,"chroot||")){
      char* mcmd = malloc(strlen(cmd)*(sizeof(char)+8+strlen(rootfs)));
      for(int i=8;i<strlen(cmd);i++){
        mcmd[i-8]=cmd[i];
      }
      mcmd[strlen(cmd)-7]='\0';
      ncmd = malloc(sizeof(char)*(strlen(cmd)+strlen(rootfs)+13));
      strcpy(ncmd,"chroot ");
      strcat(ncmd,rootfs);
      strcat(ncmd," ");
      strcat(ncmd,mcmd);
  }else{
    ncmd = cmd;
  }
  return system(ncmd);
}

char* colorize(char* msg, char* num){
    if(nocolor){
        return msg;
    }
    char* ret = malloc((strlen(msg)+strlen(num))*(sizeof(char)+13));
    strcpy(ret,"\x1b[");
    strcat(ret,num);
    strcat(ret,"m");
    strcat(ret,msg);
    strcat(ret,"\x1b[0m");
    return ret;
}

// logging
void err(char* msg, char* date){
     fprintf(stderr,colorize("%s - [mkteaiso] ERROR: %s","31;1"),date,msg);
     fputc('\n',stderr);
     fflush(stderr);
}
void dbg(char* msg, char* date){
     fprintf(stderr,colorize("%s - [mkteaiso] DEBUG: %s","35"),date,msg);
     fputc('\n',stderr);
     fflush(stderr);
}
void inf(char* msg, char* date){
    fprintf(stdout,colorize("%s - [mkteaiso] INFO: %s","36"),date,msg);
    fputc('\n',stdout);
    fflush(stdout);
}
void out(char* msg){
    fprintf(stdout,"%s",msg);
    fputc('\n',stdout);
    fflush(stdout);
}
void warn(char* msg, char* date){
    fprintf(stderr,colorize("%s - [mkteaiso] WARN: %s","33"),date,msg);
    fputc('\n',stderr);
    fflush(stderr);
}

char* get_argument_value(char* arg, char* val){
  char* ret = malloc((strlen(arg)*(sizeof(char)+1)));
    for(int i=0;i<strlen(arg)-strlen(val);i++){
      ret[i] = arg[i+strlen(val)+1];
    }
    ret[strlen(arg)-strlen(val)]='\0';
  return ret;
}

int is_root(){
  return 0 == getuid();
}
