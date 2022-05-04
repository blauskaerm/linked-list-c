
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked-list.h"

static int nr_of_items = 0;
static struct node *head = NULL;
static struct node *tail = NULL;

int add_item(int value)
{
  int result = -1;
  struct node *new_node = NULL;

  new_node = calloc(1, sizeof(*new_node));
  if(new_node == NULL)
    {
      goto cleanup;
    }
  new_node->value = value;

  if(nr_of_items == 0)
    {
      head = new_node;
      new_node->next = head;
      tail = new_node;
    }
  else
    {
      tail->next = new_node;
      tail = new_node;
    }

  nr_of_items += 1;
  result = 0;

 cleanup:
  return result;
}

int add_item_idx(int value, int idx) {
  int result = -1;
  int i = 0;int main() {

  int i;

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

  printf("head: %p\n", head);
  printf("tail: %p\n", tail);

  return 0;
}

  struct node *item_pre_add = NULL;
  struct node *item_to_add = NULL;

  if(idx < 0)
    goto cleanup;

  if(idx > nr_of_items)
    goto cleanup;

  item_to_add = calloc(1, sizeof(*item_to_add));
  if(item_to_add == NULL)
    goto cleanup;
  item_to_add->value = value;

  if(idx == 0) {
    if(head != NULL)
        item_to_add->next = head;
    else
        tail = item_to_add;
    head = item_to_add;
  }
  else if(idx == nr_of_items - 1)
    {
      item_pre_add = head;
      for(i = 0; i < idx; i++)
          item_pre_add = item_pre_add->next;
      item_pre_add->next = item_to_add;
      tail = item_to_add;
    }
  else
    {
      item_pre_add = head;
      for(i = 0; i < idx-1; i++)
          item_pre_add = item_pre_add->next;
      item_to_add->next = item_pre_add->next;
      item_pre_add->next = item_to_add;
    }

  result = 0;
  nr_of_items += 1;

 cleanup:
  return result;
}

int delete_item(int idx)
{
  int i;
  int result = -1;
  struct node *item_pre_delete = NULL;
  struct node *item_to_delete = NULL;

  if(nr_of_items == 0)
    goto cleanup;

  if(idx < 0)
    goto cleanup;

  if(idx >= nr_of_items)
    goto cleanup;

  if(nr_of_items == 1) {
    memset(tail, 0, sizeof(*tail));
    free(tail);
    head = NULL;
    tail = NULL;
  }
  else if(idx == 0) {
    item_to_delete = head;
    head = head->next;
    memset(item_to_delete, 0, sizeof(*item_to_delete));
    free(item_to_delete);
  }
  else if(idx == nr_of_items - 1)
    {
      item_pre_delete = head;
      for(i = 0; i < idx-1; i++)
          item_pre_delete = item_pre_delete->next;
      item_to_delete = item_pre_delete->next;
      tail = item_pre_delete;
      memset(item_to_delete, 0, sizeof(*item_to_delete));
      free(item_to_delete);
    }
  else
    {
      item_pre_delete = head;
      for(i = 0; i < idx-1; i++)
          item_pre_delete = item_pre_delete->next;
      item_to_delete = item_pre_delete->next;
      item_pre_delete->next = item_pre_delete->next->next;
      memset(item_to_delete, 0, sizeof(*item_to_delete));
      free(item_to_delete);
    }

  nr_of_items -= 1;
  result = 0;

 cleanup:
  return result;
}

int items_in_list() {
  return nr_of_items;
}

void print_list()
{
  int i = 0;
  struct node *idx_node = NULL;

  if(head == NULL || tail == NULL)
    return;

  printf("Nr of Items: %d\n", nr_of_items);
  for(idx_node = head; idx_node != tail; idx_node = idx_node->next)
    {
      printf("Value[%d]: %d\n", i, idx_node->value);
      i += 1;
    }
  printf("Value[%d]: %d\n", i++, tail->value);
}

int linked_list_init(struct linked_list_t *list,
                     int (*add_item_cb)(void *),
                     int (*delete_item_cb)(void *),
                     int (*add_item_idx_cb)(void *),
                     int (*item_iterator_cb)(void *)) {
  memset(list, 0, sizeof(*list));

  list->add_item_callback = add_item_cb;
  list->delete_item_callback = delete_item_cb;
  list->add_item_idx_callback = add_item_idx_cb;
  list->item_iterator_callack = item_iterator_cb;

  return 0;
}
