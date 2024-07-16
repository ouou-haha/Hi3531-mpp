#ifndef HISIVPSS_H
#define HISIVPSS_H

#include "HisiBase.h"


class HisiVpss : public HisiBase
{
private:

    hi_vpss_grp m_vpss_grp_id;
    hi_vpss_chn m_vpss_chn_id;

    hi_vpss_grp_attr m_grp_attr;
    hi_vpss_chn_attr m_chn_attr[HI_VPSS_MAX_PHYS_CHN_NUM];
    hi_bool m_chn_enable[HI_VPSS_MAX_PHYS_CHN_NUM];

    hi_size m_venc_size;
    hi_size m_vo_size;

protected:
    hi_s32 vpss_set_attr();
    hi_s32 vi_bind_vpss();

    hi_s32 stop_vpss_grp_chn();

public:
    HisiVpss(hi_vpss_grp vpss_grp_id, hi_s32 width, hi_s32 height);

    hi_s32 vpss_init();
    hi_s32 vpss_deinit();

    ~HisiVpss(){};
};

#endif


