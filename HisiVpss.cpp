#include "HisiVpss.h"


HisiVpss::HisiVpss(hi_vpss_grp vpss_grp_id, hi_s32 width, hi_s32 height) : HisiBase(0, 0, width, height, 0), m_vpss_grp_id(vpss_grp_id){
    if(m_vpss_grp_id % 2 == 0){
        m_vpss_chn_id = HI_VPSS_CHN0;
    }else{
        m_vpss_chn_id = HI_VPSS_CHN2;
    }

    hi_s32 ret;
    // m_grp_attr = { 0 };
    // m_chn_attr = { 0 };
    // m_chn_enable = { 0 };
    // memset(m_chn_enable, 0, sizeof(m_chn_enable));
    // memset(m_chn_attr, 0, sizeof(hi_vpss_chn_attr));
    // memset(m_grp_attr, 0, sizeof(hi_vpss_grp_attr));

    memset_s(&m_chn_attr, sizeof(hi_vpss_chn_attr), 0, sizeof(hi_vpss_chn_attr));
    memset_s(&m_grp_attr, sizeof(hi_vpss_grp_attr), 0, sizeof(hi_vpss_grp_attr));
    memset_s(&m_chn_enable, sizeof(m_chn_enable), 0, sizeof(m_chn_enable));

    if (m_vpss_chn_id >= HI_VPSS_MAX_PHYS_CHN_NUM) {
        sample_print("vpss_chn:%d invalid!\n", m_vpss_chn_id);
    }

    m_grp_attr.nr_en = HI_TRUE;

    m_grp_attr.ie_en = HI_TRUE;
    m_grp_attr.dci_en = HI_TRUE;
    m_grp_attr.nr_attr.compress_mode = HI_COMPRESS_MODE_FRAME;
    m_grp_attr.dei_mode = HI_VPSS_DEI_MODE_OFF;
    m_grp_attr.pixel_format = SAMPLE_PIXEL_FORMAT;
    m_grp_attr.frame_rate.src_frame_rate = -1;
    m_grp_attr.frame_rate.dst_frame_rate = -1;

    
    
    m_grp_attr.max_width = get_size().width;
    m_grp_attr.max_height = get_size().height;

    m_chn_enable[m_vpss_chn_id] = HI_TRUE;

    m_chn_attr[m_vpss_chn_id].chn_mode = HI_VPSS_CHN_MODE_AUTO;
    m_chn_attr[m_vpss_chn_id].width = get_size().width;
    m_chn_attr[m_vpss_chn_id].height = get_size().height;
    m_chn_attr[m_vpss_chn_id].pixel_format = HI_PIXEL_FORMAT_YVU_SEMIPLANAR_420;
    m_chn_attr[m_vpss_chn_id].frame_rate.src_frame_rate = -1;
    m_chn_attr[m_vpss_chn_id].frame_rate.dst_frame_rate = -1;


    m_chn_attr[m_vpss_chn_id].border_en = HI_TRUE;
    m_chn_attr[m_vpss_chn_id].border_attr.color = COLOR_RGB_GREEN;
    m_chn_attr[m_vpss_chn_id].border_attr.top_width = 2; /* 2 : border top width */
    m_chn_attr[m_vpss_chn_id].border_attr.bottom_width = 2; /* 2 : border bottom width */
    m_chn_attr[m_vpss_chn_id].border_attr.left_width = 2; /* 2 : border left width */
    m_chn_attr[m_vpss_chn_id].border_attr.right_width = 2; /* 2 : border right width */

}



hi_s32 HisiVpss::vpss_set_attr(){

    hi_s32 ret;
    hi_s32 i;
    hi_vpss_chn vpss_chn;

    ret = hi_mpi_vpss_create_grp(m_vpss_grp_id, &m_grp_attr);
    if (ret != HI_SUCCESS) {
        sample_print("hi_mpi_vpss_create_grp(grp:%d) failed with %#x!\n", m_vpss_grp_id, ret);
        return HI_FAILURE;
    }

    ret = hi_mpi_vpss_start_grp(m_vpss_grp_id);
    if (ret != HI_SUCCESS) {
        sample_print("hi_mpi_vpss_start_grp failed with %#x\n", ret);
        return HI_FAILURE;
    }


    for (i = 0; i < HI_VPSS_MAX_PHYS_CHN_NUM; ++i) {
        if (m_chn_enable[i] == HI_TRUE) {
            vpss_chn = i;
            ret = hi_mpi_vpss_set_chn_attr(m_vpss_grp_id, vpss_chn, &m_chn_attr[vpss_chn]);
            if (ret != HI_SUCCESS) {
                sample_print("hi_mpi_vpss_set_chn_attr failed with %#x\n", ret);
                return HI_FAILURE;
            }

            ret = hi_mpi_vpss_enable_chn(m_vpss_grp_id, vpss_chn);
            if (ret != HI_SUCCESS) {
                sample_print("hi_mpi_vpss_enable_chn failed with %#x\n", ret);
                return HI_FAILURE;
            }
        }
    }
    return HI_SUCCESS;

}


hi_s32 HisiVpss::vi_bind_vpss(){
    hi_mpp_chn src_chn;
    hi_mpp_chn dest_chn;
    hi_vi_chn vi_chn = m_vpss_grp_id;

    src_chn.mod_id = HI_ID_VI;
    src_chn.dev_id = 0; // vi_pipe
    src_chn.chn_id = vi_chn;

    dest_chn.mod_id = HI_ID_VPSS;
    dest_chn.dev_id = m_vpss_grp_id;
    dest_chn.chn_id = 0; // vpss_chn

    check_return(hi_mpi_sys_bind(&src_chn, &dest_chn), "hi_mpi_sys_bind(VI-VPSS)");

    return HI_SUCCESS;
}


hi_s32 HisiVpss::vpss_init(){

    vpss_set_attr();
    vi_bind_vpss();
    printf("init vpss success \n");
    return HI_SUCCESS;
}


hi_s32 HisiVpss::stop_vpss_grp_chn(){

    hi_s32 ret;
    hi_bool chn_enable[HI_VPSS_MAX_PHYS_CHN_NUM];
    hi_vpss_chn vpss_chn;
    if(m_vpss_grp_id % 2 == 0){
        vpss_chn = HI_VPSS_CHN0;
    }else{
        vpss_chn = HI_VPSS_CHN2;
    }

    if (vpss_chn >= HI_VPSS_MAX_PHYS_CHN_NUM) {
        sample_print("vpss_chn:%d invalid!\n", vpss_chn);
        return HI_FAILURE;
    }

    chn_enable[vpss_chn] = HI_TRUE;

    // ret = sample_common_vpss_stop(vpss_grp, chn_enable, HI_VPSS_MAX_PHYS_CHN_NUM);

    hi_u32 chn_array_size = HI_VPSS_MAX_CHN_NUM;

    if (chn_array_size < HI_VPSS_MAX_PHYS_CHN_NUM) {
        sample_print("array size(%u) of chn_enable need > %u!\n", chn_array_size, HI_VPSS_MAX_PHYS_CHN_NUM);
        return HI_FAILURE;
    }

    for (hi_s32 i = 0; i < HI_VPSS_MAX_PHYS_CHN_NUM; ++i) {
        if (chn_enable[i] == HI_TRUE) {
            vpss_chn = i;
            ret = hi_mpi_vpss_disable_chn(m_vpss_grp_id, vpss_chn);
            if (ret != HI_SUCCESS) {
                sample_print("failed with %#x!\n", ret);
                return HI_FAILURE;
            }
        }
    }

    ret = hi_mpi_vpss_stop_grp(m_vpss_grp_id);
    if (ret != HI_SUCCESS) {
        sample_print("failed with %#x!\n", ret);
        return HI_FAILURE;
    }

    ret = hi_mpi_vpss_destroy_grp(m_vpss_grp_id);
    if (ret != HI_SUCCESS) {
        sample_print("failed with %#x!\n", ret);
        return HI_FAILURE;
    }

    if (ret != HI_SUCCESS) {
        sample_print("failed with %#x!\n", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

hi_s32 HisiVpss::vpss_deinit(){

    hi_mpp_chn src_chn;
    hi_mpp_chn dest_chn;
    hi_vi_chn vi_chn = m_vpss_grp_id;
    hi_s32 ret;
    
    src_chn.mod_id = HI_ID_VI;
    src_chn.dev_id = 0;
    src_chn.chn_id = vi_chn;

    dest_chn.mod_id = HI_ID_VPSS;
    dest_chn.dev_id = m_vpss_grp_id;
    dest_chn.chn_id = 0;

    check_return(hi_mpi_sys_unbind(&src_chn, &dest_chn), "hi_mpi_sys_unbind(VI-VPSS)");

    ret = stop_vpss_grp_chn();

    if(ret != HI_SUCCESS){
        printf("stop vpss fail \n");
        return ret;
    }

    printf("stop vpss success \n");
    return HI_SUCCESS;
    


}