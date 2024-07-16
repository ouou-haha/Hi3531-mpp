/*
 * Copyright (c) Hisilicon Technologies Co., Ltd. 2017-2019. All rights reserved.
 * Description:Initial Draft
 * Author: Hisilicon multimedia software group
 * Create: 2017/07/15
 */

#ifndef __HI_COMMON_VIDEO_H__
#define __HI_COMMON_VIDEO_H__

#include "hi_type.h"
#include "hi_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define HI_ISP_BAYER_CHN           4
#define HI_DCF_DRSCRIPTION_LENGTH  32
#define HI_DCF_CAPTURE_TIME_LENGTH 20
#define HI_CFACOLORPLANE           3
#define HI_DNG_NP_SIZE             6
#define HI_ISP_WB_GAIN_NUM         4
/* 3*3=9 matrix */
#define HI_ISP_CAP_CCM_NUM         9
#define HI_SRC_LENS_COEF_NUM       9
#define HI_DST_LENS_COEF_NUM       14
#define HI_ISP_WDR_MAX_FRAME_NUM  4

typedef enum  {
    HI_OP_MODE_AUTO   = 0,
    HI_OP_MODE_MANUAL = 1,
    HI_OP_MODE_BUTT
} hi_op_mode;

typedef enum  {
    HI_VB_SRC_COMMON  = 0,
    HI_VB_SRC_MOD  = 1,
    HI_VB_SRC_PRIVATE = 2,
    HI_VB_SRC_USER    = 3,
    HI_VB_SRC_BUTT
} hi_vb_src;

typedef enum  {
    HI_ASPECT_RATIO_NONE   = 0,        /* full screen */
    HI_ASPECT_RATIO_AUTO   = 1,        /* ratio no change, 1:1 */
    HI_ASPECT_RATIO_MANUAL = 2,        /* ratio manual set */
    HI_ASPECT_RATIO_BUTT
} hi_aspect_ratio_type;

typedef enum  {
    HI_VIDEO_FIELD_TOP         = 1,    /* even field */
    HI_VIDEO_FIELD_BOTTOM      = 2,    /* odd field */
    HI_VIDEO_FIELD_INTERLACED  = 3,    /* two interlaced fields */
    HI_VIDEO_FIELD_FRAME       = 4,    /* frame */

    HI_VIDEO_FIELD_BUTT
} hi_video_field;

typedef enum  {
    HI_VIDEO_FORMAT_LINEAR = 0,       /* nature video line */
    HI_VIDEO_FORMAT_TILE_64x16,       /* tile cell: 64pixel x 16line */
    HI_VIDEO_FORMAT_TILE_16x8,        /* tile cell: 16pixel x 8line */
    HI_VIDEO_FORMAT_BUTT
} hi_video_format;

typedef enum  {
    HI_COMPRESS_MODE_NONE = 0,      /* no compress */
    HI_COMPRESS_MODE_SEG,           /* compress unit is 256x1 bytes as a segment. */
    HI_COMPRESS_MODE_SEG_COMPACT,   /* compact compress unit is 256x1 bytes as a segment. */
    HI_COMPRESS_MODE_TILE,          /* compress unit is a tile. */
    HI_COMPRESS_MODE_LINE,          /* compress unit is the whole line. */
    HI_COMPRESS_MODE_FRAME,         /* compress unit is the whole frame. YUV for VPSS(3DNR) */

    HI_COMPRESS_MODE_BUTT
} hi_compress_mode;

typedef enum  {
    HI_VIDEO_DISPLAY_MODE_PREVIEW  = 0,
    HI_VIDEO_DISPLAY_MODE_PLAYBACK = 1,

    HI_VIDEO_DISPLAY_MODE_BUTT
} hi_video_display_mode;

typedef enum  {
    HI_FRAME_FLAG_SNAP_FLASH  = 0x1 << 0,
    HI_FRAME_FLAG_SNAP_CUR    = 0x1 << 1,
    HI_FRAME_FLAG_SNAP_REF    = 0x1 << 2,
    HI_FRAME_FLAG_SNAP_END    = 0x1 << 3,
    HI_FRAME_FLAG_MIRROR      = 0x1 << 4,
    HI_FRAME_FLAG_FLIP        = 0x1 << 5,
    HI_FRAME_FLAG_BUTT
} hi_frame_flag;

typedef enum  {
    HI_COLOR_GAMUT_BT601 = 0,
    HI_COLOR_GAMUT_BT709,
    HI_COLOR_GAMUT_BT2020,
    HI_COLOR_GAMUT_USER,
    HI_COLOR_GAMUT_BUTT
} hi_color_gamut;

/* we ONLY define picture format used, all unused will be deleted! */
typedef enum {
    HI_PIXEL_FORMAT_RGB_444 = 0,
    HI_PIXEL_FORMAT_RGB_555,
    HI_PIXEL_FORMAT_RGB_565,
    HI_PIXEL_FORMAT_RGB_888,

    HI_PIXEL_FORMAT_BGR_444,
    HI_PIXEL_FORMAT_BGR_555,
    HI_PIXEL_FORMAT_BGR_565,
    HI_PIXEL_FORMAT_BGR_888,

    HI_PIXEL_FORMAT_ARGB_1555,
    HI_PIXEL_FORMAT_ARGB_4444,
    HI_PIXEL_FORMAT_ARGB_8565,
    HI_PIXEL_FORMAT_ARGB_8888,
    HI_PIXEL_FORMAT_ARGB_2BPP,
    HI_PIXEL_FORMAT_ARGB_CLUT2,
    HI_PIXEL_FORMAT_ARGB_CLUT4,

    HI_PIXEL_FORMAT_ABGR_1555,
    HI_PIXEL_FORMAT_ABGR_4444,
    HI_PIXEL_FORMAT_ABGR_8565,
    HI_PIXEL_FORMAT_ABGR_8888,

    HI_PIXEL_FORMAT_RGB_BAYER_8BPP,
    HI_PIXEL_FORMAT_RGB_BAYER_10BPP,
    HI_PIXEL_FORMAT_RGB_BAYER_12BPP,
    HI_PIXEL_FORMAT_RGB_BAYER_14BPP,
    HI_PIXEL_FORMAT_RGB_BAYER_16BPP,

    HI_PIXEL_FORMAT_YVU_PLANAR_422,
    HI_PIXEL_FORMAT_YVU_PLANAR_420,
    HI_PIXEL_FORMAT_YVU_PLANAR_444,

    HI_PIXEL_FORMAT_YVU_SEMIPLANAR_422,
    HI_PIXEL_FORMAT_YVU_SEMIPLANAR_420,
    HI_PIXEL_FORMAT_YVU_SEMIPLANAR_444,

    HI_PIXEL_FORMAT_YUV_SEMIPLANAR_422,
    HI_PIXEL_FORMAT_YUV_SEMIPLANAR_420,
    HI_PIXEL_FORMAT_YUV_SEMIPLANAR_444,

    HI_PIXEL_FORMAT_YUYV_PACKAGE_422,
    HI_PIXEL_FORMAT_YVYU_PACKAGE_422,
    HI_PIXEL_FORMAT_UYVY_PACKAGE_422,
    HI_PIXEL_FORMAT_VYUY_PACKAGE_422,
    HI_PIXEL_FORMAT_YYUV_PACKAGE_422,
    HI_PIXEL_FORMAT_YYVU_PACKAGE_422,
    HI_PIXEL_FORMAT_UVYY_PACKAGE_422,
    HI_PIXEL_FORMAT_VUYY_PACKAGE_422,
    HI_PIXEL_FORMAT_VY1UY0_PACKAGE_422,

    HI_PIXEL_FORMAT_YUV_400,
    HI_PIXEL_FORMAT_UV_420,

    /* SVP data format */
    HI_PIXEL_FORMAT_BGR_888_PLANAR,
    HI_PIXEL_FORMAT_HSV_888_PACKAGE,
    HI_PIXEL_FORMAT_HSV_888_PLANAR,
    HI_PIXEL_FORMAT_LAB_888_PACKAGE,
    HI_PIXEL_FORMAT_LAB_888_PLANAR,
    HI_PIXEL_FORMAT_S8C1,
    HI_PIXEL_FORMAT_S8C2_PACKAGE,
    HI_PIXEL_FORMAT_S8C2_PLANAR,
    HI_PIXEL_FORMAT_S8C3_PLANAR,
    HI_PIXEL_FORMAT_S16C1,
    HI_PIXEL_FORMAT_U8C1,
    HI_PIXEL_FORMAT_U16C1,
    HI_PIXEL_FORMAT_S32C1,
    HI_PIXEL_FORMAT_U32C1,
    HI_PIXEL_FORMAT_U64C1,
    HI_PIXEL_FORMAT_S64C1,

    HI_PIXEL_FORMAT_BUTT
} hi_pixel_format;

typedef enum  {
    HI_DYNAMIC_RANGE_SDR8 = 0,
    HI_DYNAMIC_RANGE_SDR10,
    HI_DYNAMIC_RANGE_HDR10,
    HI_DYNAMIC_RANGE_HLG,
    HI_DYNAMIC_RANGE_SLF,
    HI_DYNAMIC_RANGE_XDR,
    HI_DYNAMIC_RANGE_BUTT
} hi_dynamic_range;

typedef enum  {
    HI_DATA_BIT_WIDTH_8 = 0,
    HI_DATA_BIT_WIDTH_10,
    HI_DATA_BIT_WIDTH_12,
    HI_DATA_BIT_WIDTH_14,
    HI_DATA_BIT_WIDTH_16,
    HI_DATA_BIT_WIDTH_BUTT
} hi_data_bit_width;

typedef struct {
    hi_u32 top_width;
    hi_u32 bottom_width;
    hi_u32 left_width;
    hi_u32 right_width;
    hi_u32 color;
} hi_border;

typedef struct {
    hi_s32 x;
    hi_s32 y;
} hi_point;

typedef struct {
    hi_u32 width;
    hi_u32 height;
} hi_size;

typedef struct {
    hi_s32 x;
    hi_s32 y;
    hi_u32 width;
    hi_u32 height;
} hi_rect;

typedef enum {
    HI_COORD_ABS = 0,                          /* Absolute coordinate. */
    HI_COORD_RATIO,                            /* Ratio coordinate. */
    HI_COORD_BUTT
} hi_coord;

typedef enum {
    HI_COVER_RECT = 0,                         /* Rectangle cover. */
    HI_COVER_QUAD,                             /* Quadrangle cover. */
    HI_COVER_BUTT
} hi_cover_type;

typedef struct {
    hi_bool        is_solid;                   /* RW; Solid or hollow cover. */
    hi_u32         thick;                      /* RW; Thick of the hollow quadrangle. */
    hi_point       point[HI_QUAD_POINT_NUM];   /* RW; Four points of the quadrangle. */
} hi_quad_cover;

typedef struct {
    hi_cover_type      type;   /* RW; Cover type. */
    union {
        hi_rect        rect;   /* RW; The rectangle area. AUTO:hi_cover_type:HI_COVER_RECT; */
        hi_quad_cover  quad;   /* RW; The quadrangle area.  AUTO:hi_cover_type:HI_COVER_QUAD; */
    };
    hi_u32             color;  /* RW; Range: [0,0xFFFFFF]; Color of cover. */
} hi_cover;

typedef enum  {
    HI_MOSAIC_BLK_SIZE_4 = 0, /* block size 4 * 4 of MOSAIC */
    HI_MOSAIC_BLK_SIZE_8,     /* block size 8 * 8 of MOSAIC */
    HI_MOSAIC_BLK_SIZE_16,    /* block size 16 * 16 of MOSAIC */
    HI_MOSAIC_BLK_SIZE_32,    /* block size 32 * 32 of MOSAIC */
    HI_MOSAIC_BLK_SIZE_64,    /* block size 64 * 64 of MOSAIC */
    HI_MOSAIC_BLK_SIZE_128,   /* block size 128 * 128 of MOSAIC */
    HI_MOSAIC_BLK_SIZE_BUTT
} hi_mosaic_blk_size;

typedef struct {
    hi_mosaic_blk_size blk_size;
    hi_rect            rect;   /* RW; The rectangle area. */
} hi_mosaic;

typedef struct {
    hi_bool enable;
    hi_rect  rect;
} hi_crop_info;

typedef struct {
    hi_s32  src_frame_rate;        /* RW; source frame rate */
    hi_s32  dst_frame_rate;        /* RW; dest frame rate */
} hi_frame_rate_ctrl;

typedef struct {
    hi_aspect_ratio_type mode;          /* aspect ratio mode: none/auto/manual */
    hi_u32         bg_color;      /* background color, RGB 888 */
    hi_rect         video_rect;     /* valid in ASPECT_RATIO_MANUAL mode */
} hi_aspect_ratio;

typedef struct {
    hi_s16              offset_top;           /* top offset of show area */
    hi_s16              offset_left;          /* left offset of show area */
    hi_s16              offset_bottom;        /* bottom offset of show area */
    hi_s16              offset_right;         /* right offset of show area */

    hi_u32              max_luma;             /* for HDR */
    hi_u32              min_luma;             /* for HDR */
    hi_u64              private_data[HI_MAX_PRIVATE_DATA_NUM];
} hi_video_supplement_misc;

typedef struct {
    hi_phys_addr_t   misc_info_phys_addr;        /* default allocated buffer */
    hi_phys_addr_t   jpeg_dcf_phys_addr;
    hi_phys_addr_t   isp_info_phys_addr;
    hi_phys_addr_t   low_delay_phys_addr;
    hi_phys_addr_t   bnr_rnt_phys_addr;
    hi_phys_addr_t   motion_data_phys_addr;
    hi_phys_addr_t   frame_dng_phys_addr;

    hi_void* ATTRIBUTE misc_info_virt_addr;       /* misc info */
    hi_void* ATTRIBUTE jpeg_dcf_virt_addr;        /* jpeg_dcf, used in JPEG DCF */
    hi_void* ATTRIBUTE isp_info_virt_addr;        /* isp_frame_info, used in ISP debug, when get raw and send raw */
    hi_void* ATTRIBUTE low_delay_virt_addr;       /* used in low delay */
    hi_void* ATTRIBUTE bnr_mot_virt_addr;         /* used for 3dnr from bnr mot */
    hi_void* ATTRIBUTE motion_data_virt_addr;     /* vpss 3dnr use: gme motion data, filter motion data, gyro data. */
    hi_void* ATTRIBUTE frame_dng_virt_addr;
} hi_video_supplement;

typedef struct {
    hi_u32              width;
    hi_u32              height;
    hi_video_field      field;
    hi_pixel_format     pixel_format;
    hi_video_format     video_format;
    hi_compress_mode    compress_mode;
    hi_dynamic_range    dynamic_range;
    hi_color_gamut      color_gamut;

    hi_u32              header_stride[HI_MAX_COLOR_COMPONENT];
    hi_u32              stride[HI_MAX_COLOR_COMPONENT];

    hi_phys_addr_t      header_phys_addr[HI_MAX_COLOR_COMPONENT];
    hi_phys_addr_t      phys_addr[HI_MAX_COLOR_COMPONENT];
    hi_void* ATTRIBUTE  header_virt_addr[HI_MAX_COLOR_COMPONENT];
    hi_void* ATTRIBUTE  virt_addr[HI_MAX_COLOR_COMPONENT];

    hi_u32              time_ref;
    hi_u64              pts;

    hi_u64              user_data[HI_MAX_USER_DATA_NUM];
    hi_u32              frame_flag;     /* frame_flag, can be OR operation. */
    hi_video_supplement supplement;
} hi_video_frame;

typedef struct {
    hi_video_frame video_frame;
    hi_u32        pool_id;
    hi_mod_id      mod_id;
} hi_video_frame_info;

typedef struct {
    hi_u32 vb_size;

    hi_u32 head_stride;
    hi_u32 head_size;
    hi_u32 head_y_size;

    hi_u32 main_stride;
    hi_u32 main_size;
    hi_u32 main_y_size;
} hi_vb_calc_cfg;

typedef struct {
    hi_pixel_format pixel_format;  /* bitmap's pixel format */
    hi_u32 width;               /* bitmap's width */
    hi_u32 height;              /* bitmap's height */
    hi_void* ATTRIBUTE data;      /* address of bitmap's data */
} hi_bmp;

typedef struct {
    hi_bool    aspect;      /* RW;range: [0, 1];whether aspect ration  is keep */
    hi_s32     x_ratio;     /* RW; range: [0, 100]; field angle ration of  horizontal,valid when aspect=0. */
    hi_s32     y_ratio;     /* RW; range: [0, 100]; field angle ration of  vertical,valid when aspect=0. */
    hi_s32     xy_ratio;    /* RW; range: [0, 100]; field angle ration of  all,valid when aspect=1. */
     /* RW; range: [-511, 511]; horizontal offset of the image distortion center relative to image center. */
    hi_s32 center_x_offset;
     /* RW; range: [-511, 511]; vertical offset of the image distortion center relative to image center. */
    hi_s32 center_y_offset;
    /* RW; range: [-300, 500]; LDC distortion ratio.when spread on,distortion_ratio range should be [0, 500] */
    hi_s32 distortion_ratio;
} hi_ldc_v1_attr;

typedef struct {
    /* RW; range: [6400, 117341700]; focal length in horizontal direction, with 2 decimal numbers */
    hi_s32 focal_len_x;
    /* RW; range: [6400, 117341700]; focal length in vertical direction, with 2 decimal numbers */
    hi_s32 focal_len_y;
    /* RW; range: [35*width, 65*width]; coordinate of image center, with 2 decimal numbers */
    hi_s32 coord_shift_x;
    /* RW; range: [35*height, 65*height]; Y coordinate of image center, with 2 decimal numbers */
    hi_s32 coord_shift_y;
    /* RW; lens distortion coefficients of the source image, with 5 decimal numbers */
    hi_s32 src_calibration_ratio[HI_SRC_LENS_COEF_NUM];
    /* RW; lens distortion coefficients, with 5 decimal numbers */
    hi_s32 dst_calibration_ratio[HI_DST_LENS_COEF_NUM];
    /* RW; range: [0, 1048576]; max undistorted distance before 3rd polynomial drop, with 16bits decimal */
    hi_s32 max_du;
} hi_ldc_v2_attr;

typedef struct {
    hi_bool    aspect;      /* RW;range: [0, 1];whether aspect ration  is keep */
    hi_s32     x_ratio;     /* RW; range: [0, 100]; field angle ration of  horizontal,valid when aspect=0. */
    hi_s32     y_ratio;     /* RW; range: [0, 100]; field angle ration of  vertical,valid when aspect=0. */
    hi_s32     xy_ratio;    /* RW; range: [0, 100]; field angle ration of  all,valid when aspect=1. */
    /* RW; range: [6400, 3276700]; focal length in horizontal direction, with 2 decimal numbers */
    hi_s32 focal_len_x;
    /* RW; range: [6400, 3276700]; focal length in vertical direction, with 2 decimal numbers */
    hi_s32 focal_len_y;
    /* RW; range: [35*width, 65*width]; coordinate of image center, with 2 decimal numbers */
    hi_s32 coord_shift_x;
    /* RW; range: [35*height, 65*height]; Y coordinate of image center, with 2 decimal numbers */
    hi_s32 coord_shift_y;
    /* RW; lens distortion coefficients of the source image, with 5 decimal numbers */
    hi_s32 src_calibration_ratio[HI_SRC_LENS_COEF_NUM];
    /* RW; lens distortion coefficients of the source image (for interpolation), with 5 decimal numbers */
    hi_s32 src_calibration_ratio_next[HI_SRC_LENS_COEF_NUM];
    hi_u32 coef_intp_ratio; /* RW; range: [0, 32768]; interpolation ratio between two coefficient sets, 15bits */
} hi_ldc_v3_attr;

typedef enum {
    HI_LDC_V1 = 0,
    HI_LDC_V2 = 1,
    HI_LDC_V3 = 2,

    HI_LDC_VERSION_BUTT
} hi_ldc_version;

typedef struct {
    hi_bool enable;                 /* RW; Range [0,1];Whether LDC is enable */
    hi_ldc_version ldc_version;     /* RW; Version of LDC */
    union {
        hi_ldc_v1_attr ldc_v1_attr; /* RW; Attribute of LDC v1. AUTO:hi_ldc_version:HI_LDC_V1; */
        hi_ldc_v2_attr ldc_v2_attr; /* RW; Attribute of LDC v2. AUTO:hi_ldc_version:HI_LDC_V2; */
        hi_ldc_v3_attr ldc_v3_attr; /* RW; Attribute of LDC v3. AUTO:hi_ldc_version:HI_LDC_V3; */
    };
} hi_ldc_attr;

/* Angle of rotation */
typedef enum  {
    HI_ROTATION_0   = 0,
    HI_ROTATION_90  = 1,
    HI_ROTATION_180 = 2,
    HI_ROTATION_270 = 3,
    HI_ROTATION_BUTT
} hi_rotation;

typedef enum {
    HI_ROTATION_VIEW_TYPE_ALL      = 0, /* View all source Image,no lose */
    HI_ROTATION_VIEW_TYPE_TYPICAL  = 1, /* View from rotation Image with source size,same lose */
    HI_ROTATION_VIEW_TYPE_INSIDE   = 2, /* View with no black section,all  in dest Image */
    HI_ROTATION_VIEW_TYPE_BUTT,
} hi_rotation_view_type;

typedef struct {
    hi_rotation_view_type view_type; /* RW;range: [0, 2];rotation mode */
    hi_u32    angle; /* RW;range: [0,360];rotation angle:[0,360] */
    /* RW;range: [-511, 511];horizontal offset of the image distortion center relative to image center. */
    hi_s32    center_x_offset;
    /* RW;range: [-511, 511];vertical offset of the image distortion center relative to image center. */
    hi_s32    center_y_offset;
    hi_size   dst_size; /* RW; range: width:[480, 8192],height:[360, 8192]; dest size of any angle rotation */
} hi_free_rotation_attr;

typedef enum {
    HI_ROTATION_ANG_FIXED = 0,  /* Fixed angle. */
    HI_ROTATION_ANG_FREE,       /* Free angle. */
    HI_ROTATION_ANG_BUTT
} hi_rotation_type;

typedef struct {
    hi_bool             enable;         /* RW; range: [0, 1]; Rotate enable. */
    hi_rotation_type    rotation_type;  /* RW; Rotate type. */
    union {
        /*
         * RW; Fixed rotation attribute.
         * AUTO:hi_rotation_type:HI_ROTATION_ANG_FIXED;
         */
        hi_rotation rotation_fixed;
        /*
         * RW; Free rotation attribute.
         * AUTO:hi_rotation_type:HI_ROTATION_ANG_FREE;
         */
        hi_free_rotation_attr rotation_free;
    };
} hi_rotation_attr;

/* spread correction attribute */
typedef struct {
    /* RW; range: [0, 1];whether enable spread or not, when spread on,ldc distortion_ratio range should be [0, 500] */
    hi_bool enable;
    hi_u32  spread_coef; /* RW; range: [0, 18];strength coefficient of spread correction */
} hi_spread_attr;

typedef enum  {
    HI_FRAME_INTERRUPT_START,
    HI_FRAME_INTERRUPT_EARLY,
    HI_FRAME_INTERRUPT_EARLY_END,
    HI_FRAME_INTERRUPT_EARLY_EARLY,
    HI_FRAME_INTERRUPT_BUTT,
} hi_frame_interrupt_type;

typedef struct {
    hi_frame_interrupt_type interrupt_type;
    hi_u32 early_line;
} hi_frame_interrupt_attr;

typedef enum {
    HI_DATA_RATE_X1 = 0, /* RW; output 1 pixel per clock */
    HI_DATA_RATE_X2,     /* RW; output 2 pixel per clock */

    HI_DATA_RATE_BUTT
} hi_data_rate;

typedef enum {
    HI_WDR_MODE_NONE = 0,
    HI_WDR_MODE_BUILT_IN,
    HI_WDR_MODE_QUDRA,

    HI_WDR_MODE_2To1_LINE,
    HI_WDR_MODE_2To1_FRAME,

    HI_WDR_MODE_3To1_LINE,
    HI_WDR_MODE_3To1_FRAME,

    HI_WDR_MODE_4To1_LINE,
    HI_WDR_MODE_4To1_FRAME,

    HI_WDR_MODE_BUTT,
} hi_wdr_mode;

typedef enum {
    HI_CORNER_RECT_TYPE_CORNER = 0,
    HI_CORNER_RECT_TYPE_FULL_LINE,
    HI_CORNER_RECT_TYPE_BUTT
}hi_corner_rect_type;

typedef struct {
    hi_rect      rect;
    hi_u32       hor_len;
    hi_u32       ver_len;
    hi_u32       thick;
} hi_corner_rect;

typedef struct {
    hi_corner_rect_type    corner_rect_type;
    hi_u32                 color;
} hi_corner_rect_attr;

typedef struct {
    hi_u8 image_description[HI_DCF_DRSCRIPTION_LENGTH];
    /* shows manufacturer of digital cameras */
    hi_u8 make[HI_DCF_DRSCRIPTION_LENGTH];
    /* shows model number of digital cameras */
    hi_u8 model[HI_DCF_DRSCRIPTION_LENGTH];
    /* shows firmware (internal software of digital cameras) version number */
    hi_u8 software[HI_DCF_DRSCRIPTION_LENGTH];
    /*
     * light source, actually this means white balance setting. '0' means unknown, '1' daylight,
     * '2' fluorescent, '3' tungsten, '10' flash, '17' standard light A, '18' standard light B,
     * '19' standard light C, '20' D55, '21' D65, '22' D75, '255' other.
     */
    hi_u8 light_source;
    /* focal length of lens used to take image. unit is millimeter */
    hi_u32 focal_length;
    /* indicates the type of scene. value '0x01' means that the image was directly photographed. */
    hi_u8 scene_type;
    /*
     * indicates the use of special processing on image data, such as rendering geared to output.
     * 0 = normal process, 1 = custom process.
     */
    hi_u8 custom_rendered;
    /* indicates the equivalent focal length assuming a 35mm film camera, in mm */
    hi_u8 focal_length_in35mm_film;
    /* indicates the type of scene that was shot. 0 = standard, 1 = landscape, 2 = portrait, 3 = night scene. */
    hi_u8 scene_capture_type;
    /*
     * indicates the degree of overall image gain adjustment. 0 = none, 1 = low gain up, 2 = high gain up,
     * 3 = low gain down, 4 = high gain down.
     */
    hi_u8 gain_control;
    /*
     * indicates the direction of contrast processing applied by the camera when the image was shot.
     * 0 = normal, 1 = soft, 2 = hard.
     */
    hi_u8 contrast;
    /*
     * indicates the direction of saturation processing applied by the camera when the image was shot.
     * 0 = normal, 1 = low saturation, 2 = high saturation.
     */
    hi_u8 saturation;
    /*
     * indicates the direction of sharpness processing applied by the camera when the image was shot.
     * 0 = normal, 1 = soft, 2 = hard.
     */
    hi_u8 sharpness;
    /*
     * exposure metering method. '0' means unknown, '1' average, '2' center weighted average, '3' spot,
     * '4' multi-spot, '5' multi-segment, '6' partial, '255' other.
     */
    hi_u8 metering_mode;
} hi_isp_dcf_const_info;

typedef struct {
    /* CCD sensitivity equivalent to ag-hr film speedrate */
    hi_u32 iso_speed_ratings;
    /* exposure time (reciprocal of shutter speed). */
    hi_u32 exposure_time;
    /* exposure bias (compensation) value of taking picture */
    hi_u32 exposure_bias_value;
    /*
     * exposure program that the camera used when image was taken. '1' means manual control,
     * '2' program normal, '3' aperture priority, '4' shutter priority, '5' program creative (slow program),
     * '6' program action(high-speed program), '7' portrait mode, '8' landscape mode.
     */
    hi_u8 exposure_program;
    /* the actual F-number (F-stop) of lens when the image was taken */
    hi_u32 f_number;
    /* maximum aperture value of lens. */
    hi_u32 max_aperture_value;
    /*
     * indicates the exposure mode set when the image was shot.
     * 0 = auto exposure, 1 = manual exposure, 2 = auto bracket
     */
    hi_u8 exposure_mode;
    /*
     * indicates the white balance mode set when the image was shot.
     * 0 = auto white balance, 1 = manual white balance.
     */
    hi_u8 white_balance;
} hi_isp_dcf_update_info;

typedef struct {
    hi_isp_dcf_const_info  isp_dcf_const_info;
    hi_isp_dcf_update_info isp_dcf_update_info;
} hi_isp_dcf_info;

typedef struct {
    /* the date and time when the picture data was generated */
    hi_u8           capture_time[HI_DCF_CAPTURE_TIME_LENGTH];
    /* whether the picture is captured when a flash lamp is on */
    hi_bool         flash;
    /*
     * indicates the digital zoom ratio when the image was shot.
     * if the numerator of the recorded value is 0, this indicates that digital zoom was not used.
     */
    hi_u32          digital_zoom_ratio;
    hi_isp_dcf_info isp_dcf_info;
} hi_jpeg_dcf;

typedef struct {
    hi_u32      iso;                    /* ISP internal ISO : again*dgain*is_pgain */
    hi_u32      exposure_time;          /* exposure time (reciprocal of shutter speed), unit is us */
    hi_u32      isp_dgain;
    hi_u32      again;
    hi_u32      dgain;
    hi_u32      ratio[3];
    hi_u32      isp_nr_strength;
    hi_u32      f_number;               /* the actual F-number (F-stop) of lens when the image was taken */
    hi_u32      sensor_id;              /* which sensor is used */
    hi_u32      sensor_mode;
    hi_u32      hmax_times;             /* sensor hmax_times,unit is ns */
    hi_u32      vmax;                   /* sensor vmax,unit is line */
    hi_u32      vc_num;                 /* when dump wdr frame, which is long or short  exposure frame. */
    hi_u32      wb_gain[HI_ISP_WB_GAIN_NUM]; /* white balance gain info */
    hi_u16      ccm[HI_ISP_CAP_CCM_NUM];     /* RW; Range: [0x0, 0xFFFF]; Format:8.8; Manual CCM matrix. */
    hi_u32      exposure_distance[HI_ISP_WDR_MAX_FRAME_NUM - 1]; /* wdr sensor exposure distance line number. */
} hi_isp_frame_info;

typedef struct {
    hi_u32 color_temp;
    hi_u16 ccm[9];
    hi_u8  saturation;
} hi_isp_hdr_info;

typedef struct {
    hi_isp_hdr_info isp_hdr;
    hi_u32 iso;
    hi_u32 init_iso;
    hi_u8 sns_wdr_mode;
} hi_isp_attach_info;

typedef struct {
    hi_color_gamut color_gamut;
} hi_isp_colorgammut_info;

typedef struct {
    hi_u32 numerator;   /* represents the numerator of a fraction. */
    hi_u32 denominator; /* the denominator. */
} hi_dng_rational;

/* defines the structure of DNG image dynamic information */
typedef struct {
    /* RO; range: [0x0, 0xFFFF]; black level. */
    hi_u32 black_level[HI_ISP_BAYER_CHN];
    /*
     * specifies the selected white balance at time of capture,
     * encoded as the coordinates of a perfectly neutral color in linear reference space values.
     */
    hi_dng_rational as_shot_neutral[HI_CFACOLORPLANE];
    /* RO; describes the amount of noise in a raw image */
    hi_double ad_noise_profile[HI_DNG_NP_SIZE];
} hi_dng_image_dynamic_info;

typedef struct {
    hi_u32 iso;
    hi_u32 isp_dgain;
    hi_u32 exposure_time;
    hi_u32 white_balance_gain[HI_ISP_WB_GAIN_NUM];
    hi_u32 color_temperature;
    hi_u16 cap_ccm[HI_ISP_CAP_CCM_NUM];
} hi_isp_config_info;

typedef struct {
    hi_bool enable;         /* RW; low delay enable. */
    hi_u32  line_cnt;       /* RW; range: [16, 8192]; low delay shoreline. */
    hi_bool one_buf_en;     /* RW; one buffer for low delay enable. */
} hi_low_delay_info;

typedef enum {
    HI_SCHEDULE_NORMAL = 0,
    HI_SCHEDULE_QUICK,
    HI_SCHEDULE_BUTT
} hi_schedule_mode;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_COMMON_VIDEO_H__ */
