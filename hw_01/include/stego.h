#include "bmp.h"

#define bits_per_char 5

#ifndef STEGO_H_
#define STEGO_H_

typedef struct key_str {
    int x, y;
    char c;
} key_str_t;

void insert(const bmp_img_t img, bmp_img_t *const result, const key_str_t *const key, const char *const message);
void extract(const bmp_img_t img, const key_str_t *const key, int n, char *const message);

#endif
