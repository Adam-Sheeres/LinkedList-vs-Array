/*
Adam SHeeres-Paulicpulle
Student ID: 1036569
email: asheeres@uoguelph.ca
*/

#include <stdio.h>
#include <stdlib.h>

#include "ds_memory.h"
#include "ds_array.h"

long elements;

int ds_create_array() {

  /*initialize the bin file and array*/
  ds_init("array.bin");
  /*call ds_malloc for single long at begining of bin file*/
  elements = ds_malloc(sizeof(elements));
  if (elements != 0) {
    return -1;
  }
  /*call ds_malloc to allocate data for the entire array*/
  elements = ds_malloc(MAX_ELEMENTS*sizeof(int));

  /*set the value of that long to 0*/
  elements = 0;
  /*call ds_finish()*/
  ds_finish();
  return 0;
}

int ds_init_array() {
  /*read first long from bin file to elements*/
  ds_init("array.bin");
  fseek(ds_file.fp, sizeof(ds_file.block), SEEK_SET);

  ds_read(&elements, 0, sizeof(elements));
  return 0;
}

int ds_replace(int value, long index) {
  /*replace a value in a cell*/
  index = index * sizeof(int) + sizeof(elements);
  ds_write(index, &value, sizeof(value));
  return 0;
}

int ds_insert(int value, long index) {
  int old, location1, location2;
  old = location1 = location2 = 0;

  /*if index exceeds max*/
  if (index >= MAX_ELEMENTS || index > elements) {
    return -1;
  }
  /*find location*/
  location1 = index * sizeof(int) + sizeof(elements);
  ds_read(&old, location1, sizeof(old));
  if (old == 0) { /*if unoccupied*/
    ds_write(location1, &value, sizeof(value));
    elements++;
    return 0;
  } else {
    ds_insert(old, index + 1);
    ds_write(location1, &value, sizeof(value));
    return 0;
  }
  /*write elements in proper place*/
  return -1;
}

int ds_delete(long index) {
  int old, i, index2;
  old = index2 = 0;

  if (index > elements) {
    printf("Unable to delete.. exceeded elements\n");
    return -1;
  }

  for (i = index + 1; i < elements - 1; i++) {
    index2 = (i-1) * sizeof(int) + sizeof(elements);
    index = i * sizeof(int) + sizeof(elements);
    ds_read(&old, index, sizeof(old));
    ds_write(index2, &old, sizeof(old));
  }

  /*decrement number of elements*/
  elements --;
  return 0;
}

int ds_swap(long index1, long index2) {
  int temp1, temp2;
  temp1 = temp2 = 0;
  index1 = index1 * sizeof(int) + sizeof(elements);
  index2 = index2 * sizeof(int) + sizeof(elements);

  /*retreive values*/
  ds_read(&temp1, index1, sizeof(temp1));
  ds_read(&temp2, index2, sizeof(temp2));

  /*write 2 to 1 and 1 to 2*/
  ds_write(index1, &temp2, sizeof(temp2));
  ds_write(index2, &temp1, sizeof(temp1));


  return 0;
}

int ds_find(int target) {
  int i, temp;
  temp = 0;

  for (i = 0; i < elements; i++) {
    ds_read(&temp, (i*sizeof(int)) + sizeof(elements), sizeof(temp));
    if (temp == target) {
      return i;
    }
  }
  return -1;
}

int ds_read_elements(char *filename) {
  char buffer[10000];
  int bufferVals[MAX_ELEMENTS];
  int i, j, temp;
  long position, end;
  FILE *fp;

  position = end = temp = 0;

  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("FAILED TO FIND FILE\n");
    return -1;
  }
  /*get length of file*/
  fseek(fp, 0, SEEK_END);
  end = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  /*loop for max number of elements*/
  for (i = 0; i < MAX_ELEMENTS; i++) {
    fscanf(fp, "%s", buffer);
    position = ftell(fp);
    /*convert string to text*/
    bufferVals[i] = atoi(buffer);
    if (position == end) { /*if at end of file*/
      bufferVals[i] = 0;
      break;
    }
  }
  for (j = 0; j < i; j++) {
    ds_insert(bufferVals[j], j);
  }

  return 0;
}

int ds_finish_array() {
  fseek(ds_file.fp, sizeof(ds_file.block), SEEK_SET);

  /*write elements to the begining of teh binary file*/
  ds_write(0, &elements, sizeof(elements));
  ds_finish();
  return 0;
}
