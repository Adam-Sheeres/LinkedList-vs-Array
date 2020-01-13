/*
Adam SHeeres-Paulicpulle
Student ID: 1036569
email: asheeres@uoguelph.ca
*/

struct ds_list_items_struct {
  int item;
  long next;
};

void ds_create_list();
int ds_init_list();
int ds_replace(int, long);
int ds_insert(int, long);
int ds_delete(long);
int ds_swap(long, long);
long ds_find(int);
int ds_read_elements(char *);
int ds_finish_list();
