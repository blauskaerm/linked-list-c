struct node {
  void *item;
  struct node *next;
};

struct linked_list_t {

  int nr_of_items;

  struct node *head;
  struct node *tail;

  int (*add_item_callback)(void **, void *);
  int (*delete_item_callback)(void *);
  int (*add_item_idx_callback)(void *, void *);
  int (*item_iterator_callack)(void *);
};

int add_item(struct linked_list_t *, void *);
int add_item_idx(int, int);
int delete_item(struct linked_list_t *, int);
int items_in_list(struct linked_list_t *);
void print_list();
int iterate_items(struct linked_list_t *);

int linked_list_init(struct linked_list_t *list,
                     int (*add_item_bc)(void **, void *),
                     int (*delete_item_cb)(void *),
                     int (*add_item_idx_cb)(void *, void *),
                     int (*item_iterator_cb)(void *));
