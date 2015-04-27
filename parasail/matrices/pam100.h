/**
 * @file
 *
 * @author jeff.daily@pnnl.gov
 *
 * Copyright (c) 2014 Battelle Memorial Institute.
 *
 * All rights reserved. No warranty, explicit or implicit, provided.
 *
 * This file was converted to C code from the raw file found at
 * ftp://ftp.cbi.pku.edu.cn/pub/software/blast/matrices/PAM100, the
 * Center for Bioinformatics, Peking University, China.
 */
#ifndef _PARASAIL_PAM100_H_
#define _PARASAIL_PAM100_H_

#include "parasail.h"
#include "pam_map.h"

/* # */
/* # This matrix was produced by "pam" Version 1.0.6 [28-Jul-93] */
/* # */
/* # PAM 100 substitution matrix, scale = ln(2)/2 = 0.346574 */
/* # */
/* # Expected score = -1.99, Entropy = 1.18 bits */
/* # */
/* # Lowest score = -9, Highest score = 12 */
/* # */

static const int8_t parasail_pam100_[] = {
/*        A   R   N   D   C   Q   E   G   H   I   L   K   M   F   P   S   T   W   Y   V   B   Z   X   * */
/* A */   4, -3, -1, -1, -3, -2,  0,  1, -3, -2, -3, -3, -2, -5,  1,  1,  1, -7, -4,  0, -1, -1, -1, -9,
/* R */  -3,  7, -2, -4, -5,  1, -3, -5,  1, -3, -5,  2, -1, -6, -1, -1, -3,  1, -6, -4, -3, -1, -2, -9,
/* N */  -1, -2,  5,  3, -5, -1,  1, -1,  2, -3, -4,  1, -4, -5, -2,  1,  0, -5, -2, -3,  4,  0, -1, -9,
/* D */  -1, -4,  3,  5, -7,  0,  4, -1, -1, -4, -6, -1, -5, -8, -3, -1, -2, -9, -6, -4,  4,  3, -2, -9,
/* C */  -3, -5, -5, -7,  9, -8, -8, -5, -4, -3, -8, -8, -7, -7, -4, -1, -4, -9, -1, -3, -6, -8, -5, -9,
/* Q */  -2,  1, -1,  0, -8,  6,  2, -3,  3, -4, -2,  0, -2, -7, -1, -2, -2, -7, -6, -3,  0,  5, -2, -9,
/* E */   0, -3,  1,  4, -8,  2,  5, -1, -1, -3, -5, -1, -4, -8, -2, -1, -2, -9, -5, -3,  3,  4, -2, -9,
/* G */   1, -5, -1, -1, -5, -3, -1,  5, -4, -5, -6, -3, -4, -6, -2,  0, -2, -9, -7, -3, -1, -2, -2, -9,
/* H */  -3,  1,  2, -1, -4,  3, -1, -4,  7, -4, -3, -2, -4, -3, -1, -2, -3, -4, -1, -3,  1,  1, -2, -9,
/* I */  -2, -3, -3, -4, -3, -4, -3, -5, -4,  6,  1, -3,  1,  0, -4, -3,  0, -7, -3,  3, -3, -3, -2, -9,
/* L */  -3, -5, -4, -6, -8, -2, -5, -6, -3,  1,  6, -4,  3,  0, -4, -4, -3, -3, -3,  0, -5, -4, -3, -9,
/* K */  -3,  2,  1, -1, -8,  0, -1, -3, -2, -3, -4,  5,  0, -7, -3, -1, -1, -6, -6, -4,  0, -1, -2, -9,
/* M */  -2, -1, -4, -5, -7, -2, -4, -4, -4,  1,  3,  0,  9, -1, -4, -3, -1, -6, -5,  1, -4, -2, -2, -9,
/* F */  -5, -6, -5, -8, -7, -7, -8, -6, -3,  0,  0, -7, -1,  8, -6, -4, -5, -1,  4, -3, -6, -7, -4, -9,
/* P */   1, -1, -2, -3, -4, -1, -2, -2, -1, -4, -4, -3, -4, -6,  7,  0, -1, -7, -7, -3, -3, -1, -2, -9,
/* S */   1, -1,  1, -1, -1, -2, -1,  0, -2, -3, -4, -1, -3, -4,  0,  4,  2, -3, -4, -2,  0, -2, -1, -9,
/* T */   1, -3,  0, -2, -4, -2, -2, -2, -3,  0, -3, -1, -1, -5, -1,  2,  5, -7, -4,  0, -1, -2, -1, -9,
/* W */  -7,  1, -5, -9, -9, -7, -9, -9, -4, -7, -3, -6, -6, -1, -7, -3, -7, 12, -2, -9, -6, -8, -6, -9,
/* Y */  -4, -6, -2, -6, -1, -6, -5, -7, -1, -3, -3, -6, -5,  4, -7, -4, -4, -2,  9, -4, -4, -6, -4, -9,
/* V */   0, -4, -3, -4, -3, -3, -3, -3, -3,  3,  0, -4,  1, -3, -3, -2,  0, -9, -4,  5, -4, -3, -2, -9,
/* B */  -1, -3,  4,  4, -6,  0,  3, -1,  1, -3, -5,  0, -4, -6, -3,  0, -1, -6, -4, -4,  4,  2, -2, -9,
/* Z */  -1, -1,  0,  3, -8,  5,  4, -2,  1, -3, -4, -1, -2, -7, -1, -2, -2, -8, -6, -3,  2,  5, -2, -9,
/* X */  -1, -2, -1, -2, -5, -2, -2, -2, -2, -2, -3, -2, -2, -4, -2, -1, -1, -6, -4, -2, -2, -2, -2, -9,
/* * */  -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,  1
};

static const int parasail_pam100__[24][24] = {
/*        A   R   N   D   C   Q   E   G   H   I   L   K   M   F   P   S   T   W   Y   V   B   Z   X   * */
/* A */{  4, -3, -1, -1, -3, -2,  0,  1, -3, -2, -3, -3, -2, -5,  1,  1,  1, -7, -4,  0, -1, -1, -1, -9},
/* R */{ -3,  7, -2, -4, -5,  1, -3, -5,  1, -3, -5,  2, -1, -6, -1, -1, -3,  1, -6, -4, -3, -1, -2, -9},
/* N */{ -1, -2,  5,  3, -5, -1,  1, -1,  2, -3, -4,  1, -4, -5, -2,  1,  0, -5, -2, -3,  4,  0, -1, -9},
/* D */{ -1, -4,  3,  5, -7,  0,  4, -1, -1, -4, -6, -1, -5, -8, -3, -1, -2, -9, -6, -4,  4,  3, -2, -9},
/* C */{ -3, -5, -5, -7,  9, -8, -8, -5, -4, -3, -8, -8, -7, -7, -4, -1, -4, -9, -1, -3, -6, -8, -5, -9},
/* Q */{ -2,  1, -1,  0, -8,  6,  2, -3,  3, -4, -2,  0, -2, -7, -1, -2, -2, -7, -6, -3,  0,  5, -2, -9},
/* E */{  0, -3,  1,  4, -8,  2,  5, -1, -1, -3, -5, -1, -4, -8, -2, -1, -2, -9, -5, -3,  3,  4, -2, -9},
/* G */{  1, -5, -1, -1, -5, -3, -1,  5, -4, -5, -6, -3, -4, -6, -2,  0, -2, -9, -7, -3, -1, -2, -2, -9},
/* H */{ -3,  1,  2, -1, -4,  3, -1, -4,  7, -4, -3, -2, -4, -3, -1, -2, -3, -4, -1, -3,  1,  1, -2, -9},
/* I */{ -2, -3, -3, -4, -3, -4, -3, -5, -4,  6,  1, -3,  1,  0, -4, -3,  0, -7, -3,  3, -3, -3, -2, -9},
/* L */{ -3, -5, -4, -6, -8, -2, -5, -6, -3,  1,  6, -4,  3,  0, -4, -4, -3, -3, -3,  0, -5, -4, -3, -9},
/* K */{ -3,  2,  1, -1, -8,  0, -1, -3, -2, -3, -4,  5,  0, -7, -3, -1, -1, -6, -6, -4,  0, -1, -2, -9},
/* M */{ -2, -1, -4, -5, -7, -2, -4, -4, -4,  1,  3,  0,  9, -1, -4, -3, -1, -6, -5,  1, -4, -2, -2, -9},
/* F */{ -5, -6, -5, -8, -7, -7, -8, -6, -3,  0,  0, -7, -1,  8, -6, -4, -5, -1,  4, -3, -6, -7, -4, -9},
/* P */{  1, -1, -2, -3, -4, -1, -2, -2, -1, -4, -4, -3, -4, -6,  7,  0, -1, -7, -7, -3, -3, -1, -2, -9},
/* S */{  1, -1,  1, -1, -1, -2, -1,  0, -2, -3, -4, -1, -3, -4,  0,  4,  2, -3, -4, -2,  0, -2, -1, -9},
/* T */{  1, -3,  0, -2, -4, -2, -2, -2, -3,  0, -3, -1, -1, -5, -1,  2,  5, -7, -4,  0, -1, -2, -1, -9},
/* W */{ -7,  1, -5, -9, -9, -7, -9, -9, -4, -7, -3, -6, -6, -1, -7, -3, -7, 12, -2, -9, -6, -8, -6, -9},
/* Y */{ -4, -6, -2, -6, -1, -6, -5, -7, -1, -3, -3, -6, -5,  4, -7, -4, -4, -2,  9, -4, -4, -6, -4, -9},
/* V */{  0, -4, -3, -4, -3, -3, -3, -3, -3,  3,  0, -4,  1, -3, -3, -2,  0, -9, -4,  5, -4, -3, -2, -9},
/* B */{ -1, -3,  4,  4, -6,  0,  3, -1,  1, -3, -5,  0, -4, -6, -3,  0, -1, -6, -4, -4,  4,  2, -2, -9},
/* Z */{ -1, -1,  0,  3, -8,  5,  4, -2,  1, -3, -4, -1, -2, -7, -1, -2, -2, -8, -6, -3,  2,  5, -2, -9},
/* X */{ -1, -2, -1, -2, -5, -2, -2, -2, -2, -2, -3, -2, -2, -4, -2, -1, -1, -6, -4, -2, -2, -2, -2, -9},
/* * */{ -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,  1}
};

#define PARASAIL_MATRIX_PAM100 \
    "pam100", \
    parasail_pam100_, \
    parasail_pam100__, \
    parasail_pam_map, \
    24

static const parasail_matrix_t parasail_pam100 = {
PARASAIL_MATRIX_PAM100
};

#endif /* _PARASAIL_PAM100_H_ */
