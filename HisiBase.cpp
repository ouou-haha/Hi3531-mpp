#include "HisiBase.h"


hi_s32 HisiBase::vpss_chn_dump_make_yuv_file_name(hi_vpss_grp grp, hi_vpss_chn chn, hi_u32 frame_cnt, FILE* fd, hi_char* yuv_name){

    const hi_s32 milli_sec = GET_CHN_FRAME_TIMEOUT;
    hi_s32 ret;

    hi_char pixel_str[PIXEL_FORMAT_STRING_LEN];
    hi_video_frame_info frame;

    ret = hi_mpi_vpss_get_chn_frame(grp, chn, &frame, milli_sec);
    if(ret != HI_SUCCESS){
        printf("can not make file name (can not get frame) \n");
        return HI_FAILURE;
    }

    if (frame.video_frame.video_format != HI_VIDEO_FORMAT_LINEAR) {
        printf("only support linear frame dump!\n");
        hi_mpi_vpss_release_chn_frame(grp, chn, &frame);
        frame.pool_id = HI_VB_INVALID_POOL_ID;
        return HI_FAILURE;
    }

    switch (frame.video_frame.pixel_format) {
        case HI_PIXEL_FORMAT_YVU_SEMIPLANAR_420:
        case HI_PIXEL_FORMAT_YUV_SEMIPLANAR_420:
            if (snprintf_s(pixel_str, PIXEL_FORMAT_STRING_LEN, PIXEL_FORMAT_STRING_LEN - 1, "P420") == -1) {
                printf("set pixel name fail!\n");
                return HI_FAILURE;
            }
            break;

        case HI_PIXEL_FORMAT_YVU_SEMIPLANAR_422:
        case HI_PIXEL_FORMAT_YUV_SEMIPLANAR_422:
            if (snprintf_s(pixel_str, PIXEL_FORMAT_STRING_LEN, PIXEL_FORMAT_STRING_LEN - 1, "P422") == -1) {
                printf("set pixel name fail!\n");
                return HI_FAILURE;
            }
            break;

        default:
            if (snprintf_s(pixel_str, PIXEL_FORMAT_STRING_LEN, PIXEL_FORMAT_STRING_LEN - 1, "P400") == -1) {
                printf("set pixel name fail!\n");
                return HI_FAILURE;
            }
            break;
    }

    /* make file name */
    if (snprintf_s(yuv_name, FILE_NAME_LENGTH, FILE_NAME_LENGTH - 1, "./vpss_grp%d_chn%d_%dx%d_%s_%d.yuv",
        grp, chn, frame.video_frame.width,
        frame.video_frame.height, pixel_str, frame_cnt) == -1) {
        printf("set out put file name fail!\n");
        return HI_FAILURE;
    }
    printf("Dump YUV frame of vpss chn %d  to file: \"%s\"\n", chn, yuv_name);

    /* open file */
    fd = fopen(yuv_name, "wb");
    if (fd == HI_NULL) {
        printf("open file failed, errno %d!\n", errno);
        return HI_FAILURE;
    }
    fflush(stdout);


    ret = hi_mpi_vpss_release_chn_frame(grp, chn, &frame);
    if (ret != HI_SUCCESS) {
        printf("Release frame error ,now exit !!!\n");
        return HI_FAILURE;
    }
    frame.pool_id = HI_VB_INVALID_POOL_ID;
    return HI_SUCCESS;

}

hi_s32 HisiBase::vpss_chn_dump_get_frame(hi_vpss_grp grp, hi_vpss_chn chn, hi_u32 frame_cnt){

    hi_u32 depth = 2;
    hi_vpss_chn_attr chn_attr;
    hi_vpss_ext_chn_attr ext_chn_attr;
    hi_s32 ret;
    hi_u32 cnt = frame_cnt;
    const hi_s32 milli_sec = GET_CHN_FRAME_TIMEOUT;
    hi_u32 orig_depth = 0;
    hi_vpss_chn_mode orig_chn_mode = HI_VPSS_CHN_MODE_AUTO;
    hi_video_frame_info frame;
    hi_char yuv_name[FILE_NAME_LENGTH];
    FILE *fd = HI_NULL;
    // hi_char *g_user_page_addr[2] = { HI_NULL, HI_NULL }; /* 2 Y and C */

    ret = hi_mpi_vpss_get_chn_attr(grp, chn, &chn_attr);
    if (ret != HI_SUCCESS) {
        printf("get chn attr error!!!\n");
        return HI_FAILURE;
    }

    orig_depth = chn_attr.depth;
    orig_chn_mode = chn_attr.chn_mode;
    chn_attr.depth = depth;
    chn_attr.chn_mode = HI_VPSS_CHN_MODE_USER;

    if (hi_mpi_vpss_set_chn_attr(grp, chn, &chn_attr) != HI_SUCCESS) {
        printf("set chn attr error!!!\n");
        // goto exit;
        return HI_FAILURE;
    }

    // g_vpss_depth_flag = 1;

    if (memset_s(&frame, sizeof(hi_video_frame_info), 0, sizeof(hi_video_frame_info)) != EOK) {
        printf("memset_s frame error!!!\n");
        // goto exit;
        return HI_FAILURE;
    }

    ret = vpss_chn_dump_make_yuv_file_name(grp, chn, frame_cnt, fd, yuv_name);
    if(ret != HI_SUCCESS){
        printf("make file fail \n");
        return HI_FAILURE;
    }

    /* get frame */
    while (cnt--) {

        if (hi_mpi_vpss_get_chn_frame(grp, chn, &frame, milli_sec) != HI_SUCCESS) {
            printf("Get frame fail \n");
            usleep(1000); /* 1000 sleep */
            continue;
        }

        if (HI_DYNAMIC_RANGE_SDR8 == frame.video_frame.dynamic_range) {
            yuv_8bit_dump(&frame.video_frame, fd, yuv_name);
        } else {
            printf("Only support dump 8-bit data!\n");
        }
        

        printf("Get frame %d!!\n", cnt);
        /* release frame after using */
        ret = hi_mpi_vpss_release_chn_frame(grp, chn, &frame);
        if (ret != HI_SUCCESS) {
            printf("Release frame error ,now exit !!!\n");
            return ret;
        }
        frame.pool_id = HI_VB_INVALID_POOL_ID;
    }
    return HI_SUCCESS;
}



hi_void HisiBase::yuv_8bit_dump(const hi_video_frame *frame, FILE *fd, hi_char* yuv_name)
{
    char *virt_addr_y = HI_NULL;
    char *virt_addr_c = HI_NULL;
    char *mem_content = HI_NULL;
    hi_u32 g_size = 0;
    hi_u32 g_c_size = 0;
    hi_phys_addr_t phys_addr;
    hi_pixel_format pixel_format = frame->pixel_format;
    hi_char *g_user_page_addr[2] = { HI_NULL, HI_NULL };    /* 2 Y and C */

    /* When the storage format is a planar format, this variable is used to keep the height of the UV component */
    hi_u32 uv_height = 0;
    hi_bool is_uv_invert = (pixel_format == HI_PIXEL_FORMAT_YUV_SEMIPLANAR_420 ||
        pixel_format == HI_PIXEL_FORMAT_YUV_SEMIPLANAR_422) ? HI_TRUE : HI_FALSE;

    g_size = (frame->stride[0]) * (frame->height);
    if (pixel_format == HI_PIXEL_FORMAT_YVU_SEMIPLANAR_420 || pixel_format == HI_PIXEL_FORMAT_YUV_SEMIPLANAR_420) {
        g_c_size = (frame->stride[1]) * (frame->height) / 2;    /* 2 uv height */
        uv_height = frame->height / 2;  /* 2 uv height */
    } else if (pixel_format == HI_PIXEL_FORMAT_YVU_SEMIPLANAR_422 ||
        pixel_format == HI_PIXEL_FORMAT_YUV_SEMIPLANAR_422) {
        g_c_size = (frame->stride[1]) * (frame->height);
        uv_height = frame->height;
    } else if (pixel_format == HI_PIXEL_FORMAT_YUV_400) {
        g_c_size = 0;
        uv_height = frame->height;
    }

    phys_addr = frame->phys_addr[0];
    g_user_page_addr[0] = (hi_char *)hi_mpi_sys_mmap(phys_addr, g_size);
    if (g_user_page_addr[0] == HI_NULL) {
        printf("vy =  null \n");
    }

    virt_addr_y = g_user_page_addr[0];

    
    /* save Y */
    fprintf(stderr, "saving......Y......");
    fflush(stderr);

    /* open file */
    fd = fopen(yuv_name, "wb");
    if (fd == HI_NULL) {
        printf("open file failed, errno %d!\n", errno);
    }

    for (hi_s32 h = 0; h < frame->height; h++) {
        mem_content = virt_addr_y + h * frame->stride[0];

        fwrite(mem_content, frame->width, 1, fd);
    }
    printf("save y ok \n");
    fflush(fd);
    if (pixel_format != HI_PIXEL_FORMAT_YUV_400) {
        unsigned char tmp_buf[MAX_FRM_WIDTH];
        mem_content = HI_NULL;
        virt_addr_c = HI_NULL;
        hi_u32 w, h;

        phys_addr = frame->phys_addr[1];
        g_user_page_addr[1] = (hi_char *)hi_mpi_sys_mmap(phys_addr, g_c_size);
        if (g_user_page_addr[1] == HI_NULL) {
            printf("mmap chroma data error!!!\n");
            return;
        }
        virt_addr_c = g_user_page_addr[1];

        fflush(fd);
        /* save U */
        fprintf(stderr, "U......");
        fflush(stderr);
        for (h = 0; h < uv_height; h++) {
            mem_content = virt_addr_c + h * frame->stride[1];
            if (!is_uv_invert) {
                mem_content += 1;
            }

            for (w = 0; w < frame->width / 2; w++) { /* 2 chroma width */
                tmp_buf[w] = *mem_content;
                mem_content += 2; /* 2 semiplanar steps */
            }

            fwrite(tmp_buf, frame->width / 2, 1, fd); /* 2 chroma width */
        }
        fflush(fd);

        /* save V */
        fprintf(stderr, "V......");
        fflush(stderr);
        for (h = 0; h < uv_height; h++) {
            mem_content = virt_addr_c + h * frame->stride[1];
            if (is_uv_invert) {
                mem_content += 1;
            }

            for (w = 0; w < frame->width / 2; w++) { /* 2 chroma width */
                tmp_buf[w] = *mem_content;
                mem_content += 2; /* 2 semiplanar steps */
            }

            fwrite(tmp_buf, frame->width / 2, 1, fd); /* 2 chroma width */
        }

        fflush(fd);
        if (g_user_page_addr[1] != HI_NULL) {
            hi_mpi_sys_munmap(g_user_page_addr[1], g_c_size);
            g_user_page_addr[1] = HI_NULL;
        }
    }

    fprintf(stderr, "done %d!\n", frame->time_ref);
    fflush(stderr);
    hi_mpi_sys_munmap(g_user_page_addr[0], g_size);
    g_user_page_addr[0] = NULL;

}