#include <stdio.h>
#include <stdlib.h>
 int a1 = 1;
 int a2 = 1;



int main() {
  printf("%d\n", myFunction(20));


  return 0;
}

int myFunction(int index) {
    if (index == 1) {
      return a1;
    } else if (index == 2) {
      return a2;
    } else {
      myFunction(index - 1);
    }
}
