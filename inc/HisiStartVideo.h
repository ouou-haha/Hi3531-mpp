#ifndef __HISISTARTVIDEO_H__
#define __HISISTARTVIDEO_H__

#include "HisiVin.h"
#include "HisiVo.h"
#include "HisiVpss.h"
#include "HisiSysvbmipi.h"
#include <memory>

class HisiStartVideo
{
private:
    hi_u32 m_video;

    std::unique_ptr<HisiVin> m_vin;
    std::unique_ptr<HisiVpss> m_vpss1;
    std::unique_ptr<HisiVpss> m_vpss2; 
    std::unique_ptr<HisiVo> m_vo1;
    std::unique_ptr<HisiVo> m_vo2;
    std::unique_ptr<HisiSysvbmipi> m_sys;

public:
    HisiStartVideo(hi_u32 video);
    hi_s32 start_video();

    ~HisiStartVideo(){};
};







#endif