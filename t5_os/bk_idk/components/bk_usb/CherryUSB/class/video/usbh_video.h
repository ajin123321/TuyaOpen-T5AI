/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_VIDEO_H
#define USBH_VIDEO_H

#include "usb_video.h"
#include "usb_hc.h"

#define USBH_VIDEO_FORMAT_UNCOMPRESSED 0
#define USBH_VIDEO_FORMAT_MJPEG        1
#define USBH_VIDEO_FORMAT_H264         2
#define USBH_VIDEO_FORMAT_H265         3

#define USBH_VIDEO_FORMAT_MAX_NUM         3
#define USBH_VIDEO_FRAME_MAX_NUM          8

struct usbh_video_resolution {
    uint16_t wWidth;
    uint16_t wHeight;
    uint16_t frame_index;
    uint16_t fps_num;
    uint32_t *fps;

};

struct usbh_video_format {
    struct usbh_video_resolution frame[USBH_VIDEO_FRAME_MAX_NUM];
    uint8_t format_type;
    uint8_t num_of_frames;
};

struct usbh_videostreaming {
    uint8_t *bufbase;
    uint32_t bufoffset;
    void (*video_one_frame_callback)(struct usbh_videostreaming *stream);
};

struct usbh_video {
    uint32_t idx_uvc;
    struct usbh_hubport *hport;

    uint8_t ctrl_intf; /* interface number */
    uint8_t data_intf; /* interface number */
    uint8_t minor;
    usbh_pipe_t isoin;  /* ISO IN endpoint */
    usbh_pipe_t isoout; /* ISO OUT endpoint */
    struct video_probe_and_commit_controls probe;
    struct video_probe_and_commit_controls commit;
    uint16_t isoin_mps;
    uint16_t isoout_mps;
    bool is_opened;
    uint16_t bcdVDC;
    uint8_t num_of_intf_altsettings;
    uint8_t num_of_formats;
    struct usbh_video_format format[USBH_VIDEO_FORMAT_MAX_NUM];
};

#ifdef __cplusplus
extern "C" {
#endif

int usbh_video_get_cur(struct usbh_video *video_class, uint8_t intf, uint8_t entity_id, uint8_t cs, uint8_t *buf, uint16_t len);
int usbh_video_set_cur(struct usbh_video *video_class, uint8_t intf, uint8_t entity_id, uint8_t cs, uint8_t *buf, uint16_t len);
int usbh_videostreaming_get_cur_probe(struct usbh_video *video_class);
int usbh_videostreaming_set_cur_probe(struct usbh_video *video_class, uint8_t formatindex, uint8_t frameindex, uint32_t dwMaxVideoFrameSize, uint32_t dwMaxPayloadTransferSize);
int usbh_videostreaming_set_cur_commit(struct usbh_video *video_class, uint8_t formatindex, uint8_t frameindex, uint32_t dwMaxVideoFrameSize, uint32_t dwMaxPayloadTransferSize);

int usbh_video_open(struct usbh_video *video_class, uint8_t altsetting);
int usbh_video_close(struct usbh_video *video_class);

void usbh_video_list_info(struct usbh_video *video_class);

void usbh_videostreaming_parse_mjpeg(struct usbh_urb *urb, struct usbh_videostreaming *stream);
void usbh_videostreaming_parse_yuyv2rgb565(struct usbh_urb *urb, struct usbh_videostreaming *stream);

void bk_usbh_video_sw_init(struct usbh_hubport *hport, uint8_t interface_num, uint8_t interface_sub_class);
void bk_usbh_video_sw_deinit( struct usbh_hubport *hport, uint8_t interface_num, uint8_t interface_sub_class);

void bk_usbh_video_unregister_dev(void);

#ifdef __cplusplus
}
#endif

#endif /* USBH_VIDEO_H */
