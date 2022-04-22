
#include <stdio.h>
#include <stdlib.h>

struct node {
  int value;
  struct node *next;
};

int nr_of_items = 0;
struct node *head = NULL;
struct node *tail = NULL;

int add_item(int value)
{
  int result = -1;
  struct node *new_node = NULL;

  new_node = calloc(1, sizeof(struct node));
  if(new_node == NULL)
    {
      printf("Unable to allocate new item\n”");
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

int delete_item(int idx)
{
  int i;
  int result = -1;
  struct node *item_pre_delete = NULL;
  struct node *item_to_delete = NULL;

  if(nr_of_items == 0)
    goto cleanup;

  if(idx >= nr_of_items)
    goto cleanup;

  printf("Delete index %d\n", idx);

  if(idx == 0) {
    printf("Delete first item\n");

    item_to_delete = head;
    head = head->next;
    free(item_to_delete);
  }
  else if(idx == nr_of_items - 1)
    {
      printf("Delete last item\n");

      item_pre_delete = head;
      for(i = 0; i < idx-1; i++)
        {
          item_pre_delete = item_pre_delete->next;
        }
      item_to_delete = item_pre_delete->next;
      tail = item_pre_delete;

      printf("Stop at item: %d, item_to_delete: %d\n", item_pre_delete->value, item_to_delete->value);

      free(item_to_delete);
    }
  else
    {
      printf("Delete intermediate item\n");

      item_pre_delete = head;
      for(i = 0; i < idx-1; i++)
        {
          item_pre_delete = item_pre_delete->next;
        }
      item_to_delete = item_pre_delete->next;
      item_pre_delete->next = item_pre_delete->next->next;
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

int main() {

  int i;

  for(i = 0; i < 10; i++)
      add_item(i);

  printf("Print after insertion\n");
  print_list();
  printf("\n");

  delete_item(4);
  printf("Print after delete 4\n");
  print_list();
  printf("\n");

  delete_item(6);
  printf("Print after delete 6\n");
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


  return 0;
}
