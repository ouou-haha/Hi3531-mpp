/*
 * Copyright (c) Hisilicon Technologies Co., Ltd. 2019-2020. All rights reserved.
 * Description:Common definition  struct of region
 * Author: Hisilicon multimedia software group
 * Create: 2019/06/15
 */

#ifndef __HI_COMMON_REGION_H__
#define __HI_COMMON_REGION_H__

#include "hi_common.h"
#include "hi_common_video.h"
#include "hi_errno.h"
#include "hi_defines.h"

#define HI_RGN_MAX_BMP_UPDATE_NUM      16
#define HI_RGN_BATCH_HANDLE_MAX        24
#define HI_RGN_QUAD_POINT_NUM          4
#define HI_RGN_LINE_POINT_NUM          2
#define HI_RGN_CLUT_NUM                16
typedef hi_u32 hi_rgn_handle;
typedef hi_u32 hi_rgn_handle_grp;

/* type of video regions */
typedef enum {
    HI_RGN_OVERLAY = 0,
    HI_RGN_COVER,
    HI_RGN_OVERLAYEX,
    HI_RGN_COVEREX,
    HI_RGN_LINE,
    HI_RGN_MOSAIC,
    HI_RGN_MOSAICEX,
    HI_RGN_CORNER_RECTEX,
    HI_RGN_BUTT
} hi_rgn_type;

typedef enum  {
    HI_RGN_ATTACH_JPEG_MAIN = 0,
    HI_RGN_ATTACH_JPEG_MPF0,
    HI_RGN_ATTACH_JPEG_MPF1,
    HI_RGN_ATTACH_JPEG_BUTT
} hi_rgn_attach_dst;

typedef struct {
    hi_bool        enable;
    hi_bool        is_abs_qp;
    hi_s32         qp_val;
} hi_rgn_overlay_qp_info;

typedef struct {
    hi_pixel_format        pixel_format;    /* bitmap pixel format now support clut2 and clut4 */
    hi_u32                 bg_color;    /* background color, pixel format depends on "pixel_format" */
    /*
     * region size, width:[2, HI_RGN_OVERLAY_MAX_WIDTH], align:2,
     * height:[2, HI_RGN_OVERLAY_MAX_HEIGHT], align:2
     */
    hi_size                size;
    hi_u32                 canvas_num;
    hi_u32                 clut[HI_RGN_CLUT_NUM];      /* color look up table */
} hi_rgn_overlay_attr;

typedef struct {
    /*
     * x:[0, HI_RGN_OVERLAY_MAX_X], align:2,
     * y:[0, HI_RGN_OVERLAY_MAX_Y], align:2
     */
    hi_point                       point;
    hi_u32                         fg_alpha;
    hi_u32                         bg_alpha;
    hi_u32                         layer;     /* OVERLAY region layer range depends on OVERLAY max num */
    hi_rgn_overlay_qp_info         qp_info;
    hi_rgn_attach_dst              dst;
} hi_rgn_overlay_chn_attr;

typedef struct {
    hi_pixel_format                pixel_format;
    hi_u32                         bg_color;    /* background color, pixel format depends on "pixel_format" */
    /*
     * region size, width:[2, HI_RGN_OVERLAY_MAX_WIDTH], align:2,
     * height:[2, HI_RGN_OVERLAY_MAX_HEIGHT], align:2
     */
    hi_size                        size;
    hi_u32                         canvas_num;
    hi_u32                         clut[HI_RGN_CLUT_NUM];
} hi_rgn_overlayex_attr;

typedef struct {
    /*
     * x:[0, HI_RGN_OVERLAYEX_MAX_X], align:2,
     * y:[0, HI_RGN_OVERLAYEX_MAX_Y], align:2
     */
    hi_point                       point;
    hi_u32                         fg_alpha;
    hi_u32                         bg_alpha;
    hi_u32                         layer;     /* OVERLAYEX region layer range depends on OVERLAYEX max num */
} hi_rgn_overlayex_chn_attr;

typedef struct {
    hi_cover                       cover;
    hi_u32                         layer;  /* COVER region layer range depends on COVER max num */
    hi_coord                       coord;  /* ratio coordinate or abs coordinate */
} hi_rgn_cover_chn_attr;

typedef struct {
    hi_cover                       coverex;
    hi_u32                         layer;  /* COVEREX region layer range depends on COVEREX max num */
    hi_coord                       coord;  /* ratio coordinate or abs coordinate */
} hi_rgn_coverex_chn_attr;

typedef struct {
    hi_rect                        rect;              /* location of MOSAIC */
    hi_mosaic_blk_size             blk_size;          /* block size of MOSAIC */
    hi_u32                         layer;             /* MOSAIC region layer range depends on MOSAIC max num */
} hi_rgn_mosaic_chn_attr;

typedef struct {
    hi_rect                        rect;              /* location of MOSAICEX */
    hi_mosaic_blk_size             blk_size;          /* block size of MOSAIC EX */
    hi_u32                         layer;             /* MOSAICEX region layer range depends on MOSAICEX max num */
} hi_rgn_mosaicex_chn_attr;

typedef union {
    hi_rgn_overlay_attr           overlay; /* attribute of overlay region. AUTO:hi_rgn_type:HI_RGN_OVERLAY; */
    hi_rgn_overlayex_attr         overlayex; /* attribute of overlayex region. AUTO:hi_rgn_type:HI_RGN_OVERLAYEX; */
} hi_rgn_type_attr;

typedef struct {
    /* width of line range[HI_RGN_LINE_MIN_THICK, HI_RGN_LINE_MAX_THICK] */
    hi_u32                         thick;
    hi_u32                         color;                           /* color of line range [0, 0xffffff] */
    hi_point                       points[HI_RGN_LINE_POINT_NUM];   /* startpoint and endpoint of line */
} hi_rgn_line_chn_attr;

typedef struct {
    hi_corner_rect                 corner_rect;      /* location and size of corner rect */
    hi_corner_rect_attr            corner_rect_attr; /* attribute of corner rect region */
    hi_u32                         layer;            /* CORNER_RECT region layer range depends on CORNER_RECT max num */
} hi_rgn_corner_rect_chn_attr;

typedef union {
    hi_rgn_overlay_chn_attr     overlay_chn; /* attribute of overlay region. AUTO:hi_rgn_type:HI_RGN_OVERLAY; */
    hi_rgn_cover_chn_attr       cover_chn; /* attribute of cover region. AUTO:hi_rgn_type: HI_RGN_COVER; */
    hi_rgn_overlayex_chn_attr   overlayex_chn; /* attribute of overlayex region. AUTO:hi_rgn_type: HI_RGN_OVERLAYEX; */
    hi_rgn_coverex_chn_attr     coverex_chn; /* attribute of coverex region. AUTO:hi_rgn_type:HI_RGN_COVEREX; */
    hi_rgn_line_chn_attr        line_chn; /* attribute of line region. AUTO:hi_rgn_type:HI_RGN_LINE; */
    hi_rgn_mosaic_chn_attr      mosaic_chn; /* attribute of mosaic region. AUTO:hi_rgn_type:HI_RGN_MOSAIC; */
    hi_rgn_mosaicex_chn_attr    mosaicex_chn; /* attribute of mosaicex region. AUTO:hi_rgn_type:HI_RGN_MOSAICEX; */
    /*
     * attribute of corner rectex region.
     * AUTO:hi_rgn_type:HI_RGN_CORNER_RECTEX;
     */
    hi_rgn_corner_rect_chn_attr corner_rectex_chn;
} hi_rgn_type_chn_attr;

/* attribute of a region */
typedef struct {
    hi_rgn_type                    type;
    hi_rgn_type_attr               attr; /* region attribute */
} hi_rgn_attr;

/* attribute of a region */
typedef struct {
    hi_bool                        is_show;
    hi_rgn_type                    type;
    hi_rgn_type_chn_attr           attr;        /* region attribute */
} hi_rgn_chn_attr;

typedef struct {
    hi_phys_addr_t                 phys_addr;
    hi_size                        size;
    hi_u32                         stride;
    hi_pixel_format                pixel_format;
    hi_void  ATTRIBUTE             *virt_addr;
} hi_rgn_canvas_info;

    /* invalid device ID */
#define HI_ERR_RGN_INVALID_DEV_ID HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_INVALID_DEV_ID)
    /* invalid channel ID */
#define HI_ERR_RGN_INVALID_CHN_ID HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_INVALID_CHN_ID)
    /* at least one parameter is illegal, e.g. an illegal enumeration value */
#define HI_ERR_RGN_ILLEGAL_PARAM HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_ILLEGAL_PARAM)
    /* channel exists */
#define HI_ERR_RGN_EXIST HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_EXIST)
    /* not exist */
#define HI_ERR_RGN_UNEXIST HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_UNEXIST)
    /* using a NULL pointer */
#define HI_ERR_RGN_NULL_PTR HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_NULL_PTR)
    /* try to enable or initialize system, device or channel, before configuring attribute */
#define HI_ERR_RGN_NOT_CFG HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_CFG)
    /* operation is not supported */
#define HI_ERR_RGN_NOT_SUPPORT HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_SUPPORT)
    /* operation is not permitted, e.g. try to change static attribute */
#define HI_ERR_RGN_NOT_PERM HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_PERM)
    /* failure caused by malloc memory */
#define HI_ERR_RGN_NO_MEM HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_NO_MEM)
    /* failure caused by malloc buffer */
#define HI_ERR_RGN_NO_BUF HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_NO_BUF)
    /* no data in buffer */
#define HI_ERR_RGN_BUF_EMPTY HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_BUF_EMPTY)
    /* no buffer for new data */
#define HI_ERR_RGN_BUF_FULL HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_BUF_FULL)
    /* bad address, e.g. used for copy_from_user & copy_to_user */
#define HI_ERR_RGN_BAD_ADDR HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_BAD_ADDR)
    /* resource is busy, e.g. destroy a venc chn without unregistering it */
#define HI_ERR_RGN_BUSY HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_BUSY)
    /*
     * System is not ready, maybe not initialized or loaded.
     * Returning the error code when opening a device file failed.
     */
#define HI_ERR_RGN_NOT_READY HI_DEFINE_ERR(HI_ID_RGN, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_READY)

#endif /* __HI_COMMON_REGION_H__ */
