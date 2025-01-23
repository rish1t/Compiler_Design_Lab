#include <stdio.h>
#include "my.h"
int main(){
      int a=5, b=6;
    //this should be removed;
      printf("%d %d #include ", a, b);
    /*should be #removed as well*/
    if(a != b){
      float c = a/b;
      return c;
    }
}
//#include