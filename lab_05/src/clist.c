#include "clist.h"
#include "stdlib.h"

void init_list(intrusive_list_t* list) {
    list->head = (intrusive_node_t*)malloc(sizeof(intrusive_node_t));
    list->head->next = NULL;
    list->head->prev = NULL;
}

void add_node(intrusive_list_t* list, intrusive_node_t* elem) {
    intrusive_node_t* cur = list->head;
    while(cur->next)
    	cur = cur->next;
    	
    cur->next = elem;
    elem->prev = cur;
}

void remove_node(intrusive_list_t* list, intrusive_node_t* elem) {
    intrusive_node_t* cur = list->head;
    while(cur && cur != elem)
        cur = cur->next;

    if(cur){
        if(cur->prev)
            cur->prev->next = cur->next;
        if(cur->next)
            cur->next->prev = cur->prev;
    }
}

int get_length(intrusive_list_t* list) {
    int len = 0;
    intrusive_node_t* cur = list->head;
    while(cur->next){
        cur = cur->next;
        len++;
    }
    return len;
}

void apply(intrusive_list_t* list, void (*op)(intrusive_node_t* node, void* data), void *data) {
    intrusive_node_t* cur = list->head->next;
    while(cur){
        op(cur, data);
        cur = cur->next;
    }
}
