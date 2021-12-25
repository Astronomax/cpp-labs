#include "test_str.h"

void test_my_strcpy(){
    char a[] = "aa";
    char b[40];
    assert(!my_strcmp("aa", my_strcpy(b, a)));
}

void test_my_strcat(){
    char a[] = "aaa";
    char b[6] = "bbb";
    assert(!my_strcmp("bbbaaa", my_strcat(b, a)));
}

void test_my_strcmp(){
    assert(my_strcmp("aaa", "aa") > 0);
    assert(my_strcmp("ab", "aa") > 0);
    assert(my_strcmp("aann", "aannnss") < 0);
    assert(my_strcmp("adfs", "adft") < 0);
    assert(my_strcmp("aa", "aa") == 0);
}

void test_my_strlen(){
    assert(my_strlen("") == 0);
    assert(my_strlen("ajde") == 4);
    assert(my_strlen("aasdee") == 6);
    assert(my_strlen("hthtkrksdee") == 11);
}
