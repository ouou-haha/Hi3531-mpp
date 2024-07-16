/*
 * Copyright (c) Hisilicon Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: Head file for common otp.
 * Author     : Hisilicon multimedia software group
 * Create     : 2020-06-01
 */

#ifndef __HI_COMMON_OTP_H__
#define __HI_COMMON_OTP_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/* OTP error code value */
#define HI_ERR_OTP_NOT_INIT                                 0x804E0001
#define HI_ERR_OTP_NULL_PTR                                 0x804E0002
#define HI_ERR_OTP_BUSY                                     0x804E0003
#define HI_ERR_OTP_FAILED_INIT                              0x804E0004
#define HI_ERR_OTP_FAILED_MEM                               0x804E0005
#define HI_ERR_OTP_FAILED_SEC_FUNC                          0x804E0006
#define HI_ERR_OTP_INVALID_PARAM                            0x804E0007
#define HI_ERR_OTP_INVALID_FIELD_NAME                       0x804E0008
#define HI_ERR_OTP_ZONE_ALREADY_SET                         0x804E0009
#define HI_ERR_OTP_ZONE_LOCKED                              0x804E000A
#define HI_ERR_OTP_ZONE_NO_PERMIT                           0x804E000B
#define HI_ERR_OTP_WAIT_TIMEOUT                             0x804E000C
#define HI_ERR_OTP_FUNC_UNSUPPORT                           0x804E000D

#define HI_OTP_PV_NAME_MAX_LEN                              32
#define HI_OTP_PV_VALUE_MAX_LEN                             32

/* PV enum */
typedef struct {
    hi_bool burn;                                   /* Burn OTP fuse or read OTP fuse. */
    hi_char field_name[HI_OTP_PV_NAME_MAX_LEN];     /* OTP fuse name. */
    hi_u32  value_len;                              /* OTP fuse value bit length. */
    hi_u8   value[HI_OTP_PV_VALUE_MAX_LEN];         /* OTP fuse value. */
    hi_bool lock;                                   /* Burn OTP fuse lock or not,
                                                      If this item not support lock. ignore it */
} hi_otp_burn_pv_item;

typedef enum {
    HI_OTP_STA_ALL_UNLOCKED = 0,                    /* user data area is all unlock. */
    HI_OTP_STA_PARTIAL_LOCKED,                      /* user data area is partial unlock. */
    HI_OTP_STA_ALL_LOCKED,                          /* user data area is all lock. */
    HI_OTP_STA_BUTT,                                /* invalid param. */
} hi_otp_lock_status;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_COMMON_OTP_H__ */
