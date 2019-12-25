/******************************************************************************/
/* Copyright (c) 2013-2014 VectorChief (at github, bitbucket, sourceforge)    */
/* Distributed under the MIT software license, see the accompanying           */
/* file COPYING or http://www.opensource.org/licenses/mit-license.php         */
/******************************************************************************/

#include <malloc.h>
#include <string.h>

#include "engine.h"

#define RUN_LEVEL       9
#define VERBOSE         RT_FALSE
#define CYC_SIZE        5

#define RT_X_RES        800
#define RT_Y_RES        480

rt_cell     x_res   = RT_X_RES;
rt_cell     y_res   = RT_Y_RES;
rt_cell     x_row   = RT_X_RES;
rt_word     frame[RT_X_RES * RT_Y_RES];

rt_cell     fsaa    = RT_FSAA_NO;

rt_Scene   *scene   = RT_NULL;

static
rt_void frame_cpy(rt_word *fd, rt_word *fs)
{
    rt_cell i;

    for (i = 0; i < y_res * x_row; i++)
    {
       *fd++ = *fs++;
    }
}

static
rt_cell frame_cmp(rt_word *f1, rt_word *f2)
{
    rt_cell i, ret = 0;

    for (i = 0; i < y_res * x_row; i++)
    {
        if (f1[i] != f2[i])
        {
            ret = 1;

            RT_LOGI("Frames differ (%06X %06X) at x = %d, y = %d\n",
                        f1[i], f2[i], i % x_row, i / x_row);

            if (!VERBOSE)
            {
                break;
            }
        }
    }

    if (VERBOSE && ret == 0)
    {
        RT_LOGI("Frames are identical\n");
    }

    return ret;
}

/******************************************************************************/
/******************************   RUN LEVEL  1   ******************************/
/******************************************************************************/

#if RUN_LEVEL >=  1

#include "scn_test01.h"

rt_void test01(rt_cell opts)
{
    scene = new rt_Scene(&scn_test01::sc_root,
                        x_res, y_res, x_row, RT_NULL,
                        malloc, free,
                        RT_NULL, RT_NULL,
                        RT_NULL, RT_NULL);

    scene->set_opts(opts);
}

#endif /* RUN_LEVEL  1 */

/******************************************************************************/
/******************************   RUN LEVEL  2   ******************************/
/******************************************************************************/

#if RUN_LEVEL >=  2

#include "scn_test02.h"

rt_void test02(rt_cell opts)
{
    scene = new rt_Scene(&scn_test02::sc_root,
                        x_res, y_res, x_row, RT_NULL,
                        malloc, free,
                        RT_NULL, RT_NULL,
                        RT_NULL, RT_NULL);

    scene->set_opts(opts);
}

#endif /* RUN_LEVEL  2 */

/******************************************************************************/
/******************************   RUN LEVEL  3   ******************************/
/******************************************************************************/

#if RUN_LEVEL >=  3

#include "scn_test03.h"

rt_void test03(rt_cell opts)
{
    scene = new rt_Scene(&scn_test03::sc_root,
                        x_res, y_res, x_row, RT_NULL,
                        malloc, free,
                        RT_NULL, RT_NULL,
                        RT_NULL, RT_NULL);

    scene->set_opts(opts);
}

#endif /* RUN_LEVEL  3 */

/******************************************************************************/
/******************************   RUN LEVEL  4   ******************************/
/******************************************************************************/

#if RUN_LEVEL >=  4

#include "scn_test04.h"

rt_void test04(rt_cell opts)
{
    scene = new rt_Scene(&scn_test04::sc_root,
                        x_res, y_res, x_row, RT_NULL,
                        malloc, free,
                        RT_NULL, RT_NULL,
                        RT_NULL, RT_NULL);

    scene->set_opts(opts);
}

#endif /* RUN_LEVEL  4 */

/******************************************************************************/
/******************************   RUN LEVEL  5   ******************************/
/******************************************************************************/

#if RUN_LEVEL >=  5

#include "scn_test05.h"

rt_void test05(rt_cell opts)
{
    scene = new rt_Scene(&scn_test05::sc_root,
                        x_res, y_res, x_row, RT_NULL,
                        malloc, free,
                        RT_NULL, RT_NULL,
                        RT_NULL, RT_NULL);

    scene->set_opts(opts);
}

#endif /* RUN_LEVEL  5 */

/******************************************************************************/
/******************************   RUN LEVEL  6   ******************************/
/******************************************************************************/

#if RUN_LEVEL >=  6

#include "scn_test06.h"

rt_void test06(rt_cell opts)
{
    scene = new rt_Scene(&scn_test06::sc_root,
                        x_res, y_res, x_row, RT_NULL,
                        malloc, free,
                        RT_NULL, RT_NULL,
                        RT_NULL, RT_NULL);

    scene->set_opts(opts);
}

#endif /* RUN_LEVEL  6 */

/******************************************************************************/
/******************************   RUN LEVEL  7   ******************************/
/******************************************************************************/

#if RUN_LEVEL >=  7

#include "scn_test07.h"

rt_void test07(rt_cell opts)
{
    scene = new rt_Scene(&scn_test07::sc_root,
                        x_res, y_res, x_row, RT_NULL,
                        malloc, free,
                        RT_NULL, RT_NULL,
                        RT_NULL, RT_NULL);

    scene->set_opts(opts);
}

#endif /* RUN_LEVEL  7 */

/******************************************************************************/
/******************************   RUN LEVEL  8   ******************************/
/******************************************************************************/

#if RUN_LEVEL >=  8

#include "scn_test08.h"

rt_void test08(rt_cell opts)
{
    scene = new rt_Scene(&scn_test08::sc_root,
                        x_res, y_res, x_row, RT_NULL,
                        malloc, free,
                        RT_NULL, RT_NULL,
                        RT_NULL, RT_NULL);

    scene->set_opts(opts);
}

#endif /* RUN_LEVEL  8 */

/******************************************************************************/
/******************************   RUN LEVEL  9   ******************************/
/******************************************************************************/

#if RUN_LEVEL >=  9

#include "scn_test09.h"

rt_void test09(rt_cell opts)
{
    scene = new rt_Scene(&scn_test09::sc_root,
                        x_res, y_res, x_row, RT_NULL,
                        malloc, free,
                        RT_NULL, RT_NULL,
                        RT_NULL, RT_NULL);

    scene->set_opts(opts);
}

#endif /* RUN_LEVEL  9 */

/******************************************************************************/
/*********************************   TABLES   *********************************/
/******************************************************************************/

typedef rt_void (*testXX)(rt_cell);

testXX test[RUN_LEVEL] =
{
#if RUN_LEVEL >=  1
    test01,
#endif /* RUN_LEVEL  1 */

#if RUN_LEVEL >=  2
    test02,
#endif /* RUN_LEVEL  2 */

#if RUN_LEVEL >=  3
    test03,
#endif /* RUN_LEVEL  3 */

#if RUN_LEVEL >=  4
    test04,
#endif /* RUN_LEVEL  4 */

#if RUN_LEVEL >=  5
    test05,
#endif /* RUN_LEVEL  5 */

#if RUN_LEVEL >=  6
    test06,
#endif /* RUN_LEVEL  6 */

#if RUN_LEVEL >=  7
    test07,
#endif /* RUN_LEVEL  7 */

#if RUN_LEVEL >=  8
    test08,
#endif /* RUN_LEVEL  8 */

#if RUN_LEVEL >=  9
    test09,
#endif /* RUN_LEVEL  9 */
};

/******************************************************************************/
/**********************************   MAIN   **********************************/
/******************************************************************************/

rt_long get_time();

rt_cell main()
{
    rt_long time1 = 0;
    rt_long time2 = 0;
    rt_long tN = 0;
    rt_long tF = 0;

    rt_cell i, j;

    for (i = 0; i < RUN_LEVEL; i++)
    {
        RT_LOGI("-----------------  RUN LEVEL = %2d  -----------------\n", i+1);
        try
        {
            scene = RT_NULL;
            test[i](RT_OPTS_NONE);

            time1 = get_time();

            for (j = 0; j < CYC_SIZE; j++)
            {
                scene->render(j * 16);
            }

            time2 = get_time();
            tN = time2 - time1;
            RT_LOGI("Time N = %d\n", (rt_cell)tN);

            frame_cpy(frame, scene->get_frame());
            delete scene;


            scene = RT_NULL;
            test[i](RT_OPTS_FULL);

            time1 = get_time();

            for (j = 0; j < CYC_SIZE; j++)
            {
                scene->render(j * 16);
            }

            time2 = get_time();
            tF = time2 - time1;
            RT_LOGI("Time F = %d\n", (rt_cell)tF);

            frame_cmp(frame, scene->get_frame());
            delete scene;
        }
        catch (rt_Exception e)
        {
            RT_LOGE("Exception: %s\n", e.err);
        }
        RT_LOGI("----------------------------------------------------\n");
    }

#if   defined (RT_WIN32) /* Win32, MSVC ------------------------------------- */

    RT_LOGI("Type any letter and press ENTER to exit:");
    rt_char str[256]; /* not secure, do not inherit this practice */
    scanf("%s", str); /* not secure, do not inherit this practice */

#endif /* ----------------- OS specific ------------------------------------- */

    return 0;
}

#if   defined (RT_WIN32) /* Win32, MSVC ------------------------------------- */

#include <windows.h>

rt_long get_time()
{
    LARGE_INTEGER fr;
    QueryPerformanceFrequency(&fr);
    LARGE_INTEGER tm;
    QueryPerformanceCounter(&tm);
    return (rt_long)(tm.QuadPart * 1000 / fr.QuadPart);
}

#elif defined (RT_LINUX) /* Linux, GCC -------------------------------------- */

#include <sys/time.h>

rt_long get_time()
{
    timeval tm;
    gettimeofday(&tm, NULL);
    return (rt_long)(tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

#endif /* ----------------- OS specific ------------------------------------- */

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
