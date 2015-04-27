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

#include <emmintrin.h>

#include "parasail.h"
#include "parasail/memory.h"
#include "parasail/internal_sse.h"
#include "parasail/matrices/blosum_map.h"

#define NEG_INF (INT64_MIN/(int64_t)(2))

static inline __m128i _mm_blendv_epi8_rpl(__m128i a, __m128i b, __m128i mask) {
    a = _mm_andnot_si128(mask, a);
    a = _mm_or_si128(a, _mm_and_si128(mask, b));
    return a;
}

static inline __m128i _mm_cmpgt_epi64_rpl(__m128i a, __m128i b) {
    __m128i_64_t A;
    __m128i_64_t B;
    A.m = a;
    B.m = b;
    A.v[0] = (A.v[0]>B.v[0]) ? 0xFFFFFFFFFFFFFFFF : 0;
    A.v[1] = (A.v[1]>B.v[1]) ? 0xFFFFFFFFFFFFFFFF : 0;
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

static inline int64_t _mm_extract_epi64_rpl(__m128i a, const int imm) {
    __m128i_64_t A;
    A.m = a;
    return A.v[imm];
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

static inline __m128i _mm_cmpeq_epi64_rpl(__m128i a, __m128i b) {
    __m128i_64_t A;
    __m128i_64_t B;
    A.m = a;
    B.m = b;
    A.v[0] = (A.v[0]==B.v[0]) ? 0xFFFFFFFFFFFFFFFF : 0;
    A.v[1] = (A.v[1]==B.v[1]) ? 0xFFFFFFFFFFFFFFFF : 0;
    return A.m;
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

#ifdef PARASAIL_TABLE
#define FNAME sw_stats_table_striped_sse2_128_64
#else
#define FNAME sw_stats_striped_sse2_128_64
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
    const int32_t segWidth = 2; /* number of values in vector unit */
    const int32_t segLen = (s1Len + segWidth - 1) / segWidth;
    __m128i* const restrict vProfile  = parasail_memalign___m128i(16, n * segLen);
    __m128i* const restrict vProfileM = parasail_memalign___m128i(16, n * segLen);
    __m128i* const restrict vProfileS = parasail_memalign___m128i(16, n * segLen);
    __m128i* restrict pvHStore        = parasail_memalign___m128i(16, segLen);
    __m128i* restrict pvHLoad         = parasail_memalign___m128i(16, segLen);
    __m128i* restrict pvHMStore       = parasail_memalign___m128i(16, segLen);
    __m128i* restrict pvHMLoad        = parasail_memalign___m128i(16, segLen);
    __m128i* restrict pvHSStore       = parasail_memalign___m128i(16, segLen);
    __m128i* restrict pvHSLoad        = parasail_memalign___m128i(16, segLen);
    __m128i* restrict pvHLStore       = parasail_memalign___m128i(16, segLen);
    __m128i* restrict pvHLLoad        = parasail_memalign___m128i(16, segLen);
    __m128i* restrict pvEStore        = parasail_memalign___m128i(16, segLen);
    __m128i* restrict pvELoad         = parasail_memalign___m128i(16, segLen);
    __m128i* const restrict pvEM      = parasail_memalign___m128i(16, segLen);
    __m128i* const restrict pvES      = parasail_memalign___m128i(16, segLen);
    __m128i* const restrict pvEL      = parasail_memalign___m128i(16, segLen);
    __m128i vGapO = _mm_set1_epi64x(open);
    __m128i vGapE = _mm_set1_epi64x(gap);
    __m128i vZero = _mm_setzero_si128();
    __m128i vOne = _mm_set1_epi64x(1);
    int64_t score = NEG_INF;
    int64_t matches = NEG_INF;
    int64_t similar = NEG_INF;
    int64_t length = NEG_INF;
    
    __m128i vMaxH = vZero;
    __m128i vMaxHM = vZero;
    __m128i vMaxHS = vZero;
    __m128i vMaxHL = vZero;
#ifdef PARASAIL_TABLE
    parasail_result_t *result = parasail_result_new_table3(segLen*segWidth, s2Len);
#else
    parasail_result_t *result = parasail_result_new();
#endif

    parasail_memset___m128i(pvHMStore, vZero, segLen);
    parasail_memset___m128i(pvHSStore, vZero, segLen);
    parasail_memset___m128i(pvHLStore, vZero, segLen);

    /* Generate query profile.
     * Rearrange query sequence & calculate the weight of match/mismatch.
     * Don't alias. */
    {
        int32_t index = 0;
        for (k=0; k<n; ++k) {
            for (i=0; i<segLen; ++i) {
                __m128i_64_t p;
                __m128i_64_t m;
                __m128i_64_t s;
                j = i;
                for (segNum=0; segNum<segWidth; ++segNum) {
                    p.v[segNum] = j >= s1Len ? 0 : matrix->matrix[matrix->size*k+parasail_blosum_map[(unsigned char)s1[j]]];
                    m.v[segNum] = j >= s1Len ? 0 : (k == parasail_blosum_map[(unsigned char)s1[j]]);
                    s.v[segNum] = p.v[segNum] > 0;
                    j += segLen;
                }
                _mm_store_si128(&vProfile[index], p.m);
                _mm_store_si128(&vProfileM[index], m.m);
                _mm_store_si128(&vProfileS[index], s.m);
                ++index;
            }
        }
    }

    /* initialize H and E */
    {
        int32_t index = 0;
        for (i=0; i<segLen; ++i) {
            __m128i_64_t h;
            __m128i_64_t e;
            for (segNum=0; segNum<segWidth; ++segNum) {
                h.v[segNum] = 0;
                e.v[segNum] = -open;
            }
            _mm_store_si128(&pvHStore[index], h.m);
            _mm_store_si128(&pvEStore[index], e.m);
            ++index;
        }
    }

    /* outer loop over database sequence */
    for (j=0; j<s2Len; ++j) {
        __m128i vE;
        __m128i vEM;
        __m128i vES;
        __m128i vEL;
        __m128i vF;
        __m128i vFM;
        __m128i vFS;
        __m128i vFL;
        __m128i vH;
        __m128i vHM;
        __m128i vHS;
        __m128i vHL;
        const __m128i* vP = NULL;
        const __m128i* vPM = NULL;
        const __m128i* vPS = NULL;
        __m128i* pv = NULL;

        /* Initialize F value to 0.  Any errors to vH values will be corrected
         * in the Lazy_F loop.  */
        vF = vZero;
        vFM = vZero;
        vFS = vZero;
        vFL = vZero;

        /* load final segment of pvHStore and shift left by 2 bytes */
        vH = _mm_slli_si128(pvHStore[segLen - 1], 8);
        vHM = _mm_slli_si128(pvHMStore[segLen - 1], 8);
        vHS = _mm_slli_si128(pvHSStore[segLen - 1], 8);
        vHL = _mm_slli_si128(pvHLStore[segLen - 1], 8);

        /* Correct part of the vProfile */
        vP = vProfile + parasail_blosum_map[(unsigned char)s2[j]] * segLen;
        vPM = vProfileM + parasail_blosum_map[(unsigned char)s2[j]] * segLen;
        vPS = vProfileS + parasail_blosum_map[(unsigned char)s2[j]] * segLen;

        /* Swap the 2 H buffers. */
        pv = pvHLoad;
        pvHLoad = pvHStore;
        pvHStore = pv;
        pv = pvHMLoad;
        pvHMLoad = pvHMStore;
        pvHMStore = pv;
        pv = pvHSLoad;
        pvHSLoad = pvHSStore;
        pvHSStore = pv;
        pv = pvHLLoad;
        pvHLLoad = pvHLStore;
        pvHLStore = pv;
        pv = pvELoad;
        pvELoad = pvEStore;
        pvEStore = pv;

        /* inner loop to process the query sequence */
        for (i=0; i<segLen; ++i) {
            __m128i case1not;
            __m128i case2not;
            __m128i case2;
            __m128i case3;
            __m128i cond_zero;

            vH = _mm_add_epi64(vH, _mm_load_si128(vP + i));
            vE = _mm_load_si128(pvELoad + i);

            /* determine which direction of length and match to
             * propagate, before vH is finished calculating */
            case1not = _mm_or_si128(
                    _mm_cmplt_epi64_rpl(vH,vF),_mm_cmplt_epi64_rpl(vH,vE));
            case2not = _mm_cmplt_epi64_rpl(vF,vE);
            case2 = _mm_andnot_si128(case2not,case1not);
            case3 = _mm_and_si128(case1not,case2not);

            /* Get max from vH, vE and vF. */
            vH = _mm_max_epi64_rpl(vH, vE);
            vH = _mm_max_epi64_rpl(vH, vF);
            vH = _mm_max_epi64_rpl(vH, vZero);
            /* Save vH values. */
            _mm_store_si128(pvHStore + i, vH);
            cond_zero = _mm_cmpeq_epi64_rpl(vH, vZero);

            /* calculate vM */
            vEM = _mm_load_si128(pvEM + i);
            vHM = _mm_blendv_epi8_rpl(
                    _mm_add_epi64(vHM, _mm_load_si128(vPM + i)),
                    _mm_or_si128(
                        _mm_and_si128(case2, vFM),
                        _mm_and_si128(case3, vEM)),
                    case1not);
            vHM = _mm_andnot_si128(cond_zero, vHM);
            _mm_store_si128(pvHMStore + i, vHM);

            /* calculate vS */
            vES = _mm_load_si128(pvES + i);
            vHS = _mm_blendv_epi8_rpl(
                    _mm_add_epi64(vHS, _mm_load_si128(vPS + i)),
                    _mm_or_si128(
                        _mm_and_si128(case2, vFS),
                        _mm_and_si128(case3, vES)),
                    case1not);
            vHS = _mm_andnot_si128(cond_zero, vHS);
            _mm_store_si128(pvHSStore + i, vHS);

            /* calculate vL */
            vEL = _mm_load_si128(pvEL + i);
            vHL = _mm_blendv_epi8_rpl(
                    _mm_add_epi64(vHL, vOne),
                    _mm_or_si128(
                        _mm_and_si128(case2, _mm_add_epi64(vFL, vOne)),
                        _mm_and_si128(case3, _mm_add_epi64(vEL, vOne))),
                    case1not);
            vHL = _mm_andnot_si128(cond_zero, vHL);
            _mm_store_si128(pvHLStore + i, vHL);
            
#ifdef PARASAIL_TABLE
            arr_store_si128(result->matches_table, vHM, i, segLen, j, s2Len);
            arr_store_si128(result->similar_table, vHS, i, segLen, j, s2Len);
            arr_store_si128(result->length_table, vHL, i, segLen, j, s2Len);
            arr_store_si128(result->score_table, vH, i, segLen, j, s2Len);
#endif
            /* update max vector seen so far */
            {
                __m128i cond_max = _mm_cmpgt_epi64_rpl(vH, vMaxH);
                vMaxH = _mm_blendv_epi8_rpl(vMaxH, vH,  cond_max);
                vMaxHM = _mm_blendv_epi8_rpl(vMaxHM, vHM, cond_max);
                vMaxHS = _mm_blendv_epi8_rpl(vMaxHS, vHS, cond_max);
                vMaxHL = _mm_blendv_epi8_rpl(vMaxHL, vHL, cond_max);
            }

            /* Update vE value. */
            vH = _mm_sub_epi64(vH, vGapO);
            vE = _mm_sub_epi64(vE, vGapE);
            vE = _mm_max_epi64_rpl(vE, vH);
            _mm_store_si128(pvEStore + i, vE);
            _mm_store_si128(pvEM + i, vHM);
            _mm_store_si128(pvES + i, vHS);
            _mm_store_si128(pvEL + i, vHL);

            /* Update vF value. */
            vF = _mm_sub_epi64(vF, vGapE);
            vF = _mm_max_epi64_rpl(vF, vH);
            vFM = vHM;
            vFS = vHS;
            vFL = vHL;

            /* Load the next vH. */
            vH = _mm_load_si128(pvHLoad + i);
            vHM = _mm_load_si128(pvHMLoad + i);
            vHS = _mm_load_si128(pvHSLoad + i);
            vHL = _mm_load_si128(pvHLLoad + i);
        }

        /* Lazy_F loop: has been revised to disallow adjecent insertion and
         * then deletion, so don't update E(i, i), learn from SWPS3 */
        for (k=0; k<segWidth; ++k) {
            __m128i vHp = _mm_slli_si128(pvHLoad[segLen - 1], 8);
            vF = _mm_slli_si128(vF, 8);
            vFM = _mm_slli_si128(vFM, 8);
            vFS = _mm_slli_si128(vFS, 8);
            vFL = _mm_slli_si128(vFL, 8);
            for (i=0; i<segLen; ++i) {
                __m128i case1not;
                __m128i case2not;
                __m128i case2;
                __m128i cond_zero;

                /* need to know where match and length come from so
                 * recompute the cases as in the main loop */
                vHp = _mm_add_epi64(vHp, _mm_load_si128(vP + i));
                vE = _mm_load_si128(pvELoad + i);
                case1not = _mm_or_si128(
                        _mm_cmplt_epi64_rpl(vHp,vF),_mm_cmplt_epi64_rpl(vHp,vE));
                case2not = _mm_cmplt_epi64_rpl(vF,vE);
                case2 = _mm_andnot_si128(case2not,case1not);

                vH = _mm_load_si128(pvHStore + i);
                vH = _mm_max_epi64_rpl(vH,vF);
                _mm_store_si128(pvHStore + i, vH);
                cond_zero = _mm_cmpeq_epi64_rpl(vH, vZero);

                vHM = _mm_load_si128(pvHMStore + i);
                vHM = _mm_blendv_epi8_rpl(vHM, vFM, case2);
                vHM = _mm_andnot_si128(cond_zero, vHM);
                _mm_store_si128(pvHMStore + i, vHM);
                _mm_store_si128(pvEM + i, vHM);

                vHS = _mm_load_si128(pvHSStore + i);
                vHS = _mm_blendv_epi8_rpl(vHS, vFS, case2);
                vHS = _mm_andnot_si128(cond_zero, vHS);
                _mm_store_si128(pvHSStore + i, vHS);
                _mm_store_si128(pvES + i, vHS);

                vHL = _mm_load_si128(pvHLStore + i);
                vHL = _mm_blendv_epi8_rpl(vHL, _mm_add_epi64(vFL,vOne), case2);
                vHL = _mm_andnot_si128(cond_zero, vHL);
                _mm_store_si128(pvHLStore + i, vHL);
                _mm_store_si128(pvEL + i, vHL);

#ifdef PARASAIL_TABLE
                arr_store_si128(result->matches_table, vHM, i, segLen, j, s2Len);
                arr_store_si128(result->similar_table, vHS, i, segLen, j, s2Len);
                arr_store_si128(result->length_table, vHL, i, segLen, j, s2Len);
                arr_store_si128(result->score_table, vH, i, segLen, j, s2Len);
#endif
                vH = _mm_sub_epi64(vH, vGapO);
                vF = _mm_sub_epi64(vF, vGapE);
                if (! _mm_movemask_epi8(_mm_cmpgt_epi64_rpl(vF, vH))) goto end;
                /*vF = _mm_max_epi64_rpl(vF, vH);*/
                vFM = vHM;
                vFS = vHS;
                vFL = vHL;
                vHp = _mm_load_si128(pvHLoad + i);
            }
        }
end:
        {
        }
    }

    /* max in vec */
    for (j=0; j<segWidth; ++j) {
        int64_t value = (int64_t) _mm_extract_epi64_rpl(vMaxH, 1);
        if (value > score) {
            score = value;
            matches = (int64_t)_mm_extract_epi64_rpl(vMaxHM, 1);
            similar = (int64_t)_mm_extract_epi64_rpl(vMaxHS, 1);
            length = (int64_t)_mm_extract_epi64_rpl(vMaxHL, 1);
        }
        vMaxH = _mm_slli_si128(vMaxH, 8);
        vMaxHM = _mm_slli_si128(vMaxHM, 8);
        vMaxHS = _mm_slli_si128(vMaxHS, 8);
        vMaxHL = _mm_slli_si128(vMaxHL, 8);
    }

    

    result->score = score;
    result->matches = matches;
    result->similar = similar;
    result->length = length;

    parasail_free(pvEL);
    parasail_free(pvES);
    parasail_free(pvEM);
    parasail_free(pvELoad);
    parasail_free(pvEStore);
    parasail_free(pvHLLoad);
    parasail_free(pvHLStore);
    parasail_free(pvHSLoad);
    parasail_free(pvHSStore);
    parasail_free(pvHMLoad);
    parasail_free(pvHMStore);
    parasail_free(pvHLoad);
    parasail_free(pvHStore);
    parasail_free(vProfileS);
    parasail_free(vProfileM);
    parasail_free(vProfile);

    return result;
}

