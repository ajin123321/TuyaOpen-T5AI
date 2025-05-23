// Copyright 2022-2023 Beken
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "FreeRTOS.h"
#include "task.h"
#include "audio_pipeline.h"
#include "audio_mem.h"
#include "mp3_decoder.h"
#include <os/os.h>
#include "ff.h"
#include "diskio.h"
#include "fatfs_stream.h"


#define TAG  "MP3_DECODER_TEST"

#define TEST_FATFS_READER  "1:/single.mp3"
#define TEST_FATFS_WRITER  "1:/single.pcm"

#define TEST_CHECK_NULL(ptr) do {\
		if (ptr == NULL) {\
			BK_LOGI(TAG, "TEST_CHECK_NULL fail \n");\
			return BK_FAIL;\
		}\
	} while(0)


static FATFS *pfs = NULL;

static bk_err_t tf_mount(void)
{
	FRESULT fr;

	if (pfs != NULL)
	{
		os_free(pfs);
	}

	pfs = os_malloc(sizeof(FATFS));
	if(NULL == pfs)
	{
		BK_LOGI(TAG, "f_mount malloc failed!\r\n");
		return BK_FAIL;
	}

	fr = f_mount(pfs, "1:", 1);
	if (fr != FR_OK)
	{
		BK_LOGE(TAG, "f_mount failed:%d\r\n", fr);
		return BK_FAIL;
	}
	else
	{
		BK_LOGI(TAG, "f_mount OK!\r\n");
	}

	return BK_OK;
}

static bk_err_t tf_unmount(void)
{
	FRESULT fr;
	fr = f_unmount(DISK_NUMBER_SDIO_SD, "1:", 1);
	if (fr != FR_OK)
	{
		BK_LOGE(TAG, "f_unmount failed:%d\r\n", fr);
		return BK_FAIL;
	}
	else
	{
		BK_LOGI(TAG, "f_unmount OK!\r\n");
	}

	if (pfs)
	{
		os_free(pfs);
		pfs = NULL;
	}

	return BK_OK;
}


/* The "mp3-decoder" element is neither a producer nor a consumer when test element
   is neither first element nor last element of the pipeline. Usually this element has
   both src and sink. The data flow model of this element is as follow:
   +--------------+               +--------------+               +--------------+
   |    fatfs     |               |     mp3      |               |     fatfs    |
   |  stream[IN]  |               |   decoder    |               |  stream[OUT] |
  ...            src - ringbuf - sink           src - ringbuf - sink           ...
   |              |               |              |               |              |
   +--------------+               +--------------+               +--------------+

   Function: Use mp3 decoder to decode mp3 file to pcm file in tf card.

   The "fatfs-stream[IN]" element read mp3 file from tfcard to ringbuffer. The 
   "mp3-decoder" element read audio data from ringbuffer, decode the data to pcm format
   and write the data to ringbuffer. The "fatfs-stream[OUT]" element read pcmd data from
   ringbuffer, and save to tfcard.
*/
bk_err_t asdf_mp3_decoder_test_case_0(void)
{
	audio_pipeline_handle_t pipeline;
	audio_element_handle_t mp3_dec, mp3_in, pcm_out;

	bk_set_printf_sync(true);
#if 0
		extern void bk_enable_white_list(int enabled);
		bk_enable_white_list(1);
		bk_disable_mod_printf("AUDIO_PIPELINE", 0);
		bk_disable_mod_printf("AUDIO_ELEMENT", 0);
		bk_disable_mod_printf("AUDIO_EVENT", 0);
//		bk_disable_mod_printf("AUDIO_MEM", 0);
//		bk_disable_mod_printf("MP3_DECODER", 0);
		bk_disable_mod_printf("FATFS_STREAM", 0);
		bk_disable_mod_printf("MP3_DECODER_TEST", 0);
#endif
	BK_LOGI(TAG, "--------- %s ----------\n", __func__);
	AUDIO_MEM_SHOW("start \n");

	if (BK_OK != tf_mount()) {
		BK_LOGE(TAG, "mount tfcard fail, %d \n", __LINE__);
		return BK_FAIL;
	}

	BK_LOGI(TAG, "--------- step1: pipeline init ----------\n");
	audio_pipeline_cfg_t pipeline_cfg = DEFAULT_AUDIO_PIPELINE_CONFIG();
	pipeline = audio_pipeline_init(&pipeline_cfg);
	TEST_CHECK_NULL(pipeline);

	BK_LOGI(TAG, "--------- step2: init elements ----------\n");
    fatfs_stream_cfg_t fatfs_reader_cfg = FATFS_STREAM_CFG_DEFAULT();
	fatfs_reader_cfg.buf_sz = MP3_DECODER_MAIN_BUFF_SIZE;
	fatfs_reader_cfg.out_rb_size = MP3_DECODER_MAIN_BUFF_SIZE;
    fatfs_reader_cfg.type = AUDIO_STREAM_READER;
    mp3_in = fatfs_stream_init(&fatfs_reader_cfg);
    TEST_CHECK_NULL(mp3_in);

    fatfs_stream_cfg_t fatfs_writer_cfg = FATFS_STREAM_CFG_DEFAULT();
    fatfs_writer_cfg.type = AUDIO_STREAM_WRITER;
    pcm_out = fatfs_stream_init(&fatfs_writer_cfg);
    TEST_CHECK_NULL(pcm_out);

    if (BK_OK != audio_element_set_uri(mp3_in, TEST_FATFS_READER)) {
		BK_LOGE(TAG, "set uri fail, %d \n", __LINE__);
		return BK_FAIL;
	}

    if (BK_OK != audio_element_set_uri(pcm_out, TEST_FATFS_WRITER)) {
		BK_LOGE(TAG, "set uri fail, %d \n", __LINE__);
		return BK_FAIL;
	}

	mp3_decoder_cfg_t mp3_decoder_cfg = DEFAULT_MP3_DECODER_CONFIG();
	mp3_dec = mp3_decoder_init(&mp3_decoder_cfg);
	TEST_CHECK_NULL(mp3_dec);

	BK_LOGI(TAG, "--------- step3: pipeline register ----------\n");
	if (BK_OK != audio_pipeline_register(pipeline, mp3_in, "stream_in")) {
		BK_LOGE(TAG, "register element fail, %d \n", __LINE__);
		return BK_FAIL;
	}
	if (BK_OK != audio_pipeline_register(pipeline, mp3_dec, "mp3_dec")) {
		BK_LOGE(TAG, "register element fail, %d \n", __LINE__);
		return BK_FAIL;
	}
	if (BK_OK != audio_pipeline_register(pipeline, pcm_out, "stream_out")) {
		BK_LOGE(TAG, "register element fail, %d \n", __LINE__);
		return BK_FAIL;
	}

	BK_LOGI(TAG, "--------- step4: pipeline link ----------\n");
	if (BK_OK != audio_pipeline_link(pipeline, (const char *[]) {"stream_in", "mp3_dec", "stream_out"}, 3)) {
		BK_LOGE(TAG, "pipeline link fail, %d \n", __LINE__);
		return BK_FAIL;
	}

	BK_LOGI(TAG, "--------- step5: init event listener ----------\n");
	audio_event_iface_cfg_t evt_cfg = AUDIO_EVENT_IFACE_DEFAULT_CFG();
	audio_event_iface_handle_t evt = audio_event_iface_init(&evt_cfg);

	if (BK_OK != audio_pipeline_set_listener(pipeline, evt)) {
		BK_LOGE(TAG, "set uri fail, %d \n", __LINE__);
		return BK_FAIL;
	}

	BK_LOGI(TAG, "--------- step6: pipeline run ----------\n");
	if (BK_OK != audio_pipeline_run(pipeline)) {
		BK_LOGE(TAG, "pipeline run fail, %d \n", __LINE__);
		return BK_FAIL;
	}

	while (1) {
		audio_event_iface_msg_t msg;
		bk_err_t ret = audio_event_iface_listen(evt, &msg, portMAX_DELAY);
		if (ret != BK_OK) {
			BK_LOGE(TAG, "[ * ] Event interface error : %d \n", ret);
			continue;
		}

		if (msg.source_type == AUDIO_ELEMENT_TYPE_ELEMENT && msg.source == (void *) mp3_dec
			&& msg.cmd == AEL_MSG_CMD_REPORT_MUSIC_INFO) {
			audio_element_info_t music_info = {0};
			audio_element_getinfo(mp3_dec, &music_info);
			BK_LOGI(TAG, "[ * ] Receive music info from mp3 decoder, sample_rates=%d, bits=%d, ch=%d",
						music_info.sample_rates, music_info.bits, music_info.channels);
			continue;
		}

		if (msg.source_type == AUDIO_ELEMENT_TYPE_ELEMENT
			&& msg.cmd == AEL_MSG_CMD_REPORT_STATUS
			&& (((int)msg.data == AEL_STATUS_STATE_STOPPED)
			|| ((int)msg.data == AEL_STATUS_STATE_FINISHED)
			|| (int)msg.data == AEL_STATUS_ERROR_PROCESS)) {
			BK_LOGW(TAG, "[ * ] Stop event received \n");
			break;
		}
	}

	BK_LOGI(TAG, "--------- step7: deinit pipeline ----------\n");
	if (BK_OK != audio_pipeline_stop(pipeline)) {
		BK_LOGE(TAG, "pipeline stop fail, %d \n", __LINE__);
		return BK_FAIL;
	}
	if (BK_OK != audio_pipeline_wait_for_stop(pipeline)) {
		BK_LOGE(TAG, "pipeline wait stop fail, %d \n", __LINE__);
		return BK_FAIL;
	}

	if (BK_OK != audio_pipeline_terminate(pipeline)) {
		BK_LOGE(TAG, "pipeline terminate fail, %d \n", __LINE__);
		return BK_FAIL;
	}
	if (BK_OK != audio_pipeline_unregister(pipeline, mp3_in)) {
		BK_LOGE(TAG, "pipeline terminate fail, %d \n", __LINE__);
		return BK_FAIL;
	}
	if (BK_OK != audio_pipeline_unregister(pipeline, mp3_dec)) {
		BK_LOGE(TAG, "pipeline terminate fail, %d \n", __LINE__);
		return BK_FAIL;
	}
	if (BK_OK != audio_pipeline_unregister(pipeline, pcm_out)) {
		BK_LOGE(TAG, "pipeline terminate fail, %d \n", __LINE__);
		return BK_FAIL;
	}

	if (BK_OK != audio_pipeline_remove_listener(pipeline)) {
		BK_LOGE(TAG, "pipeline terminate fail, %d \n", __LINE__);
		return BK_FAIL;
	}

	if (BK_OK != audio_event_iface_destroy(evt)) {
		BK_LOGE(TAG, "pipeline terminate fail, %d \n", __LINE__);
		return BK_FAIL;
	}

	if (BK_OK != audio_pipeline_deinit(pipeline)) {
		BK_LOGE(TAG, "pipeline terminate fail, %d \n", __LINE__);
		return BK_FAIL;
	}

	if (BK_OK != audio_element_deinit(mp3_in)) {
		BK_LOGE(TAG, "element deinit fail, %d \n", __LINE__);
		return BK_FAIL;
	}

	if (BK_OK != audio_element_deinit(mp3_dec)) {
		BK_LOGE(TAG, "element deinit fail, %d \n", __LINE__);
		return BK_FAIL;
	}

	if (BK_OK != audio_element_deinit(pcm_out)) {
		BK_LOGE(TAG, "element deinit fail, %d \n", __LINE__);
		return BK_FAIL;
	}

	tf_unmount();

	BK_LOGI(TAG, "--------- mp3 decoder test complete ----------\n");
	AUDIO_MEM_SHOW("end \n");

	return BK_OK;
}

