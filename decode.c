#include "rle.h"
#include <stdlib.h>
#include <stdio.h>

static void decode_error(const char *msg) {
    fprintf(stderr, "decode error: %s\n", msg);
    exit(1);
}

void rle_decode(FILE *in, FILE *out) {
    int L;

    while ((L = fgetc(in)) != EOF) {
        if (L & 0x80) {
            int len = (L & 0x7F) + 2;
            int v = fgetc(in);
            if (v == EOF)
                decode_error("unexpected EOF in run block");

            for (int i = 0; i < len; i++)
                fputc(v, out);
        } else {
            int len = (L & 0x7F) + 1;
            for (int i = 0; i < len; i++) {
                int v = fgetc(in);
                if (v == EOF)
                    decode_error("unexpected EOF in raw block"); 
                fputc(v, out);
            }
        }
    }
}
