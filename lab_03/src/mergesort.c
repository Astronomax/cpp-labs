#include <mergesort.h>

void my_merge(void* begin1, void* end1, void* begin2, void* end2, void* begin, size_t element_size, int(*cmp)(const void* el1, const void* el2)) {
    char* p1 = (char*)begin1;
    char* p2 = (char*)begin2;
    char* p = (char*)begin;

    while (p1 != end1 && p2 != end2) {
        if (cmp(p1, p2) < 1) {
            for (int i = 0; i < element_size; i++)
                *((char*)p + i) = *((char*)p1 + i);
            p1 += element_size;
        }
        else {
            for (int i = 0; i < element_size; i++)
                *((char*)p + i) = *((char*)p2 + i);
            p2 += element_size;
        }
        p += element_size;
    }
    while (p1 != end1) {
        for (int i = 0; i < element_size; i++)
            *((char*)p + i) = *((char*)p1 + i);
        p1 += element_size;
        p += element_size;
    }
    while (p2 != end2) {
        for (int i = 0; i < element_size; i++)
            *((char*)p + i) = *((char*)p2 + i);
        p2 += element_size;
        p += element_size;
    }
}

int mergesort(void* arr, size_t elements, size_t element_size, int(*comparator)(const void* el1, const void* el2)) {
    if (elements <= 1)
        return 0;
    int middle = elements / 2;
    if(mergesort(arr, middle, element_size, comparator) == -1)
    	return -1;
    if(mergesort((char*)arr + middle * element_size, elements - middle, element_size, comparator) == -1)
    	return -1;

    char* const res = (char*)malloc(elements * element_size);
    if(res == NULL)
    	return -1;
    my_merge(((char*)arr), ((char*)arr + middle * element_size), ((char*)arr + middle * element_size), ((char*)arr + elements * element_size), res, element_size, comparator);

    for (int i = 0; i < elements * element_size; i++)
        *((char*)arr + i) = *((char*)res + i);
    free(res);
    return 0;
}
