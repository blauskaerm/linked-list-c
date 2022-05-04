struct node {
  int value;
  struct node *next;
};

struct linked_list_t {

  int nr_of_items;

  struct node *head;
  struct node *tail;

  int (*add_item_callback)(void *);
  int (*delete_item_callback)(void *);
  int (*add_item_idx_callback)(void *);
  int (*item_iterator_callack)(void *);
};

int add_item(int);
int add_item_idx(int, int);
int delete_item(int);
int items_in_list();
void print_list();

int linked_list_init(struct linked_list_t *list,
                     int (*add_item_bc)(void *),
                     int (*delete_item_cb)(void *),
                     int (*add_item_idx_cb)(void *),
                     int (*item_iterator_cb)(void *));
