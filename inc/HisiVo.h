#ifndef __HISIVO_H__
#define __HISIVO_H__

#include "HisiBase.h"





typedef enum {
    VO_MODE_1MUX = 0,
    VO_MODE_2MUX,
    VO_MODE_4MUX,
    VO_MODE_8MUX,
    VO_MODE_9MUX,
    VO_MODE_16MUX,
    VO_MODE_25MUX,
    VO_MODE_36MUX,
    VO_MODE_49MUX,
    VO_MODE_64MUX,
    VO_MODE_2X4,
    VO_MODE_BUTT
} vo_mode_num;

typedef struct {
    vo_mode_num mode;
    hi_u32 wnd_num;
    hi_u32 square;
    hi_u32 row;
    hi_u32 col;
} vo_wnd_info;

extern vo_wnd_info g_vo_sample_wnd_info[];

typedef enum {
    PIC_CIF,
    PIC_360P,    /* 640 * 360 */
    PIC_D1_PAL,  /* 720 * 576 */
    PIC_D1_NTSC, /* 720 * 480 */
    PIC_960H,      /* 960 * 576 */
    PIC_720P,    /* 1280 * 720 */
    PIC_1080P,   /* 1920 * 1080 */
    PIC_480P,
    PIC_576P,
    PIC_800X600,
    PIC_1024X768,
    PIC_1280X1024,
    PIC_1366X768,
    PIC_1440X900,
    PIC_1280X800,
    PIC_1600X1200,
    PIC_1680X1050,
    PIC_1920X1200,
    PIC_640X480,
    PIC_1920X2160,
    PIC_2560X1440,
    PIC_2560X1600,
    PIC_2592X1520,
    PIC_2592X1944,
    PIC_3840X2160,
    PIC_4096X2160,
    PIC_3000X3000,
    PIC_4000X3000,
    PIC_7680X4320,
    PIC_3840X8640,
    PIC_BUTT
} hi_pic_size;





typedef struct {
    /* for device */
    hi_vo_dev vo_dev;
    hi_vo_intf_type vo_intf_type;
    hi_vo_intf_sync intf_sync;
    hi_pic_size pic_size;
    hi_u32 bg_color;

    /* for layer */
    hi_pixel_format pix_format;
    hi_rect disp_rect;
    hi_size image_size;
    hi_vo_partition_mode vo_part_mode;
    hi_compress_mode compress_mode;

    hi_u32 dis_buf_len;
    hi_dynamic_range dst_dynamic_range;

    /* for chnnel */
    vo_mode_num vo_mode;

    /* for user sync */
    hi_vo_sync_info sync_info;
    hi_vo_user_sync_info user_sync;
    hi_u32 dev_frame_rate;
} vo_cfg;



class HisiVo : public HisiBase
{
private:
    hi_vo_pub_attr m_vo_pub_attr;
    hi_vo_video_layer_attr m_layer_attr;
    hi_bool g_vo_hdmi_rgb_mode;
    vo_wnd_info m_wnd_info;
    hi_vpss_chn m_vpss_chn_dhd0;
    hi_vpss_grp m_vpss_grpId;


    vo_cfg m_vo_config;
    static bool isInitialized;  // 静态变量，默认为false
    static bool isBegin;  // 静态变量，默认为false
    static hi_vo_chn vo_chn;

protected:
    // static hi_s32 start_vo();
    // hi_s32 set_intf();
    // hi_s32 start_hdmi();
    // hi_s32 vo_bind_vpss();
    
public:
    HisiVo(hi_u32 width, hi_u32 height, hi_u32 frame_rate, hi_s32 vpss_grpId);
    hi_s32 start_vo();
    hi_s32 vo_bind_vpss();
    hi_s32 vo_begin();
    hi_s32 init();
    ~HisiVo(){};
};




#endif