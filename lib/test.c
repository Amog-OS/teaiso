#include <stdio.h>
char* get_argument_value(char* arg, char* val);
int main(){
  /*Test some stuff*/
  warn(get_argument_value("variable=value","variable"));
  out("this is output");
  disable_color();
  err("this is error");
  run("cat /etc/os-release | grep ^NAME=");
}
