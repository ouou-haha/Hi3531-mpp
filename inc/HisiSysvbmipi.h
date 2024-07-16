#ifndef __HISISYSVBMIPI_H__
#define __HISISYSVBMIPI_H__

#include "HisiBase.h"
#include "hi_mipi_rx.h"
class HisiSysvbmipi
{

private:
    // 缓存区配置
    hi_vb_cfg m_vb_cfg;
    hi_pic_buf_attr m_pic_buf_attr;
    hi_u32 m_blk_size;
    hi_s32 m_vi_dev_cnt;

    // 设置 MIPI 属性
    combo_dev_attr_t m_mipi_dev_attr;


    // vi参数

    hi_size m_minor_dst_size;
    hi_rect m_capture_rect;

    static bool isInitialized;  // 静态变量，默认为false

protected:
    hi_s32 stop_mipi();
    hi_s32 stop_sys();

public:
    HisiSysvbmipi(hi_s32 vi_cnt, hi_s32 width, hi_s32 height);
    hi_s32 init();
    hi_s32 deinit();
    ~HisiSysvbmipi();
};




#endif // HISIVIN_H
