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

#include "parasail.h"
#include "parasail/cpuid.h"
#include "parasail/memory.h"

/* forward declare the dispatcher function */
parasail_function_t parasail_sg_scan_32_dispatcher;
parasail_function_t parasail_sg_scan_16_dispatcher;
parasail_function_t parasail_sg_scan_8_dispatcher;
parasail_function_t parasail_sg_striped_32_dispatcher;
parasail_function_t parasail_sg_striped_16_dispatcher;
parasail_function_t parasail_sg_striped_8_dispatcher;
parasail_function_t parasail_sg_diag_32_dispatcher;
parasail_function_t parasail_sg_diag_16_dispatcher;
parasail_function_t parasail_sg_diag_8_dispatcher;

/* declare and initialize the sg pointer to the dispatcher function */
parasail_function_t * parasail_sg_scan_32_pointer = &parasail_sg_scan_32_dispatcher;
parasail_function_t * parasail_sg_scan_16_pointer = &parasail_sg_scan_16_dispatcher;
parasail_function_t * parasail_sg_scan_8_pointer  = &parasail_sg_scan_8_dispatcher;
parasail_function_t * parasail_sg_striped_32_pointer = &parasail_sg_striped_32_dispatcher;
parasail_function_t * parasail_sg_striped_16_pointer = &parasail_sg_striped_16_dispatcher;
parasail_function_t * parasail_sg_striped_8_pointer  = &parasail_sg_striped_8_dispatcher;
parasail_function_t * parasail_sg_diag_32_pointer = &parasail_sg_diag_32_dispatcher;
parasail_function_t * parasail_sg_diag_16_pointer = &parasail_sg_diag_16_dispatcher;
parasail_function_t * parasail_sg_diag_8_pointer  = &parasail_sg_diag_8_dispatcher;

/* dispatcher function implementation */
parasail_result_t* parasail_sg_scan_32_dispatcher(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
#if HAVE_KNC
    parasail_sg_scan_32_pointer = sg_scan_knc_512_32;
#else
#if HAVE_AVX2
    if (parasail_can_use_avx2()) {
        parasail_sg_scan_32_pointer = sg_scan_avx2_256_32;
    }
    else
#endif
#if HAVE_SSE41
    if (parasail_can_use_sse41()) {
        parasail_sg_scan_32_pointer = sg_scan_sse41_128_32;
    }
    else
#endif
#if HAVE_SSE2
    if (parasail_can_use_sse2()) {
        parasail_sg_scan_32_pointer = sg_scan_sse2_128_32;
    }
    else
#endif
#endif
    {
    }
    return parasail_sg_scan_32_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* dispatcher function implementation */
parasail_result_t* parasail_sg_scan_16_dispatcher(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
#if HAVE_KNC
    parasail_sg_scan_16_pointer = sg_scan_knc_512_32;
#else
#if HAVE_AVX2
    if (parasail_can_use_avx2()) {
        parasail_sg_scan_16_pointer = sg_scan_avx2_256_16;
    }
    else
#endif
#if HAVE_SSE41
    if (parasail_can_use_sse41()) {
        parasail_sg_scan_16_pointer = sg_scan_sse41_128_16;
    }
    else
#endif
#if HAVE_SSE2
    if (parasail_can_use_sse2()) {
        parasail_sg_scan_16_pointer = sg_scan_sse2_128_16;
    }
    else
#endif
#endif
    {
    }
    return parasail_sg_scan_16_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* dispatcher function implementation */
parasail_result_t* parasail_sg_scan_8_dispatcher(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
#if HAVE_KNC
    parasail_sg_scan_8_pointer = sg_scan_knc_512_32;
#else
#if HAVE_AVX2
    if (parasail_can_use_avx2()) {
        parasail_sg_scan_8_pointer = sg_scan_avx2_256_8;
    }
    else
#endif
#if HAVE_SSE41
    if (parasail_can_use_sse41()) {
        parasail_sg_scan_8_pointer = sg_scan_sse41_128_8;
    }
    else
#endif
#if HAVE_SSE2
    if (parasail_can_use_sse2()) {
        parasail_sg_scan_8_pointer = sg_scan_sse2_128_8;
    }
    else
#endif
#endif
    {
    }
    return parasail_sg_scan_8_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* dispatcher function implementation */
parasail_result_t* parasail_sg_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
    parasail_result_t *result;

    result = parasail_sg_scan_8(s1, s1Len, s2, s2Len, open, gap, matrix);
    if (result->saturated) {
        parasail_result_free(result);
        result = parasail_sg_scan_16(s1, s1Len, s2, s2Len, open, gap, matrix);
    }
    if (result->saturated) {
        parasail_result_free(result);
        result = parasail_sg_scan_32(s1, s1Len, s2, s2Len, open, gap, matrix);
    }

    return result;
}

/* sg implementation which simply calls the pointer,
 * first time it's the dispatcher, otherwise it's correct sg impl */
parasail_result_t* parasail_sg_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
    return parasail_sg_scan_32_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* sg implementation which simply calls the pointer,
 * first time it's the dispatcher, otherwise it's correct sg impl */
parasail_result_t* parasail_sg_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
    return parasail_sg_scan_16_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* sg implementation which simply calls the pointer,
 * first time it's the dispatcher, otherwise it's correct sg impl */
parasail_result_t* parasail_sg_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
    return parasail_sg_scan_8_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* dispatcher function implementation */
parasail_result_t* parasail_sg_striped_32_dispatcher(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
#if HAVE_KNC
    parasail_sg_striped_32_pointer = sg_striped_knc_512_32;
#else
#if HAVE_AVX2
    if (parasail_can_use_avx2()) {
        parasail_sg_striped_32_pointer = sg_striped_avx2_256_32;
    }
    else
#endif
#if HAVE_SSE41
    if (parasail_can_use_sse41()) {
        parasail_sg_striped_32_pointer = sg_striped_sse41_128_32;
    }
    else
#endif
#if HAVE_SSE2
    if (parasail_can_use_sse2()) {
        parasail_sg_striped_32_pointer = sg_striped_sse2_128_32;
    }
    else
#endif
#endif
    {
    }
    return parasail_sg_striped_32_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* dispatcher function implementation */
parasail_result_t* parasail_sg_striped_16_dispatcher(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
#if HAVE_KNC
    parasail_sg_striped_16_pointer = sg_striped_knc_512_32;
#else
#if HAVE_AVX2
    if (parasail_can_use_avx2()) {
        parasail_sg_striped_16_pointer = sg_striped_avx2_256_16;
    }
    else
#endif
#if HAVE_SSE41
    if (parasail_can_use_sse41()) {
        parasail_sg_striped_16_pointer = sg_striped_sse41_128_16;
    }
    else
#endif
#if HAVE_SSE2
    if (parasail_can_use_sse2()) {
        parasail_sg_striped_16_pointer = sg_striped_sse2_128_16;
    }
    else
#endif
#endif
    {
    }
    return parasail_sg_striped_16_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* dispatcher function implementation */
parasail_result_t* parasail_sg_striped_8_dispatcher(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
#if HAVE_KNC
    parasail_sg_striped_8_pointer = sg_striped_knc_512_32;
#else
#if HAVE_AVX2
    if (parasail_can_use_avx2()) {
        parasail_sg_striped_8_pointer = sg_striped_avx2_256_8;
    }
    else
#endif
#if HAVE_SSE41
    if (parasail_can_use_sse41()) {
        parasail_sg_striped_8_pointer = sg_striped_sse41_128_8;
    }
    else
#endif
#if HAVE_SSE2
    if (parasail_can_use_sse2()) {
        parasail_sg_striped_8_pointer = sg_striped_sse2_128_8;
    }
    else
#endif
#endif
    {
    }
    return parasail_sg_striped_8_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* dispatcher function implementation */
parasail_result_t* parasail_sg_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
    parasail_result_t *result;

    result = parasail_sg_striped_8(s1, s1Len, s2, s2Len, open, gap, matrix);
    if (result->saturated) {
        parasail_result_free(result);
        result = parasail_sg_striped_16(s1, s1Len, s2, s2Len, open, gap, matrix);
    }
    if (result->saturated) {
        parasail_result_free(result);
        result = parasail_sg_striped_32(s1, s1Len, s2, s2Len, open, gap, matrix);
    }

    return result;
}

/* sg implementation which simply calls the pointer,
 * first time it's the dispatcher, otherwise it's correct sg impl */
parasail_result_t* parasail_sg_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
    return parasail_sg_striped_32_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* sg implementation which simply calls the pointer,
 * first time it's the dispatcher, otherwise it's correct sg impl */
parasail_result_t* parasail_sg_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
    return parasail_sg_striped_16_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* sg implementation which simply calls the pointer,
 * first time it's the dispatcher, otherwise it's correct sg impl */
parasail_result_t* parasail_sg_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
    return parasail_sg_striped_8_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* dispatcher function implementation */
parasail_result_t* parasail_sg_diag_32_dispatcher(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
#if HAVE_KNC
    parasail_sg_diag_32_pointer = sg_diag_knc_512_32;
#else
#if HAVE_AVX2
    if (parasail_can_use_avx2()) {
        parasail_sg_diag_32_pointer = sg_diag_avx2_256_32;
    }
    else
#endif
#if HAVE_SSE41
    if (parasail_can_use_sse41()) {
        parasail_sg_diag_32_pointer = sg_diag_sse41_128_32;
    }
    else
#endif
#if HAVE_SSE2
    if (parasail_can_use_sse2()) {
        parasail_sg_diag_32_pointer = sg_diag_sse2_128_32;
    }
    else
#endif
#endif
    {
    }
    return parasail_sg_diag_32_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* dispatcher function implementation */
parasail_result_t* parasail_sg_diag_16_dispatcher(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
#if HAVE_KNC
    parasail_sg_diag_16_pointer = sg_diag_knc_512_32;
#else
#if HAVE_AVX2
    if (parasail_can_use_avx2()) {
        parasail_sg_diag_16_pointer = sg_diag_avx2_256_16;
    }
    else
#endif
#if HAVE_SSE41
    if (parasail_can_use_sse41()) {
        parasail_sg_diag_16_pointer = sg_diag_sse41_128_16;
    }
    else
#endif
#if HAVE_SSE2
    if (parasail_can_use_sse2()) {
        parasail_sg_diag_16_pointer = sg_diag_sse2_128_16;
    }
    else
#endif
#endif
    {
    }
    return parasail_sg_diag_16_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* dispatcher function implementation */
parasail_result_t* parasail_sg_diag_8_dispatcher(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
#if HAVE_KNC
    parasail_sg_diag_8_pointer = sg_diag_knc_512_32;
#else
#if HAVE_AVX2
    if (parasail_can_use_avx2()) {
        parasail_sg_diag_8_pointer = sg_diag_avx2_256_8;
    }
    else
#endif
#if HAVE_SSE41
    if (parasail_can_use_sse41()) {
        parasail_sg_diag_8_pointer = sg_diag_sse41_128_8;
    }
    else
#endif
#if HAVE_SSE2
    if (parasail_can_use_sse2()) {
        parasail_sg_diag_8_pointer = sg_diag_sse2_128_8;
    }
    else
#endif
#endif
    {
    }
    return parasail_sg_diag_8_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* dispatcher function implementation */
parasail_result_t* parasail_sg_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
    parasail_result_t *result;

    result = parasail_sg_diag_8(s1, s1Len, s2, s2Len, open, gap, matrix);
    if (result->saturated) {
        parasail_result_free(result);
        result = parasail_sg_diag_16(s1, s1Len, s2, s2Len, open, gap, matrix);
    }
    if (result->saturated) {
        parasail_result_free(result);
        result = parasail_sg_diag_32(s1, s1Len, s2, s2Len, open, gap, matrix);
    }

    return result;
}

/* sg implementation which simply calls the pointer,
 * first time it's the dispatcher, otherwise it's correct sg impl */
parasail_result_t* parasail_sg_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
    return parasail_sg_diag_32_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* sg implementation which simply calls the pointer,
 * first time it's the dispatcher, otherwise it's correct sg impl */
parasail_result_t* parasail_sg_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
    return parasail_sg_diag_16_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

/* sg implementation which simply calls the pointer,
 * first time it's the dispatcher, otherwise it's correct sg impl */
parasail_result_t* parasail_sg_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
    return parasail_sg_diag_8_pointer(s1, s1Len, s2, s2Len, open, gap, matrix);
}

