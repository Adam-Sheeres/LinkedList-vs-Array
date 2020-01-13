/*
Adam SHeeres-Paulicpulle
Student ID: 1036569
email: asheeres@uoguelph.ca
*/

#include <stdio.h>
#include <stdlib.h>

#include "ds_list.h"
#include "ds_memory.h"

void ds_create_list() {
  long localVar = -1;

  ds_init("list.bin");

  localVar = ds_malloc(sizeof(localVar));
  if (localVar != 0) {
  }
  localVar = -1;
  ds_write(0, &localVar, sizeof(localVar));
  ds_finish();

}

int ds_init_list() {
  ds_init("list.bin");
  return 0;
}

int ds_replace(int value, long index) {
  struct ds_list_items_struct previous;
  register int prevVal, i;
  long head;

  /*initialize loop and get head*/
  ds_read(&head, 0, sizeof(head));
  previous.next = head;

  /*traverse list*/
  for (i = index; i>= 0; i--) {
    prevVal = previous.next;
    ds_read(&previous, previous.next, sizeof(previous));
    if (previous.next == head) {
      return -1;
    }
  }

  /*once at wanted location, re-write values*/
  previous.item = value;
  ds_write(prevVal, &previous, sizeof(previous));
  return 0;
}

int ds_insert(int value, long index) {
  register int i;
  long previous_loc, previous_previous_location;
  struct ds_list_items_struct previous;
  struct ds_list_items_struct new;
  previous_loc = sizeof(long);
  previous_previous_location = 0;

  ds_read(&previous.next, 0, sizeof(previous.next)); /*initialize dummy*/

  /*traverse list to see if insert index above what is possible*/
  for (i = index; i >= 0; i--) {
    previous_previous_location = previous_loc;
    ds_read(&previous, previous_loc, sizeof(previous));
    previous_loc = previous.next;
    if (previous.next == -1) {
      return -1;
    }
    previous_loc = previous.next;
  }

  new.item = value;
  new.next = previous.next;

  previous.next = ds_malloc(sizeof(new));
  ds_write(previous.next, &new, sizeof(new));

  if (index == 0) {
    ds_write(0, &previous.next, sizeof(previous.next));
  }
  if (previous_loc == 0) {
    new.next = previous.next;
    ds_write(previous.next, &new, sizeof(new));

    /*write to file*/
    return 0;
  } else {
    ds_write(previous_previous_location, &previous, sizeof(previous));

  return 0;
  }
}

int ds_delete(long index) {
  register int i;
  struct ds_list_items_struct previous;
  struct ds_list_items_struct forward;
  long head, before;
  ds_read(&head, 0, sizeof(head));
  previous.next = head;
  before = 0;

  /*reset head if delete at index 0*/
  if (index == 0) {
    ds_read(&previous, head, sizeof(previous));
    ds_free(head);
    head = previous.next;
    ds_write(0, &head, sizeof(head));
  } else {
    index -= 1;
    /*traverse list to find correct place*/
      for (i = index; i  >= 0; i--) {
        before = previous.next;
        ds_read(&previous, previous.next, sizeof(previous));
        if (previous.next == -1 || previous.next == head) {
          return -1;
        }
      }
      /*change the next of the value before the deleted one*/
      ds_read(&forward, previous.next, sizeof(forward));
      ds_free(previous.next);
      previous.next = forward.next;
      ds_write(before, &previous, sizeof(previous));
  }


  return 0;
}

int ds_swap(long index1, long index2) {
  register int i;
  struct ds_list_items_struct previous;
  struct ds_list_items_struct forward;
  int prevVal, forVal;
  long head, previousLocation, forwardLocation;
  prevVal = forVal = 0;
  head = previousLocation = forwardLocation = 0;

  /*get head and initialize loops*/
  ds_read(&head, 0, sizeof(head));
  previous.next = head;
  forward.next = head;

  if (index1 == index2) {
    return -1;
  }
  /*traverse to find location at index1*/
  for (i = index1; i >= 0; i--) {
    previousLocation = previous.next;
    ds_read(&previous, previous.next, sizeof(previous));
    if (previous.next == head) {
      return -1;
    }
  }

  /*traverse to find location at index2*/
  for (i = index2; i >= 0; i--) {
    forwardLocation = forward.next;
    ds_read(&forward, forward.next, sizeof(forward));
    if (forward.next == head) {
      return -1;
    }
  }
  /*swap values*/
  prevVal = previous.item;
  forVal = forward.item;

  previous.item = forVal;
  forward.item = prevVal;

  /*write locations*/
  ds_write(previousLocation, &previous, sizeof(previous));
  ds_write(forwardLocation, &forward, sizeof(forward));

  return 0;
}

long ds_find(int target) {
  struct ds_list_items_struct previous;
  long head;
  int count;

  /*initialize head and loop*/
  ds_read(&head, 0, sizeof(head));
  previous.next = head;
  count = 0;

  while(1) {
    /*traverse*/
  ds_read(&previous, previous.next, sizeof(previous));
  if (previous.next == head) { /*if at end*/
    return -1;
  }
  if (previous.item == target) { /*if at target*/
      return count;
    }
    count++;
  }
  return -1;
}

int ds_read_elements(char *filename) {
  char buffer[10000];
  int bufferVals[1000];
  int i, j, temp;
  long position, end;
  FILE *fp;

  position = end = temp = 0;

  /*open file*/
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
  for (i = 0; i < 1000; i++) {
    fscanf(fp, "%s", buffer);
    position = ftell(fp);
    /*convert string to text*/
    bufferVals[i] = atoi(buffer);
    if (position == end) { /*if at end of file*/
      bufferVals[i] = 0;
      break;
    }
  }
  for (j = i-1; j >= 0; j--) {
    ds_insert(bufferVals[j], 0);
  }

  return 0;
}

int ds_finish_list() {
  if (ds_finish() == 1) {
    return 0;
  } else {
    return 1;
  }
}
