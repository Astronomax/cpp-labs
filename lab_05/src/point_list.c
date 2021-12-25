#include "point_list.h"

void add_point(intrusive_list_t *list, int x, int y) {
    point_t* p = (point_t*)malloc(sizeof(point_t));
    p->x = x;
    p->y = y;
    p->node.next = NULL;
    p->node.prev = NULL;
    add_node(list, &(p->node));
}

void remove_point(intrusive_list_t *list, int x, int y) { // removes all (x, y) pairs
    intrusive_node_t *cur = list->head;
    while(cur->next) {
        point_t* p = container_of(cur->next, point_t, node);
        if(p->x == x && p->y == y) {
            remove_node(list, cur->next);
            free(p);
        }
        else cur = cur->next;
    }
}

void show_all_points(intrusive_list_t* list) {
    intrusive_node_t *cur = list->head;
    while(cur->next){
        point_t* p = container_of(cur->next, point_t, node);
        printf("(%d %d) ", p->x, p->y);
        cur = cur->next;
    }
    printf("\n");
}

void remove_all_points(intrusive_list_t* list) {
    intrusive_node_t *cur = list->head;
    while(cur->next){
        point_t* p = container_of(cur->next, point_t, node);
        remove_node(list, cur->next);
        free(p);
    }
}
