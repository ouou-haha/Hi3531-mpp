/*
 * Copyright (c) Hisilicon Technologies Co., Ltd. 2017-2019. All rights reserved.
 * Description:Initial Draft
 * Author: Hisilicon multimedia software group
 * Create: 2017/07/15
 */

#ifndef __HI_TYPE_H__
#define __HI_TYPE_H__

#ifdef __KERNEL__

#include <linux/types.h>
#else

#include <stdint.h>
#endif
#include "autoconf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef NULL
    #define NULL                0L
#endif

#define HI_NULL                 0L
#define HI_SUCCESS              0
#define HI_FAILURE              (-1)

typedef unsigned char           hi_uchar;
typedef unsigned char           hi_u8;
typedef unsigned short          hi_u16;
typedef unsigned int            hi_u32;
typedef unsigned long           hi_ulong;

typedef char                    hi_char;
typedef signed char             hi_s8;
typedef short                   hi_s16;
typedef int                     hi_s32;
typedef long                    hi_slong;

typedef float                   hi_float;
typedef double                  hi_double;

typedef void                    hi_void;

typedef unsigned long long  hi_u64;
typedef long long           hi_s64;

#ifdef CONFIG_PHYS_ADDR_BIT_WIDTH_64
    typedef unsigned long long  hi_phys_addr_t;
#else
    typedef unsigned int        hi_phys_addr_t;
#endif

typedef hi_u32                  hi_handle;
typedef uintptr_t               hi_uintptr_t;
typedef unsigned int            hi_fr32;

typedef enum {
    HI_FALSE = 0,
    HI_TRUE  = 1,
} hi_bool;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_TYPE_H__ */

