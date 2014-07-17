/******************************************************************************/
/* Copyright (c) 2013 VectorChief (at github, bitbucket, sourceforge)         */
/* Distributed under the MIT software license, see the accompanying           */
/* file COPYING or http://www.opensource.org/licenses/mit-license.php         */
/******************************************************************************/

#ifndef RT_FORMAT_H
#define RT_FORMAT_H

#include "rtbase.h"

/******************************************************************************/
/*******************************   DEFINITIONS   ******************************/
/******************************************************************************/

#define RT_TAG_ARRAY   /* generic tag  */  -1 /* used for textures as well */

#define RT_TAG_PLANE                        0
#define RT_TAG_SURFACE_MAX                  1

#define RT_TAG_CAMERA                       100
#define RT_TAG_LIGHT                        101
#define RT_TAG_MAX                          102

#define RT_IS_ARRAY(o)                                                      \
        ((o)->tag == RT_TAG_ARRAY)

#define RT_IS_SURFACE(o)                                                    \
        ((o)->tag  > RT_TAG_ARRAY && (o)->tag < RT_TAG_SURFACE_MAX)

/******************************************************************************/
/********************************   RELATION   ********************************/
/******************************************************************************/

#define RT_REL_MINUS_INNER                 -1 /* subtract srf inner subspace */
#define RT_REL_MINUS_OUTER                 +1 /* subtract srf outer subspace */

struct rt_RELATION
{
    rt_cell             obj1;
    rt_cell             rel;
    rt_cell             obj2;
};

/******************************************************************************/
/********************************   TRANSFORM   *******************************/
/******************************************************************************/

struct rt_TRANSFORM2D
{
    rt_vec2             scl;
    rt_real             rot;
    rt_vec2             pos;
};

struct rt_TRANSFORM3D
{
    rt_vec3             scl;
    rt_vec3             rot;
    rt_vec3             pos;
};

/******************************************************************************/
/**********************************   COLOR   *********************************/
/******************************************************************************/

#define RT_COL(val)                                                         \
{                                                                           \
    val,    {0.0f}                                                          \
}

#define RT_COL_HDR(r, g, b, a)                                              \
{                                                                           \
    0x0,    {r, g, b, a}                                                    \
}

struct rt_COL
{
    rt_word             val;
    rt_vec4             hdr;
};

/******************************************************************************/
/*********************************   TEXTURE   ********************************/
/******************************************************************************/

#define RT_TEX_PCOLOR                       0   /* plain-color, XRGB */
#define RT_TEX_ACOLOR                       1   /* alpha-color, ARGB */
#define RT_TEX_PALPHA                       2   /* plain-alpha, A    */

#define RT_TEX_HDR_PCOLOR                   10  /* plain-color, XRGB */
#define RT_TEX_HDR_ACOLOR                   11  /* alpha-color, ARGB */
#define RT_TEX_HDR_PALPHA                   12  /* plain-alpha, A    */

/* add HDR16, HDR24, HDR32, HDR64 later if needed, default is HDR32 */

#define RT_TEX(tag, val)                                                    \
{                                                                           \
    RT_TEX_##tag,           RT_COL(val),                                    \
    RT_NULL,                0,                                              \
    RT_NULL,                0,                                              \
    0,                      0                                               \
}

#define RT_TEX_HDR(tag, r, g, b, a)                                         \
{                                                                           \
    RT_TEX_HDR_##tag,       RT_COL_HDR(r, g, b  a),                         \
    RT_NULL,                0,                                              \
    RT_NULL,                0,                                              \
    0,                      0                                               \
}

#define RT_TEX_LOAD(tag, pstr)                                              \
{                                                                           \
    RT_TEX_##tag,           RT_COL(0x0),                                    \
    (rt_pntr)pstr,          0,                                              \
    RT_NULL,                0,                                              \
    0,                      0                                               \
}

#define RT_TEX_BIND(tag, ptex)                                              \
{                                                                           \
    RT_TEX_##tag,           RT_COL(0x0),                                    \
   *ptex,                   0,                                              \
    RT_NULL,                0,                                              \
    RT_ARR_SIZE(**ptex),    RT_ARR_SIZE(*ptex)                              \
}

#define RT_TEX_ARRAY(parr)                                                  \
{/* use generic tag here */                                                 \
    RT_TAG_ARRAY,           RT_COL(0x0),                                    \
   *parr,                   RT_ARR_SIZE(*parr),                             \
    RT_NULL,                0,                                              \
    0,                      0                                               \
}

#define RT_TEX_ARRAY_REL(parr, prel)                                        \
{/* use generic tag here */                                                 \
    RT_TAG_ARRAY,           RT_COL(0x0),                                    \
   *parr,                   RT_ARR_SIZE(*parr),                             \
   *prel,                   RT_ARR_SIZE(*prel),                             \
    0,                      0                                               \
}

struct rt_TEX
{
    rt_cell             tag;
    rt_COL              col;

    rt_void            *ptex;
    rt_cell             tex_num;

    rt_RELATION        *prel;
    rt_cell             rel_num;

    rt_cell             x_dim;
    rt_cell             y_dim;
};

struct rt_TEXTURE
{
    /* TRANSFORM2D (implicit) */
    rt_vec2             scl;
    rt_real             rot;
    rt_vec2             pos;

    rt_TEX              tex;
    rt_real             wgt; /* texture's weight in the array */
};

/******************************************************************************/
/********************************   MATERIAL   ********************************/
/******************************************************************************/

#define RT_MAT_PLAIN                        0
#define RT_MAT_LIGHT                        1
#define RT_MAT_METAL                        2

#define RT_MAT(tag)                         RT_MAT_##tag

struct rt_MATERIAL
{
    rt_cell             tag;
    rt_TEX              tex;

    rt_real             lgt[4];
    rt_real             prp[4];
};

struct rt_SIDE
{
    /* TRANSFORM2D (implicit) */
    rt_vec2             scl;
    rt_real             rot;
    rt_vec2             pos;

    rt_MATERIAL        *pmat;
};

/******************************************************************************/
/*********************************   OBJECT   *********************************/
/******************************************************************************/

struct rt_OBJ
{
    rt_cell             tag;

    rt_void            *pobj;
    rt_cell             obj_num;

    rt_RELATION        *prel;
    rt_cell             rel_num;

    rt_MATERIAL        *pmat_outer; /* srf material override */
    rt_MATERIAL        *pmat_inner; /* srf material override */
};

typedef rt_void (*rt_FUNC_ANIM3D)(rt_long time, rt_long last_time,
                                  rt_TRANSFORM3D *trm, rt_pntr pobj);

struct rt_OBJECT
{
    rt_TRANSFORM3D      trm;
    rt_OBJ              obj;
    rt_FUNC_ANIM3D      f_anim;
    rt_long             time;
};

static /* needed for strict typization */
rt_cell AR_(rt_OBJECT *pobj)
{
    return RT_TAG_ARRAY;
}

#define RT_OBJ_ARRAY(parr)                                                  \
{                                                                           \
    AR_(*parr),                                                             \
   *parr,                   RT_ARR_SIZE(*parr),                             \
    RT_NULL,                0,                                              \
    RT_NULL,                RT_NULL                                         \
}

static /* needed for strict typization */
rt_cell RL_(rt_OBJECT *pobj, rt_RELATION *prel)
{
    return RT_TAG_ARRAY;
}

#define RT_OBJ_ARRAY_REL(parr, prel)                                        \
{                                                                           \
    RL_(*parr, *prel),                                                      \
   *parr,                   RT_ARR_SIZE(*parr),                             \
   *prel,                   RT_ARR_SIZE(*prel),                             \
    RT_NULL,                RT_NULL                                         \
}

/******************************************************************************/
/*********************************   CAMERA   *********************************/
/******************************************************************************/

#define RT_CAM_PLAIN                        0

#define RT_CAM(tag)                         RT_CAM_##tag

struct rt_CAMERA
{
    rt_cell             tag;
    rt_COL              col;    /* global ambient color */
    rt_real             lum[1]; /* global ambient intensity */

    rt_real             vpt[1]; /* viewport (pov: distance from screen) */
    rt_vec3             dps;    /* delta position (per unit of time) */
    rt_vec3             drt;    /* delta rotation (per unit of time) */
};

static /* needed for strict typization */
rt_cell CM_(rt_CAMERA *pobj)
{
    return RT_TAG_CAMERA;
}

#define RT_OBJ_CAMERA(pobj)                                                 \
{                                                                           \
    CM_(pobj),                                                              \
    pobj,                   1,                                              \
    RT_NULL,                0,                                              \
    RT_NULL,                RT_NULL                                         \
}

/******************************************************************************/
/**********************************   LIGHT   *********************************/
/******************************************************************************/

#define RT_LGT_PLAIN                        0

#define RT_LGT(tag)                         RT_LGT_##tag

struct rt_LIGHT
{
    rt_cell             tag;
    rt_COL              col;    /* light's color */
    rt_real             lum[2]; /* light's ambient and source intensity */
    rt_real             atn[4]; /* light's attenuation properties */
};

static /* needed for strict typization */
rt_cell LT_(rt_LIGHT *pobj)
{
    return RT_TAG_LIGHT;
}

#define RT_OBJ_LIGHT(pobj)                                                  \
{                                                                           \
    LT_(pobj),                                                              \
    pobj,                   1,                                              \
    RT_NULL,                0,                                              \
    RT_NULL,                RT_NULL                                         \
}

/******************************************************************************/
/*********************************   SURFACE   ********************************/
/******************************************************************************/

struct rt_SURFACE
{
    rt_vec3             min;
    rt_vec3             max;

    rt_SIDE             side_outer;
    rt_SIDE             side_inner;
};

/******************************************************************************/
/**********************************   PLANE   *********************************/
/******************************************************************************/

struct rt_PLANE
{
    rt_SURFACE          srf;
};

static /* needed for strict typization */
rt_cell PL_(rt_PLANE *pobj)
{
    return RT_TAG_PLANE;
}

#define RT_OBJ_PLANE(pobj)                                                  \
{                                                                           \
    PL_(pobj),                                                              \
    pobj,                   1,                                              \
    RT_NULL,                0,                                              \
    RT_NULL,                RT_NULL                                         \
}

#define RT_OBJ_PLANE_MAT(pobj, pmat_outer, pmat_inner)                      \
{                                                                           \
    PL_(pobj),                                                              \
    pobj,                   1,                                              \
    RT_NULL,                0,                                              \
    pmat_outer,             pmat_inner                                      \
}

/******************************************************************************/
/**********************************   SCENE   *********************************/
/******************************************************************************/

struct rt_SCENE
{
    rt_OBJ              root;
};

#endif /* RT_FORMAT_H */

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/