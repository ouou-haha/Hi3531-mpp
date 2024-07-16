#include "HisiVin.h"


// 全局函数声明
hi_s32 start_tp2854b_cfg(video_encoding encoding);


hi_vi_chn_attr def_vi_chn_attr = {
    /* crop_x crop_y, crop_w  crop_h */
    { 0, 0, 1280, 720 },
    /* dest_w  dest_h */
    { 1280, 720 },
    /* capture_select */
    HI_VI_CAPTURE_SELECT_BOTH,
    /* scan mode */
    HI_VI_SCAN_PROGRESSIVE,
    /* pixel_format */
    HI_PIXEL_FORMAT_YVU_SEMIPLANAR_420,
    /* mirror_en  flip_en */
    HI_FALSE,
    HI_FALSE,
    /* compress mode */
    HI_COMPRESS_MODE_SEG_COMPACT,
    /* src_frame_rate   dst_frame_rate */
    -1,
    -1
};

hi_vi_dev_attr def_vi_dev_attr = {
    /* interface mode */
    HI_VI_MODE_MIPI_YUV422,
    /* work mode, 1/2/4 multiplex */
    HI_VI_WORK_MODE_MULTIPLEX_1,
    /* r_mask    g_mask    b_mask */
    { 0xFF000000, 0x0 },
    /* for single/double edge, must be set when double edge */
    HI_VI_CLK_EDGE_SINGLE_UP,
    /* enDataSeq, just support yuv */
    HI_VI_IN_DATA_YVYU,
    /* sync info */
    {
        /* port_vsync  port_vsync_neg  port_hsync  port_hsync_neg */
        HI_VI_VSYNC_FIELD,
        HI_VI_VSYNC_NEG_HIGH,
        HI_VI_HSYNC_VALID_SIG,
        HI_VI_HSYNC_NEG_HIGH,
        HI_VI_VSYNC_VALID_SIG,
        HI_VI_VSYNC_VALID_NEG_HIGH,
        /*
         * timing info:
         * hsync_hfb  hsync_act  hsync_hhb
         * vsync0_vhb vsync0_act vsync0_hhb
         * vsync1_vhb vsync1_act vsync1_hhb
         */
        { 0, 0, 0,
          0, 0, 0,
          0, 0, 0 }
    },
    /* data_reverse_en */
    HI_FALSE,
    /* mixed_capture_en */
    HI_FALSE,
};


HisiVin::HisiVin(hi_s32 vi_devId, hi_s32 vi_chnId, hi_s32 width, hi_s32 height, hi_bool minor_en) : HisiBase(vi_devId, vi_chnId, width, height, 60){

    // this->vi_devId = vi_devId;
    // this->vi_chnId = vi_chnId;
    // this->size.height = height;
    // this->size.width = width;
    this->minor_en = minor_en;

    // 捕捉位置
    this->capture_rect.x = 0;
    this->capture_rect.y = 0;
    this->capture_rect.width = get_size().width;
    this->capture_rect.height = get_size().height;


    // 主通道 辅通道目标尺寸
    this->dst_size.width = capture_rect.width;
    this->dst_size.height = capture_rect.height;
    this->minor_dst_size.width = HD_WIDTH;
    this->minor_dst_size.height = HD_HEIGHT;


    // 配置ad编码类型
    video_encoding ad_encoding = SAMPLE_VIDEO_ENCODING_NTSC;

    // 配置vi dev
    (hi_void)memcpy_s(&vi_dev_attr, sizeof(hi_vi_dev_attr), &def_vi_dev_attr, sizeof(hi_vi_dev_attr));
    vi_dev_attr.work_mode = HI_VI_WORK_MODE_MULTIPLEX_2;  // 每个 VI 设备可以处理 2 路视频通道（2路复用）
    vi_dev_attr.intf_mode = HI_VI_MODE_MIPI_YUV422;
    vi_dev_attr.component_mask[0] = 0x00ff0;
    vi_dev_attr.component_mask[1] = 0xff000;
    vi_dev_attr.data_seq = HI_VI_IN_DATA_UVUV;
    vi_dev_attr.clk_edge = HI_VI_CLK_EDGE_DOUBLE;

    // 配置vi 通道
    memset_s(&major_chn_attr, sizeof(hi_vi_chn_attr), 0, sizeof(hi_vi_chn_attr));
    (hi_void)memcpy_s(&major_chn_attr, sizeof(hi_vi_chn_attr), &def_vi_chn_attr, sizeof(hi_vi_chn_attr));
    (hi_void)memcpy_s(&major_chn_attr.capture_rect, sizeof(hi_rect), &capture_rect, sizeof(hi_rect));
    (hi_void)memcpy_s(&major_chn_attr.dst_size, sizeof(hi_size), &dst_size, sizeof(hi_size));
    major_chn_attr.pixel_format = SAMPLE_PIXEL_FORMAT;
    major_chn_attr.scan_mode = HI_VI_SCAN_PROGRESSIVE;
    major_chn_attr.src_frame_rate = -1;
    major_chn_attr.dst_frame_rate = -1;

    (hi_void)memcpy_s(&minor_chn_attr, sizeof(hi_vi_chn_attr), &major_chn_attr, sizeof(hi_vi_chn_attr));
    (hi_void)memcpy_s(&minor_chn_attr.dst_size, sizeof(hi_size), &minor_dst_size, sizeof(hi_size));
    minor_chn_attr.src_frame_rate = -1;
    minor_chn_attr.dst_frame_rate = -1;
}



hi_s32 HisiVin::init_ad(){

    hi_s32 ret;
    ret = start_tp2854b_cfg(ad_encoding);
    if (ret != HI_SUCCESS) {
        sample_print("tp2854b config failed!\n");
        return ret;
    }

    printf("init ad success  \n");
    return HI_SUCCESS;
}

hi_s32 HisiVin::init_dev(){

    hi_s32 ret = HI_FAILURE;
	hi_vi_dev_attr old_dev_attr;
    ret = hi_mpi_vi_get_dev_attr(get_vi_id(), &old_dev_attr);
    if(ret == HI_SUCCESS){
       printf("vi_dev have been set \n ");
       return HI_SUCCESS;
    }

    ret = hi_mpi_vi_set_dev_attr(get_vi_id(), &vi_dev_attr);
    if (ret != HI_SUCCESS) {
        sample_print("hi_mpi_vi_set_dev_attr failed 0x%x\n", ret);
        return ret;
    }

    ret = hi_mpi_vi_enable_dev(get_vi_id());
    if (ret != HI_SUCCESS) {
        sample_print("hi_mpi_vi_enable_dev failed 0x%x\n", ret);
        return ret;
    }

    printf("init vi_dev success \n");
    return HI_SUCCESS;
}

hi_s32 HisiVin::init_chn(){

    hi_s32 ret = HI_FAILURE;
    hi_vi_chn_bind_attr chn_bind_attr;

    // // 防止重复绑定时报错 先释放
    // ret = hi_mpi_vi_disable_chn(minor_chn(get_chn_id()));
    // if (ret != HI_SUCCESS) {
    //     sample_print("hi_mpi_vi_disable_minor_chn failed!\n");
    //     return ret;
    // }

    // ret = hi_mpi_vi_disable_chn(get_chn_id());
    // if (ret != HI_SUCCESS) {
    //     sample_print("hi_mpi_vi_disable_chn failed!\n");
    //     return ret;
    // }


    /* chn 2,6,10,14,18,22,26,30 */
    if (get_chn_id() == CHN_NUM_PRE_DEV * get_vi_id() + SECOND_CHN_OFFSET_2MUX) {
        ret = hi_mpi_vi_unbind_chn(get_chn_id());
        if (ret != HI_SUCCESS) {
            sample_print("hi_mpi_vi_unbind_chn 0x%x\n", ret);
            return ret;
        }
        chn_bind_attr.vi_dev = get_vi_id();
        chn_bind_attr.vi_way = get_chn_id();
        ret = hi_mpi_vi_bind_chn(get_chn_id(), &chn_bind_attr);
        if (ret != HI_SUCCESS) {
            sample_print("hi_mpi_vi_bind_chn failed 0x%x\n", ret);
            return ret;
        }
    }



    ret = hi_mpi_vi_set_chn_attr(get_chn_id(), &major_chn_attr);
    if (ret != HI_SUCCESS) {
        sample_print("hi_mpi_vi_set_chn_attr failed 0x%x\n", ret);
        return ret;
    }

    ret = hi_mpi_vi_enable_chn(get_chn_id());
    if (ret != HI_SUCCESS) {
        sample_print("hi_mpi_vi_enable_chn failed 0x%x\n", ret);
        return ret;
    }


    // 辅助通道 
    if (minor_en == HI_TRUE) {
        ret = hi_mpi_vi_set_minor_chn_attr(minor_chn(get_chn_id()), &minor_chn_attr);
        if (ret != HI_SUCCESS) {
            sample_print("hi_mpi_vi_set_minor_chn_attr failed 0x%x\n", ret);
            return ret;
        }

        ret = hi_mpi_vi_enable_chn(minor_chn(get_chn_id()));
        if (ret != HI_SUCCESS) {
            sample_print("hi_mpi_vi_enable_chn failed 0x%x\n", ret);
            return ret;
        }
    }

    printf("init vi_chn success \n");
    return HI_SUCCESS;
}


hi_s32 HisiVin::init(){
    hi_s32 ret = HI_FAILURE;

    ret = init_ad();
    if(ret != HI_SUCCESS){
        printf("init ad faile \n");
    }

    ret = init_dev();
    if(ret != HI_SUCCESS){
        printf("init dev faile \n");
    }

    ret = init_chn();
    if(ret != HI_SUCCESS){
        printf("init chn faile \n");
		printf("init vi faile  \n");
        return HI_FAILURE;
    }

    printf("init vi success \n");
    return HI_SUCCESS;
    
}



hi_s32 HisiVin::stop_chn(){

    hi_s32 ret;
    // 禁用通道
    // ps：在禁用该通道之前必须先禁用辅通道 所以向后往前禁用 避免报错
    ret = hi_mpi_vi_disable_chn(minor_chn(get_chn_id()));
    if (ret != HI_SUCCESS) {
        sample_print("hi_mpi_vi_disable_chn failed!\n");
        return ret;
    }

    ret = hi_mpi_vi_disable_chn(get_chn_id());
    if (ret != HI_SUCCESS) {
        sample_print("hi_mpi_vi_disable_minor_chn failed!\n");
        return ret;
    }


    printf("stop chn success \n");
    return HI_SUCCESS;

}

hi_s32 HisiVin::stop_dev(){
    // 禁用设备
    // 必须先禁用所有与该 VI 设备绑定的 VI 通道后，才能禁用 VI 设备。 报错很正常
    hi_s32 ret;
    ret = hi_mpi_vi_disable_dev(get_vi_id());
    if (ret != HI_SUCCESS) {
        sample_print("hi_mpi_vi_disable_dev failed!  \n");
        return ret;
    }
    printf("stop dev success \n");
    return HI_SUCCESS;
}



hi_s32 HisiVin::deinit(){
    hi_s32 ret;
    ret = stop_chn();
    if(ret != HI_SUCCESS){
        printf("stop vi chn fail \n");
    }

    ret = stop_dev();
    if(ret != HI_SUCCESS){
        printf("stop vi dev fail \n");
    }

    return HI_SUCCESS;    
}

// 全局函数
hi_s32 start_tp2854b_cfg(video_encoding encoding) 
{
    int fd, i, j;
    tp2802_video_mode tp_video_mode;
    const int chip_cnt = 8;

    fd = open(TP2854B_FILE, O_RDWR);
    if (fd < 0) {
        printf("open tp2854b (%s) fail\n", TP2854B_FILE);
        return -1;
    }

    for (i = 0; i < chip_cnt; i++) {
        tp_video_mode.chip = i;

        for (j = 0; j < CHANNELS_PER_CHIP; j++) {
            tp_video_mode.ch = j;
            tp_video_mode.std = STD_HDA;
            tp_video_mode.mode = (encoding == SAMPLE_VIDEO_ENCODING_PAL) ? TP2802_1080P25 : TP2802_1080P30;
            //tp_video_mode.mode = TP2802_720P25;
            // 写死2通道复用
            tp_video_mode.output = MIPI_2CH4LANE_297M;
            ioctl(fd, TP2802_SET_VIDEO_MODE, &tp_video_mode);
        }
    }
    close(fd);
    return HI_SUCCESS;
}
