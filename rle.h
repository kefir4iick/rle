#ifndef RLE_H
#define RLE_H

#include <stdio.h>

void rle_encode(FILE *in, FILE *out);
void rle_decode(FILE *in, FILE *out);

#endif
