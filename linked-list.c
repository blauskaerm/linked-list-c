
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked-list.h"

/* static int nr_of_items = 0; */
/* static struct node *head = NULL; */
/* static struct node *tail = NULL; */

int add_item(struct linked_list_t *list, void *value)
{
  int result = -1;
  struct node *new_node = NULL;

  new_node = calloc(1, sizeof(*new_node));
  if(new_node == NULL)
    {
      goto cleanup;
    }
  if (list->add_item_callback(&new_node->item, value) != 0)
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
    struct node *idx_node = NULL;

    if(list->head == NULL || list->tail == NULL)
      return 0;

    for(idx_node = list->head; idx_node != list->tail; idx_node = idx_node->next)
        list->item_iterator_callack(idx_node->item);
    list->item_iterator_callack(list->tail->item);

    return 0;
}

int add_item_idx(struct linked_list_t *list, void *value, int idx) {
  int result = -1;
  int i = 0;

  struct node *item_pre_add = NULL;
  struct node *item_to_add = NULL;

  if(idx < 0)
    goto cleanup;

  if(idx > list->nr_of_items)
    goto cleanup;

  item_to_add = calloc(1, sizeof(*item_to_add));
  if(item_to_add == NULL)
    goto cleanup;
  if (list->add_item_callback(&item_to_add->item, value) != 0)
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
      for(i = 0; i < idx; i++)
          item_pre_add = item_pre_add->next;
      item_pre_add->next = item_to_add;
      list->tail = item_to_add;
    }
  else
    {
      item_pre_add = list->head;
      for(i = 0; i < idx-1; i++)
          item_pre_add = item_pre_add->next;
      item_to_add->next = item_pre_add->next;
      item_pre_add->next = item_to_add;
    }

  result = 0;
  list->nr_of_items += 1;

 cleanup:
  return result;
}

int delete_item(struct linked_list_t *list, int idx)
{
  int i;
  int result = -1;
  struct node *item_pre_delete = NULL;
  struct node *item_to_delete = NULL;

  if(list->nr_of_items == 0)
    goto cleanup;

  if(idx < 0)
    goto cleanup;

  if(idx >= list->nr_of_items)
    goto cleanup;

  if(list->nr_of_items == 1) { // Only one item
    list->delete_item_callback(list->tail->item);
    memset(list->tail, 0, sizeof(*list->tail));
    free(list->tail);
    list->head = NULL;
    list->tail = NULL;
  }
  else if(idx == 0) { // first item
    item_to_delete = list->head;
    list->head = list->head->next;
    list->delete_item_callback(item_to_delete->item);
    memset(item_to_delete, 0, sizeof(*item_to_delete));
    free(item_to_delete);
  }
  else if(idx == list->nr_of_items - 1) // last item
    {
      item_pre_delete = list->head;
      for(i = 0; i < idx-1; i++)
          item_pre_delete = item_pre_delete->next;
      item_to_delete = item_pre_delete->next;
      list->tail = item_pre_delete;
      list->delete_item_callback(item_to_delete->item);
      memset(item_to_delete, 0, sizeof(*item_to_delete));
      free(item_to_delete);
    }
  else // Intermediate item
    {
      item_pre_delete = list->head;
      for(i = 0; i < idx-1; i++)
          item_pre_delete = item_pre_delete->next;
      item_to_delete = item_pre_delete->next;
      list->delete_item_callback(item_to_delete->item);
      item_pre_delete->next = item_pre_delete->next->next;
      memset(item_to_delete, 0, sizeof(*item_to_delete));
      free(item_to_delete);
    }

  list->nr_of_items -= 1;
  result = 0;

 cleanup:
  return result;
}

/* int delete_item(int idx) */
/* { */
/*   int i; */
/*   int result = -1; */
/*   struct node *item_pre_delete = NULL; */
/*   struct node *item_to_delete = NULL; */

/*   if(nr_of_items == 0) */
/*     goto cleanup; */

/*   if(idx < 0) */
/*     goto cleanup; */

/*   if(idx >= nr_of_items) */
/*     goto cleanup; */

/*   if(nr_of_items == 1) { */
/*     memset(tail, 0, sizeof(*tail)); */
/*     free(tail); */
/*     head = NULL; */
/*     tail = NULL; */
/*   } */
/*   else if(idx == 0) { */
/*     item_to_delete = head; */
/*     head = head->next; */
/*     memset(item_to_delete, 0, sizeof(*item_to_delete)); */
/*     free(item_to_delete); */
/*   } */
/*   else if(idx == nr_of_items - 1) */
/*     { */
/*       item_pre_delete = head; */
/*       for(i = 0; i < idx-1; i++) */
/*           item_pre_delete = item_pre_delete->next; */
/*       item_to_delete = item_pre_delete->next; */
/*       tail = item_pre_delete; */
/*       memset(item_to_delete, 0, sizeof(*item_to_delete)); */
/*       free(item_to_delete); */
/*     } */
/*   else */
/*     { */
/*       item_pre_delete = head; */
/*       for(i = 0; i < idx-1; i++) */
/*           item_pre_delete = item_pre_delete->next; */
/*       item_to_delete = item_pre_delete->next; */
/*       item_pre_delete->next = item_pre_delete->next->next; */
/*       memset(item_to_delete, 0, sizeof(*item_to_delete)); */
/*       free(item_to_delete); */
/*     } */

/*   nr_of_items -= 1; */
/*   result = 0; */

/*  cleanup: */
/*   return result; */
/* } */

int items_in_list(struct linked_list_t *list) {
  return list->nr_of_items;
}

/* void print_list() */
/* { */
/*   int i = 0; */
/*   struct node *idx_node = NULL; */

/*   if(head == NULL || tail == NULL) */
/*     return; */

/*   printf("Nr of Items: %d\n", nr_of_items); */
/*   for(idx_node = head; idx_node != tail; idx_node = idx_node->next) */
/*     { */
/*       printf("Value[%d]: %d\n", i, idx_node->value); */
/*       i += 1; */
/*     } */
/*   printf("Value[%d]: %d\n", i++, tail->value); */
/* } */

int linked_list_init(struct linked_list_t *list,
                     int (*add_item_cb)(void **, void *),
                     int (*delete_item_cb)(void *),
                     int (*add_item_idx_cb)(void *, void *),
                     int (*item_iterator_cb)(void *)) {
  memset(list, 0, sizeof(*list));

  list->add_item_callback = add_item_cb;
  list->delete_item_callback = delete_item_cb;
  list->add_item_idx_callback = add_item_idx_cb;
  list->item_iterator_callack = item_iterator_cb;

  return 0;
}
