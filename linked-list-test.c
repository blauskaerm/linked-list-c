#include <stdio.h>

#include "linked-list.h"

int dummy_callback(void *ptr) {
  return 0;
}

int main() {

  int i;
  struct linked_list_t list;
  linked_list_init(&list,
                   &dummy_callback,
                   &dummy_callback,
                   &dummy_callback,
                   &dummy_callback);

  for(i = 0; i < 9; i++)
    add_item_idx(i, 0);
  add_item_idx(9, items_in_list() - 1);

  printf("Print after insertion\n");
  print_list();
  printf("\n");

  delete_item(4);
  printf("Print after delete 4\n");
  print_list();
  printf("\n");

  add_item_idx(4, 4);
  printf("Print after add 4 at 4\n");
  print_list();
  printf("\n");

  delete_item(0);
  printf("Print after deleting head\n");
  print_list();
  printf("\n");

  delete_item(items_in_list() - 1);

  printf("Print after deleting tail\n");
  print_list();
  printf("\n");

  for(i = items_in_list(); i >= 0; i--)
    delete_item(0);

  return 0;
}
