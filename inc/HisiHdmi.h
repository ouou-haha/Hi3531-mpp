#ifndef __HISIHDMI_H__
#define __HISIHDMI_H__

#include "HisiBase.h"




extern hi_hdmi_video_format g_vo_hdmi_sync[HI_VO_OUT_BUTT];

class HisiHdmi
{
private:
    /* data */
    hi_vo_dev vo_devId;

    hi_bool m_vo_hdmi_rgb_mode;
    hi_vo_intf_sync m_intf_sync;

protected:
    hi_void vo_set_intf_param();
    hi_s32 start_hdmi_bt1120();

public:
    hi_s32 init();
    hi_s32 show_video();

    HisiHdmi();
    ~HisiHdmi(){};
};



#endif