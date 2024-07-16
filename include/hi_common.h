/*
 * Copyright (c) Hisilicon Technologies Co., Ltd. 2017-2019. All rights reserved.
 * Description:Initial Draft
 * Author: Hisilicon multimedia software group
 * Create: 2017/07/15
 */

#ifndef __HI_COMMON_H__
#define __HI_COMMON_H__

#include "autoconf.h"
#include "hi_type.h"
#include "hi_defines.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#ifndef VER_X
#define VER_X                  1
#endif

#ifndef VER_Y
#define VER_Y                  0
#endif

#ifndef VER_Z
#define VER_Z                  0
#endif

#ifndef VER_P
#define VER_P                  0
#endif

#ifndef VER_B
#define VER_B                  0
#endif

#ifdef HI_DEBUG
#define VER_D                  " Debug"
#else
#define VER_D                  " Release"
#endif

#define ATTRIBUTE              __attribute__((aligned(HI_ALIGN_NUM)))
#define hi_unused(x)             ((hi_void)(x))

#define HI_COMPAT_POINTER(ptr, type) \
    do { \
        hi_u32 dest_addr_ = (hi_u32)(hi_uintptr_t)ptr; \
        ptr = (type)(hi_uintptr_t)dest_addr_; \
    } while (0)

#define __MK_VERSION(x, y, z, p, b) #x "." #y "." #z "." #p " B0" #b
#define MK_VERSION(x, y, z, p, b) __MK_VERSION(x, y, z, p, b)
#define HI_MPP_VERSION            HI_CHIP_NAME HI_MPP_VER_PRIX MK_VERSION(VER_X, VER_Y, VER_Z, VER_P, VER_B) VER_D

#define HI_MAX_VERSION_NAME_LEN    64
#define HI_INVALID_CHN         (-1)
#define HI_INVALID_WAY         (-1)
#define HI_INVALID_LAYER       (-1)
#define HI_INVALID_DEV         (-1)
#define HI_INVALID_HANDLE      (-1)
#define HI_INVALID_VALUE       (-1)
#define HI_INVALID_TYPE        (-1)

#define HI_MPP_MOD_VI             "vi"
#define HI_MPP_MOD_VO             "vo"
#define HI_MPP_MOD_AVS            "avs"
#define HI_MPP_MOD_HDMI           "hdmi"
#define HI_MPP_MOD_VGS            "vgs"
#define HI_MPP_MOD_GDC            "gdc"
#define HI_MPP_MOD_DIS            "dis"
#define HI_MPP_MOD_GYRODIS        "gyrodis"
#define HI_MPP_MOD_CHNL           "chnl"
#define HI_MPP_MOD_VENC           "venc"
#define HI_MPP_MOD_VPSS           "vpss"
#define HI_MPP_MOD_RGN            "rgn"
#define HI_MPP_MOD_IVE            "ive"
#define HI_MPP_MOD_FD             "fd"
#define HI_MPP_MOD_MD             "md"
#define HI_MPP_MOD_IVP            "ivp"
#define HI_MPP_MOD_SVP            "svp"
#define HI_MPP_MOD_SVP_NNIE       "nnie"
#define HI_MPP_MOD_SVP_DSP        "dsp"
#define HI_MPP_MOD_SVP_ALG        "svp_alg"
#define HI_MPP_MOD_DPU_RECT       "rect"
#define HI_MPP_MOD_DPU_MATCH      "match"
#define HI_MPP_MOD_SVP_MAU        "mau"
#define HI_MPP_MOD_H264E          "h264e"
#define HI_MPP_MOD_H265E          "h265e"
#define HI_MPP_MOD_JPEGE          "jpege"
#define HI_MPP_MOD_MPEG4E         "mpeg4e"
#define HI_MPP_MOD_VEDU           "vedu"
#define HI_MPP_MOD_PRORES         "prores"
#define HI_MPP_MOD_VDEC           "vdec"
#define HI_MPP_MOD_H264D          "h264d"
#define HI_MPP_MOD_JPEGD          "jpegd"
#define HI_MPP_MOD_AI             "ai"
#define HI_MPP_MOD_AO             "ao"
#define HI_MPP_MOD_AENC           "aenc"
#define HI_MPP_MOD_ADEC           "adec"
#define HI_MPP_MOD_AIO            "aio"
#define HI_MPP_MOD_ACODEC         "acodec"
#define HI_MPP_MOD_VB             "vb"
#define HI_MPP_MOD_SYS            "sys"
#define HI_MPP_MOD_CMPI           "cmpi"
#define HI_MPP_MOD_PCIV           "pciv"
#define HI_MPP_MOD_PCIVFMW        "pcivfmw"
#define HI_MPP_MOD_PROC           "proc"
#define HI_MPP_MOD_LOG            "logmpp"
#define HI_MPP_MOD_LOG_MDC        "logmpp_mdc"
#define HI_MPP_MOD_FB             "fb"
#define HI_MPP_MOD_RC             "rc"
#define HI_MPP_MOD_TDE            "tde"
#define HI_MPP_MOD_ISP            "isp"
#define HI_MPP_MOD_USR            "usr"
#define HI_MPP_MOD_MCF            "mcf"
#define HI_MPP_MOD_PM             "pm"
#define HI_MPP_MOD_MFUSION        "motionfusion"
#define HI_MPP_MOD_VDA            "vda"
#define HI_MPP_MOD_VPP            "vpp"
#define HI_MPP_MOD_KCF            "kcf"
#define HI_MPP_MOD_PQP            "pqp"
#define HI_MPP_MOD_SVP_NPU        "svp_npu"
#define HI_MPP_MOD_NPU_DEV        "npudev"
#define HI_MPP_MOD_NPU_AICPU      "aicpu"
#define HI_MPP_MOD_NPU_DFX        "npudfx"
#define HI_MPP_MOD_NPU_TSFW       "tsfw"
#define HI_MPP_MOD_CIPHER         "cipher"
#define HI_MPP_MOD_KLAD           "klad"
#define HI_MPP_MOD_OTP            "otp"
#define HI_MPP_MOD_DCC            "dcc"
#define HI_MPP_MOD_VDEC_SERVERS   "vdec_server"
#define HI_MPP_MOD_VDEC_ADAPT     "vdec_adapt"
typedef struct {
    hi_char version[HI_MAX_VERSION_NAME_LEN];
} hi_mpp_version;

typedef hi_s32 hi_ai_chn;
typedef hi_s32 hi_ao_chn;
typedef hi_s32 hi_aenc_chn;
typedef hi_s32 hi_adec_chn;
typedef hi_s32 hi_audio_dev;
typedef hi_s32 hi_vi_dev;
typedef hi_s32 hi_vi_pipe;
typedef hi_s32 hi_vi_way;
typedef hi_s32 hi_vi_chn;
typedef hi_s32 hi_vi_grp;
typedef hi_s32 hi_vo_dev;
typedef hi_s32 hi_vo_layer;
typedef hi_s32 hi_vo_chn;
typedef hi_s32 hi_vo_wbc;
typedef hi_s32 hi_gfx_layer;
typedef hi_s32 hi_venc_chn;
typedef hi_s32 hi_vdec_chn;
typedef hi_s32 hi_ive_handle;
typedef hi_s32 hi_fd_chn;
typedef hi_s32 hi_md_chn;
typedef hi_s32 hi_isp_dev;
typedef hi_s32 hi_blk_dev;
typedef hi_s32 hi_sensor_id;
typedef hi_s32 hi_mipi_dev;
typedef hi_s32 hi_slave_dev;
typedef hi_s32 hi_svp_nnie_handle;
typedef hi_s32 hi_svp_dsp_handle;
typedef hi_s32 hi_svp_alg_chn;
typedef hi_s32 hi_svp_mau_handle;
typedef hi_s32 hi_vpss_grp;
typedef hi_s32 hi_vpss_grp_pipe;
typedef hi_s32 hi_vpss_chn;
typedef hi_s32 hi_avs_grp;
typedef hi_s32 hi_avs_pipe;
typedef hi_s32 hi_avs_chn;
typedef hi_s32 hi_mcf_grp;
typedef hi_s32 hi_mcf_pipe;
typedef hi_s32 hi_mcf_chn;
typedef hi_s32 hi_vda_chn;
typedef hi_s32 hi_pciv_chn;

typedef enum {
    HI_ID_CMPI    = 0,
    HI_ID_VB      = 1,
    HI_ID_SYS     = 2,
    HI_ID_RGN      = 3,
    HI_ID_CHNL    = 4,
    HI_ID_VDEC    = 5,
    HI_ID_AVS     = 6,
    HI_ID_VPSS    = 7,
    HI_ID_VENC    = 8,
    HI_ID_SVP     = 9,
    HI_ID_H264E   = 10,
    HI_ID_JPEGE   = 11,
    HI_ID_H265E   = 13,
    HI_ID_JPEGD   = 14,
    HI_ID_VO      = 15,
    HI_ID_VI      = 16,
    HI_ID_DIS     = 17,
    HI_ID_VALG    = 18,
    HI_ID_RC      = 19,
    HI_ID_AIO     = 20,
    HI_ID_AI      = 21,
    HI_ID_AO      = 22,
    HI_ID_AENC    = 23,
    HI_ID_ADEC    = 24,
    HI_ID_VPU    = 25,
    HI_ID_PCIV    = 26,
    HI_ID_PCIVFMW = 27,
    HI_ID_ISP      = 28,
    HI_ID_IVE      = 29,
    HI_ID_USER    = 30,
    HI_ID_PROC    = 33,
    HI_ID_LOG     = 34,
    HI_ID_VFMW    = 35,
    HI_ID_GDC     = 37,
    HI_ID_PHOTO   = 38,
    HI_ID_FB      = 39,
    HI_ID_HDMI    = 40,
    HI_ID_VOIE    = 41,
    HI_ID_TDE     = 42,
    HI_ID_HDR      = 43,
    HI_ID_PRORES  = 44,
    HI_ID_VGS     = 45,
    HI_ID_FD      = 47,
    HI_ID_OD      = 48,
    HI_ID_LPR      = 50,
    HI_ID_SVP_NNIE     = 51,
    HI_ID_SVP_DSP      = 52,
    HI_ID_DPU_RECT     = 53,
    HI_ID_DPU_MATCH    = 54,

    HI_ID_MOTIONSENSOR = 55,
    HI_ID_MOTIONFUSION = 56,

    HI_ID_GYRODIS      = 57,
    HI_ID_PM           = 58,
    HI_ID_SVP_ALG      = 59,
    HI_ID_IVP          = 60,
    HI_ID_MCF          = 61,
    HI_ID_SVP_MAU      = 62,
    HI_ID_VDA          = 63,
    HI_ID_VPP          = 64,
    HI_ID_KCF          = 65,
    HI_ID_PQP          = 66,

    HI_ID_NPUDEV       = 67,
    HI_ID_AICPU        = 68,
    HI_ID_NPUDFX       = 69,
    HI_ID_TSFW         = 70,

    HI_ID_CIPHER       = 71,
    HI_ID_KLAD         = 72,
    HI_ID_KEYSLOT      = 73,
    HI_ID_OTP          = 74,
    HI_ID_VDEC_ADAPT   = 75,
    HI_ID_DCC          = 76,
    HI_ID_VDEC_SERVER  = 77,
    HI_ID_VFMW_MDC     = 78,
    HI_ID_VB_LOG     = 79,
    HI_ID_MCF_CALIBRATION = 80,
    HI_ID_SVP_NPU      = 81,
    HI_ID_HNR          = 82,
    HI_ID_SNAP         = 83,
    HI_ID_LOG_MDC     = 84,
    HI_ID_BUTT,
} hi_mod_id;

typedef struct {
    hi_mod_id    mod_id;
    hi_s32      dev_id;
    hi_s32      chn_id;
} hi_mpp_chn;

/* We just copy this value of payload type from RTP/RTSP definition */
typedef enum {
    HI_PT_PCMU          = 0,
    HI_PT_1016          = 1,
    HI_PT_G721          = 2,
    HI_PT_GSM           = 3,
    HI_PT_G723          = 4,
    HI_PT_DVI4_8K       = 5,
    HI_PT_DVI4_16K      = 6,
    HI_PT_LPC           = 7,
    HI_PT_PCMA          = 8,
    HI_PT_G722          = 9,
    HI_PT_S16BE_STEREO  = 10,
    HI_PT_S16BE_MONO    = 11,
    HI_PT_QCELP         = 12,
    HI_PT_CN            = 13,
    HI_PT_MPEGAUDIO     = 14,
    HI_PT_G728          = 15,
    HI_PT_DVI4_3        = 16,
    HI_PT_DVI4_4        = 17,
    HI_PT_G729          = 18,
    HI_PT_G711A         = 19,
    HI_PT_G711U         = 20,
    HI_PT_G726          = 21,
    HI_PT_G729A         = 22,
    HI_PT_LPCM          = 23,
    HI_PT_CelB          = 25,
    HI_PT_JPEG          = 26,
    HI_PT_CUSM          = 27,
    HI_PT_NV            = 28,
    HI_PT_PICW          = 29,
    HI_PT_CPV           = 30,
    HI_PT_H261          = 31,
    HI_PT_MPEGVIDEO     = 32,
    HI_PT_MPEG2TS       = 33,
    HI_PT_H263          = 34,
    HI_PT_SPEG          = 35,
    HI_PT_MPEG2VIDEO    = 36,
    HI_PT_AAC           = 37,
    HI_PT_WMA9STD       = 38,
    HI_PT_HEAAC         = 39,
    HI_PT_PCM_VOICE     = 40,
    HI_PT_PCM_AUDIO     = 41,
    HI_PT_MP3           = 43,
    HI_PT_ADPCMA        = 49,
    HI_PT_AEC           = 50,
    HI_PT_X_LD          = 95,
    HI_PT_H264          = 96,
    HI_PT_D_GSM_HR      = 200,
    HI_PT_D_GSM_EFR     = 201,
    HI_PT_D_L8          = 202,
    HI_PT_D_RED         = 203,
    HI_PT_D_VDVI        = 204,
    HI_PT_D_BT656       = 220,
    HI_PT_D_H263_1998   = 221,
    HI_PT_D_MP1S        = 222,
    HI_PT_D_MP2P        = 223,
    HI_PT_D_BMPEG       = 224,
    HI_PT_MP4VIDEO      = 230,
    HI_PT_MP4AUDIO      = 237,
    HI_PT_VC1           = 238,
    HI_PT_JVC_ASF       = 255,
    HI_PT_D_AVI         = 256,
    HI_PT_DIVX3         = 257,
    HI_PT_AVS           = 258,
    HI_PT_REAL8         = 259,
    HI_PT_REAL9         = 260,
    HI_PT_VP6           = 261,
    HI_PT_VP6F          = 262,
    HI_PT_VP6A          = 263,
    HI_PT_SORENSON      = 264,
    HI_PT_H265          = 265,
    HI_PT_VP8           = 266,
    HI_PT_MVC           = 267,
    HI_PT_PNG           = 268,
    /* add by hisilicon */
    HI_PT_AMR           = 1001,
    HI_PT_MJPEG         = 1002,
    HI_PT_AMRWB         = 1003,
    HI_PT_PRORES        = 1006,
    HI_PT_OPUS          = 1007,
    HI_PT_BUTT
} hi_payload_type;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* __HI_COMMON_H__ */
