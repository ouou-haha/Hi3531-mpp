#ifndef HISIBASE_H
#define HISIBASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>


#include "hi_common.h"

#include "hi_math.h"

#include "hi_buffer.h"
#include "hi_defines.h"
#include "securec.h"
#include "hi_common_sys.h"
#include "hi_common_vb.h"
#include "hi_common_vi.h"
#include "hi_common_vo.h"
#include "hi_common_venc.h"
#include "hi_common_vdec.h"
#include "hi_common_vpss.h"
#include "hi_common_region.h"
#include "hi_common_adec.h"
#include "hi_common_aenc.h"

#include "hi_common_aio.h"

// #include "hi_common_hdmi.h"

#include "hi_common_vgs.h"
#include "hi_common_vda.h"
#include "hi_mpi_sys.h"
#include "hi_mpi_vb.h"
#include "hi_mpi_vi.h"
#include "hi_mpi_vo.h"
#include "hi_mpi_venc.h"
#include "hi_mpi_vdec.h"
#include "hi_mpi_vpss.h"
#include "hi_mpi_region.h"
#include "hi_mpi_audio.h"
// #include "hi_mpi_hdmi.h"
#include "hi_mpi_vgs.h"
#include "hi_mpi_vda.h"
#include "hi_mipi_rx.h"
#include "tp2854.h"


#define TP2854B_FILE "/dev/tp2802dev"
#define HD_WIDTH            1280
#define HD_HEIGHT           720
#define FHD_WIDTH           1920
#define FHD_HEIGHT          1080
#define SAMPLE_PIXEL_FORMAT HI_PIXEL_FORMAT_YVU_SEMIPLANAR_420
#define SECOND_CHN_OFFSET_2MUX     2
#define VB_NUM_PRE_CHN 8
#define SAMPLE_CHN_NUM 4
#define MIPI_DEV_NODE "/dev/hi_mipi"
#define CHN_NUM_PRE_DEV 4

#define COLOR_RGB_RED      0xFF0000
#define COLOR_RGB_GREEN    0x00FF00
#define COLOR_RGB_BLUE     0x0000FF
#define COLOR_RGB_BLACK    0x000000
#define COLOR_RGB_YELLOW   0xFFFF00
#define COLOR_RGB_CYN      0x00ffff
#define COLOR_RGB_WHITE    0xffffff


#define sample_print(fmt...) \
    do { \
        printf("[%s]-%d: ", __FUNCTION__, __LINE__); \
        printf(fmt); \
    } while (0)

#define check_return(express, name) \
    do { \
        hi_s32 ret_ = express; \
        if (ret_ != HI_SUCCESS) { \
            printf("\033[0;31m%s failed at %s: LINE: %d with %#x!\033[0;39m\n", \
                   name, __FUNCTION__, __LINE__, ret_); \
            return ret_; \
        } \
    } while (0)


#define minor_chn(vi_chn) ((vi_chn) + 1)


typedef enum {
    SAMPLE_VIDEO_ENCODING_PAL = 0,
    SAMPLE_VIDEO_ENCODING_NTSC,
    SAMPLE_VIDEO_ENCODING_AUTO,
    SAMPLE_VIDEO_ENCODING_BUTT
} video_encoding;



class HisiBase{

protected:
    hi_s32 vi_devId;
    hi_s32 vi_chnId;
    hi_size size;

    hi_u32 vo_frame_rate;



public:
    HisiBase(hi_s32 devId, hi_s32 chnId, hi_s32 width, hi_s32 height, hi_u32 vo_frame_rate) : vi_devId(devId), vi_chnId(chnId){
        this->size.width = width;
        this->size.height = height;
        this->vo_frame_rate = vo_frame_rate;
    }

    hi_s32 get_vi_id() const {
        return vi_devId;
    }


    hi_s32 get_chn_id() const {
        return vi_chnId;
    }

    hi_size get_size() const {
        return size;
    }

    hi_u32 get_frame_rate() const {
        return vo_frame_rate;
    }



    ~HisiBase(){}

};

#endif