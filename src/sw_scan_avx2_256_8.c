/**
 * @file
 *
 * @author jeff.daily@pnnl.gov
 *
 * Copyright (c) 2014 Battelle Memorial Institute.
 *
 * All rights reserved. No warranty, explicit or implicit, provided.
 */
#include "config.h"

#include <stdint.h>
#include <stdlib.h>

#include <immintrin.h>

#include "parasail.h"
#include "parasail/memory.h"
#include "parasail/internal_avx.h"
#include "parasail/matrices/blosum_map.h"

#define NEG_INF INT8_MIN

#define _mm256_rlli_si256_rpl(a,imm) _mm256_alignr_epi8(a, _mm256_permute2x128_si256(a, a, _MM_SHUFFLE(0,0,0,1)), 16-imm)

#define _mm256_slli_si256_rpl(a,imm) _mm256_alignr_epi8(a, _mm256_permute2x128_si256(a, a, _MM_SHUFFLE(0,0,3,0)), 16-imm)


#ifdef PARASAIL_TABLE
static inline void arr_store_si256(
        int *array,
        __m256i vH,
        int32_t t,
        int32_t seglen,
        int32_t d,
        int32_t dlen)
{
    array[( 0*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH,  0);
    array[( 1*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH,  1);
    array[( 2*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH,  2);
    array[( 3*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH,  3);
    array[( 4*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH,  4);
    array[( 5*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH,  5);
    array[( 6*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH,  6);
    array[( 7*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH,  7);
    array[( 8*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH,  8);
    array[( 9*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH,  9);
    array[(10*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 10);
    array[(11*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 11);
    array[(12*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 12);
    array[(13*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 13);
    array[(14*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 14);
    array[(15*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 15);
    array[(16*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 16);
    array[(17*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 17);
    array[(18*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 18);
    array[(19*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 19);
    array[(20*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 20);
    array[(21*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 21);
    array[(22*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 22);
    array[(23*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 23);
    array[(24*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 24);
    array[(25*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 25);
    array[(26*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 26);
    array[(27*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 27);
    array[(28*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 28);
    array[(29*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 29);
    array[(30*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 30);
    array[(31*seglen+t)*dlen + d] = (int8_t)_mm256_extract_epi8(vH, 31);
}
#endif

#ifdef PARASAIL_TABLE
#define FNAME sw_table_scan_avx2_256_8
#else
#define FNAME sw_scan_avx2_256_8
#endif

parasail_result_t* FNAME(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap, const parasail_matrix_t *matrix)
{
    int32_t i = 0;
    int32_t j = 0;
    int32_t k = 0;
    int32_t segNum = 0;
    const int32_t n = 24; /* number of amino acids in table */
    const int32_t segWidth = 32; /* number of values in vector unit */
    const int32_t segLen = (s1Len + segWidth - 1) / segWidth;
    __m256i* const restrict pvP = parasail_memalign___m256i(32, n * segLen);
    __m256i* const restrict pvE = parasail_memalign___m256i(32, segLen);
    __m256i* const restrict pvHt= parasail_memalign___m256i(32, segLen);
    __m256i* const restrict pvH = parasail_memalign___m256i(32, segLen);
    __m256i vGapO = _mm256_set1_epi8(open);
    __m256i vGapE = _mm256_set1_epi8(gap);
    __m256i vNegInf = _mm256_set1_epi8(NEG_INF);
    __m256i vZero = _mm256_setzero_si256();
    int8_t score = NEG_INF;
    __m256i vMaxH = vNegInf;
    const int8_t segLenXgap = -segLen*gap;
    __m256i insert_mask = _mm256_cmpeq_epi8(vZero,
            _mm256_set_epi8(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0));
    __m256i vSegLenXgap1 = _mm256_set1_epi8((segLen-1)*gap);
    __m256i vSegLenXgap = _mm256_blendv_epi8(vNegInf,
            _mm256_set1_epi8(segLenXgap),
            insert_mask);
    __m256i vNegLimit = _mm256_set1_epi8(INT8_MIN);
    __m256i vPosLimit = _mm256_set1_epi8(INT8_MAX);
    __m256i vSaturationCheckMin = vPosLimit;
    __m256i vSaturationCheckMax = vNegLimit;
#ifdef PARASAIL_TABLE
    parasail_result_t *result = parasail_result_new_table1(segLen*segWidth, s2Len);
#else
    parasail_result_t *result = parasail_result_new();
#endif

    /* Generate query profile.
     * Rearrange query sequence & calculate the weight of match/mismatch.
     * Don't alias. */
    {
        int32_t index = 0;
        for (k=0; k<n; ++k) {
            for (i=0; i<segLen; ++i) {
                __m256i_8_t t;
                j = i;
                for (segNum=0; segNum<segWidth; ++segNum) {
                    t.v[segNum] = j >= s1Len ? 0 : matrix->matrix[matrix->size*k+parasail_blosum_map[(unsigned char)s1[j]]];
                    j += segLen;
                }
                _mm256_store_si256(&pvP[index], t.m);
                ++index;
            }
        }
    }

    /* initialize H and E */
    {
        int32_t index = 0;
        for (i=0; i<segLen; ++i) {
            __m256i_8_t h;
            __m256i_8_t e;
            for (segNum=0; segNum<segWidth; ++segNum) {
                h.v[segNum] = 0;
                e.v[segNum] = NEG_INF;
            }
            _mm256_store_si256(&pvH[index], h.m);
            _mm256_store_si256(&pvE[index], e.m);
            ++index;
        }
    }

    /* outer loop over database sequence */
    for (j=0; j<s2Len; ++j) {
        __m256i vE;
        __m256i vHt;
        __m256i vFt;
        __m256i vH;
        __m256i vHp;
        __m256i *pvW;
        __m256i vW;

        /* calculate E */
        /* calculate Ht */
        /* calculate Ft first pass */
        vHp = _mm256_load_si256(pvH+(segLen-1));
        vHp = _mm256_slli_si256_rpl(vHp, 1);
        pvW = pvP + parasail_blosum_map[(unsigned char)s2[j]]*segLen;
        vHt = vNegInf;
        vFt = vNegInf;
        for (i=0; i<segLen; ++i) {
            vH = _mm256_load_si256(pvH+i);
            vE = _mm256_load_si256(pvE+i);
            vW = _mm256_load_si256(pvW+i);
            vE = _mm256_max_epi8(
                    _mm256_subs_epi8(vE, vGapE),
                    _mm256_subs_epi8(vH, vGapO));
            vFt = _mm256_subs_epi8(vFt, vGapE);
            vFt = _mm256_max_epi8(vFt, vHt);
            vHt = _mm256_max_epi8(
                    _mm256_adds_epi8(vHp, vW),
                    vE);
            _mm256_store_si256(pvE+i, vE);
            _mm256_store_si256(pvHt+i, vHt);
            vHp = vH;
        }

        /* adjust Ft before local prefix scan */
        vHt = _mm256_slli_si256_rpl(vHt, 1);
        vFt = _mm256_max_epi8(vFt,
                _mm256_subs_epi8(vHt, vSegLenXgap1));
        /* local prefix scan */
        vFt = _mm256_blendv_epi8(vNegInf, vFt, insert_mask);
        for (i=0; i<segWidth-1; ++i) {
                __m256i vFtt = _mm256_rlli_si256_rpl(vFt, 1);
                vFtt = _mm256_adds_epi8(vFtt, vSegLenXgap);
                vFt = _mm256_max_epi8(vFt, vFtt);
        }
        vFt = _mm256_rlli_si256_rpl(vFt, 1);

        /* second Ft pass */
        /* calculate vH */
        for (i=0; i<segLen; ++i) {
            vFt = _mm256_subs_epi8(vFt, vGapE);
            vFt = _mm256_max_epi8(vFt, vHt);
            vHt = _mm256_load_si256(pvHt+i);
            vH = _mm256_max_epi8(vHt, _mm256_subs_epi8(vFt, vGapO));
            vH = _mm256_max_epi8(vH, vZero);
            _mm256_store_si256(pvH+i, vH);
            /* check for saturation */
            {
                vSaturationCheckMax = _mm256_max_epi8(vSaturationCheckMax, vH);
                vSaturationCheckMin = _mm256_min_epi8(vSaturationCheckMin, vH);
            }
#ifdef PARASAIL_TABLE
            arr_store_si256(result->score_table, vH, i, segLen, j, s2Len);
#endif
            vMaxH = _mm256_max_epi8(vH, vMaxH);
        }
    }

    /* max in vec */
    for (j=0; j<segWidth; ++j) {
        int8_t value = (int8_t) _mm256_extract_epi8(vMaxH, 31);
        if (value > score) {
            score = value;
        }
        vMaxH = _mm256_slli_si256_rpl(vMaxH, 1);
    }

    if (_mm256_movemask_epi8(_mm256_or_si256(
            _mm256_cmpeq_epi8(vSaturationCheckMin, vNegLimit),
            _mm256_cmpeq_epi8(vSaturationCheckMax, vPosLimit)))) {
        result->saturated = 1;
        score = INT8_MAX;
    }

    result->score = score;

    parasail_free(pvH);
    parasail_free(pvHt);
    parasail_free(pvE);
    parasail_free(pvP);

    return result;
}

