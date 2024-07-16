/*
 * Copyright (c) Hisilicon Technologies Co., Ltd. 2019-2020. All rights reserved.
 * Description: gdc user struct and err code adapt declaration
 * Author: Hisilicon multimedia software group
 * Create: 2019/06/27
 */
#ifndef __HI_COMMON_GDC_H__
#define __HI_COMMON_GDC_H__

#include "hi_type.h"
#include "hi_common.h"
#include "hi_errno.h"
#include "hi_common_video.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/* failure caused by malloc buffer */
#define HI_ERR_GDC_NO_BUF           HI_DEFINE_ERR(HI_ID_GDC, HI_ERR_LEVEL_ERROR, HI_ERR_NO_BUF)
#define HI_ERR_GDC_BUF_EMPTY        HI_DEFINE_ERR(HI_ID_GDC, HI_ERR_LEVEL_ERROR, HI_ERR_BUF_EMPTY)
#define HI_ERR_GDC_NULL_PTR         HI_DEFINE_ERR(HI_ID_GDC, HI_ERR_LEVEL_ERROR, HI_ERR_NULL_PTR)
#define HI_ERR_GDC_ILLEGAL_PARAM    HI_DEFINE_ERR(HI_ID_GDC, HI_ERR_LEVEL_ERROR, HI_ERR_ILLEGAL_PARAM)
#define HI_ERR_GDC_BUF_FULL         HI_DEFINE_ERR(HI_ID_GDC, HI_ERR_LEVEL_ERROR, HI_ERR_BUF_FULL)
#define HI_ERR_GDC_NOT_READY        HI_DEFINE_ERR(HI_ID_GDC, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_READY)
#define HI_ERR_GDC_NOT_SUPPORT      HI_DEFINE_ERR(HI_ID_GDC, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_SUPPORT)
#define HI_ERR_GDC_NOT_PERM         HI_DEFINE_ERR(HI_ID_GDC, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_PERM)
#define HI_ERR_GDC_BUSY             HI_DEFINE_ERR(HI_ID_GDC, HI_ERR_LEVEL_ERROR, HI_ERR_BUSY)
#define HI_ERR_GDC_INVALID_CHN_ID   HI_DEFINE_ERR(HI_ID_GDC, HI_ERR_LEVEL_ERROR, HI_ERR_INVALID_CHN_ID)
#define HI_ERR_GDC_CHN_UNEXIST      HI_DEFINE_ERR(HI_ID_GDC, HI_ERR_LEVEL_ERROR, HI_ERR_UNEXIST)

#define HI_GDC_PRIVATE_DATA_NUM         4
#define HI_GDC_PMF_COEF_NUM             9

#define HI_FISHEYE_MAX_RGN_NUM          4
#define HI_FISHEYE_LMF_COEF_NUM         128

typedef hi_u32 hi_gdc_handle;

typedef struct {
    hi_video_frame_info img_in; /* input picture */
    hi_video_frame_info img_out; /* output picture */
    hi_u64 private_data[HI_GDC_PRIVATE_DATA_NUM]; /* RW; private data of task */
    hi_u64 reserved; /* RW; debug information,state of current picture */
} hi_gdc_task_attr;

/* mount mode of device */
typedef enum {
    HI_FISHEYE_MOUNT_MODE_DESKTOP = 0, /* Desktop mount mode */
    HI_FISHEYE_MOUNT_MODE_CEILING = 1, /* Ceiling mount mode */
    HI_FISHEYE_MOUNT_MODE_WALL = 2, /* wall mount mode */

    HI_FISHEYE_MOUNT_MODE_BUTT
} hi_fisheye_mount_mode;

/* view mode of client */
typedef enum {
    HI_FISHEYE_VIEW_MODE_360_PANORAMA = 0, /* 360 panorama mode of gdc correction */
    HI_FISHEYE_VIEW_MODE_180_PANORAMA = 1, /* 180 panorama mode of gdc correction */
    HI_FISHEYE_VIEW_MODE_NORM = 2, /* normal mode of gdc correction */
    HI_FISHEYE_VIEW_MODE_NO_TRANS = 3, /* no gdc correction */

    HI_FISHEYE_VIEW_MODE_BUTT
} hi_fisheye_view_mode;

/* fisheye region correction attribute */
typedef struct {
    hi_fisheye_view_mode view_mode; /* RW; range: [0, 3];gdc view mode */
    hi_u32 in_radius; /* RW; inner radius of gdc correction region */
    hi_u32 out_radius; /* RW; out radius of gdc correction region */
    hi_u32 pan; /* RW; range: [0, 360] */
    hi_u32 tilt; /* RW; range: [0, 360] */
    hi_u32 hor_zoom; /* RW; Range: [1, 5265]; horizontal zoom of correction region */
    hi_u32 ver_zoom; /* RW; Range: [1, 4095]; vertical zoom of correction region */
    hi_rect out_rect; /* RW; out imge rectangle attribute */
} hi_fisheye_rgn_attr;

typedef struct {
    hi_fisheye_view_mode view_mode; /* RW; range: [0, 3];gdc view mode */
    hi_u32 in_radius; /* RW; inner radius of gdc correction region */
    hi_u32 out_radius; /* RW; out radius of gdc correction region */
    hi_u32 x; /* RW; Range: [0, 8192); x-coordinate of the centre point of correction region */
    hi_u32 y; /* RW; Range: [0, 8192); y-coordinate of the centre point of correction region */
    hi_u32 hor_zoom; /* RW; Range: [1, 4095]; horizontal zoom of correction region */
    hi_u32 ver_zoom; /* RW; Range: [1, 4095]; vertical zoom of correction region */
    hi_rect out_rect; /* RW; out imge rectangle attribute */
} hi_fisheye_rgn_attr_ex;

/* fisheye all regions correction attribute */
typedef struct {
     /*
      * RW; range: [0, 1];
      * whether gdc len's LMF coefficient is from user config or from default linear config
      */
    hi_bool lmf_en;
    hi_bool bg_color_en; /* RW; range: [0, 1];whether use background color or not */
    hi_u32  bg_color; /* RW; range: [0,0xffffff];the background color RGB888 */

    /*
     * RW; range: [-511, 511];
     * the horizontal offset between image center and physical center of len
     */
    hi_s32  hor_offset;
    /*
     * RW; range: [-511, 511];
     * the vertical offset between image center and physical center of len
     */
    hi_s32  ver_offset;

    hi_u32  trapezoid_coef; /* RW; range: [0, 32];strength coefficient of trapezoid correction */
    hi_s32  fan_strength; /* RW; range: [-760, 760];strength coefficient of fan correction */

    hi_fisheye_mount_mode mount_mode; /* RW; range: [0, 2];gdc mount mode */

    hi_u32 rgn_num; /* RW; range: [1, 4]; gdc correction region number */
    hi_fisheye_rgn_attr fisheye_rgn_attr[HI_FISHEYE_MAX_RGN_NUM]; /* RW; attribution of gdc correction region */
} hi_fisheye_attr;

typedef struct {
     /*
      * RW; range: [0, 1];
      * whether gdc len's LMF coefficient is from user config or from default linear config
      */
    hi_bool lmf_en;
    hi_bool bg_color_en; /* RW; range: [0, 1];whether use background color or not */
    hi_u32 bg_color; /* RW; range: [0,0xffffff];the background color RGB888 */

    /*
     * RW; range: [-511, 511];
     * the horizontal offset between image center and physical center of len
     */
    hi_s32 hor_offset;
    /*
     * RW; range: [-511, 511];
     * the vertical offset between image center and physical center of len
     */
    hi_s32 ver_offset;

    hi_u32 trapezoid_coef; /* RW; range: [0, 32];strength coefficient of trapezoid correction */
    hi_s32 fan_strength; /* RW; range: [-760, 760];strength coefficient of fan correction */

    hi_fisheye_mount_mode mount_mode; /* RW; range: [0, 2];gdc mount mode */

    hi_u32 rgn_num; /* RW; range: [1, 4]; gdc correction region number */
    hi_fisheye_rgn_attr_ex fisheye_rgn_attr[HI_FISHEYE_MAX_RGN_NUM]; /* RW; attribution of gdc correction region */
} hi_fisheye_attr_ex;

/* fisheye correction attribute in channel */
typedef struct {
    hi_bool enable; /* RW; range: [0, 1]; */
    hi_fisheye_attr fisheye_attr;
    hi_size dst_size; /* RW; range: width:[640, 8192],height:[360, 8192]; */
} hi_fisheye_correction_attr;

/* fisheye config */
typedef struct {
    hi_u16 lmf_coef[HI_FISHEYE_LMF_COEF_NUM]; /* RW;  LMF coefficient of gdc len */
} hi_fisheye_cfg;

/* fisheye job config */
typedef struct {
    hi_phys_addr_t len_map_phys_addr; /* LMF coefficient physic addr */
} hi_gdc_fisheye_job_cfg;

/* gdc PMF attr */
typedef struct {
    hi_s64 pmf_coef[HI_GDC_PMF_COEF_NUM]; /* W;  PMF coefficient of gdc */
} hi_gdc_pmf_attr;

/* Gdc FISHEYE POINT QUERY Attr */
typedef struct {
    hi_u32 rgn_index;
    hi_fisheye_attr *fisheye_attr;
    hi_u16 lmf_coef[HI_FISHEYE_LMF_COEF_NUM];
} hi_gdc_fisheye_point_query_attr;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_COMMON_GDC_H__ */
