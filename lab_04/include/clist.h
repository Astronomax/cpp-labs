#ifndef CLIST_H_
#define CLIST_H_

typedef struct intrusive_node {
  struct intrusive_node *next;
  struct intrusive_node *prev;
} intrusive_node_t;

typedef struct intrusive_list {
  struct intrusive_node *head;
} intrusive_list_t;

void init_list(intrusive_list_t *list);
void add_node(intrusive_list_t *list, intrusive_node_t *elem);
void remove_node(intrusive_list_t *list, intrusive_node_t *elem);

int get_length(intrusive_list_t *list);

#endif
