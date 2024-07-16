#ifndef HISIVIN_H
#define HISIVIN_H


#include "HisiBase.h"




extern hi_vi_chn_attr def_vi_chn_attr;
extern hi_vi_dev_attr def_vi_dev_attr;



class HisiVin : public HisiBase
{
private:
    // hi_s32 vi_devId;
    // hi_s32 vi_chnId;
    // hi_size size;
    // vi参数
    hi_size dst_size;
    hi_size minor_dst_size;
    hi_rect capture_rect;
    // AD配置
    video_encoding ad_encoding;
    // vi dev配置
    hi_vi_dev_attr vi_dev_attr;
    // vi 通道配置
    hi_vi_chn_attr major_chn_attr;  // 主通道
    hi_vi_chn_attr minor_chn_attr; // 辅通道
    hi_bool minor_en;

protected:

    hi_s32 init_ad();
    hi_s32 init_dev();
    hi_s32 init_chn();


    hi_s32 stop_chn();
    hi_s32 stop_dev();



public:
    HisiVin(hi_s32 vi_devId, hi_s32 vi_chnId, hi_s32 width, hi_s32 height, hi_bool minor_en);

    hi_s32 init();
    hi_s32 deinit();


    ~HisiVin(){};
};




#endif // HISIVIN_H
