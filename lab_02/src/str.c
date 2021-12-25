#include "str.h"

char *my_strcpy(char * s1, char * s2) {
    char *res = s1;
    while(*s2)
	*s1++ = *s2++;
    *s1 = '\0';
    return res;
}

char *my_strcat(char * s1, char * s2) {
    char *res = s1;
    while(*s1)
	s1++;
    while(*s2)
        *s1++ = *s2++;
    *s1 = '\0';
    return res;
}

int my_strcmp(char *s1, char *s2) {
    while (*s1 && *s2) {
	if (*s1 > *s2)
	    return 1;
	else if (*s1 < *s2)
	    return -1;
	s1++; s2++;
    }

    if (*s1)
	return 1;
    else if (*s2)
	return -1;
    else
	return 0;
}

size_t my_strlen(char *s) {
    size_t res = 0;
	while(*s++)
	    res++;
    return res;
}
