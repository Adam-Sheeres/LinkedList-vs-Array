/*
Adam SHeeres-Paulicpulle
Student ID: 1036569
email: asheeres@uoguelph.ca
*/

#include <stdio.h>
#include "ds_memory.h"

/*Global Variables*/
struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;

int ds_searchFor(int, int);

int ds_create(char *filename, long size) {

  int tempBytes = 0;
  int i = 0;
  /*assign block values*/
  for (i = 1; i < MAX_BLOCKS; i++) {
    ds_file.block[i].start = 0;
    ds_file.block[i].alloced = '0';
    ds_file.block[i].length = 0;
  }
  ds_file.block[0].start = 0;
  ds_file.block[0].alloced = '0';
  ds_file.block[0].length = size;

  /*create file*/
  ds_file.fp = fopen(filename, "wb");
  if (ds_file.fp == NULL) {
    printf("FAILED TO CREATE FILE\n");
    return 1;
  }

  /*write all the blocks to the file*/
  if (fwrite(&ds_file.block, sizeof(ds_file.block), 1, ds_file.fp) == 0) {
    return 1;
  };

  /*write the extra bytes to file*/
  for (i = 0; i < size; i++) {
    if (fwrite(&tempBytes, 1, 1, ds_file.fp) == 0) {
      return 1;
    }
  }

  fclose(ds_file.fp);
  return 0;
}

int ds_init(char *filename) {

  /*open file in read*/
  ds_file.fp = fopen(filename, "rb+");

  if (ds_file.fp == NULL) {
    printf("UNABLE TO OPEN FILE\n");
    return 1;
  }

  /*go to begining of file*/
  fseek(ds_file.fp, 0, SEEK_SET);

  /*load header into global variable*/
  fread(&ds_file.block, sizeof(ds_file.block), 1, ds_file.fp);

  /*set reads and writes to 0 of global var*/
  ds_counts.writes = 0;
  ds_counts.reads = 0;

  /*return 0 if succes, 1 if not*/
  return 0;
}

long ds_malloc(long amount) {
  long returnVal;
  int index1, oldAmt, i;
  oldAmt = i = 0;
  index1 = -1;
  returnVal = 0;

  /*search block array for correct cell*/
  for (i = 0; i < MAX_BLOCKS; i++) {
    if (ds_file.block[i].length >= amount && ds_file.block[i].alloced == '0') {
      index1 = i;
      returnVal = ds_file.block[i].start;
      break;
    }
  }
  if (index1 == -1) {
    return -1;
  }
  /*change that block's length to amount, and the alloced to 1*/
  oldAmt = ds_file.block[index1].length;
  ds_file.block[index1].length = amount;
  ds_file.block[index1].alloced = '1';

  /*search block array for another block*/
  for (i = 0; i < MAX_BLOCKS; i++) {
    if (ds_file.block[i].length == 0) {
      /*set second block to be un alloced*/
      ds_file.block[i].start = ds_file.block[index1].start + amount;
      ds_file.block[i].length = oldAmt - amount;
      ds_file.block[i].alloced = '0';
      break;
    }
  }
  if (index1 == -1) {
    return index1;
  } else {
    return returnVal;
  }
}

void ds_free(long start) {
  int i;
  for (i = 0; i < MAX_BLOCKS; i++) {
    if(ds_file.block[i].start == start) {
      ds_file.block[i].alloced = '0';
      break;
    }
  }
}

int ds_finish() {

  /*write block arrays to file*/
  fseek(ds_file.fp, 0, SEEK_SET);
  if (fwrite(&ds_file.block, sizeof(ds_file.block), 1, ds_file.fp) == 0) {
    return 0;
  }

  /*print out reads and writes*/
  printf("reads: %d\nwrites: %d\n", ds_counts.reads, ds_counts.writes);

  fclose(ds_file.fp);
  return 1;
}

long ds_write(long start, void *ptr, long bytes) {
  /*go to the begining of the file offset by the size of the header*/
  fseek(ds_file.fp, sizeof(ds_file.block), SEEK_SET);
  fseek(ds_file.fp, start, SEEK_CUR);

  /*write byte bytes to the file from address ptr*/
  if (fwrite(ptr, bytes, 1, ds_file.fp) == 0) {
    return -1;
  }

  /*incriment value of writes by 1*/
  ds_counts.writes++;
  return start;
}

void *ds_read(void *ptr, long start, long bytes) {
  /*go to START offset by length of header*/
  fseek(ds_file.fp, sizeof(ds_file.block), SEEK_SET);
  fseek(ds_file.fp, start, SEEK_CUR);

  /*read byte bytes*/
  if (fread(ptr, bytes, 1, ds_file.fp) == 0) {
    return NULL;
  }

  /*incriment reads global var*/
  ds_counts.reads++;

  return ptr;
}
