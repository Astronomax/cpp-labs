#include "clist.h"
#include "stdlib.h"
#include "stdio.h"
#include "stddef.h"
#include "string.h"
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

typedef struct point {
    int x, y;
    intrusive_node_t node;
} point_t;

void add_point(intrusive_list_t *list, int x, int y) {
    point_t* p = (point_t*)malloc(sizeof(point_t));
    p->x = x;
    p->y = y;
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
        printf("(%d %d)", p->x, p->y);
        cur = cur->next;
        if(cur->next)
            printf(" ");
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

int main() {
    intrusive_list_t list;
    init_list(&list);
    char s[239];
    while(1){
        scanf("%239s", s);

        if(strcmp(s, "add") == 0){
            int x, y;
            scanf("%d %d", &x, &y);
            add_point(&list, x, y);
        }
        else if(strcmp(s, "rm") == 0){
            int x, y;
            scanf("%d %d", &x, &y);
            remove_point(&list, x, y);
        }
        else if(strcmp(s, "print") == 0)
            show_all_points(&list);
        else if(strcmp(s, "rma") == 0)
            remove_all_points(&list);
        else if(strcmp(s, "len") == 0)
            printf("%d\n", get_length(&list));
        else if(strcmp(s, "exit") == 0)
            break;
        else
            printf("Unknown command\n");
    }
    remove_all_points(&list);
    free(list.head);
    return 0;
}
