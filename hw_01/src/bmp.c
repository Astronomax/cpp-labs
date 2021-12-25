#include "bmp.h"
#define skip(width) (4 - (bytes_per_pixel * width) % 4) % 4
#define bytes_per_pixel 3

int copy_bmp_img(const bmp_img_t img, bmp_img_t* const result) {
    result->header = img.header;
    result->info_header = img.info_header;
    const int height = img.info_header.height, width = img.info_header.width;

    if(get_bitmap(&(result->bitmap), height, width) != 0)
        return 1;

    for(int row = 0; row < height; row++)
        for(int col = 0; col < width; col++)
            result->bitmap[row][col] = img.bitmap[row][col];
    return 0;
}

int get_bitmap(pixel_t*** bitmap, const int height, const int width) {
    pixel_t* temp = calloc(sizeof(pixel_t), height * width);
    if(temp == NULL)
        return 1;
    *bitmap = calloc(sizeof(pixel_t*), height);
    if(*bitmap == NULL)
        return 1;
    pixel_t* uk = temp;
    for(int row = 0; row < height; row++, uk += width)
        (*bitmap)[row] = uk;
    return 0;
}

void delete_bmp_img(bmp_img_t img) {
    free(img.bitmap[0]);
    free(img.bitmap);
}

int load_bmp(FILE* const f, bmp_img_t* const result) {
    if(f == NULL)
        return 1;
    bmp_header_t header;
    fread(&header, sizeof(bmp_header_t), 1, f);

    bmp_info_header_t info_header;
    fread(&info_header, sizeof(bmp_info_header_t), 1, f);

    if(info_header.bit_count != 8 * bytes_per_pixel)
        return 1;

    const int height = info_header.height, width = info_header.width;

    pixel_t** bitmap;
    if(get_bitmap(&bitmap, height, width) != 0)
        return 1;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++)
            fread(&bitmap[row][col], sizeof(pixel_t), 1, f);
        fseek(f, skip(width), SEEK_CUR);
    }
    bmp_img_t ans = { header, info_header, bitmap};
    *result = ans;
    return 0;
}

int crop(const bmp_img_t img, bmp_img_t* const result, const int r, const int c, const int height, const int width) {
    pixel_t** bitmap;
    if(get_bitmap(&bitmap, height, width) != 0)
        return 1;

    for(int row = 0; row < height; row++)
        for(int col = 0; col < width; col++)
            bitmap[row][col] = img.bitmap[(img.info_header.height - r - height) + row][c + col];

    bmp_header_t header = img.header;
    bmp_info_header_t info_header = img.info_header;

    info_header.height = height;
    info_header.width = width;


    info_header.size_image = height * (bytes_per_pixel * width + skip(width));
    header.file_size = sizeof(bmp_header_t) + sizeof(info_header) + info_header.size_image;

    bmp_img_t ans = { header, info_header, bitmap};
    *result = ans;
    return 0;
}

int rotate(const bmp_img_t img, bmp_img_t* const result) {
    const int height = img.info_header.width, width = img.info_header.height;

    pixel_t** bitmap;
    if(get_bitmap(&bitmap, height, width) != 0)
        return 1;

    for(int row = 0; row < height; row++)
        for(int col = 0; col < width; col++)
            bitmap[row][col] = img.bitmap[col][img.info_header.width - row - 1];

    bmp_header_t header = img.header;
    bmp_info_header_t info_header = img.info_header;

    info_header.height = height;
    info_header.width = width;

    info_header.size_image = height * (bytes_per_pixel * width + skip(width));
    header.file_size = sizeof(bmp_header_t) + sizeof(info_header) + info_header.size_image;

    bmp_img_t ans = { header, info_header, bitmap};
    *result = ans;
    return 0;
}

int save_bmp(FILE* const f, const bmp_img_t img) {
    if(f == NULL)
        return 1;

    const int height = img.info_header.height, width = img.info_header.width;
    fwrite(&img.header, sizeof(bmp_header_t), 1, f);
    fwrite(&img.info_header, sizeof(bmp_info_header_t), 1, f);
    for(int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++)
            fwrite(&img.bitmap[row][col], sizeof(pixel_t), 1, f);

        uint8_t null_byte = 0;
        for(int i = 0; i < skip(width); i++)
            fwrite(&null_byte, 1, 1, f);
    }
    return 0;
}

