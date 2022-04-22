
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

  if(nr_of_items == 0)
    {
      new_node = calloc(1, sizeof(struct node));
      if(new_node == NULL)
        {
          printf("Unable to allocate new item\n”");
          goto cleanup;
        }
      new_node->value = value;

      head = new_node;
      new_node->next = head;
      tail = new_node;
    }
  else
    {
      new_node = calloc(1, sizeof(struct node));
      if(new_node == NULL)
        {
          printf("Unable to allocate new item\n”");
          goto cleanup;
        }
      new_node->value = value;

      tail->next = new_node;
      tail = new_node;
    }

  nr_of_items += 1;
  result = 0;

 cleanup:
  return result;
}

int main() {

  int i;
  struct node *idx_node = NULL;

  for(i = 0; i < 10; i++)
      add_item(i);

  for(idx_node = head; idx_node != tail; idx_node = idx_node->next)
    printf("Value: %d\n", idx_node->value);

  return 0;
}
