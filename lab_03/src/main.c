#include <mergesort.h>
#include <string.h>

int IntComparator(const void* el1, const void* el2) {
    int* _el1 = (int*)el1;
    int* _el2 = (int*)el2;
    return *_el1 - *_el2;
}

int CharComparator(const void* el1, const void* el2) {
    char* _el1 = (char*)el1;
    char* _el2 = (char*)el2;
    return *_el1 - *_el2;
}

int StringComparator(const void* el1, const void* el2) {
    char** _el1 = (char**)el1;
    char** _el2 = (char**)el2;

    char* p1 = *_el1;
    char* p2 = *_el2;

    while (*p1 != '\0' && *p2 != '\0') {
        if (*p1 != *p2)
            return *p1 - *p2;
        p1++; p2++;
    }
    if (*p1 == '\0' && *p2 == '\0')	
        return 0;
    else if (*p1 == '\0')
        return -1;
    else return 1;
}

int main(int argc, char* argv[]) {
    size_t n = argc - 2;
	
    const char* _int = "int";
    const char* _char = "char";
    const char* _str = "str";
    
    if (strcmp(argv[1], _int) == 0) {
        int* a = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            a[i] = atoi(argv[i + 2]);

        if(mergesort(a, n, sizeof(int), IntComparator) == -1) {
            printf("%s", "Error: memory allocation failed.");
            return 1;
        }
        for (int i = 0; i < n; i++)
            printf("%d ", a[i]);

        free(a);
    }
    else if (strcmp(argv[1], _char) == 0) {
        char* a = (char*)malloc(n * sizeof(char));
        for (int i = 0; i < n; i++)
            a[i] = *argv[i + 2];

        if(mergesort(a, n, sizeof(char), CharComparator) == -1) {
            printf("%s", "Error: memory allocation failed.");
            return 1;
        }
        for (int i = 0; i < n; i++)
            printf("%c ", a[i]);

        free(a);
    }
    else if (strcmp(argv[1], _str) == 0) {
        char** a = (char**)malloc(n * sizeof(char*));
        for (int i = 0; i < n; i++) {
            a[i] = (char*)malloc(strlen(argv[i + 2]) * sizeof(char*));
            strcpy(a[i], argv[i + 2]);
        }

        if(mergesort(a, n, sizeof(char*), StringComparator) == -1) {
            printf("%s", "Error: memory allocation failed.");
            return 1;
        }
        for (int i = 0; i < n; i++)
            printf("%s ", a[i]);
        for (int i = 0; i < n; i++)
            free(a[i]);
        free(a);
    }
    printf("%c", '\n');
    return 0;
}
