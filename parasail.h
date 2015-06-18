/**
 * @file
 *
 * @author jeff.daily@pnnl.gov
 *
 * Copyright (c) 2015 Battelle Memorial Institute.
 */
#ifndef _PARASAIL_H_
#define _PARASAIL_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Version macros for compile-time API version detection */
#define PARASAIL_VERSION_MAJOR 1
#define PARASAIL_VERSION_MINOR 0
#define PARASAIL_VERSION_PATCH 0

#define PARASAIL_MAKE_VERSION(major, minor, patch) \
    ((major) * 10000 + (minor) * 100 + (patch))
#define PARASAIL_VERSION \
    PARASAIL_MAKE_VERSION(PARASAIL_VERSION_MAJOR, PARASAIL_VERSION_MINOR, PARASAIL_VERSION_PATCH)

/* Generic helper definitions for shared library support */
#if defined _WIN32 || defined __CYGWIN__
  #define PARASAIL_HELPER_DLL_IMPORT __declspec(dllimport)
  #define PARASAIL_HELPER_DLL_EXPORT __declspec(dllexport)
  #define PARASAIL_HELPER_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define PARASAIL_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define PARASAIL_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define PARASAIL_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define PARASAIL_HELPER_DLL_IMPORT
    #define PARASAIL_HELPER_DLL_EXPORT
    #define PARASAIL_HELPER_DLL_LOCAL
  #endif
#endif

/*
 * Now we use the generic helper definitions above to define
 * PARASAIL_API and PARASAIL_LOCAL.  PARASAIL_API is used for the public
 * API symbols. It either DLL imports or DLL exports (or does nothing
 * for static build) PARASAIL_LOCAL is used for non-api symbols.
 */

/* defined if PARASAIL is compiled as a DLL */
#ifdef PARASAIL_DLL
  /* defined if we are building the PARASAIL DLL (instead of using it) */
  #ifdef PARASAIL_DLL_EXPORTS
    #define PARASAIL_API PARASAIL_HELPER_DLL_EXPORT
  #else
    #define PARASAIL_API PARASAIL_HELPER_DLL_IMPORT
  #endif /* PARASAIL_DLL_EXPORTS */
  #define PARASAIL_LOCAL PARASAIL_HELPER_DLL_LOCAL
#else /* PARASAIL_DLL is not defined: this means PARASAIL is a static lib. */
  #define PARASAIL_API
  #define PARASAIL_LOCAL
#endif /* PARASAIL_DLL */

typedef struct parasail_result {
    int saturated;  /* for the 8-bit functions, whether score overflowed and should be discarded */
    int score;      /* alignment score */
    int matches;    /* number of exactly matching characters in the alignment */
    int similar;    /* number of similar characters (positive substitutions) in the alignment */
    int length;     /* length of the alignment */
    int * restrict score_table;     /* DP table of scores */
    int * restrict matches_table;   /* DP table of exact match counts */
    int * restrict similar_table;   /* DP table of similar substitution counts */
    int * restrict length_table;    /* DP table of lengths */
    int * restrict score_row;       /* last row of DP table of scores */
    int * restrict matches_row;     /* last row of DP table of exact match counts */
    int * restrict similar_row;     /* last row of DP table of similar substitution counts */
    int * restrict length_row;      /* last row of DP table of lengths */
    int * restrict score_col;       /* last col of DP table of scores */
    int * restrict matches_col;     /* last col of DP table of exact match counts */
    int * restrict similar_col;     /* last col of DP table of similar substitution counts */
    int * restrict length_col;      /* last col of DP table of lengths */
} parasail_result_t;

typedef struct parasail_matrix {
    const char * name;
    const int *matrix;
    const int *mapper;
    int size;
    int need_free;
} parasail_matrix_t;

typedef parasail_result_t* parasail_function_t(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix);

typedef struct parasail_function_info {
    parasail_function_t * pointer;
    const char * name;
    const char * alg;
    const char * type;
    const char * isa;
    const char * bits;
    const char * width;
    int lanes;
    char is_table;
    char is_rowcol;
    char is_stats;
    char is_ref;
} parasail_function_info_t;

/* Run-time API version detection */
extern PARASAIL_API
void parasail_version(int *major, int *minor, int *patch);

/** Deallocate result. */
extern PARASAIL_API
void parasail_result_free(parasail_result_t *result);

/** Lookup function by name. */
extern PARASAIL_API
parasail_function_t * parasail_lookup_function(const char *funcname);

/** Lookup function info by name. */
extern PARASAIL_API
const parasail_function_info_t * parasail_lookup_function_info(const char *funcname);

/** Current time in seconds with nanosecond resolution. */
extern PARASAIL_API
double parasail_time(void);

/** Lookup substitution matrix by name. */
extern PARASAIL_API
const parasail_matrix_t* parasail_matrix_lookup(const char *matrixname);

/** Create simple substitution matrix. */
extern PARASAIL_API
parasail_matrix_t* parasail_matrix_create(
        const char *alphabet, const int match, const int mismatch);

/** Deallocate substitution matrix. */
extern PARASAIL_API
void parasail_matrix_free(parasail_matrix_t *matrix);

/* The following function signatures were generated by the 'names.py'
 * script located in the 'util' directory of the main distribution. */

/* BEGIN GENERATED NAMES */

extern PARASAIL_API
parasail_result_t* parasail_nw(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_sse2_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_sse2_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_sse2_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_sse2_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_sse41_128_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_sse41_128_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_avx2_256_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_avx2_256_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_avx2_256_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_avx2_256_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_knc_512_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_blocked_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_blocked_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_blocked_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_blocked_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_blocked_sse41_128_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_blocked_sse41_128_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_table_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_rowcol_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_table_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_nw_stats_rowcol_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_table_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_rowcol_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_table_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sg_stats_rowcol_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_table_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_rowcol_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_table_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_scan_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_striped_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_64(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_32(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_16(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

extern PARASAIL_API
parasail_result_t* parasail_sw_stats_rowcol_diag_8(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t* matrix);

/* END GENERATED NAMES */

#ifdef __cplusplus
}
#endif

#endif /* _PARASAIL_H_ */
