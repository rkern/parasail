/**
 * @file
 *
 * @author jeff.daily@pnnl.gov
 *
 * Copyright (c) 2015 Battelle Memorial Institute.
 */
#include "config.h"

#include <stdint.h>
#include <stdlib.h>

#if defined(_MSC_VER)
#include <intrin.h>
#else
#include <emmintrin.h>
#endif

#include "parasail.h"
#include "parasail/memory.h"
#include "parasail/internal_sse.h"


static inline __m128i _mm_cmpgt_epi64_rpl(__m128i a, __m128i b) {
    __m128i_64_t A;
    __m128i_64_t B;
    A.m = a;
    B.m = b;
    A.v[0] = (A.v[0]>B.v[0]) ? 0xFFFFFFFFFFFFFFFF : 0;
    A.v[1] = (A.v[1]>B.v[1]) ? 0xFFFFFFFFFFFFFFFF : 0;
    return A.m;
}

static inline __m128i _mm_cmpeq_epi64_rpl(__m128i a, __m128i b) {
    __m128i_64_t A;
    __m128i_64_t B;
    A.m = a;
    B.m = b;
    A.v[0] = (A.v[0]==B.v[0]) ? 0xFFFFFFFFFFFFFFFF : 0;
    A.v[1] = (A.v[1]==B.v[1]) ? 0xFFFFFFFFFFFFFFFF : 0;
    return A.m;
}

static inline __m128i _mm_max_epi64_rpl(__m128i a, __m128i b) {
    __m128i_64_t A;
    __m128i_64_t B;
    A.m = a;
    B.m = b;
    A.v[0] = (A.v[0]>B.v[0]) ? A.v[0] : B.v[0];
    A.v[1] = (A.v[1]>B.v[1]) ? A.v[1] : B.v[1];
    return A.m;
}

#if HAVE_SSE2_MM_SET_EPI64X
#define _mm_set_epi64x_rpl _mm_set_epi64x
#else
static inline __m128i _mm_set_epi64x_rpl(int64_t e1, int64_t e0) {
    __m128i_64_t A;
    A.v[0] = e0;
    A.v[1] = e1;
    return A.m;
}
#endif

static inline int64_t _mm_extract_epi64_rpl(__m128i a, const int imm) {
    __m128i_64_t A;
    A.m = a;
    return A.v[imm];
}

static inline __m128i _mm_min_epi64_rpl(__m128i a, __m128i b) {
    __m128i_64_t A;
    __m128i_64_t B;
    A.m = a;
    B.m = b;
    A.v[0] = (A.v[0]<B.v[0]) ? A.v[0] : B.v[0];
    A.v[1] = (A.v[1]<B.v[1]) ? A.v[1] : B.v[1];
    return A.m;
}

static inline __m128i _mm_cmplt_epi64_rpl(__m128i a, __m128i b) {
    __m128i_64_t A;
    __m128i_64_t B;
    A.m = a;
    B.m = b;
    A.v[0] = (A.v[0]<B.v[0]) ? 0xFFFFFFFFFFFFFFFF : 0;
    A.v[1] = (A.v[1]<B.v[1]) ? 0xFFFFFFFFFFFFFFFF : 0;
    return A.m;
}

#if HAVE_SSE2_MM_SET1_EPI64X
#define _mm_set1_epi64x_rpl _mm_set1_epi64x
#else
static inline __m128i _mm_set1_epi64x_rpl(int64_t i) {
    __m128i_64_t A;
    A.v[0] = i;
    A.v[1] = i;
    return A.m;
}
#endif

static inline int64_t _mm_hmax_epi64_rpl(__m128i a) {
    a = _mm_max_epi64_rpl(a, _mm_srli_si128(a, 8));
    return _mm_extract_epi64_rpl(a, 0);
}


#ifdef PARASAIL_TABLE
static inline void arr_store_si128(
        int *array,
        __m128i vH,
        int32_t t,
        int32_t seglen,
        int32_t d,
        int32_t dlen)
{
    array[(0*seglen+t)*dlen + d] = (int64_t)_mm_extract_epi64_rpl(vH, 0);
    array[(1*seglen+t)*dlen + d] = (int64_t)_mm_extract_epi64_rpl(vH, 1);
}
#endif

#ifdef PARASAIL_ROWCOL
static inline void arr_store_col(
        int *col,
        __m128i vH,
        int32_t t,
        int32_t seglen)
{
    col[0*seglen+t] = (int64_t)_mm_extract_epi64_rpl(vH, 0);
    col[1*seglen+t] = (int64_t)_mm_extract_epi64_rpl(vH, 1);
}
#endif

#ifdef PARASAIL_TABLE
#define FNAME parasail_sg_table_scan_sse2_128_64
#define PNAME parasail_sg_table_scan_profile_sse2_128_64
#else
#ifdef PARASAIL_ROWCOL
#define FNAME parasail_sg_rowcol_scan_sse2_128_64
#define PNAME parasail_sg_rowcol_scan_profile_sse2_128_64
#else
#define FNAME parasail_sg_scan_sse2_128_64
#define PNAME parasail_sg_scan_profile_sse2_128_64
#endif
#endif

parasail_result_t* FNAME(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap, const parasail_matrix_t *matrix)
{
    parasail_profile_t *profile = parasail_profile_create_sse_128_64(s1, s1Len, matrix);
    parasail_result_t *result = PNAME(profile, s2, s2Len, open, gap);
    parasail_profile_free(profile);
    return result;
}

parasail_result_t* PNAME(
        const parasail_profile_t * const restrict profile,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap)
{
    int32_t i = 0;
    int32_t j = 0;
    int32_t k = 0;
    int32_t end_query = 0;
    int32_t end_ref = 0;
    const int s1Len = profile->s1Len;
    const parasail_matrix_t *matrix = profile->matrix;
    const int32_t segWidth = 2; /* number of values in vector unit */
    const int32_t segLen = (s1Len + segWidth - 1) / segWidth;
    const int32_t offset = (s1Len - 1) % segLen;
    const int32_t position = (segWidth - 1) - (s1Len - 1) / segLen;
    __m128i* const restrict pvP = (__m128i*)profile->profile64.score;
    __m128i* const restrict pvE = parasail_memalign___m128i(16, segLen);
    __m128i* const restrict pvHt= parasail_memalign___m128i(16, segLen);
    __m128i* const restrict pvH = parasail_memalign___m128i(16, segLen);
    __m128i* const restrict pvGapper = parasail_memalign___m128i(16, segLen);
    __m128i vGapO = _mm_set1_epi64x_rpl(open);
    __m128i vGapE = _mm_set1_epi64x_rpl(gap);
    const int64_t NEG_LIMIT = (-open < matrix->min ?
        INT64_MIN + open : INT64_MIN - matrix->min) + 1;
    const int64_t POS_LIMIT = INT64_MAX - matrix->max - 1;
    __m128i vZero = _mm_setzero_si128();
    int64_t score = NEG_LIMIT;
    __m128i vNegLimit = _mm_set1_epi64x_rpl(NEG_LIMIT);
    __m128i vPosLimit = _mm_set1_epi64x_rpl(POS_LIMIT);
    __m128i vSaturationCheckMin = vPosLimit;
    __m128i vSaturationCheckMax = vNegLimit;
    __m128i vMaxH = vNegLimit;
    __m128i vPosMask = _mm_cmpeq_epi64_rpl(_mm_set1_epi64x_rpl(position),
            _mm_set_epi64x_rpl(0,1));
    __m128i vNegInfFront = _mm_set_epi64x_rpl(0,NEG_LIMIT);
    __m128i vSegLenXgap = _mm_add_epi64(vNegInfFront,
            _mm_slli_si128(_mm_set1_epi64x_rpl(-segLen*gap), 8));
#ifdef PARASAIL_TABLE
    parasail_result_t *result = parasail_result_new_table1(segLen*segWidth, s2Len);
#else
#ifdef PARASAIL_ROWCOL
    parasail_result_t *result = parasail_result_new_rowcol1(segLen*segWidth, s2Len);
#else
    parasail_result_t *result = parasail_result_new();
#endif
#endif

    /* initialize H and E */
    parasail_memset___m128i(pvH, vZero, segLen);
    parasail_memset___m128i(pvE, vNegLimit, segLen);
    {
        __m128i vGapper = _mm_sub_epi64(vZero,vGapO);
        for (i=segLen-1; i>=0; --i) {
            _mm_store_si128(pvGapper+i, vGapper);
            vGapper = _mm_sub_epi64(vGapper, vGapE);
        }
    }

    /* outer loop over database sequence */
    for (j=0; j<s2Len; ++j) {
        __m128i vE;
        __m128i vHt;
        __m128i vF;
        __m128i vH;
        __m128i vHp;
        __m128i *pvW;
        __m128i vW;

        /* calculate E */
        /* calculate Ht */
        /* calculate F and H first pass */
        vHp = _mm_load_si128(pvH+(segLen-1));
        vHp = _mm_slli_si128(vHp, 8);
        pvW = pvP + matrix->mapper[(unsigned char)s2[j]]*segLen;
        vHt = _mm_sub_epi64(vNegLimit, pvGapper[0]);
        vF = vNegLimit;
        for (i=0; i<segLen; ++i) {
            vH = _mm_load_si128(pvH+i);
            vE = _mm_load_si128(pvE+i);
            vW = _mm_load_si128(pvW+i);
            vE = _mm_max_epi64_rpl(
                    _mm_sub_epi64(vE, vGapE),
                    _mm_sub_epi64(vH, vGapO));
            vHp = _mm_add_epi64(vHp, vW);
            vF = _mm_max_epi64_rpl(vF, _mm_add_epi64(vHt, pvGapper[i]));
            vHt = _mm_max_epi64_rpl(vE, vHp);
            _mm_store_si128(pvE+i, vE);
            _mm_store_si128(pvHt+i, vHt);
            vHp = vH;
        }

        /* pseudo prefix scan on F and H */
        vHt = _mm_slli_si128(vHt, 8);
        vF = _mm_max_epi64_rpl(vF, _mm_add_epi64(vHt, pvGapper[0]));
        for (i=0; i<segWidth-2; ++i) {
            __m128i vFt = _mm_slli_si128(vF, 8);
            vFt = _mm_add_epi64(vFt, vSegLenXgap);
            vF = _mm_max_epi64_rpl(vF, vFt);
        }

        /* calculate final H */
        vF = _mm_slli_si128(vF, 8);
        vF = _mm_add_epi64(vF, vNegInfFront);
        vH = _mm_max_epi64_rpl(vHt, vF);
        for (i=0; i<segLen; ++i) {
            vHt = _mm_load_si128(pvHt+i);
            vF = _mm_max_epi64_rpl(
                    _mm_sub_epi64(vF, vGapE),
                    _mm_sub_epi64(vH, vGapO));
            vH = _mm_max_epi64_rpl(vHt, vF);
            _mm_store_si128(pvH+i, vH);
            vSaturationCheckMin = _mm_min_epi64_rpl(vSaturationCheckMin, vH);
            vSaturationCheckMax = _mm_max_epi64_rpl(vSaturationCheckMax, vH);
#ifdef PARASAIL_TABLE
            arr_store_si128(result->tables->score_table, vH, i, segLen, j, s2Len);
#endif
        } 

        /* extract vector containing last value from column */
        {
            __m128i vCompare;
            vH = _mm_load_si128(pvH + offset);
            vCompare = _mm_and_si128(vPosMask, _mm_cmpgt_epi64_rpl(vH, vMaxH));
            vMaxH = _mm_max_epi64_rpl(vH, vMaxH);
            if (_mm_movemask_epi8(vCompare)) {
                end_ref = j;
                end_query = s1Len - 1;
            }
#ifdef PARASAIL_ROWCOL
            for (k=0; k<position; ++k) {
                vH = _mm_slli_si128(vH, 8);
            }
            result->rowcols->score_row[j] = (int64_t) _mm_extract_epi64_rpl (vH, 1);
#endif
        }
    }

    /* max last value from all columns */
    {
        int64_t value;
        for (k=0; k<position; ++k) {
            vMaxH = _mm_slli_si128(vMaxH, 8);
        }
        value = (int64_t) _mm_extract_epi64_rpl(vMaxH, 1);
        if (value > score) {
            score = value;
        }
    }

    /* max of last column */
    {
        int64_t score_last;
        vMaxH = vNegLimit;

        for (i=0; i<segLen; ++i) {
            __m128i vH = _mm_load_si128(pvH + i);
            vMaxH = _mm_max_epi64_rpl(vH, vMaxH);
#ifdef PARASAIL_ROWCOL
            arr_store_col(result->rowcols->score_col, vH, i, segLen);
#endif
        }

        /* max in vec */
        score_last = _mm_hmax_epi64_rpl(vMaxH);
        if (score_last > score || (score_last == score && end_ref == s2Len - 1)) {
            score = score_last;
            end_ref = s2Len - 1;
            end_query = s1Len;
            /* Trace the alignment ending position on read. */
            {
                int64_t *t = (int64_t*)pvH;
                int32_t column_len = segLen * segWidth;
                for (i = 0; i<column_len; ++i, ++t) {
                    if (*t == score) {
                        int32_t temp = i / segWidth + i % segWidth * segLen;
                        if (temp < end_query) {
                            end_query = temp;
                        }
                    }
                }
            }
        }
    }

    if (_mm_movemask_epi8(_mm_or_si128(
            _mm_cmplt_epi64_rpl(vSaturationCheckMin, vNegLimit),
            _mm_cmpgt_epi64_rpl(vSaturationCheckMax, vPosLimit)))) {
        result->flag |= PARASAIL_FLAG_SATURATED;
        score = 0;
        end_query = 0;
        end_ref = 0;
    }

    result->score = score;
    result->end_query = end_query;
    result->end_ref = end_ref;
    result->flag |= PARASAIL_FLAG_SG | PARASAIL_FLAG_SCAN
        | PARASAIL_FLAG_BITS_64 | PARASAIL_FLAG_LANES_2;
#ifdef PARASAIL_TABLE
    result->flag |= PARASAIL_FLAG_TABLE;
#endif
#ifdef PARASAIL_ROWCOL
    result->flag |= PARASAIL_FLAG_ROWCOL;
#endif

    parasail_free(pvGapper);
    parasail_free(pvH);
    parasail_free(pvHt);
    parasail_free(pvE);

    return result;
}


