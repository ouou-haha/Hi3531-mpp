#include "HisiSysvbmipi.h"



bool HisiSysvbmipi::isInitialized = false;

HisiSysvbmipi::HisiSysvbmipi(hi_s32 vi_cnt, hi_s32 width, hi_s32 height) 
    : m_vi_dev_cnt(vi_cnt),
      m_vb_cfg({}), // 如果需要，初始化结构体为默认值
      m_blk_size(0) // 初始化为零或适当的默认值
   
{   
    m_capture_rect.x = 0;
    m_capture_rect.y = 0;
    m_capture_rect.width = width;
    m_capture_rect.height = height;

    m_minor_dst_size.width = HD_WIDTH;
    m_minor_dst_size.height = HD_HEIGHT;

    m_pic_buf_attr.width = width;
    m_pic_buf_attr.height = height;
    m_pic_buf_attr.pixel_format = HI_PIXEL_FORMAT_YVU_SEMIPLANAR_420;
    m_pic_buf_attr.bit_width = HI_DATA_BIT_WIDTH_8;
    m_pic_buf_attr.compress_mode = HI_COMPRESS_MODE_SEG_COMPACT;
    
    // 视频缓冲区(VB)池的配置
    memset_s(&m_vb_cfg, sizeof(hi_vb_cfg), 0, sizeof(hi_vb_cfg));
    m_vb_cfg.max_pool_cnt = 3;

    // 计算第一个视频缓冲池的块大小
    m_pic_buf_attr.align = HI_DEFAULT_ALIGN;
    m_blk_size = hi_common_get_pic_buf_size(&m_pic_buf_attr);
    m_vb_cfg.common_pool[0].blk_size = m_blk_size;
    m_vb_cfg.common_pool[0].blk_cnt = SAMPLE_CHN_NUM * VB_NUM_PRE_CHN;

    // 为无压缩模式更新块大小
    m_pic_buf_attr.compress_mode = HI_COMPRESS_MODE_NONE;
    m_blk_size = hi_common_get_pic_buf_size(&m_pic_buf_attr);
    m_vb_cfg.common_pool[1].blk_size = m_blk_size;
    m_vb_cfg.common_pool[1].blk_cnt = 4 * VB_NUM_PRE_CHN;

    // 计算第二个视频缓冲池的块大小
    m_pic_buf_attr.width = m_minor_dst_size.width;
    m_pic_buf_attr.height = m_minor_dst_size.height;
    m_blk_size = hi_common_get_pic_buf_size(&m_pic_buf_attr);
    m_vb_cfg.common_pool[2].blk_size = m_blk_size; /* 第二个池 */
    m_vb_cfg.common_pool[2].blk_cnt = 4 * VB_NUM_PRE_CHN; /* 第二个池 */
}


HisiSysvbmipi::~HisiSysvbmipi()
{
}

hi_s32 HisiSysvbmipi::init(){

    if(isInitialized == true){
        printf("have inited sys \n");
        return HI_SUCCESS;
    }

    isInitialized = true;
    
    
    // vb初始化 系统初始化 
    hi_s32 ret;
    hi_s32 fd;
    lane_divide_mode_t hs_mode = LANE_DIVIDE_MODE_0;


    hi_mpi_sys_exit();
    hi_mpi_vb_exit();

    ret = hi_mpi_vb_set_cfg(&m_vb_cfg);
    if (ret != HI_SUCCESS) {
        sample_print("hi_mpi_vb_set_conf failed!\n");
        return HI_FAILURE;
    }

    ret = hi_mpi_vb_init();
    if (ret != HI_SUCCESS) {
        sample_print("hi_mpi_vb_init failed!\n");
        return HI_FAILURE;
    }

    ret = hi_mpi_sys_init();
    if (ret != HI_SUCCESS) {
        sample_print("hi_mpi_sys_init failed!\n");
        hi_mpi_vb_exit();
        return HI_FAILURE;
    }

    printf("init vb success \n");



    // 启动 mipi

    
    fd = open(MIPI_DEV_NODE, O_RDWR);

    if (fd < 0) {
        sample_print("open hi_mipi dev failed\n");
        return HI_FAILURE;
    }

    ret = ioctl(fd, HI_MIPI_SET_HS_MODE, &hs_mode);
    if (ret != HI_SUCCESS) {
        sample_print("HI_MIPI_SET_HS_MODE failed\n");
        close(fd);
        return ret;
    }

    combo_dev_t mipi_dev;

    for (hi_s32 i = 0; i < m_vi_dev_cnt; i++) {
        mipi_dev = i * 1;
        // 启用 MIPI 时钟
        ret = ioctl(fd, HI_MIPI_ENABLE_MIPI_CLOCK, &mipi_dev);
        if (ret != HI_SUCCESS) {
            sample_print("HI_MIPI_ENABLE_MIPI_CLOCK failed\n");
            close(fd);
            return ret;
        }

        // 重置 MIPI 设备
        ret = ioctl(fd, HI_MIPI_RESET_MIPI, &mipi_dev);
        if (ret != HI_SUCCESS) {
            sample_print("HI_MIPI_RESET_MIPI failed\n");
            close(fd);
            return ret;
        }

        // 设置 MIPI 属性
        combo_dev_attr_t mipi_dev_attr;
        mipi_dev_attr.devno = mipi_dev;
        mipi_dev_attr.img_rect.x = 0;
        mipi_dev_attr.img_rect.y = 0;
        mipi_dev_attr.img_rect.width = m_capture_rect.width;
        mipi_dev_attr.img_rect.height = m_capture_rect.height;
        mipi_dev_attr.input_mode = INPUT_MODE_MIPI;
        mipi_dev_attr.mipi_attr.input_data_type = DATA_TYPE_YUV422_8BIT;
        mipi_dev_attr.scan_mode = (mipi_scan_mode_t)HI_VI_SCAN_PROGRESSIVE;

        for (hi_s32 j = 0; j < MIPI_LANE_NUM_PRE_DEV; j++) {
            mipi_dev_attr.mipi_attr.lane_id[j] = mipi_dev * MIPI_LANE_NUM_PRE_DEV + j;
        }

        // 解除重置 MIPI 设备
        ret = ioctl(fd, HI_MIPI_SET_DEV_ATTR, &mipi_dev_attr);
        if (ret != HI_SUCCESS) {
            sample_print("HI_MIPI_SET_DEV_ATTR failed\n");
            return HI_FAILURE;
        }

        ret = ioctl(fd, HI_MIPI_UNRESET_MIPI, &mipi_dev);
        if (ret != HI_SUCCESS) {
            sample_print("HI_MIPI_UNRESET_MIPI failed\n");
            close(fd);
            return ret;
        }


    }

    close(fd);
    printf("set mipi success \n");
    return HI_SUCCESS;
}


hi_s32 HisiSysvbmipi::stop_mipi(){

    hi_s32 fd, ret;
    fd = open(MIPI_DEV_NODE, O_RDWR);
    if (fd < 0) {
        sample_print("open hi_mipi dev failed\n");
        return HI_FAILURE;
    }

    combo_dev_t mipi_dev;
    for (hi_s32 i = 0; i < m_vi_dev_cnt; i++) {
        mipi_dev = i * 1;
        ret = ioctl(fd, HI_MIPI_RESET_MIPI, &mipi_dev);
        if (ret != HI_SUCCESS) {
            sample_print("HI_MIPI_RESET_MIPI failed\n");
            close(fd);
            return HI_FAILURE;
        }

        ret = ioctl(fd, HI_MIPI_DISABLE_MIPI_CLOCK, &mipi_dev);
        if (ret != HI_SUCCESS) {
            sample_print("HI_MIPI_ENABLE_MIPI_CLOCK failed\n");
            close(fd);
            return HI_FAILURE;
        }
    }

    close(fd);

    if (ret != HI_SUCCESS) {
        sample_print("stop mipi failed!\n");
        return ret;
    }

}

hi_s32 HisiSysvbmipi::stop_sys(){

    hi_mpi_sys_exit();
    hi_mpi_vb_exit_mod_common_pool(HI_VB_UID_VDEC);
    hi_mpi_vb_exit();

    printf("stop sys success \n");
    return HI_SUCCESS;
}

hi_s32 HisiSysvbmipi::deinit(){
    hi_s32 ret;
    ret = stop_mipi();
    if(ret != HI_SUCCESS){
        printf("stop mipi fail \n");
    }

    ret = stop_sys();
    if(ret != HI_SUCCESS){
        printf("stop sys fail \n");
    }

    return HI_SUCCESS;
    
}
