#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

#ifndef BMP_H_
#define BMP_H_

#pragma pack(push, 1)
typedef struct bmp_header {
    uint16_t signature;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} bmp_header_t;

typedef struct bmp_info_header {
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t size_image;
    uint32_t x_per_meter;
    uint32_t y_per_meter;
    uint32_t clr_num;
    uint32_t clr_important;
} bmp_info_header_t;

typedef struct pixel {
    uint8_t r, g, b;
} pixel_t;

typedef struct bmp_img {
    bmp_header_t header;
    bmp_info_header_t info_header;
    pixel_t** bitmap;
} bmp_img_t;
#pragma pack(pop)

int copy_bmp_img(const bmp_img_t img, bmp_img_t* const result);
int get_bitmap(pixel_t*** bitmap, const int height, const int width);
void delete_bmp_img(bmp_img_t img);
int load_bmp(FILE* const f, bmp_img_t* const result);
int crop(const bmp_img_t img, bmp_img_t* const result, const int r, const int c, const int height, const int width);
int rotate(const bmp_img_t img, bmp_img_t* const result);
int save_bmp(FILE* const f, const bmp_img_t img);

#endif
