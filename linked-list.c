
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked-list.h"

int add_item(struct linked_list_t *list, void *item)
{
  int result = -1;
  struct node *new_node = NULL;

  if(list == NULL)
    goto cleanup;
  if(item == NULL)
    goto cleanup;

  new_node = calloc(1, sizeof(*new_node));
  if(new_node == NULL)
    {
      goto cleanup;
    }
  if (list->add_item_callback(&new_node->item, item) != 0)
    goto cleanup;

  if(list->nr_of_items == 0)
    {
      list->head = new_node;
      new_node->next = list->head;
      list->tail = new_node;
    }
  else
    {
      list->tail->next = new_node;
      list->tail = new_node;
    }

  list->nr_of_items += 1;
  result = 0;

 cleanup:
  return result;
}

int iterate_items(struct linked_list_t *list) {

  int result = -1;
  struct node *idx_node = NULL;

  if(list == NULL)
    goto cleanup;
  if(list->head == NULL || list->tail == NULL)
    goto cleanup;

  for(idx_node = list->head; idx_node != list->tail; idx_node = idx_node->next)
    if(list->item_iterator_callack(idx_node->item) != 0)
      goto cleanup;
  if(list->item_iterator_callack(list->tail->item) != 0)
    goto cleanup;

  result = 0;

 cleanup:
  return result;
}

int set_iterate_callback(struct linked_list_t *list, int (*item_iterator_cb)(void *)) {
  if(item_iterator_cb == NULL)
    return -1;
  list->item_iterator_callack = item_iterator_cb;
  return 0;
}

int add_item_idx(struct linked_list_t *list, void *item, int idx) {
  int result = -1;

  struct node *item_pre_add = NULL;
  struct node *item_to_add = NULL;

  if(item == NULL)
    goto cleanup;
  if(list == NULL)
    goto cleanup;
  if(idx < 0)
    goto cleanup;
  if(idx > list->nr_of_items)
    goto cleanup;

  item_to_add = calloc(1, sizeof(*item_to_add));
  if(item_to_add == NULL)
    goto cleanup;
  if (list->add_item_callback(&item_to_add->item, item) != 0)
    goto cleanup;

  if(idx == 0) {
    if(list->head != NULL)
        item_to_add->next = list->head;
    else
        list->tail = item_to_add;
    list->head = item_to_add;
  }
  else if(idx == list->nr_of_items - 1)
    {
      item_pre_add = list->head;
      while(idx--)
        item_pre_add = item_pre_add->next;
      item_pre_add->next = item_to_add;
      list->tail = item_to_add;
    }
  else
    {
      item_pre_add = list->head;
      while(idx--)
        item_pre_add = item_pre_add->next;
      item_to_add->next = item_pre_add->next;
      item_pre_add->next = item_to_add;
    }

  result = 0;
  list->nr_of_items += 1;

 cleanup:
  return result;
}

int delete_item_idx(struct linked_list_t *list, int idx)
{
  int result = -1;
  struct node *item_pre_delete = NULL;
  struct node *item_to_delete = NULL;

  if(list == NULL)
    goto cleanup;
  if(list->nr_of_items == 0)
    goto cleanup;
  if(idx < 0)
    goto cleanup;
  if(idx >= list->nr_of_items)
    goto cleanup;

  if(list->nr_of_items == 1) { // Only one item
    if(list->delete_item_callback(list->tail->item) != 0)
      goto cleanup;
    memset(list->tail, 0, sizeof(*list->tail));
    free(list->tail);
    list->head = NULL;
    list->tail = NULL;
  }
  else if(idx == 0) { // first item
    item_to_delete = list->head;
    if(list->delete_item_callback(item_to_delete->item) != 0)
      goto cleanup;
    list->head = list->head->next;
    memset(item_to_delete, 0, sizeof(*item_to_delete));
    free(item_to_delete);
  }
  else if(idx == list->nr_of_items - 1) // last item
    {
      item_pre_delete = list->head;
      while(--idx)
        item_pre_delete = item_pre_delete->next;
      item_to_delete = item_pre_delete->next;
      if(list->delete_item_callback(item_to_delete->item) != 0)
        goto cleanup;
      list->tail = item_pre_delete;
      memset(item_to_delete, 0, sizeof(*item_to_delete));
      free(item_to_delete);
    }
  else // Intermediate item
    {
      item_pre_delete = list->head;
      while(idx--)
        item_pre_delete = item_pre_delete->next;
      item_to_delete = item_pre_delete->next;
      if(list->delete_item_callback(item_to_delete->item) != 0)
        goto cleanup;
      item_pre_delete->next = item_pre_delete->next->next;
      memset(item_to_delete, 0, sizeof(*item_to_delete));
      free(item_to_delete);
    }

  list->nr_of_items -= 1;
  result = 0;

 cleanup:
  return result;
}

int get_item_idx(struct linked_list_t *list, int idx, void **item) {

  int result = -1;
  struct node *item_to_get = NULL;

  if(list == NULL)
    goto cleanup;
  if(item == NULL)
    goto cleanup;
  if (idx < 0)
    goto cleanup;
  if (idx >= items_in_list(list))
    goto cleanup;

  item_to_get = list->head;
  while(idx--)
      item_to_get = item_to_get->next;

  *item = item_to_get->item;
  result = 0;

 cleanup:
  return result;
}

int items_in_list(struct linked_list_t *list) {
  return list->nr_of_items;
}

int linked_list_init(struct linked_list_t *list,
                     int (*add_item_cb)(void **, void *),
                     int (*delete_item_cb)(void *),
                     int (*item_iterator_cb)(void *)) {

  int result = -1;

  if(add_item_cb == NULL)
    goto cleanup;
  if (delete_item_cb == NULL)
    goto cleanup;
  if(item_iterator_cb == NULL)
    goto cleanup;

  memset(list, 0, sizeof(*list));
  list->add_item_callback = add_item_cb;
  list->delete_item_callback = delete_item_cb;
  list->item_iterator_callack = item_iterator_cb;

  result = 0;

 cleanup:
  return result;
}
