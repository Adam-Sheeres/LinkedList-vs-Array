#include <stdio.h>
#include <stdlib.h>
#include "ds_list.h"
#include "ds_memory.h"

int main() {
  /*10*/
  register int i;
  long index1, index2;
  ds_create("list.bin", 2048);
  ds_create_list();
  ds_init_list();
  ds_read_elements("test10.txt");
  ds_finish_list();

  ds_init_list();
  for (i = 0; i < 30; i++) {
    index1 = rand() % 10;
    index2 = rand() % 10;
    ds_swap(index1, index2);
  }
  printf("v~~~~~~~~~~~~~~~~v\n");
  ds_finish_list();
  printf("^~~~~~~~~~~~~~~~~^\n");

  /*20*/
  ds_create("list.bin", 2048);
  ds_create_list();
  ds_init_list();
  ds_read_elements("test20.txt");
  ds_finish_list();

  ds_init_list();
  for (i = 0; i < 30; i++) {
    index1 = rand() % 20;
    index2 = rand() % 20;
    ds_swap(index1, index2);
  }
  printf("v~~~~~~~~~~~~~~~~v\n");
  ds_finish_list();
  printf("^~~~~~~~~~~~~~~~~^\n");

  /*30*/
  ds_create("list.bin", 2048);
  ds_create_list();
  ds_init_list();
  ds_read_elements("test30.txt");
  ds_finish_list();

  ds_init_list();
  for (i = 0; i < 30; i++) {
    index1 = rand() % 30;
    index2 = rand() % 30;
    ds_swap(index1, index2);
  }
  printf("v~~~~~~~~~~~~~~~~v\n");
  ds_finish_list();
  printf("^~~~~~~~~~~~~~~~~^\n");

  /*40*/
  ds_create("list.bin", 2048);
  ds_create_list();
  ds_init_list();
  ds_read_elements("test40.txt");
  ds_finish_list();

  ds_init_list();
  for (i = 0; i < 30; i++) {
    index1 = rand() % 40;
    index2 = rand() % 40;
    ds_swap(index1, index2);
  }
  printf("v~~~~~~~~~~~~~~~~v\n");
  ds_finish_list();
  printf("^~~~~~~~~~~~~~~~~^\n");

  /*50*/
  ds_create("list.bin", 2048);
  ds_create_list();
  ds_init_list();
  ds_read_elements("test50.txt");
  ds_finish_list();

  ds_init_list();
  for (i = 0; i < 30; i++) {
    index1 = rand() % 50;
    index2 = rand() % 50;
    ds_swap(index1, index2);
  }
  printf("v~~~~~~~~~~~~~~~~v\n");
  ds_finish_list();
  printf("^~~~~~~~~~~~~~~~~^\n");

  /*60*/
  ds_create("list.bin", 2048);
  ds_create_list();
  ds_init_list();
  ds_read_elements("test60.txt");
  ds_finish_list();

  ds_init_list();
  for (i = 0; i < 30; i++) {
    index1 = rand() % 60;
    index2 = rand() % 60;
    ds_swap(index1, index2);
  }
  printf("v~~~~~~~~~~~~~~~~v\n");
  ds_finish_list();
  printf("^~~~~~~~~~~~~~~~~^\n");

  /*70*/
  ds_create("list.bin", 2048);
  ds_create_list();
  ds_init_list();
  ds_read_elements("test70.txt");
  ds_finish_list();

  ds_init_list();
  for (i = 0; i < 30; i++) {
    index1 = rand() % 70;
    index2 = rand() % 70;
    ds_swap(index1, index2);
  }
  printf("v~~~~~~~~~~~~~~~~v\n");
  ds_finish_list();
  printf("^~~~~~~~~~~~~~~~~^\n");

  /*80*/
  ds_create("list.bin", 2048);
  ds_create_list();
  ds_init_list();
  ds_read_elements("test80.txt");
  ds_finish_list();

  ds_init_list();
  for (i = 0; i < 30; i++) {
    index1 = rand() % 80;
    index2 = rand() % 80;
    ds_swap(index1, index2);
  }
  printf("v~~~~~~~~~~~~~~~~v\n");
  ds_finish_list();
  printf("^~~~~~~~~~~~~~~~~^\n");

  /*90*/
  ds_create("list.bin", 2048);
  ds_create_list();
  ds_init_list();
  ds_read_elements("test90.txt");
  ds_finish_list();

  ds_init_list();
  for (i = 0; i < 30; i++) {
    index1 = rand() % 90;
    index2 = rand() % 90;
    ds_swap(index1, index2);
  }
  printf("v~~~~~~~~~~~~~~~~v\n");
  ds_finish_list();
  printf("^~~~~~~~~~~~~~~~~^\n");

  /*100*/
  ds_create("list.bin", 2048);
  ds_create_list();
  ds_init_list();
  ds_read_elements("test100.txt");
  ds_finish_list();

  ds_init_list();
  for (i = 0; i < 30; i++) {
    index1 = rand() % 100;
    index2 = rand() % 100;
    ds_swap(index1, index2);
  }
  printf("v~~~~~~~~~~~~~~~~v\n");
  ds_finish_list();
  printf("^~~~~~~~~~~~~~~~~^\n");
  return 0;
}
