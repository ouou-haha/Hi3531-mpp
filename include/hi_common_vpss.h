/*
 * Copyright (c) Hisilicon Technologies Co., Ltd. 2019-2021. All rights reserved.
 * Description: Vpss common interface
 * Author: Hisilicon multimedia software group
 * Create: 2019/07/30
 */

#ifndef __HI_COMMON_VPSS_H__
#define __HI_COMMON_VPSS_H__

#include "hi_type.h"
#include "hi_common.h"
#include "hi_errno.h"
#include "hi_common_video.h"
#include "hi_common_sys.h"

#define HI_ERR_VPSS_NULL_PTR           HI_DEFINE_ERR(HI_ID_VPSS, HI_ERR_LEVEL_ERROR, HI_ERR_NULL_PTR)
#define HI_ERR_VPSS_NOT_READY          HI_DEFINE_ERR(HI_ID_VPSS, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_READY)
#define HI_ERR_VPSS_INVALID_DEV_ID     HI_DEFINE_ERR(HI_ID_VPSS, HI_ERR_LEVEL_ERROR, HI_ERR_INVALID_DEV_ID)
#define HI_ERR_VPSS_INVALID_CHN_ID     HI_DEFINE_ERR(HI_ID_VPSS, HI_ERR_LEVEL_ERROR, HI_ERR_INVALID_CHN_ID)
#define HI_ERR_VPSS_EXIST              HI_DEFINE_ERR(HI_ID_VPSS, HI_ERR_LEVEL_ERROR, HI_ERR_EXIST)
#define HI_ERR_VPSS_UNEXIST            HI_DEFINE_ERR(HI_ID_VPSS, HI_ERR_LEVEL_ERROR, HI_ERR_UNEXIST)
#define HI_ERR_VPSS_NOT_SUPPORT        HI_DEFINE_ERR(HI_ID_VPSS, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_SUPPORT)
#define HI_ERR_VPSS_NOT_PERM           HI_DEFINE_ERR(HI_ID_VPSS, HI_ERR_LEVEL_ERROR, HI_ERR_NOT_PERM)
#define HI_ERR_VPSS_NO_MEM             HI_DEFINE_ERR(HI_ID_VPSS, HI_ERR_LEVEL_ERROR, HI_ERR_NO_MEM)
#define HI_ERR_VPSS_NO_BUF             HI_DEFINE_ERR(HI_ID_VPSS, HI_ERR_LEVEL_ERROR, HI_ERR_NO_BUF)
#define HI_ERR_VPSS_SIZE_NOT_ENOUGH    HI_DEFINE_ERR(HI_ID_VPSS, HI_ERR_LEVEL_ERROR, HI_ERR_SIZE_NOT_ENOUGH)
#define HI_ERR_VPSS_ILLEGAL_PARAM      HI_DEFINE_ERR(HI_ID_VPSS, HI_ERR_LEVEL_ERROR, HI_ERR_ILLEGAL_PARAM)
#define HI_ERR_VPSS_BUSY               HI_DEFINE_ERR(HI_ID_VPSS, HI_ERR_LEVEL_ERROR, HI_ERR_BUSY)
#define HI_ERR_VPSS_BUF_EMPTY          HI_DEFINE_ERR(HI_ID_VPSS, HI_ERR_LEVEL_ERROR, HI_ERR_BUF_EMPTY)

#define HI_VPSS_CHN0                   0
#define HI_VPSS_CHN1                   1
#define HI_VPSS_CHN2                   2
#define HI_VPSS_CHN3                   3
#define HI_VPSS_INVALID_CHN            (-1)

#define HI_VPSS_S_IDX_LEN                 17
#define HI_VPSS_3DNR_MAX_AUTO_PARAM_NUM   16

/* Define de-interlace mode */
typedef enum {
    HI_VPSS_DEI_MODE_OFF = 0,
    HI_VPSS_DEI_MODE_ON,
    HI_VPSS_DEI_MODE_AUTO,
    HI_VPSS_DEI_MODE_BUTT
} hi_vpss_dei_mode;

typedef enum {
    HI_VPSS_NR_TYPE_VIDEO_NORM = 0,
    HI_VPSS_NR_TYPE_SNAP_NORM,
    HI_VPSS_NR_TYPE_VIDEO_SPATIAL,
    HI_VPSS_NR_TYPE_VIDEO_ENHANCED,
    HI_VPSS_NR_TYPE_BUTT
} hi_vpss_nr_type;

typedef enum {
    HI_VPSS_NR_MOTION_MODE_NORM = 0,              /* Normal. */
    HI_VPSS_NR_MOTION_MODE_COMPENSATION,          /* Motion compensate. */
    HI_VPSS_NR_MOTION_MODE_BUTT
} hi_vpss_nr_motion_mode;

typedef struct {
    hi_vpss_nr_type     nr_type;                  /* RW; NR type. */
    hi_compress_mode    compress_mode;            /* RW; Reference frame compression mode. */
    hi_vpss_nr_motion_mode   nr_motion_mode;      /* RW; NR motion compensate mode. */
} hi_vpss_nr_attr;

typedef struct {
    hi_bool             nr_en;                    /* RW; Range: [0, 1]; NR enable. */
    hi_bool             ie_en;                    /* RW; Range: [0, 1]; Image enhance enable. */
    hi_bool             dci_en;                   /* RW; Range: [0, 1]; Dynamic contrast improve enable. */
    hi_bool             buf_share_en;             /* RW; Range: [0, 1]; Buffer share enable. */
    hi_bool             mcf_en;                   /* RW; Range: [0, 1]; MCF enable. */
    /* RW; Range: HI3531DV200/HI3521DV200 = [64, 16384]; Width of source image. */
    hi_u32              max_width;
    /* RW; Range: HI3531DV200/HI3521DV200 = [64, 8192]; Height of source image. */
    hi_u32              max_height;
    /* RW; Range: HI3531DV200/HI3521DV200 = [64, 960]; Width of max dei image. */
    hi_u32              max_dei_width;
    /* RW; Range: HI3531DV200/HI3521DV200 = [64, 4096]; Height of max dei image. */
    hi_u32              max_dei_height;
    hi_dynamic_range    dynamic_range;            /* RW; Dynamic range of source image. */
    hi_pixel_format     pixel_format;             /* RW; Pixel format of source image. */
    hi_vpss_dei_mode    dei_mode;                 /* RW; De-interlace enable. */
    hi_vpss_chn         buf_share_chn;            /* RW; Buffer share channel. */
    hi_vpss_nr_attr     nr_attr;                  /* RW; NR attr. */
    hi_frame_rate_ctrl  frame_rate;               /* RW; Group frame rate control. */
} hi_vpss_grp_attr;

typedef enum {
    HI_VPSS_CHN_MODE_AUTO = 0,                    /* Auto mode. */
    HI_VPSS_CHN_MODE_USER,                        /* User mode. */
    HI_VPSS_CHN_MODE_BUTT
} hi_vpss_chn_mode;

typedef struct {
    hi_bool             mirror_en;                /* RW; Range: [0, 1]; Mirror enable. */
    hi_bool             flip_en;                  /* RW; Range: [0, 1]; Flip enable. */
    hi_bool             border_en;                /* RW; Range: [0, 1]; Border enable. */
    /* RW; range: HI3531DV200/HI3521DV200 = [64, 16384]; Width of target image. */
    hi_u32              width;
    /* RW; range: HI3531DV200/HI3521DV200 = [64, 8192]; Height of target image. */
    hi_u32              height;
    hi_u32              depth;                    /* RW; Range: [0, 8]; Depth of chn image list. */
    hi_vpss_chn_mode    chn_mode;                 /* RW; Work mode of vpss channel. */
    hi_video_format     video_format;             /* RW; Video format of target image. */
    hi_dynamic_range    dynamic_range;            /* RW; Dynamic range of target image. */
    hi_pixel_format     pixel_format;             /* RW; Pixel format of target image. */
    hi_compress_mode    compress_mode;            /* RW; Compression mode of the output. */
    hi_frame_rate_ctrl  frame_rate;               /* RW; Frame rate control info. */
    hi_border           border_attr;              /* RW; Border info. */
    hi_aspect_ratio     aspect_ratio;             /* RW; Aspect ratio info. */
} hi_vpss_chn_attr;

typedef struct {
    hi_vpss_chn            bind_chn;
    hi_ext_chn_src_type    src_type;
    hi_u32                 width;
    hi_u32                 height;
    hi_u32                 depth;
    hi_video_format        video_format;
    hi_dynamic_range       dynamic_range;
    hi_pixel_format        pixel_format;
    hi_compress_mode       compress_mode;
    hi_frame_rate_ctrl     frame_rate;
} hi_vpss_ext_chn_attr;

/* Define vpss filter info */
typedef struct {
    hi_bool             enable;                   /* RW; Range: [0, 1]; Image filter enable. */
    hi_size             size;                     /* RW; Image filter size info. */
} hi_vpss_sizer_info;

typedef struct {
    hi_bool                  enable;              /* RW; Range: [0, 1]; Crop enable. */
    hi_coord                 crop_mode;           /* RW; Coordinate mode of crop. */
    hi_rect                  crop_rect;           /* RW; Crop rectangular. */
} hi_vpss_crop_info;

/* Only used for HI3531DV200/HI3521DV200 */
typedef struct {
    hi_u32                   sf_strength;         /* RW; Range: [0, 255]; Strength of y space filter. */
    hi_u32                   tf_strength;         /* RW; Range: [0, 63]; Strength of y time filter. */
    hi_u32                   csf_strength;        /* RW; Range: [0, 255]; Strength of c space filter. */
    hi_u32                   ctf_strength;        /* RW; Range: [0, 32]; Strength of c time filter. */
    hi_u32                   cvbs_strength;       /* RW; Range: [0, 32]; Strength of cvbs. */
} hi_vpss_nrx_norm_param_v1;

typedef struct {
    hi_u8   ies0;   /* RW; Range: [0, 255]; The gains of edge and texture enhancement. */
    hi_u8   ies1;   /* RW; Range: [0, 255]; The gains of edge and texture enhancement. */
    hi_u8   ies2;   /* RW; Range: [0, 255]; The gains of edge and texture enhancement. */
    hi_u8   ies3;   /* RW; Range: [0, 255]; The gains of edge and texture enhancement. */
    hi_u16  iedz;   /* RW; Range: [0, 999]; The threshold to control the generated artifacts. */
} hi_vpss_nrx_v2_iey;

typedef struct {
    struct {
        hi_u16 spn    : 4;  /* RW; Range: [0,   6]; The selection of filters to be mixed for NO.7 filter. */
        hi_u16 sbn    : 4;  /* RW; Range: [0,   6]; The selection of filters to be mixed for NO.7 filter. */
        hi_u16 pbr    : 5;  /* RW; Range: [0,  16]; The mix ratio between spn and sbr. */
        hi_u16 j_mode : 3;  /* RW; Range: [0,   4]; The selection modes for the blending of spatial filters. */
    };
    hi_u8   sfr7[4];    /* RW; Range: [0, 31]; The relative NR strength for NO.7 filter. (Effective when jmode = 4). */
    hi_u8   sbr7[2];    /* RW; Range: [0, 15]; The control of overshoot and undershoot. */
    hi_u8   sfs1;       /* RW; Range: [0, 255]; The NR strength parameters for NO.1 filter. */
    hi_u8   sbr1;       /* RW; Range: [0, 255]; The NR strength parameters for NO.1 filter. */
    hi_u8   sfs2;       /* RW; Range: [0, 255]; The NR strength parameters for NO.2 filter. */
    hi_u8   sft2;       /* RW; Range: [0, 255]; The NR strength parameters for NO.2 filter. */
    hi_u8   sbr2;       /* RW; Range: [0, 255]; The NR strength parameters for NO.2 filter. */
    hi_u8   sfs4;       /* RW; Range: [0, 255]; The NR strength parameters for NO.3 and NO.4 filters. */
    hi_u8   sft4;       /* RW; Range: [0, 255]; The NR strength parameters for NO.3 and NO.4 filters. */
    hi_u8   sbr4;       /* RW; Range: [0, 255]; The NR strength parameters for NO.3 and NO.4 filters. */
    /*
     * sth1_0, sth2_0, sth3_0; Range: [0, 511]; The thresholds for protection of edges on foreground from blurring.
     * sth1_1, sth2_1, sth3_1; Range: [0, 511]; The thresholds for protection of edges on background from blurring.
     * sf5_md; Range: [0, 1]; The strength control of NO.5 filter.
     * sf8_idx0, sf8_idx1; Range: [0, 7]; The filter selection for NO.8.
     * bri_idx0, bri_idx1; Range: [0, 7]; The filter selection based on brightness
     * for foreground and background, respectively.
     */
    struct {
        hi_u16 sth1_0 : 9;
        hi_u16 sf5_md : 1;
        hi_u16 _rb1_  : 6;
    };
    struct {
        hi_u16 sth2_0   : 9;
        hi_u16 sf8_idx0 : 3;
        hi_u16 bri_idx0 : 4;
    };
    struct {
        hi_u16 sth3_0   : 9;
        hi_u16 sf8_idx1 : 3;
        hi_u16 bri_idx1 : 4;
    };
    hi_u16  sth1_1;
    hi_u16  sth2_1;
    hi_u16  sth3_1;
    /*
     * sfn0_0~sfn3_0; Range: [0, 8]; Filter selection for different foreground image areas based on sth1_0~sth3_0.
     * sfn0_1~sfn3_1; Range: [0, 8]; Filter selection for different background image areas based on sth1_1~sth3_1.
     */
    struct {
        hi_u16 sfn0_0 : 4;
        hi_u16 sfn1_0 : 4;
        hi_u16 sfn2_0 : 4;
        hi_u16 sfn3_0 : 4;
    };
    struct {
        hi_u16 sfn0_1 : 4;
        hi_u16 sfn1_1 : 4;
        hi_u16 sfn2_1 : 4;
        hi_u16 sfn3_1 : 4;
    };
    hi_u8   sf8_tfr;    /* RW ; Range: [0, 255]; The blending strength for NO. 8 filter. */
    hi_u8   sf8_thrd;   /* RW ; Range: [0, 255]; The blending strength for NO. 8 filter. */
    hi_u8   sfr;        /* RW ; Range: [0, 31]; The relative NR strength to the sfi and sfk filter. */
    hi_u8   bri_str[HI_VPSS_S_IDX_LEN]; /* RW ; Range: [0, 255];  Spatial NR strength based on brightness. */
} hi_vpss_nrx_v2_sfy;

typedef struct {
    struct {
        hi_u16 tfs0  : 4;   /* RW; Range: [0,  15]; The NR strength for temporal filtering. */
        hi_u16 tdz0  : 10;  /* RW; Range: [0, 999]; Protection of the weak texturearea from temporal filtering. */
        hi_u16 _rb0_ : 2;
    };
    struct {
        hi_u16 tfs1      : 4;   /* RW; Range: [0,  15]; The NR strength for temporal filtering. */
        hi_u16 tdz1      : 10;  /* RW; Range: [0, 999]; Protection of the weak texture area from temporal filtering. */
        hi_u16 math_mode : 2;   /* RW; Range: [0,   1]; The motion dection mode. */
    };
    struct {
        hi_u16 sdz0   : 10; /* RW; Range: [0, 999]; The threshold of NR control for result mai00. */
        hi_u16 str0   : 5;  /* RW; Range: [0,  31]; The strength  of NR control for result mai00. */
        hi_u16 ref_en : 1;  /* RW; Range: [0,   1]; The enable switch for reference frame. */
    };
    struct {
        hi_u16 sdz1  : 10;  /* RW; Range: [0, 999]; The threshold of NR control for result mai00. */
        hi_u16 str1  : 5;   /* RW; Range: [0,  31]; The strength  of NR control for result mai00. */
        hi_u16 _rb1_ : 1;
    };
    hi_u8   tss0;       /* RW; Range: [0,  15]; The ratio for blending spatial NR with the temporal NR results. */
    hi_u8   tss1;       /* RW; Range: [0,  15]; The ratio for blending spatial NR with the temporal NR results. */
    hi_u16  auto_math;  /* RW; Range: [0, 999]; The motion threshold for the Level 0 denoise. */
    hi_u8   tfr0[6];    /* RW; Range: [0,  31]; The temoproal NR strength control for background (static) area. */
    hi_u8   tfr1[6];    /* RW; Range: [0,  31]; The temoproal NR strength control for background (static) area. */
} hi_vpss_nrx_v2_tfy;

typedef struct {
    struct {
        hi_u16 math0 : 10;  /* RW; Range: [0, 999]; The threshold for motion detection. */
        hi_u16 mate0 : 4;   /* RW; Range: [0,   8]; The motion index for smooth image area. */
        hi_u16 mai00 : 2;   /* RW; Range: [0,   3]; The blending results between spatial and temporal filtering. */
    };
    struct {
        hi_u16 math1 : 10;  /* RW; Range: [0, 999]; The threshold for motion detection. */
        hi_u16 mate1 : 4;   /* RW; Range: [0,   8]; The motion index for smooth image area. */
        hi_u16 mai02 : 2;   /* RW; Range: [0,   3]; The blending results between spatial and temporal filtering. */
    };
    hi_u8   mabw0;          /* RW; Range: [0,   9]; The window size for motion detection. */
    hi_u8   mabw1;          /* RW; Range: [5,   9]; The window size for motion detection. */
    struct {
        hi_u16 adv_math : 1;    /* RW; Range: [0, 1]; The switch to active the advanced mode. */
        hi_u16 adv_th   : 12;   /* RW; Range: [0, 511]; The threshold to control the effects of the adv_math. */
        hi_u16 _rb_     : 3;
    };
} hi_vpss_nrx_v2_mdy;

typedef struct {
    hi_u8   sfc;                /* RW; Range: [0, 31];  The chorma NR strength. */
    hi_u8   sfc_enhance;        /* RW; Range: [0, 255];  The chorma NR strength for sfc. */
    hi_u8   sfc_ext;            /* RW; Range: [0, 255];  The extra chorma NR strength for sfc. */
    hi_u8   trc;                /* RW; Range: [0, 255];  The temporal chorma NR strength. */
    struct {
        hi_u16 auto_math : 10;  /* RW; Range: [0, 999];  The motion threshold for chorma. */
        hi_u16 tfc       : 6;   /* RW; Range: [0, 32];   The control of temporal chorma NR strength. */
    };
} hi_vpss_nrx_v2_nrc0;

typedef struct {
    hi_u8   sfs1;       /* RW; Range: [0, 255];  The NR strength parameters for NO.1 filter. */
    hi_u8   sbr1;       /* RW; Range: [0, 255];  The NR strength parameters for NO.1 filter. */
    hi_u8   sfs2;       /* RW; Range: [0, 255];  The NR strength parameters for NO.2 filter. */
    hi_u8   sft2;       /* RW; Range: [0, 255];  The NR strength parameters for NO.2 filter. */
    hi_u8   sbr2;       /* RW; Range: [0, 255];  The NR strength parameters for NO.2 filter. */
    hi_u8   sfs4;       /* RW; Range: [0, 255];  The NR strength parameters for NO.3 and NO.4 filter. */
    hi_u8   sft4;       /* RW; Range: [0, 255];  The NR strength parameters for NO.3 and NO.4 filter. */
    hi_u8   sbr4;       /* RW; Range: [0, 255];  The NR strength parameters for NO.3 and NO.4 filter. */
    hi_u8   sfc6;       /* RW; Range: [0, 255];  The chorma NR strength for NO.6 filter. */
    hi_u8   sfc_ext6;   /* RW; Range: [0, 255];  The extra chorma NR strength for NO.6 filter. */
    /* sfr6_u, sfr6_v; Range: [0, 15]; The chorma NR strength control for U and V, respectively, for NO.6 filter. */
    struct {
        hi_u8 sfr6_u : 4;
        hi_u8 sfr6_v : 4;
    };
    /*
     * sf5_str_u, sf5_str_v; Range: [0, 31]; The chorma NR strength for U and V, respectively, for NO.5 filter.
     * post_sfc; Range: [0, 31]; The chorma NR strength for sfc filter.
     */
    struct {
        hi_u16 sf5_str_u : 5;
        hi_u16 sf5_str_v : 5;
        hi_u16 post_sfc  : 5;
        hi_u16 _rb0_     : 1;
    };
    struct {
        hi_u16 spn0 : 3;    /* RW; Range: [0,  6];  The selection of filters to be mixed for NO.7 filter. */
        hi_u16 sbn0 : 3;    /* RW; Range: [0,  6];  The selection of filters to be mixed for NO.7 filter. */
        hi_u16 pbr0 : 4;    /* RW; Range: [0, 15];  The mix ratio for NO.7 filter. */
        hi_u16 spn1 : 3;    /* RW; Range: [0,  6];  The selection of filters to be mixed for NO.7 filter. */
        hi_u16 sbn1 : 3;    /* RW; Range: [0,  6];  The selection of filters to be mixed for NO.7 filter. */
    };
    struct {
        hi_u8 pbr1  : 4;    /* RW; Range: [0, 15];  The mix ratio for NO.7 filter. */
        hi_u8 _rb1_ : 4;
    };
    struct {
        hi_u8 sat0_l_sfn8 : 4;  /* RW; Range: [0, 7];  The selection of filters to be mixed for NO.8 filter. */
        hi_u8 sat1_l_sfn8 : 4;  /* RW; Range: [0, 7];  The selection of filters to be mixed for NO.8 filter. */
    };
    struct {
        hi_u8 sat0_h_sfn8 : 4;  /* RW; Range: [0, 7];  The selection of filters to be mixed for NO.8 filter. */
        hi_u8 sat1_h_sfn8 : 4;  /* RW; Range: [0, 7];  The selection of filters to be mixed for NO.8 filter. */
    };
    struct {
        hi_u8 hue0_l_sfn9 : 4;  /* RW; Range: [0, 8];  The selection of filters to be mixed for NO.9 filter. */
        hi_u8 hue1_l_sfn9 : 4;  /* RW; Range: [0, 8];  The selection of filters to be mixed for NO.9 filter. */
    };
    struct {
        hi_u8 hue0_h_sfn9 : 4;  /* RW; Range: [0, 8];  The selection of filters to be mixed for NO.9 filter. */
        hi_u8 hue1_h_sfn9 : 4;  /* RW; Range: [0, 8];  The selection of filters to be mixed for NO.9 filter. */
    };
    struct {
        hi_u8 bri0_l_sfn10 : 4; /* RW; Range: [0, 9];  The selection of filters to be mixed for NO.10 filter. */
        hi_u8 bri1_l_sfn10 : 4; /* RW; Range: [0, 9];  The selection of filters to be mixed for NO.10 filter. */
    };
    struct {
        hi_u8 bri0_h_sfn10 : 4; /* RW; Range: [0, 9];  The selection of filters to be mixed for NO.10 filter. */
        hi_u8 bri1_h_sfn10 : 4; /* RW; Range: [0, 9];  The selection of filters to be mixed for NO.10 filter. */
    };
    struct {
        hi_u8 sfn0 : 4; /* RW; Range: [0, 10]; The selection of filters for foreground and background, respectivel. */
        hi_u8 sfn1 : 4; /* RW; Range: [0, 10]; The selection of filters for foreground and background, respectivel. */
    };
    hi_u8   bak_grd_sat[HI_VPSS_S_IDX_LEN]; /* RW; Range: [0, 255]; Chroma NR strength based on saturation. */
    hi_u8   for_grd_sat[HI_VPSS_S_IDX_LEN]; /* RW; Range: [0, 255]; Chroma NR strength based on saturation. */
    hi_u8   bak_grd_hue[HI_VPSS_S_IDX_LEN]; /* RW; Range: [0, 255]; Chroma NR strength based on hue. */
    hi_u8   for_grd_hue[HI_VPSS_S_IDX_LEN]; /* RW; Range: [0, 255]; Chroma NR strength based on hue. */
    hi_u8   bak_grd_bri[HI_VPSS_S_IDX_LEN]; /* RW; Range: [0, 255]; Chroma NR strength based on brightness. */
    hi_u8   for_grd_bri[HI_VPSS_S_IDX_LEN]; /* RW; Range: [0, 255]; Chroma NR strength based on brightness. */
} hi_vpss_nrx_v2_nrc1;

typedef struct {
    hi_vpss_nrx_v2_iey  iey[5];
    hi_vpss_nrx_v2_sfy  sfy[5];
    hi_vpss_nrx_v2_mdy  mdy[2];
    hi_vpss_nrx_v2_tfy  tfy[3];
    hi_vpss_nrx_v2_nrc0 nrc0;
    hi_vpss_nrx_v2_nrc1 nrc1;
    struct {
        hi_u16 limit_range_en : 1;  /* RW; Range: [0, 1]; The switch for limit range mode. */
        hi_u16 nry0_en        : 1;  /* RW; Range: [0, 1]; The switch for luma denoise. */
        hi_u16 nry1_en        : 1;  /* RW; Range: [0, 1]; The switch for luma denoise. */
        hi_u16 nry2_en        : 1;  /* RW; Range: [0, 1]; The switch for luma denoise. */
        hi_u16 nry3_en        : 1;  /* RW; Range: [0, 1]; The switch for luma denoise. */
        hi_u16 nrc0_en        : 1;  /* RW; Range: [0, 1]; The switch for chroma denoise. */
        hi_u16 nrc1_en        : 1;  /* RW; Range: [0, 1]; The switch for chroma denoise. */
        hi_u16 _rb_           : 9;
    };
} hi_vpss_nrx_v2;

typedef struct {
    hi_vpss_nrx_v2 nrx_param;
} hi_vpss_nrx_param_manual_v2;

typedef struct {
    hi_u32 param_num;
    hi_u32 *iso;
    hi_vpss_nrx_v2 *nrx_param;
} hi_vpss_nrx_param_auto_v2;

typedef struct {
    hi_op_mode op_mode;
    hi_vpss_nrx_param_manual_v2 nrx_manual;
    hi_vpss_nrx_param_auto_v2 nrx_auto;
} hi_vpss_nrx_norm_param_v2;

typedef struct {
    hi_u32                   mdz;                 /* RW; Range: [0, 63]; */
    hi_u32                   hard_tf_strength;    /* RW; Range: [0, 96]; Relation strength of hard NR channel. */
    /* Only for weak nr chn */
    hi_u32                   edz;                 /* RW; Range: [0, 63]; */
    hi_u32                   weak_tf_strength;    /* RW; Range: [0, 63]; Relation strength of weak NR channel. */
} hi_vpss_nrx_adv_param;

typedef enum {
    HI_VPSS_NR_V1 = 1,
    HI_VPSS_NR_V2 = 2,
    HI_VPSS_NR_BUTT
} hi_vpss_nr_version;

typedef struct {
    hi_vpss_nr_version       nr_version;                /* RW; Version of NR parameters. */
    union {
        hi_vpss_nrx_norm_param_v1 nrx_norm_param_v1;    /* AUTO: hi_vpss_nr_version:HI_VPSS_NR_V1. */
        hi_vpss_nrx_norm_param_v2 nrx_norm_param_v2;    /* AUTO: hi_vpss_nr_version:HI_VPSS_NR_V2. */
    };
} hi_vpss_grp_nrx_param;

typedef struct {
    hi_u32                  contrast;             /* RW; Range: [0, 63]; Strength of dynamic contrast improve. */
    hi_u32                  ie_strength;          /* RW; Range: [0, 63]; Strength of image enhance. */
    hi_vpss_grp_nrx_param   nrx_param;            /* RW; Parameters of NR. */
} hi_vpss_grp_param;

typedef struct {
    hi_bool                 enable;               /* RW; Range: [0, 1]; Sharpen enable. */
    hi_u32                  strength;             /* RW; Range: [0, 100]; Sharpen strength. */
} hi_vpss_chn_sharpen_param;

typedef struct {
    hi_u32                  split_node_num;        /* RW; Range: [1, 16]; Max num of split node. */
    hi_bool                 coverex_ratio_support; /* RW; Range: [0, 1]; Coverex support ratio coordinate. */
    hi_bool                 nr_low_delay_en;       /* RW; Range: [0, 1]; Low delay enable of NR */
} hi_vpss_mod_param;

typedef struct {
    hi_size                 img_size;             /* R; Image size info. */
    hi_u64 ATTRIBUTE        *luma_data;           /* R; Luma data. */
} hi_vpss_luma_result;

typedef enum {
    HI_VPSS_COLOR_RANGE_LIMITED = 0,
    HI_VPSS_COLOR_RANGE_FULL,
    HI_VPSS_COLOR_RANGE_BUTT
} hi_vpss_color_range;

typedef struct {
    hi_u8 weight;   /* RW; Range: [0, 255]; Weight of Gaussian distribution. */
    hi_u8 sigma;    /* RW; Range: [1, 255]; Sigma of Gaussian distribution. */
    hi_u8 mean;     /* RW; Range: [0, 255]; Mean of Gaussian distribution. */
} hi_vpss_ldci_gauss_coef_attr;

typedef struct {
    /* RW; Weight curve, the degree of brightening can be controlled based on the luminance of original images. */
    hi_vpss_ldci_gauss_coef_attr positive_attr;
    /* RW; Weight curve, the degree of darkening can be controlled based on the luminance of original images. */
    hi_vpss_ldci_gauss_coef_attr negative_attr;
} hi_vpss_ldci_he_weight_attr;

typedef struct {
    hi_bool enable;                     /* RW; Range: [0, 1]; LDCI enable. */
    hi_vpss_color_range color_range;    /* RW; Color range of input yuv image. */
    hi_u16 black_ctrl_strength;         /* RW; Range: [0, 511]; Restrain dark region. */
    /*
     * RW; Used for controlling the weight curve of blending
     * between histogram equalization results and original images.
     * The curve is Gaussian-distributed with the luminance as the horizontal coordinate.
     */
    hi_vpss_ldci_he_weight_attr he_weight_attr;
} hi_vpss_ldci_attr;

#endif /* __HI_COMMON_VPSS_H__ */
