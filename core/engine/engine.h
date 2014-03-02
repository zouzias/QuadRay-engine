/******************************************************************************/
/* Copyright (c) 2013-2014 VectorChief (at github, bitbucket, sourceforge)    */
/* Distributed under the MIT software license, see the accompanying           */
/* file COPYING or http://www.opensource.org/licenses/mit-license.php         */
/******************************************************************************/

#ifndef RT_ENGINE_H
#define RT_ENGINE_H

#include "rtbase.h"
#include "rtgeom.h"
#include "object.h"
#include "system.h"
#include "tracer.h"

#undef Q /* short name for RT_SIMD_QUADS */
#undef S /* short name for RT_SIMD_WIDTH */

/******************************************************************************/
/*********************************   LEGEND   *********************************/
/******************************************************************************/

/*
 * engine.h: Interface for the scene manager.
 *
 * More detailed description of this subsystem is given in engine.cpp.
 * Recommended naming scheme for C++ types and definitions is given in rtbase.h.
 */

/******************************************************************************/
/*******************************   DEFINITIONS   ******************************/
/******************************************************************************/

/*
 * Fullscreen anti-aliasing modes.
 */
#define RT_FSAA_NO                  0
#define RT_FSAA_4X                  1

/* Classes */

class rt_SceneThread;
class rt_Scene;

/******************************************************************************/
/*********************************   THREAD   *********************************/
/******************************************************************************/

/*
 * SceneThread contains set of structures used by the scene manager per thread.
 */
class rt_SceneThread : public rt_Heap
{
/*  fields */

    private:

    /* scene pointer and thread index */
    rt_Scene           *scene;
    rt_cell             index;

    /* surface's projected bbox
     * x-coord boundaries in the tilebuffer */
    rt_cell            *txmin;
    rt_cell            *txmax;
    /* temporary bbox verts buffer */
    rt_VERT            *verts;

    public:

    /* backend specific structures */
    rt_SIMD_INFOX      *s_inf;
    rt_SIMD_CAMERA     *s_cam;
    rt_SIMD_CONTEXT    *s_ctx;

    /* memory pool in the heap
     * for temporary per-frame allocs */
    rt_pntr             mpool;
    rt_word             msize;

/*  methods */

    public:

    rt_SceneThread(rt_Scene *scene, rt_cell index);

    virtual
   ~rt_SceneThread();

    rt_void     tiling(rt_vec2 p1, rt_vec2 p2);
    rt_ELEM*    insert(rt_Object *obj, rt_ELEM **ptr, rt_Surface *srf);
    rt_ELEM*    filter(rt_Object *obj, rt_ELEM **ptr);

    rt_void     stile(rt_Surface *srf);
    rt_ELEM*    ssort(rt_Object *obj);
    rt_ELEM*    lsort(rt_Object *obj);
};

/******************************************************************************/
/*****************************   MULTI-THREADING   ****************************/
/******************************************************************************/

typedef rt_pntr (*rt_FUNC_INIT)(rt_cell thnum, rt_Scene *scn);
typedef rt_void (*rt_FUNC_TERM)(rt_pntr tdata, rt_cell thnum);
typedef rt_void (*rt_FUNC_UPDATE)(rt_pntr tdata, rt_cell thnum, rt_cell phase);
typedef rt_void (*rt_FUNC_RENDER)(rt_pntr tdata, rt_cell thnum, rt_cell phase);

/******************************************************************************/
/**********************************   SCENE   *********************************/
/******************************************************************************/

/*
 * Scene manager (or instance of the engine).
 */
class rt_Scene : private rt_LogRedirect, private rt_Registry
{
/*  fields */

    private:

    /* root scene object from scene data */
    rt_SCENE           *scn;
    /* dummy for root's identity transform */
    rt_OBJECT           rootobj;

    /* framebuffer's dimensions and pointer */
    rt_word             x_res;
    rt_word             y_res;
    rt_cell             x_row;
    rt_word            *frame;

    /* single tile dimensions in pixels */
    rt_cell             tile_w;
    rt_cell             tile_h;
    /* tilebuffer's dimensions and pointer */
    rt_cell             tiles_in_row;
    rt_cell             tiles_in_col;
    rt_ELEM           **tiles;

    /* aspect ratio and pixel width */
    rt_real             aspect;
    rt_real             factor;

    /* rays depth and anti-aliasing */
    rt_word             depth;
    rt_cell             fsaa;

    /* memory pool in the heap
     * for temporary per-frame allocs */
    rt_pntr             mpool;
    rt_word             msize;

    /* threads management functions */
    rt_FUNC_INIT        f_init;
    rt_FUNC_TERM        f_term;
    rt_FUNC_UPDATE      f_update;
    rt_FUNC_RENDER      f_render;

    /* scene threads array and its
     * platform-specific handle */
    rt_cell             thnum;
    rt_SceneThread    **tharr;
    rt_pntr             tdata;

    /* global surface list and
     * global light/shadow list
     * for rendering backend */
    rt_ELEM            *slist;
    rt_ELEM            *llist;

    /* rays positioning variables */
    rt_vec4             pos;
    rt_vec4             dir;
    /* rays steppers variables */
    rt_vec4             hor;
    rt_vec4             ver;
    /* screen's normal direction */
    rt_vec4             nrm;
    /* tiles positioning variables */
    rt_vec4             org;
    /* tiles steppers variables */
    rt_vec4             htl;
    rt_vec4             vtl;
    /* accumulated ambient color */
    rt_vec4             amb;

    /* root of the objects hierarchy */
    rt_Array           *root;
    /* current camera */
    rt_Camera          *cam;

/*  methods */

    public:

    rt_Scene(rt_SCENE *scn, /* frame must be SIMD-aligned */
             rt_word x_res, rt_word y_res, rt_cell x_row, rt_word *frame,
             rt_FUNC_ALLOC f_alloc, rt_FUNC_FREE f_free,
             rt_FUNC_INIT f_init = RT_NULL, rt_FUNC_TERM f_term = RT_NULL,
             rt_FUNC_UPDATE f_update = RT_NULL,
             rt_FUNC_RENDER f_render = RT_NULL,
             rt_FUNC_PRINT_LOG f_print_log = RT_NULL,
             rt_FUNC_PRINT_ERR f_print_err = RT_NULL);

    virtual
   ~rt_Scene();

    rt_void     update(rt_long time, rt_cell action);
    rt_void     render(rt_long time);

    rt_void     update_slice(rt_cell index, rt_cell phase);
    rt_void     render_slice(rt_cell index, rt_cell phase);

    rt_void     render_fps(rt_word x, rt_word y,
                           rt_cell d, rt_word z, rt_word num);

    rt_word*    get_frame();
    rt_void     print_state();

    rt_void     set_fsaa(rt_cell fsaa);
    rt_void     set_opts(rt_cell opts);

    rt_void     next_cam();
    rt_void     save_frame(rt_cell index);

    friend      class rt_SceneThread;
};

#endif /* RT_ENGINE_H */

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
