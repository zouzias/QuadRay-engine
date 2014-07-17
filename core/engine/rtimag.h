/******************************************************************************/
/* Copyright (c) 2013 VectorChief (at github, bitbucket, sourceforge)         */
/* Distributed under the MIT software license, see the accompanying           */
/* file COPYING or http://www.opensource.org/licenses/mit-license.php         */
/******************************************************************************/

#ifndef RT_RTIMAG_H
#define RT_RTIMAG_H

#include "rtbase.h"
#include "format.h"
#include "object.h"

/******************************************************************************/
/********************************   TEXTURE   *********************************/
/******************************************************************************/

/* Convert texture from file to static array initializer.
 * Parameter fullpath must be editable char array.
 */
rt_void convert_texture(rt_char *fullpath);

/* Load texture from file to memory.
 */
rt_void load_texture(rt_Registry *rg, rt_pstr name, rt_TEX *tx);

#endif /* RT_RTIMAG_H */

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/