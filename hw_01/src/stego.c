#include "stego.h"

void insert(const bmp_img_t img, bmp_img_t *const result, const key_str_t *const key, const char *const message) {
    copy_bmp_img(img, result);
    
    const key_str_t* ptr_key = key;
    
    for (const char *ptr_msg = message; *ptr_msg != '\0'; ptr_msg++) {
        uint char_code = 0;

        switch (*ptr_msg) {
            case ' ':
                char_code = 26;
                break;
            case '.':
                char_code = 27;
                break;
            case ',':
                char_code = 28;
                break;
            default:
                char_code = *ptr_msg - 'A';
                break;
        }
        for (int i = 0; i < bits_per_char; i++, ptr_key++) {
            const uint bit = (char_code & (uint)(1 << i));
            int x = ptr_key->x, y = ptr_key->y;
            switch (ptr_key->c) {
                case 'R':
                    if((result->bitmap[x][y].r & 1))
                        result->bitmap[x][y].r ^= 1;
                    if(bit)
                        result->bitmap[x][y].r ^= 1;
                    break;
                case 'G':
                    if((result->bitmap[x][y].g & 1))
                        result->bitmap[x][y].g ^= 1;
                    if(bit)
                        result->bitmap[x][y].g ^= 1;
                    break;
                case 'B':
                    if((result->bitmap[x][y].b & 1))
                        result->bitmap[x][y].b ^= 1;
                    if(bit)
                        result->bitmap[x][y].b ^= 1;
                    break;
                default:
                    break;
            }
        }
    }
}

void extract(const bmp_img_t img, const key_str_t *const key, int n, char *const message) {
    char* ptr_msg = message;

    for (int ind_key = 0; ind_key < n; ptr_msg++) {
        uint char_code = 0;

        for(int i = 0; i < bits_per_char; i++, ind_key++) {
            int x = key[ind_key].x, y = key[ind_key].y;
            switch (key[ind_key].c) {
                case 'R':
                    char_code ^= (img.bitmap[x][y].r & 1) * (1 << i);
                    break;
                case 'G':
                    char_code ^= (img.bitmap[x][y].g & 1) * (1 << i);
                    break;
                case 'B':
                    char_code ^= (img.bitmap[x][y].b & 1) * (1 << i);
                    break;
                default:
                    break;
            }
        }

        switch (char_code) {
            case 26:
                *ptr_msg = ' ';
                break;
            case 27:
                *ptr_msg = '.';
                break;
            case 28:
                *ptr_msg = ',';
                break;
            default:
                *ptr_msg = char_code + 'A';
                break;
        }
    }
}
