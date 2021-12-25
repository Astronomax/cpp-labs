#include "point_list.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"

const size_t bin_size = 3;
const int bits_per_int = 8 * bin_size;

typedef struct stream_format {
    FILE* stream;
    char* format;
} stream_format_t;

void count(intrusive_node_t* node, void* result) {
    if(node)
    	(*(int*)result)++;
}

int read_int(int *ans, FILE* fin) {
    *ans = 0;
    int result = fread(ans, bin_size, 1, fin);
    if(result != 1)
    	return result;
    if (*ans & (1 << (bits_per_int - 1))) {
        *ans -= 1;
        for (int i = 0; i < bits_per_int; i++)
            *ans ^= (1 << i);
        *ans *= -1;
    }
    return result;
}

void write_int(int n, FILE* fout) {
    if (n < 0) {
        n *= -1;
        for (int i = 0; i < bits_per_int; i++)
            n ^= (1 << i);
        n += 1;
    }
    fwrite(&n, bin_size, 1, fout);
}

void print_text(intrusive_node_t* node, void* sf) {
    FILE* stream = ((stream_format_t*)sf)->stream;
    char* format = ((stream_format_t*)sf)->format;
    point_t* p = container_of(node, point_t, node);
    fprintf(stream, format, p->x, p->y);
}

void write_bin(intrusive_node_t* node, void* stream) {
    point_t* p = container_of(node, point_t, node);
    write_int(p->x, stream);
    write_int(p->y, stream);
}

int main(int argc, char* argv[]) {
    assert(argc > 1);

    intrusive_list_t list;
    init_list(&list);

    if(strcmp(argv[1], "loadtext") == 0) {
        FILE* inp_file = fopen(argv[2], "r");
        int x = 0, y = 0;
        while(fscanf(inp_file, "%d%d", &x, &y) != EOF)
            add_point(&list, x, y);
        fclose(inp_file);
    }
    else {
        FILE* inp_file = fopen(argv[2], "rb");
        int x, y;
        while(read_int(&x, inp_file) == 1) {
            read_int(&y, inp_file);
            add_point(&list, x, y);
        }
        fclose(inp_file);
    }

    if (strcmp(argv[3], "savetext") == 0) {
        stream_format_t sf;
        sf.stream = fopen(argv[4], "w");
        sf.format = "%d %d\n";
        apply(&list, print_text, &sf);
        fclose(sf.stream);
    } else if (strcmp(argv[3], "savebin") == 0) {
        FILE* stream = fopen(argv[4], "wb");
        apply(&list, write_bin, stream);
        fclose(stream);
    } else if (strcmp(argv[3], "print") == 0) {
        stream_format_t sf;
        sf.stream = stdout;
        sf.format = argv[4];
        apply(&list, print_text, &sf);
    } else if (strcmp(argv[3], "count") == 0) {
        int len = 0;
        apply(&list, count, &len);
        printf("%d\n", len);
    }
    
    remove_all_points(&list);
    free(list.head);
    return 0;
}
