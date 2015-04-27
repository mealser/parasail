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
 * ftp://ftp.cbi.pku.edu.cn/pub/software/blast/matrices/PAM130, the
 * Center for Bioinformatics, Peking University, China.
 */
#ifndef _PARASAIL_PAM130_H_
#define _PARASAIL_PAM130_H_

#include "parasail.h"
#include "pam_map.h"

/* # */
/* # This matrix was produced by "pam" Version 1.0.6 [28-Jul-93] */
/* # */
/* # PAM 130 substitution matrix, scale = ln(2)/2 = 0.346574 */
/* # */
/* # Expected score = -1.48, Entropy = 0.895 bits */
/* # */
/* # Lowest score = -8, Highest score = 12 */
/* # */

static const int8_t parasail_pam130_[] = {
/*        A   R   N   D   C   Q   E   G   H   I   L   K   M   F   P   S   T   W   Y   V   B   Z   X   * */
/* A */   3, -3,  0,  0, -3, -1,  0,  1, -2, -1, -3, -2, -2, -4,  1,  1,  1, -6, -4,  0,  0,  0, -1, -8,
/* R */  -3,  6, -1, -3, -4,  1, -3, -4,  1, -2, -4,  2, -1, -5, -1, -1, -2,  1, -5, -3, -2, -1, -2, -8,
/* N */   0, -1,  4,  2, -4,  0,  1,  0,  2, -2, -3,  1, -3, -4, -1,  1,  0, -4, -2, -3,  3,  0, -1, -8,
/* D */   0, -3,  2,  5, -6,  1,  3,  0,  0, -3, -5, -1, -4, -7, -2,  0, -1, -7, -5, -3,  4,  3, -1, -8,
/* C */  -3, -4, -4, -6,  9, -6, -6, -4, -4, -3, -7, -6, -6, -5, -3,  0, -3, -8, -1, -2, -5, -6, -4, -8,
/* Q */  -1,  1,  0,  1, -6,  5,  2, -2,  3, -3, -2,  0, -1, -6,  0, -1, -2, -6, -5, -3,  0,  4, -1, -8,
/* E */   0, -3,  1,  3, -6,  2,  5, -1,  0, -2, -4, -1, -3, -6, -2, -1, -1, -8, -5, -3,  2,  4, -1, -8,
/* G */   1, -4,  0,  0, -4, -2, -1,  5, -3, -4, -5, -3, -4, -5, -2,  1, -1, -7, -6, -2,  0, -1, -2, -8,
/* H */  -2,  1,  2,  0, -4,  3,  0, -3,  7, -3, -3, -1, -3, -2, -1, -2, -2, -3,  0, -3,  1,  1, -1, -8,
/* I */  -1, -2, -2, -3, -3, -3, -2, -4, -3,  5,  1, -2,  2,  0, -3, -2,  0, -6, -2,  3, -3, -3, -1, -8,
/* L */  -3, -4, -3, -5, -7, -2, -4, -5, -3,  1,  5, -4,  3,  1, -3, -4, -2, -2, -2,  1, -4, -3, -2, -8,
/* K */  -2,  2,  1, -1, -6,  0, -1, -3, -1, -2, -4,  5,  0, -6, -2, -1,  0, -5, -5, -4,  0,  0, -1, -8,
/* M */  -2, -1, -3, -4, -6, -1, -3, -4, -3,  2,  3,  0,  8, -1, -3, -2, -1, -5, -4,  1, -3, -2, -1, -8,
/* F */  -4, -5, -4, -7, -5, -6, -6, -5, -2,  0,  1, -6, -1,  7, -5, -3, -4, -1,  4, -2, -5, -6, -3, -8,
/* P */   1, -1, -1, -2, -3,  0, -2, -2, -1, -3, -3, -2, -3, -5,  6,  1, -1, -6, -6, -2, -2, -1, -1, -8,
/* S */   1, -1,  1,  0,  0, -1, -1,  1, -2, -2, -4, -1, -2, -3,  1,  3,  2, -2, -3, -2,  0, -1, -1, -8,
/* T */   1, -2,  0, -1, -3, -2, -1, -1, -2,  0, -2,  0, -1, -4, -1,  2,  4, -6, -3,  0,  0, -2, -1, -8,
/* W */  -6,  1, -4, -7, -8, -6, -8, -7, -3, -6, -2, -5, -5, -1, -6, -2, -6, 12, -1, -7, -5, -7, -5, -8,
/* Y */  -4, -5, -2, -5, -1, -5, -5, -6,  0, -2, -2, -5, -4,  4, -6, -3, -3, -1,  8, -3, -3, -5, -3, -8,
/* V */   0, -3, -3, -3, -2, -3, -3, -2, -3,  3,  1, -4,  1, -2, -2, -2,  0, -7, -3,  5, -3, -3, -1, -8,
/* B */   0, -2,  3,  4, -5,  0,  2,  0,  1, -3, -4,  0, -3, -5, -2,  0,  0, -5, -3, -3,  3,  2, -1, -8,
/* Z */   0, -1,  0,  3, -6,  4,  4, -1,  1, -3, -3,  0, -2, -6, -1, -1, -2, -7, -5, -3,  2,  4, -1, -8,
/* X */  -1, -2, -1, -1, -4, -1, -1, -2, -1, -1, -2, -1, -1, -3, -1, -1, -1, -5, -3, -1, -1, -1, -1, -8,
/* * */  -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8,  1
};

static const int parasail_pam130__[24][24] = {
/*        A   R   N   D   C   Q   E   G   H   I   L   K   M   F   P   S   T   W   Y   V   B   Z   X   * */
/* A */{  3, -3,  0,  0, -3, -1,  0,  1, -2, -1, -3, -2, -2, -4,  1,  1,  1, -6, -4,  0,  0,  0, -1, -8},
/* R */{ -3,  6, -1, -3, -4,  1, -3, -4,  1, -2, -4,  2, -1, -5, -1, -1, -2,  1, -5, -3, -2, -1, -2, -8},
/* N */{  0, -1,  4,  2, -4,  0,  1,  0,  2, -2, -3,  1, -3, -4, -1,  1,  0, -4, -2, -3,  3,  0, -1, -8},
/* D */{  0, -3,  2,  5, -6,  1,  3,  0,  0, -3, -5, -1, -4, -7, -2,  0, -1, -7, -5, -3,  4,  3, -1, -8},
/* C */{ -3, -4, -4, -6,  9, -6, -6, -4, -4, -3, -7, -6, -6, -5, -3,  0, -3, -8, -1, -2, -5, -6, -4, -8},
/* Q */{ -1,  1,  0,  1, -6,  5,  2, -2,  3, -3, -2,  0, -1, -6,  0, -1, -2, -6, -5, -3,  0,  4, -1, -8},
/* E */{  0, -3,  1,  3, -6,  2,  5, -1,  0, -2, -4, -1, -3, -6, -2, -1, -1, -8, -5, -3,  2,  4, -1, -8},
/* G */{  1, -4,  0,  0, -4, -2, -1,  5, -3, -4, -5, -3, -4, -5, -2,  1, -1, -7, -6, -2,  0, -1, -2, -8},
/* H */{ -2,  1,  2,  0, -4,  3,  0, -3,  7, -3, -3, -1, -3, -2, -1, -2, -2, -3,  0, -3,  1,  1, -1, -8},
/* I */{ -1, -2, -2, -3, -3, -3, -2, -4, -3,  5,  1, -2,  2,  0, -3, -2,  0, -6, -2,  3, -3, -3, -1, -8},
/* L */{ -3, -4, -3, -5, -7, -2, -4, -5, -3,  1,  5, -4,  3,  1, -3, -4, -2, -2, -2,  1, -4, -3, -2, -8},
/* K */{ -2,  2,  1, -1, -6,  0, -1, -3, -1, -2, -4,  5,  0, -6, -2, -1,  0, -5, -5, -4,  0,  0, -1, -8},
/* M */{ -2, -1, -3, -4, -6, -1, -3, -4, -3,  2,  3,  0,  8, -1, -3, -2, -1, -5, -4,  1, -3, -2, -1, -8},
/* F */{ -4, -5, -4, -7, -5, -6, -6, -5, -2,  0,  1, -6, -1,  7, -5, -3, -4, -1,  4, -2, -5, -6, -3, -8},
/* P */{  1, -1, -1, -2, -3,  0, -2, -2, -1, -3, -3, -2, -3, -5,  6,  1, -1, -6, -6, -2, -2, -1, -1, -8},
/* S */{  1, -1,  1,  0,  0, -1, -1,  1, -2, -2, -4, -1, -2, -3,  1,  3,  2, -2, -3, -2,  0, -1, -1, -8},
/* T */{  1, -2,  0, -1, -3, -2, -1, -1, -2,  0, -2,  0, -1, -4, -1,  2,  4, -6, -3,  0,  0, -2, -1, -8},
/* W */{ -6,  1, -4, -7, -8, -6, -8, -7, -3, -6, -2, -5, -5, -1, -6, -2, -6, 12, -1, -7, -5, -7, -5, -8},
/* Y */{ -4, -5, -2, -5, -1, -5, -5, -6,  0, -2, -2, -5, -4,  4, -6, -3, -3, -1,  8, -3, -3, -5, -3, -8},
/* V */{  0, -3, -3, -3, -2, -3, -3, -2, -3,  3,  1, -4,  1, -2, -2, -2,  0, -7, -3,  5, -3, -3, -1, -8},
/* B */{  0, -2,  3,  4, -5,  0,  2,  0,  1, -3, -4,  0, -3, -5, -2,  0,  0, -5, -3, -3,  3,  2, -1, -8},
/* Z */{  0, -1,  0,  3, -6,  4,  4, -1,  1, -3, -3,  0, -2, -6, -1, -1, -2, -7, -5, -3,  2,  4, -1, -8},
/* X */{ -1, -2, -1, -1, -4, -1, -1, -2, -1, -1, -2, -1, -1, -3, -1, -1, -1, -5, -3, -1, -1, -1, -1, -8},
/* * */{ -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8,  1}
};

#define PARASAIL_MATRIX_PAM130 \
    "pam130", \
    parasail_pam130_, \
    parasail_pam130__, \
    parasail_pam_map, \
    24

static const parasail_matrix_t parasail_pam130 = {
PARASAIL_MATRIX_PAM130
};

#endif /* _PARASAIL_PAM130_H_ */
