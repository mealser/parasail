#!/usr/bin/python

# Generate the various saturation checking and recalculating
# implementations.

import os

txt = """/**
 * @file
 *
 * @author jeff.daily@pnnl.gov
 *
 * Copyright (c) 2015 Battelle Memorial Institute.
 */
#include "config.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "parasail.h"

"""
for alg in ["nw", "sg", "sw"]:
    for table in ["", "_table", "_rowcol"]:
        for stats in ["", "_stats"]:
            for par in ["_scan", "_striped", "_diag"]:
                for isa in ["", "_sse2_128", "_sse41_128", "_avx2_256"]:
                    prefix = "parasail_%s%s%s%s%s"%(alg, stats, table, par, isa)
                    if isa:
                        isa_pre = "#if HAVE_" + isa.split('_')[1].upper()
                        isa_post = "#endif"
                    else:
                        isa_pre = ""
                        isa_post = ""
                    params = {"PREFIX":prefix,
                            "ISA_PRE":isa_pre,
                            "ISA_POST":isa_post}
                    txt += """
%(ISA_PRE)s
parasail_result_t* %(PREFIX)s_sat(
        const char * const restrict s1, const int s1Len,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap,
        const parasail_matrix_t *matrix)
{
    parasail_result_t * result = NULL;
    
    result = %(PREFIX)s_8(s1, s1Len, s2, s2Len, open, gap, matrix);
    if (result->saturated) {
        parasail_result_free(result);
        result = %(PREFIX)s_16(s1, s1Len, s2, s2Len, open, gap, matrix);
    }
    if (result->saturated) {
        parasail_result_free(result);
        result = %(PREFIX)s_32(s1, s1Len, s2, s2Len, open, gap, matrix);
    }

    return result;
}
%(ISA_POST)s
""" % params

for alg in ["nw", "sg", "sw"]:
    for table in ["", "_table", "_rowcol"]:
        for stats in [""]:
            for par in ["_scan_profile", "_striped_profile"]:
                for isa in ["", "_sse2_128", "_sse41_128", "_avx2_256"]:
                    prefix = "parasail_%s%s%s%s%s"%(alg, stats, table, par, isa)
                    if isa:
                        isa_pre = "#if HAVE_" + isa.split('_')[1].upper()
                        isa_post = "#endif"
                    else:
                        isa_pre = ""
                        isa_post = ""
                    params = {"PREFIX":prefix,
                            "ISA_PRE":isa_pre,
                            "ISA_POST":isa_post}
                    txt += """
%(ISA_PRE)s
parasail_result_t* %(PREFIX)s_sat(
        const parasail_profile_t * const restrict profile,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap)
{
    parasail_result_t * result = NULL;
    
    result = %(PREFIX)s_8(profile, s2, s2Len, open, gap);
    if (result->saturated) {
        parasail_result_free(result);
        parasail_profile_t *copy = (parasail_profile_t*)malloc(sizeof(parasail_profile_t));
        (void)memcpy(copy, profile, sizeof(parasail_profile_t));
        copy->profile = copy->profile2;
        result = %(PREFIX)s_16(copy, s2, s2Len, open, gap);
        free(copy);
    }

    return result;
}
%(ISA_POST)s
""" % params

for alg in ["nw", "sg", "sw"]:
    for table in ["", "_table", "_rowcol"]:
        for stats in ["_stats"]:
            for par in ["_scan_profile", "_striped_profile"]:
                for isa in ["", "_sse2_128", "_sse41_128", "_avx2_256"]:
                    prefix = "parasail_%s%s%s%s%s"%(alg, stats, table, par, isa)
                    if isa:
                        isa_pre = "#if HAVE_" + isa.split('_')[1].upper()
                        isa_post = "#endif"
                    else:
                        isa_pre = ""
                        isa_post = ""
                    params = {"PREFIX":prefix,
                            "ISA_PRE":isa_pre,
                            "ISA_POST":isa_post}
                    txt += """
%(ISA_PRE)s
parasail_result_t* %(PREFIX)s_sat(
        const parasail_profile_t * const restrict profile,
        const char * const restrict s2, const int s2Len,
        const int open, const int gap)
{
    parasail_result_t * result = NULL;
    
    result = %(PREFIX)s_8(profile, s2, s2Len, open, gap);
    if (result->saturated) {
        parasail_result_free(result);
        parasail_profile_t *copy = (parasail_profile_t*)malloc(sizeof(parasail_profile_t));
        (void)memcpy(copy, profile, sizeof(parasail_profile_t));
        copy->profile = copy->profile2;
        copy->profile_m = copy->profile2_m;
        copy->profile_s = copy->profile2_s;
        result = %(PREFIX)s_16(copy, s2, s2Len, open, gap);
        free(copy);
    }

    return result;
}
%(ISA_POST)s
""" % params


output_dir = "generated/"
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

output_filename = "%ssatcheck.c" % output_dir
writer = open(output_filename, "w")
writer.write(txt)
writer.write("\n")
writer.close()

