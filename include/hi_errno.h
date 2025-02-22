/*
 * Copyright (c) Hisilicon Technologies Co., Ltd. 2017-2019. All rights reserved.
 * Description:Initial Draft
 * Author: Hisilicon multimedia software group
 * Create: 2017/07/15
 */

#ifndef __HI_ERRNO_H__
#define __HI_ERRNO_H__

#include "hi_debug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

/*
 * 1010 0000b
 * VTOP use APPID from 0~31
 * so, hisilicon use APPID based on 32
 */
#define HI_ERR_APP_ID (0x80000000L + 0x20000000L)

/*
 * |----------------------------------------------------------------|
 * | 1 |   APP_ID   |   MOD_ID    | ERR_LEVEL |   ERR_ID            |
 * |----------------------------------------------------------------|
 * |<--><--7bits----><----8bits---><--3bits---><------13bits------->|
 */
#define HI_DEFINE_ERR(mod, level, err_id) \
    ((hi_s32)((HI_ERR_APP_ID) | ((mod) << 16) | ((level) << 13) | (err_id)))

/*
 * NOTE! the following defined all common error code,
 * all module must reserved 0~63 for their common error code
 */
typedef enum {
    HI_ERR_LEVEL_DEBUG = 0,  /* debug-level                                  */
    HI_ERR_LEVEL_INFO,       /* informational                                */
    HI_ERR_LEVEL_NOTICE,     /* normal but significant condition             */
    HI_ERR_LEVEL_WARNING,    /* warning conditions                           */
    HI_ERR_LEVEL_ERROR,      /* error conditions                             */
    HI_ERR_LEVEL_CRIT,       /* critical conditions                          */
    HI_ERR_LEVEL_ALERT,      /* action must be taken immediately             */
    HI_ERR_LEVEL_FATAL,      /* just for compatibility with previous version */
    HI_ERR_LEVEL_BUTT
} hi_err_level;

typedef enum {
    HI_ERR_INVALID_DEV_ID  =  0x1, /* invlalid device ID                          */
    HI_ERR_INVALID_PIPE_ID =  0x2, /* invlalid pipe ID                           */
    HI_ERR_INVALID_CHN_ID  =  0x3, /* invlalid channel ID                          */
    HI_ERR_INVALID_LAYER_ID = 0x4, /* invlalid channel ID                          */
    HI_ERR_INVALID_GRP_ID   = 0x5, /* invlalid group ID                          */

    HI_ERR_ILLEGAL_PARAM   = 0x7, /* at lease one parameter is illagal
                               * eg, an illegal enumeration value             */
    HI_ERR_EXIST           = 0x8, /* resource exists                              */
    HI_ERR_UNEXIST         = 0x9, /* resource unexists                            */
    HI_ERR_NULL_PTR        = 0xa, /* using a NULL pointer                           */
    HI_ERR_NOT_CFG         = 0xb, /* try to enable or initialize system, device
                              ** or channel, before configing attribute       */
    HI_ERR_NOT_SUPPORT     = 0xc, /* operation or type is not supported by NOW    */
    HI_ERR_NOT_PERM        = 0xd, /* operation is not permitted
                              ** eg, try to change static attribute           */
    HI_ERR_NOT_ENABLE      = 0x10,
    HI_ERR_NOT_DISABLE     = 0x11,
    HI_ERR_NOT_START       = 0x12,
    HI_ERR_NOT_STOP        = 0x13,
    HI_ERR_NO_MEM          = 0x14, /* failure caused by malloc memory              */
    HI_ERR_NO_BUF          = 0x15, /* failure caused by malloc buffer              */
    HI_ERR_BUF_EMPTY       = 0x16, /* no data in buffer                            */
    HI_ERR_BUF_FULL        = 0x17, /* no buffer for new data                       */
    HI_ERR_NOT_READY       = 0x18, /* System is not ready, maybe not initialed or
                              ** loaded. Returning the error code when opening
                              ** a device file failed.                        */
    HI_ERR_TIMEOUT         = 0x20,
    HI_ERR_BAD_ADDR        = 0x21, /* bad address,
                              ** eg. used for copy_from_user & copy_to_user   */
    HI_ERR_BUSY            = 0x22, /* resource is busy,
                              ** eg. destroy a venc chn without unregister it */
    HI_ERR_SIZE_NOT_ENOUGH = 0x23, /* buffer size is smaller than the actual size required */

    HI_ERR_NOT_BINDED      = 0x24,
    HI_ERR_BINDED          = 0x25,
    HI_ERR_BUTT            = 0x3f, /* maximum code, private error code of all modules
                              ** must be greater than it                      */
} hi_errno;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_ERRNO_H__ */
