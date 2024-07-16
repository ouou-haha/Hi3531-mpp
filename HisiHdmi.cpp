#include "HisiHdmi.h"


hi_hdmi_video_format g_vo_hdmi_sync[HI_VO_OUT_BUTT] = {
    HI_HDMI_VIDEO_FORMAT_PAL,
    HI_HDMI_VIDEO_FORMAT_NTSC,
    HI_HDMI_VIDEO_FORMAT_VESA_CUSTOMER_DEFINE,
    HI_HDMI_VIDEO_FORMAT_VESA_CUSTOMER_DEFINE,
    HI_HDMI_VIDEO_FORMAT_861D_640X480_60,
    HI_HDMI_VIDEO_FORMAT_480P_60,
    HI_HDMI_VIDEO_FORMAT_576P_50,
    HI_HDMI_VIDEO_FORMAT_VESA_800X600_60,
    HI_HDMI_VIDEO_FORMAT_VESA_1024X768_60,
    HI_HDMI_VIDEO_FORMAT_720P_50,
    HI_HDMI_VIDEO_FORMAT_720P_60,
    HI_HDMI_VIDEO_FORMAT_VESA_1280X800_60,
    HI_HDMI_VIDEO_FORMAT_VESA_1280X1024_60,
    HI_HDMI_VIDEO_FORMAT_VESA_1366X768_60,
    HI_HDMI_VIDEO_FORMAT_VESA_1400X1050_60,
    HI_HDMI_VIDEO_FORMAT_VESA_1440X900_60,
    HI_HDMI_VIDEO_FORMAT_VESA_1680X1050_60,
    HI_HDMI_VIDEO_FORMAT_1080P_24,
    HI_HDMI_VIDEO_FORMAT_1080P_25,
    HI_HDMI_VIDEO_FORMAT_1080P_30,
    HI_HDMI_VIDEO_FORMAT_1080i_50,
    HI_HDMI_VIDEO_FORMAT_1080i_60,
    HI_HDMI_VIDEO_FORMAT_1080P_50,
    HI_HDMI_VIDEO_FORMAT_1080P_60,
    HI_HDMI_VIDEO_FORMAT_VESA_1600X1200_60,
    HI_HDMI_VIDEO_FORMAT_VESA_1920X1200_60,
    HI_HDMI_VIDEO_FORMAT_1920x2160_30,
    HI_HDMI_VIDEO_FORMAT_2560x1440_30,
    HI_HDMI_VIDEO_FORMAT_2560x1440_60,
    HI_HDMI_VIDEO_FORMAT_2560x1600_60,
    HI_HDMI_VIDEO_FORMAT_3840X2160P_24,
    HI_HDMI_VIDEO_FORMAT_3840X2160P_25,
    HI_HDMI_VIDEO_FORMAT_3840X2160P_30,
    HI_HDMI_VIDEO_FORMAT_3840X2160P_50,
    HI_HDMI_VIDEO_FORMAT_3840X2160P_60,
    HI_HDMI_VIDEO_FORMAT_4096X2160P_24,
    HI_HDMI_VIDEO_FORMAT_4096X2160P_25,
    HI_HDMI_VIDEO_FORMAT_4096X2160P_30,
    HI_HDMI_VIDEO_FORMAT_4096X2160P_50,
    HI_HDMI_VIDEO_FORMAT_4096X2160P_60,
    HI_HDMI_VIDEO_FORMAT_7680X4320P_30,
    HI_HDMI_VIDEO_FORMAT_VESA_CUSTOMER_DEFINE,
    HI_HDMI_VIDEO_FORMAT_VESA_CUSTOMER_DEFINE,
    HI_HDMI_VIDEO_FORMAT_VESA_CUSTOMER_DEFINE,
    HI_HDMI_VIDEO_FORMAT_VESA_CUSTOMER_DEFINE,
    HI_HDMI_VIDEO_FORMAT_VESA_CUSTOMER_DEFINE,
    HI_HDMI_VIDEO_FORMAT_VESA_CUSTOMER_DEFINE,
    HI_HDMI_VIDEO_FORMAT_VESA_CUSTOMER_DEFINE,
    HI_HDMI_VIDEO_FORMAT_VESA_CUSTOMER_DEFINE,
};

HisiHdmi::HisiHdmi() : m_vo_hdmi_rgb_mode(HI_TRUE),
                       m_intf_sync(HI_VO_OUT_1080P60)                 
{

}

hi_void HisiHdmi::vo_set_intf_param()
{
    hi_vo_hdmi_param hdmi_param;

    /* set interface param */
    if (m_vo_hdmi_rgb_mode == HI_TRUE) {
        hi_mpi_vo_get_hdmi_param(vo_devId, &hdmi_param);
        hdmi_param.csc.csc_matrix = HI_VO_CSC_MATRIX_BT709FULL_TO_RGBFULL;
        hi_mpi_vo_set_hdmi_param(vo_devId, &hdmi_param);
    }
}


hi_s32 HisiHdmi::start_hdmi_bt1120(){
    
    /* start hdmi device. note : do this after vo device started. */
    hi_hdmi_attr attr;
    hi_hdmi_video_format video_fmt;
    hi_hdmi_id hdmi_id = HI_HDMI_ID_0;

    video_fmt = HI_HDMI_VIDEO_FORMAT_1080P_60;
    if ((m_intf_sync >= HI_VO_OUT_PAL) && (m_intf_sync < HI_VO_OUT_BUTT)) {
        video_fmt = g_vo_hdmi_sync[m_intf_sync];
    }

    check_return(hi_mpi_hdmi_init(), "hi_mpi_hdmi_init");
    check_return(hi_mpi_hdmi_open(hdmi_id), "hi_mpi_hdmi_open");
    check_return(hi_mpi_hdmi_get_attr(hdmi_id, &attr), "hi_mpi_hdmi_get_attr");
    attr.video_format = video_fmt;
    check_return(hi_mpi_hdmi_set_attr(hdmi_id, &attr), "hi_mpi_hdmi_set_attr");
    check_return(hi_mpi_hdmi_start(hdmi_id), "hi_mpi_hdmi_start");

    /* start bt1120 device. note : do this after vo device started. */

    hi_u32 lt_mode;
    lt_mode = m_intf_sync;
    hi_s32 g_vo_lt8618sx_fd = HI_INVALID_VALUE;

    g_vo_lt8618sx_fd = open(LT8618SX_DEV_NAME, O_RDONLY);
    if (g_vo_lt8618sx_fd < 0) {
        printf("open file (%s) fail!\n", LT8618SX_DEV_NAME);
        return HI_FAILURE;
    }

    if (ioctl(g_vo_lt8618sx_fd, LT_CMD_SETMODE, &lt_mode) < 0) {
        printf("ioctl (%s) fail!\n", LT8618SX_DEV_NAME);
    }
    close(g_vo_lt8618sx_fd);
    g_vo_lt8618sx_fd = HI_INVALID_VALUE;

    
    printf("start hdmi success \n");
    return HI_SUCCESS;
}

hi_s32 HisiHdmi::show_video(){
    hi_vo_layer layer = 0;
    hi_mpi_vo_batch_begin(layer);
    return HI_SUCCESS;
}

hi_s32 HisiHdmi::init(){
    (hi_void)vo_set_intf_param();
    (hi_void)start_hdmi_bt1120();
    return HI_SUCCESS;
}