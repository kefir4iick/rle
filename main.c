#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rle.h"

static void usage(const char *prog) {
    fprintf(stderr,
        "usage:\n"
        "  %s -e input [output]\n"
        "  %s -d input output\n",
        prog, prog);
    exit(1);
} // на всякий

int main(int argc, char **argv) {
    if (argc < 3)
        usage(argv[0]);

    FILE *in = fopen(argv[2], "rb");
    if (!in) {
        perror("input");
        return 1;
    }

    if (strcmp(argv[1], "-e") == 0) {
        char outname[1024];

        if (argc >= 4)
            strcpy(outname, argv[3]);
        else
            snprintf(outname, sizeof(outname), "%s.rle", argv[2]);

        FILE *out = fopen(outname, "wb");
        if (!out) {
            perror("output");
            return 1;
        }

        rle_encode(in, out);
        fclose(out);

    } else if (strcmp(argv[1], "-d") == 0) {
        if (argc != 4)
            usage(argv[0]);

        FILE *out = fopen(argv[3], "wb");
        if (!out) {
            perror("output");
            return 1;
        }

        rle_decode(in, out);
        fclose(out);

    } else {
        usage(argv[0]);
    }

    fclose(in);
    return 0;
}
