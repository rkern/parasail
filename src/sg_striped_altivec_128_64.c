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



#include "parasail.h"
#include "parasail/memory.h"
#include "parasail/internal_altivec.h"



#ifdef PARASAIL_TABLE
static inline void arr_store_si128(
        int *array,
        vec128i vH,
        int32_t t,
        int32_t seglen,
        int32_t d,
        int32_t dlen)
{
    array[(0*seglen+t)*dlen + d] = (int64_t)_mm_extract_epi64(vH, 0);
    array[(1*seglen+t)*dlen + d] = (int64_t)_mm_extract_epi64(vH, 1);
}
#endif

#ifdef PARASAIL_ROWCOL
static inline void arr_store_col(
        int *col,
        vec128i vH,
        int32_t t,
        int32_t seglen)
{
    col[0*seglen+t] = (int64_t)_mm_extract_epi64(vH, 0);
    col[1*seglen+t] = (int64_t)_mm_extract_epi64(vH, 1);
}
#endif

#ifdef PARASAIL_TABLE
#define FNAME parasail_sg_table_striped_altivec_128_64
#define PNAME parasail_sg_table_striped_profile_altivec_128_64
#else
#ifdef PARASAIL_ROWCOL
#define FNAME parasail_sg_rowcol_striped_altivec_128_64
#define PNAME parasail_sg_rowcol_striped_profile_altivec_128_64
#else
#define FNAME parasail_sg_striped_altivec_128_64
#define PNAME parasail_sg_striped_profile_altivec_128_64
#endif
#endif

parasail_result_t* FNAME(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap, const parasail_matrix_t *matrix)
{
    parasail_profile_t *profile = parasail_profile_create_altivec_128_64(s1, s1Len, matrix);
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
    vec128i* const restrict vProfile = (vec128i*)profile->profile64.score;
    vec128i* restrict pvHStore = parasail_memalign_vec128i(16, segLen);
    vec128i* restrict pvHLoad =  parasail_memalign_vec128i(16, segLen);
    vec128i* const restrict pvE = parasail_memalign_vec128i(16, segLen);
    const vec128i vGapO = _mm_set1_epi64(open);
    const vec128i vGapE = _mm_set1_epi64(gap);
    const int64_t NEG_LIMIT = (-open < matrix->min ?
        INT64_MIN + open : INT64_MIN - matrix->min) + 1;
    const int64_t POS_LIMIT = INT64_MAX - matrix->max - 1;
    int64_t score = NEG_LIMIT;
    vec128i vNegLimit = _mm_set1_epi64(NEG_LIMIT);
    vec128i vPosLimit = _mm_set1_epi64(POS_LIMIT);
    vec128i vSaturationCheckMin = vPosLimit;
    vec128i vSaturationCheckMax = vNegLimit;
    vec128i vMaxH = vNegLimit;
    vec128i vPosMask = _mm_cmpeq_epi64(_mm_set1_epi64(position),
            _mm_set_epi64(0,1));
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
    parasail_memset_vec128i(pvHStore, _mm_set1_epi64(0), segLen);
    parasail_memset_vec128i(pvE, _mm_set1_epi64(-open), segLen);

    /* outer loop over database sequence */
    for (j=0; j<s2Len; ++j) {
        vec128i vE;
        /* Initialize F value to -inf.  Any errors to vH values will be
         * corrected in the Lazy_F loop.  */
        vec128i vF = vNegLimit;

        /* load final segment of pvHStore and shift left by 2 bytes */
        vec128i vH = _mm_slli_si128(pvHStore[segLen - 1], 8);

        /* Correct part of the vProfile */
        const vec128i* vP = vProfile + matrix->mapper[(unsigned char)s2[j]] * segLen;

        /* Swap the 2 H buffers. */
        vec128i* pv = pvHLoad;
        pvHLoad = pvHStore;
        pvHStore = pv;

        /* inner loop to process the query sequence */
        for (i=0; i<segLen; ++i) {
            vH = _mm_add_epi64(vH, _mm_load_si128(vP + i));
            vE = _mm_load_si128(pvE + i);

            /* Get max from vH, vE and vF. */
            vH = _mm_max_epi64(vH, vE);
            vH = _mm_max_epi64(vH, vF);
            /* Save vH values. */
            _mm_store_si128(pvHStore + i, vH);
            vSaturationCheckMin = _mm_min_epi64(vSaturationCheckMin, vH);
            vSaturationCheckMax = _mm_max_epi64(vSaturationCheckMax, vH);
#ifdef PARASAIL_TABLE
            arr_store_si128(result->tables->score_table, vH, i, segLen, j, s2Len);
#endif

            /* Update vE value. */
            vH = _mm_sub_epi64(vH, vGapO);
            vE = _mm_sub_epi64(vE, vGapE);
            vE = _mm_max_epi64(vE, vH);
            _mm_store_si128(pvE + i, vE);

            /* Update vF value. */
            vF = _mm_sub_epi64(vF, vGapE);
            vF = _mm_max_epi64(vF, vH);

            /* Load the next vH. */
            vH = _mm_load_si128(pvHLoad + i);
        }

        /* Lazy_F loop: has been revised to disallow adjecent insertion and
         * then deletion, so don't update E(i, i), learn from SWPS3 */
        for (k=0; k<segWidth; ++k) {
            vF = _mm_slli_si128(vF, 8);
            vF = _mm_insert_epi64(vF, -open, 0);
            for (i=0; i<segLen; ++i) {
                vH = _mm_load_si128(pvHStore + i);
                vH = _mm_max_epi64(vH,vF);
                _mm_store_si128(pvHStore + i, vH);
                vSaturationCheckMin = _mm_min_epi64(vSaturationCheckMin, vH);
                vSaturationCheckMax = _mm_max_epi64(vSaturationCheckMax, vH);
#ifdef PARASAIL_TABLE
                arr_store_si128(result->tables->score_table, vH, i, segLen, j, s2Len);
#endif
                vH = _mm_sub_epi64(vH, vGapO);
                vF = _mm_sub_epi64(vF, vGapE);
                if (! _mm_movemask_epi8(_mm_cmpgt_epi64(vF, vH))) goto end;
                /*vF = _mm_max_epi64(vF, vH);*/
            }
        }
end:
        {
            /* extract vector containing last value from the column */
            vec128i vCompare;
            vH = _mm_load_si128(pvHStore + offset);
            vCompare = _mm_and_si128(vPosMask, _mm_cmpgt_epi64(vH, vMaxH));
            vMaxH = _mm_max_epi64(vH, vMaxH);
            if (_mm_movemask_epi8(vCompare)) {
                end_ref = j;
                end_query = s1Len - 1;
            }
#ifdef PARASAIL_ROWCOL
            for (k=0; k<position; ++k) {
                vH = _mm_slli_si128(vH, 8);
            }
            result->rowcols->score_row[j] = (int64_t) _mm_extract_epi64 (vH, 1);
#endif
        }
    }

    /* max last value from all columns */
    {
        for (k=0; k<position; ++k) {
            vMaxH = _mm_slli_si128(vMaxH, 8);
        }
        score = (int64_t) _mm_extract_epi64(vMaxH, 1);
    }

    /* max of last column */
    {
        int64_t score_last;
        vMaxH = vNegLimit;

        for (i=0; i<segLen; ++i) {
            vec128i vH = _mm_load_si128(pvHStore + i);
            vMaxH = _mm_max_epi64(vH, vMaxH);
#ifdef PARASAIL_ROWCOL
            arr_store_col(result->rowcols->score_col, vH, i, segLen);
#endif
        }

        /* max in vec */
        score_last = _mm_hmax_epi64(vMaxH);
        if (score_last > score || (score_last == score && end_ref == s2Len - 1)) {
            score = score_last;
            end_ref = s2Len - 1;
            end_query = s1Len;
            /* Trace the alignment ending position on read. */
            {
                int64_t *t = (int64_t*)pvHStore;
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
            _mm_cmplt_epi64(vSaturationCheckMin, vNegLimit),
            _mm_cmpgt_epi64(vSaturationCheckMax, vPosLimit)))) {
        result->flag |= PARASAIL_FLAG_SATURATED;
        score = 0;
        end_query = 0;
        end_ref = 0;
    }

    result->score = score;
    result->end_query = end_query;
    result->end_ref = end_ref;
    result->flag |= PARASAIL_FLAG_SG | PARASAIL_FLAG_STRIPED
        | PARASAIL_FLAG_BITS_64 | PARASAIL_FLAG_LANES_2;
#ifdef PARASAIL_TABLE
    result->flag |= PARASAIL_FLAG_TABLE;
#endif
#ifdef PARASAIL_ROWCOL
    result->flag |= PARASAIL_FLAG_ROWCOL;
#endif

    parasail_free(pvE);
    parasail_free(pvHLoad);
    parasail_free(pvHStore);

    return result;
}

