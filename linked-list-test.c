#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked-list.h"

int dummy_callback(void *item, void *value) {
  return 0;
}

int add_my_item(void **item, void *value) {

  int *my_value = (int *) value;

  printf("Value to add: %d, address %p, size: %u\n",
         *my_value,
         my_value,
         sizeof(*my_value));

  *item = calloc(1, sizeof(*my_value));
  printf("Pointer: %p %p\n", item, *item);
  memcpy(*item, my_value, sizeof(*my_value));

  return 0;
}

int iterator(void *value) {
  int *my_value = (int *) value;
  printf("Value: %d\n", *my_value);
  return 0;
}

int delete_my_item(void *item) {
  printf("free item\n");

  int *my_value = (int *) item;
  printf("Item to free: %p\n", my_value);

  free(my_value);
  return 0;
}

int main() {

  int i;
  struct linked_list_t list;
  linked_list_init(&list,
                   &add_my_item,
                   &delete_my_item,
                   &dummy_callback,
                   &iterator);

  for(i = 0; i < 9; i++)
    add_item(&list, &i);
  printf("Items in list: %d\n", items_in_list(&list));
  iterate_items(&list);
  //add_item_idx(9, items_in_list() - 1);

  /* printf("Print after insertion\n"); */
  /* print_list(); */
  /* printf("\n"); */

  delete_item(&list, 4);
  printf("Print after delete 4\n");
  iterate_items(&list);
  printf("\n");

  /* add_item_idx(4, 4); */
  /* printf("Print after add 4 at 4\n"); */
  /* print_list(); */
  /* printf("\n"); */

  /* delete_item(0); */
  /* printf("Print after deleting head\n"); */
  /* print_list(); */
  /* printf("\n"); */

  /* delete_item(items_in_list() - 1); */

  /* printf("Print after deleting tail\n"); */
  /* print_list(); */
  /* printf("\n"); */

  /* for(i = items_in_list(); i >= 0; i--) */
  /*   delete_item(0); */

  return 0;
}
