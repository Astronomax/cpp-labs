#include "bmp.h"
#include "stego.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"

int main(int argc, char* argv[]) {
    assert(argc > 1);
    
    if(strcmp(argv[1], "insert") == 0) {
        //‹in-bmp› ‹out_file-bmp› ‹key-txt› ‹msg-txt›
        FILE *inp_file = fopen(argv[2], "rb");

        bmp_img_t img;
        if(load_bmp(inp_file, &img) != 0)
            return 1;
        fclose(inp_file);

        //key
        FILE* key_file = fopen(argv[4], "r");
        if(key_file == NULL)
            return 1;

        key_str_t cur_key;
        int key_n = 0;
        while(fscanf(key_file, "%d %d %c", &(cur_key.x), &(cur_key.y), &(cur_key.c)) != EOF)
            key_n++;
        fseek(key_file, 0, SEEK_SET);

        key_str_t* key = calloc(sizeof(key_str_t), key_n);
        if(key == NULL)
            return 1;
        for(int i = 0; i < key_n; i++)
            fscanf(key_file, "%d %d %c", &(key[i].x), &(key[i].y), &(key[i].c));

        //msg
        FILE* msg_file = fopen(argv[5], "r");
        if(msg_file == NULL)
            return 1;

        int msg_n = 0;
        char c;
        while(fscanf(msg_file, "%c", &c) != EOF && (c == ' ' || c == '.' || c == ',' || ('A' <= c && c <= 'Z')))
            msg_n++;
        fseek(msg_file, 0, SEEK_SET);

        char* msg = calloc(sizeof(char), msg_n + 1);
        if(msg == NULL)
            return 1;
        	
        for(int i = 0; i < msg_n; i++)
            fscanf(msg_file, "%c", &msg[i]);

        fclose(msg_file);

        bmp_img_t result;
        insert(img, &result, key, msg);

        //out
        FILE *out_file = fopen(argv[3], "wb");
        if(save_bmp(out_file, result) != 0)
            return 1;

        //clear
        fclose(key_file);
        fclose(out_file);
        free(key);
        free(msg);
        delete_bmp_img(img);
        delete_bmp_img(result);
    }
    else if(strcmp(argv[1], "extract") == 0) {
        //‹in-bmp› ‹key-txt› ‹msg_file-txt›

        FILE *inp_file = fopen(argv[2], "rb");

        bmp_img_t img;
        if(load_bmp(inp_file, &img) != 0)
            return 1;
        fclose(inp_file);

        //key
        FILE* key_file = fopen(argv[3], "r");
        if(key_file == NULL)
            return 1;

        key_str_t p;
        int key_n = 0;
        while(fscanf(key_file, "%d %d %c", &(p.x), &(p.y), &(p.c)) != EOF)
            key_n++;
        fseek(key_file, 0, SEEK_SET);

        key_str_t* key = calloc(sizeof(key_str_t), key_n);
        if(key == NULL)
            return 1;
            
        for(int i = 0; i < key_n; i++)
            fscanf(key_file, "%d %d %c", &(key[i].x), &(key[i].y), &(key[i].c));

        //msg
        char *msg = calloc(sizeof(char), key_n / bits_per_char + 1);
        if(msg == NULL)
            return 1;
        extract(img, key, key_n, msg);

        //out
        FILE* msg_file = fopen(argv[4], "w");
        if(msg_file == NULL)
            return 1;

        if(fprintf(msg_file, "%s", msg) < 0)
            return 1;

        //clear
        fclose(key_file);
        fclose(msg_file);
        free(key);
        free(msg);
        delete_bmp_img(img);
    }
    else if(strcmp(argv[1], "crop-rotate") == 0) {
        FILE *inp = fopen(argv[2], "rb");

        int x = atoi(argv[4]), y = atoi(argv[5]), w = atoi(argv[6]), h = atoi(argv[7]);

        bmp_img_t img;
        if(load_bmp(inp, &img) != 0)
            return 1;
        fclose(inp);

        int height = img.info_header.height, width = img.info_header.width;

        if(x < 0 || w < 0 || x + w > width || y < 0 || h < 0 || y + h > height)
            return 1;

        bmp_img_t cropped;
        if(crop(img, &cropped, y, x, h, w) != 0)
            return 1;

        bmp_img_t rotated;
        if(rotate(cropped, &rotated) != 0)
            return 1;

        FILE *out = fopen(argv[3], "wb");

        if(save_bmp(out, rotated) != 0)
            return 1;

        //clear
        fclose(out);
        delete_bmp_img(img);
        delete_bmp_img(cropped);
        delete_bmp_img(rotated);
    }
    return 0;
}
