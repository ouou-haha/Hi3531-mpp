#include "HisiStartVideo.h"



HisiStartVideo::HisiStartVideo(hi_u32 video) : m_video(video - 1){
    hi_s32 chnId = m_video * 2;
    hi_s32 viId = chnId / 4;
    m_sys = std::make_unique<HisiSysvbmipi>(2, 1920, 1080);
    m_vin = std::make_unique<HisiVin>(viId, chnId, 1920, 1080, HI_TRUE);

    m_vpss1 = std::make_unique<HisiVpss>(chnId, 1920, 1080);
    m_vpss2 = std::make_unique<HisiVpss>(chnId + 1, 1920, 1080);

    m_vo1 = std::make_unique<HisiVo>(1920, 1080, 60, chnId);
    m_vo2 = std::make_unique<HisiVo>(1920, 1080, 60, chnId + 1);

}

hi_s32 HisiStartVideo::start_video(){
    try{
        (hi_void)m_sys->init();
        (hi_void)m_vin->init();
        (hi_void)m_vpss1->vpss_init();
        (hi_void)m_vpss2->vpss_init();
        (hi_void)m_vo1->init();
        (hi_void)m_vo2->init();

    }
    catch(const std::exception& e){
        m_sys->deinit();
        m_vpss1->vpss_deinit();
        m_vpss2->vpss_deinit();
    }


    return HI_SUCCESS;
}
