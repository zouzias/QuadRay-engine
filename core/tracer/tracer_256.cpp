/******************************************************************************/
/* Copyright (c) 2013-2015 VectorChief (at github, bitbucket, sourceforge)    */
/* Distributed under the MIT software license, see the accompanying           */
/* file COPYING or http://www.opensource.org/licenses/mit-license.php         */
/******************************************************************************/

#include "tracer.h"
#include "format.h"
#if RT_DEBUG == 1
#include "system.h"
#endif /* RT_DEBUG */

#define RT_CODE_SPLIT

#undef RT_STACK_STEP /* cross-check with tracer.h */
#define RT_STACK_STEP       (Q * 0x300)

#undef RT_SIMD_WIDTH
#undef RT_SIMD_ALIGN
#undef RT_SIMD_SET

#if   defined (RT_X86)

#undef RT_RTARCH_X86_256_H
#include "rtarch_x86_256.h"

#elif defined (RT_ARM)

#error "ARM doesn't support SIMD wider than 4, \
exclude this file from compilation"

#endif /* RT_X86, RT_ARM */

/*
 * Global pointer tables
 * for quick entry point resolution.
 */
extern
rt_pntr t_ptr[3];
extern
rt_pntr t_mat[3];
extern
rt_pntr t_clp[3];
extern
rt_pntr t_pow[6];

namespace simd_256
{
#include "tracer.cpp"
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/