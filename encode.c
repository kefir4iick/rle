#include "rle.h"

#define MAX_RUN 129
#define MAX_RAW 128

void rle_encode(FILE *in, FILE *out) {
    unsigned char raw[MAX_RAW];
    int raw_len = 0;

    int prev = fgetc(in);
    if (prev == EOF) return;

    int run_len = 1;

    while (1) {
        int c = fgetc(in);

        if (c == prev && run_len < MAX_RUN) {
            run_len++;
        } else {
            if (run_len >= 2) {
                if (raw_len > 0) {
                    fputc(raw_len - 1, out);
                    fwrite(raw, 1, raw_len, out);
                    raw_len = 0;
                }
                fputc(128 + run_len - 2, out);
                fputc(prev, out);
            } else {
                raw[raw_len++] = prev;
                if (raw_len == MAX_RAW) {
                    fputc(raw_len - 1, out);
                    fwrite(raw, 1, raw_len, out);
                    raw_len = 0;
                }
            }
            run_len = 1;
        }

        if (c == EOF)
            break;

        prev = c;
    }

    if (raw_len > 0) {
        fputc(raw_len - 1, out);
        fwrite(raw, 1, raw_len, out);
    }
}
