#include "HisiVo.h"


vo_wnd_info g_vo_sample_wnd_info[VO_MODE_BUTT] = {
    { VO_MODE_1MUX,   1,  1, 0, 0 },
    { VO_MODE_2MUX,   2,  2, 0, 0 },
    { VO_MODE_4MUX,   4,  2, 0, 0 },
    { VO_MODE_8MUX,   8,  3, 0, 0 },
    { VO_MODE_9MUX,   9,  3, 0, 0 },
    { VO_MODE_16MUX,  16, 4, 0, 0 },
    { VO_MODE_25MUX,  25, 5, 0, 0 },
    { VO_MODE_36MUX,  36, 6, 0, 0 },
    { VO_MODE_49MUX,  49, 7, 0, 0 },
    { VO_MODE_64MUX,  64, 8, 0, 0 },
    { VO_MODE_2X4,    8,  4, 4, 2 }
};

bool HisiVo::isInitialized = false;
bool HisiVo::isBegin = false;
hi_vo_chn HisiVo::vo_chn = 0;


static hi_s32 mode_to_chn_attr(vo_wnd_info *wnd_info, hi_vo_video_layer_attr *layer_attr, hi_s32 chn, hi_vo_chn_attr *chn_attr);

HisiVo::HisiVo(hi_u32 width, hi_u32 height, hi_u32 frame_rate, hi_s32 vpss_grp_id) : HisiBase(0, 0, width, height, frame_rate), 
                                                                m_vo_pub_attr({}),
                                                                m_layer_attr({}),
                                                                m_wnd_info({VO_MODE_1MUX, 1, 1, 0, 0}),
                                                                m_vpss_grpId(vpss_grp_id)

{
    

    hi_rect def_disp_rect = { 0, 0, 0, 0 };
    def_disp_rect.width = get_size().width;
    def_disp_rect.height = get_size().height;

    hi_size def_img_size = { 1920, 1080 };
    def_img_size.height = get_size().height;
    def_img_size.width = get_size().width;

    // 0     /* VO's device HD0 */
    // 1     /* VO's device HD1 */
    // 2     /* VO's device SD0 */
    m_vo_config.vo_dev = 0;
    m_vo_config.vo_intf_type = HI_VO_INTF_HDMI | HI_VO_INTF_BT1120;
    m_vo_config.intf_sync = HI_VO_OUT_1080P60;
    m_vo_config.bg_color = COLOR_RGB_BLACK;
    m_vo_config.pix_format = HI_PIXEL_FORMAT_YVU_SEMIPLANAR_420;
    m_vo_config.disp_rect = def_disp_rect;
    m_vo_config.image_size = def_img_size;
    m_vo_config.vo_part_mode = HI_VO_PARTITION_MODE_MULTI;
    m_vo_config.dis_buf_len = 4; /* 3: def buf len for single */
    m_vo_config.dst_dynamic_range = HI_DYNAMIC_RANGE_SDR8;
    m_vo_config.vo_mode = VO_MODE_4MUX;
    m_vo_config.compress_mode = HI_COMPRESS_MODE_LINE;
    

    if (m_vo_config.vo_mode >= VO_MODE_BUTT) {
        sample_print("vo mode %d not support!\n", m_vo_config.vo_mode);
    }
    /* set and start VO device vo_dev#. */
    m_vo_pub_attr.intf_type = m_vo_config.vo_intf_type;
    m_vo_pub_attr.intf_sync = m_vo_config.intf_sync;
    m_vo_pub_attr.bg_color = m_vo_config.bg_color;


    m_layer_attr.display_rect = def_disp_rect;
    m_layer_attr.display_frame_rate = get_frame_rate();

    m_layer_attr.cluster_mode_en = HI_FALSE;
    m_layer_attr.double_frame_en = HI_FALSE;
    m_layer_attr.pixel_format = m_vo_config.pix_format;

    m_layer_attr.img_size.width = FHD_WIDTH;
    m_layer_attr.img_size.height = FHD_HEIGHT;


    m_layer_attr.dst_dynamic_range = m_vo_config.dst_dynamic_range;
    m_layer_attr.display_buf_len = m_vo_config.dis_buf_len;
    m_layer_attr.partition_mode = m_vo_config.vo_part_mode;
    m_layer_attr.compress_mode =  m_vo_config.compress_mode;

    m_wnd_info.mode = m_vo_config.vo_mode;
    m_wnd_info.wnd_num = g_vo_sample_wnd_info[m_vo_config.vo_mode].wnd_num;
    m_wnd_info.square = g_vo_sample_wnd_info[m_vo_config.vo_mode].square;
    m_wnd_info.row = g_vo_sample_wnd_info[m_vo_config.vo_mode].row;
    m_wnd_info.col = g_vo_sample_wnd_info[m_vo_config.vo_mode].col;

    m_vpss_chn_dhd0 = HI_VPSS_CHN0;
}



hi_s32 HisiVo::start_vo(){

    if(isInitialized == true){
        printf("have started vo \n");
        return HI_SUCCESS;
    }

    isInitialized = true;

    // start dev
    hi_s32 ret;
    ret = hi_mpi_vo_set_pub_attr(m_vo_config.vo_dev, &m_vo_pub_attr);
    if (ret != HI_SUCCESS) {
        sample_print("failed with %#x!\n", ret);
        // return HI_FAILURE;
    }

    ret = hi_mpi_vo_enable(m_vo_config.vo_dev);
    if (ret != HI_SUCCESS) {
        sample_print("failed with %#x!\n", ret);
        // return HI_FAILURE;
    }

    printf("start vo dev success\n");

    // start layer
    hi_vo_layer vo_layer = m_vo_config.vo_dev;

    ret = hi_mpi_vo_set_video_layer_attr(vo_layer, &m_layer_attr);
    if (ret != HI_SUCCESS) {
        sample_print("failed with %#x!\n", ret);
        // return HI_FAILURE;
    }

    ret = hi_mpi_vo_enable_video_layer(vo_layer);
    if (ret != HI_SUCCESS) {
        sample_print("failed with %#x!\n", ret);
        // return HI_FAILURE;
    }
    
    hi_vo_csc csc;
    (hi_void)hi_mpi_vo_get_layer_csc(vo_layer, &csc);
    csc.luma = 90;
    hi_mpi_vo_set_layer_csc(vo_layer, &csc);

    printf("start vo layer success\n");
    

    // start vo chn
    hi_vo_chn_attr chn_attr;
    hi_vo_video_layer_attr layer_attr;
    ret = hi_mpi_vo_get_video_layer_attr(vo_layer, &layer_attr);

    for (hi_s32 i = 0; i < (hi_s32)m_wnd_info.wnd_num; i++) {
        ret = mode_to_chn_attr(&m_wnd_info, &layer_attr, i, &chn_attr);
        if (ret != HI_SUCCESS) {
            sample_print("failed with %#x!\n", ret);
            return HI_FAILURE;
        }

        ret = hi_mpi_vo_set_chn_attr(vo_layer, i, &chn_attr);
        if (ret != HI_SUCCESS) {
            sample_print("failed with %#x!\n", ret);
            return HI_FAILURE;
        }

        ret = hi_mpi_vo_enable_chn(vo_layer, i);
        if (ret != HI_SUCCESS) {
            sample_print("failed with %#x!\n", ret);
            return HI_FAILURE;
        }
    }
    return HI_SUCCESS;
}




static hi_s32 mode_to_chn_attr(vo_wnd_info *wnd_info, hi_vo_video_layer_attr *layer_attr, hi_s32 chn, hi_vo_chn_attr *chn_attr)
{
    hi_u32 width;
    hi_u32 height;

    check_null_ptr_return(wnd_info);
    check_null_ptr_return(layer_attr);
    check_null_ptr_return(chn_attr);

    width = layer_attr->img_size.width;
    height = layer_attr->img_size.height;
    if (wnd_info->mode != VO_MODE_2X4) {
        chn_attr->rect.x = HI_ALIGN_DOWN((width / wnd_info->square) * (chn % wnd_info->square), 2);  /* 2: 2 aligin */
        chn_attr->rect.y = HI_ALIGN_DOWN((height / wnd_info->square) * (chn / wnd_info->square), 2); /* 2: 2 aligin */
        chn_attr->rect.width = HI_ALIGN_DOWN(width / wnd_info->square, 2);                           /* 2: 2 aligin */
        chn_attr->rect.height = HI_ALIGN_DOWN(height / wnd_info->square, 2);                         /* 2: 2 aligin */
    } else {
        chn_attr->rect.x = HI_ALIGN_DOWN((width / wnd_info->col) * (chn % wnd_info->col), 2);  /* 2: 2 aligin */
        chn_attr->rect.y = HI_ALIGN_DOWN((height / wnd_info->row) * (chn / wnd_info->col), 2); /* 2: 2 aligin */
        chn_attr->rect.width = HI_ALIGN_DOWN(width / wnd_info->col, 2);                        /* 2: 2 aligin */
        chn_attr->rect.height = HI_ALIGN_DOWN(height / wnd_info->row, 2);                      /* 2: 2 aligin */
    }

    chn_attr->priority = 0;
    chn_attr->deflicker_en = HI_FALSE;
    return HI_SUCCESS;
}



hi_s32 HisiVo::vo_bind_vpss(){

    hi_s32 ret;

    /* this type group is sent to venc */
    if (m_vpss_grpId % 2 != 0) { /* 2 : odd-even */
        printf("not bind,  no for vo\n");
        return HI_SUCCESS;
    }

    /* this type group is sent to vo */
    
    hi_mpp_chn src_chn;
    hi_mpp_chn dest_chn;

    src_chn.mod_id = HI_ID_VPSS;
    src_chn.dev_id = m_vpss_grpId;
    src_chn.chn_id = m_vpss_chn_dhd0;

    dest_chn.mod_id = HI_ID_VO;
    dest_chn.dev_id = m_vo_config.vo_dev;
    dest_chn.chn_id = vo_chn;

    vo_chn++;

    check_return(hi_mpi_sys_bind(&src_chn, &dest_chn), "hi_mpi_sys_bind(VPSS-VO)");


    printf("vo bind vpss success \n");
    return HI_SUCCESS;

}





hi_s32 HisiVo::vo_begin(){
    if(isBegin == true){
        printf("have began \n");
        return HI_SUCCESS;
    }
    isBegin = true;
    hi_s32 ret;
    ret = hi_mpi_vo_batch_begin(m_vo_config.vo_dev);
    if (ret != HI_SUCCESS) {
        sample_print("vo batch begin failed!\n");
        return ret;
    }
    return HI_SUCCESS;
}

hi_s32 HisiVo::init(){

    (hi_void)start_vo();
    (hi_void)vo_bind_vpss();
    (hi_void)vo_begin();

    return HI_SUCCESS;
}