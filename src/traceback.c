#include "config.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parasail.h"
#include "parasail/memory.h"

static inline int weight(
        const char a,
        const char b,
        const parasail_matrix_t *matrix)
{
    return matrix->matrix[matrix->mapper[(unsigned char)a]*matrix->size + matrix->mapper[(unsigned char)b]];
}

static inline char match_char(
        const char a,
        const char b,
        const parasail_matrix_t *matrix)
{
    if (a == b) {
        return '|';
    }
    else {
        int sub = weight(a, b, matrix);
        if (sub > 0) {
            return ':';
        }
        else {
            return '.';
        }
    }

    return 'X'; /* shouldn't happen */
}

#define CONCAT_(X, Y) X##Y
#define CONCAT(X, Y) CONCAT_(X, Y)
#define CONCAT3_(X, Y, Z) X##Y##Z
#define CONCAT3(X, Y, Z) CONCAT3_(X, Y, Z)
#define LOC_NOVEC int loc = i*lenb + j;
#define LOC_STRIPED int loc = j*segLen*segWidth + (i%segLen)*segWidth + (i/segLen);

#define T 8
#include "traceback_template.c"
#undef T

#define T 8
#define STRIPED
#include "traceback_template.c"
#undef T
#undef STRIPED

#define T 16
#include "traceback_template.c"
#undef T

#define T 16
#define STRIPED
#include "traceback_template.c"
#undef T
#undef STRIPED

#define T 32
#include "traceback_template.c"
#undef T

#define T 32
#define STRIPED
#include "traceback_template.c"
#undef T
#undef STRIPED

#define T 64
#include "traceback_template.c"
#undef T

#define T 64
#define STRIPED
#include "traceback_template.c"
#undef T
#undef STRIPED

void parasail_traceback(
        const char *seqA,
        int lena,
        const char *seqB,
        int lenb,
        const parasail_matrix_t *matrix,
        parasail_result_t *result)
{
    if (result->flag & PARASAIL_FLAG_STRIPED) {
        if (result->flag & PARASAIL_FLAG_BITS_8) {
            parasail_traceback_striped_8(seqA, lena, seqB, lenb, matrix, result);
        }
        else if (result->flag & PARASAIL_FLAG_BITS_16) {
            parasail_traceback_striped_16(seqA, lena, seqB, lenb, matrix, result);
        }
        else if (result->flag & PARASAIL_FLAG_BITS_32) {
            parasail_traceback_striped_32(seqA, lena, seqB, lenb, matrix, result);
        }
        else if (result->flag & PARASAIL_FLAG_BITS_64) {
            parasail_traceback_striped_64(seqA, lena, seqB, lenb, matrix, result);
        }
    }
    else {
        if (result->flag & PARASAIL_FLAG_BITS_8) {
            parasail_traceback_8(seqA, lena, seqB, lenb, matrix, result);
        }
        else if (result->flag & PARASAIL_FLAG_BITS_16) {
            parasail_traceback_16(seqA, lena, seqB, lenb, matrix, result);
        }
        else if (result->flag & PARASAIL_FLAG_BITS_32) {
            parasail_traceback_32(seqA, lena, seqB, lenb, matrix, result);
        }
        else if (result->flag & PARASAIL_FLAG_BITS_64) {
            parasail_traceback_64(seqA, lena, seqB, lenb, matrix, result);
        }
    }
}
