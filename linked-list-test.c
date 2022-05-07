#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked-list.h"

int dummy_callback(void *item, void *value) {
  return 0;
}

int add_my_item(void **item, void *value) {

  int *my_value = (int *) value;

  printf("Value to add: %d, address %p, size: %lu\n",
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

int modify_item_iterator(void *item) {
  int *my_value = (int *) item;
  *my_value += 1;
  return 0;
}

int delete_my_item(void *item) {
  int *my_value = (int *) item;
  printf("Item to free: %p\n", my_value);
  memset(my_value, 0, sizeof(*my_value));
  free(my_value);
  return 0;
}

int main() {

  int i;
  struct linked_list_t list;
  linked_list_init(&list,
                   &add_my_item,
                   &delete_my_item,
                   &iterator);

  for(i = 0; i < 9; i++)
    add_item(&list, &i);
  printf("Items in list: %d\n", items_in_list(&list));
  iterate_items(&list);
  printf("\n");

  delete_item_idx(&list, 3);
  printf("Print after delete 4\n");
  printf("Items in list: %d\n", items_in_list(&list));
  iterate_items(&list);
  printf("\n");

  i = 4;
  add_item_idx(&list, &i, 3);
  printf("Print after add 4 at 4\n");
  printf("Items in list: %d\n", items_in_list(&list));
  iterate_items(&list);
  printf("\n");

  delete_item_idx(&list, 0);
  printf("Print after deleting head\n");
  printf("Items in list: %d\n", items_in_list(&list));
  iterate_items(&list);
  printf("\n");

  delete_item_idx(&list, items_in_list(&list) - 1);
  printf("Print after deleting tail\n");
  printf("Items in list: %d\n", items_in_list(&list));
  iterate_items(&list);
  printf("\n");

  i = 0;
  add_item_idx(&list, &i, 0);
  printf("Print after adding to head\n");
  printf("Items in list: %d\n", items_in_list(&list));
  iterate_items(&list);
  printf("\n");

  i = 8;
  add_item_idx(&list, &i, items_in_list(&list) - 1);
  printf("Print after adding to tail\n");
  printf("Items in list: %d\n", items_in_list(&list));
  iterate_items(&list);
  printf("\n");

  set_iterate_callback(&list, &modify_item_iterator);
  iterate_items(&list);
  printf("Print after adding one to each item\n");
  printf("Items in list: %d\n", items_in_list(&list));
  set_iterate_callback(&list, &iterator);
  iterate_items(&list);
  printf("\n");

  int *item = NULL;
  printf("Get item at index 3\n");
  get_item_idx(&list, 3, (void *)&item);
  printf("Got item: %d\n", *item);
  printf("\n");

  printf("Delete all items\n");
  for(i = items_in_list(&list); i >= 0; i--)
    delete_item_idx(&list, 0);
  printf("Items in list: %d\n", items_in_list(&list));
  iterate_items(&list);
  printf("\n");

  printf("Head: %p\n", list.head);
  printf("Tail: %p\n", list.tail);

  return 0;
}
