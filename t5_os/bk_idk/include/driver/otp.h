// Copyright 2020-2021 Beken
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

#pragma once

#include <common/bk_include.h>
#include <driver/otp_types.h>

#ifdef __cplusplus
extern "C" {
#endif


/* @brief Overview about this API header
 *
 */

/* @brief     OTP initialization
 *
 * @return
 *    - BK_OK: succeed
 *    - others: other errors.
 */
bk_err_t bk_otp_init(void);

/**
 * @brief     OTP finalization
 *
 * @return
 *    - BK_OK: succeed
 *    - others: other errors.
 */
bk_err_t bk_otp_deinit(void);
/**
 * @brief OTP API
 * @defgroup bk_api_otp OTP API group
 * @{
 */
 
/**
 * @brief     OTP read operation
 *
 * @param buffer point to the buffer that reads the data
 * @param addr read address, address range 0x0--0x800
 * @param len read length
 *
 * @attention 1. addr+len should be less than 0x800
 * @attention 2. this API can only access non-secure OTP bank
 * @attention 3. this api blocks for 5ms waiting for OTP to stabilize
 *
 * @return
 *    - BK_OK: succeed
 *    - BK_ERR_EFUSE_DRIVER_NOT_INIT: EFUSE driver not init
 *    - BK_ERR_EFUSE_ADDR_OUT_OF_RANGE: EFUSE address is out of range
 *    - others: other errors.
 */
bk_err_t bk_otp_read_bytes_nonsecure(uint8_t *buffer, uint32_t addr, uint32_t len);
/**
 * @brief     OTP read with item type
 *
 * @param item the item to read
 * @param buf point to the buffer that reads the data
 * @param size length of item to read
 *
 * @return
 *    - BK_OK: succeed
 *    - BK_ERR_NO_READ_PERMISSION: wrong permission to read
 *    - BK_ERR_OTP_ADDR_OUT_OF_RANGE: param size not match item real size
 *    - others: other errors.
 */
bk_err_t bk_otp_apb_read(otp_id_t item, uint8_t *buf, uint32_t size);

/**
 * @brief     update OTP write with item type
 *
 * @param item the item to update
 * @param buf point to the buffer that updates the data
 * @param size length of buffer to update
 *
 * @return
 *    - >0: succeed and return length of buffer wroten
 *    - BK_ERR_NO_WRITE_PERMISSION: wrong permission to write
 *    - BK_ERR_OTP_ADDR_OUT_OF_RANGE: param size exceeds item size
 *    - BK_ERR_OTP_UPDATE_NOT_EQUAL: updated value not match expectation 
 *    - others: other errors.
 */
bk_err_t bk_otp_apb_update(otp_id_t item, uint8_t* buf, uint32_t size);

/**
 * @brief OTP init operation
 *
 * @return
 *    - BK_OK: succeed
 *    - others: other errors.
 */
bk_err_t bk_otp_init(void);

/**
 * @brief OTP deinit operation
 *
 * @return
 *    - BK_OK: succeed
 *    - others: other errors.
 */
bk_err_t bk_otp_deinit(void);

/**
 * @brief     OTP2 read with item type
 *
 * @param item the item to read
 * @param buf point to the buffer that reads the data
 * @param size length of item to read
 *
 * @return
 *    - BK_OK: succeed
 *    - BK_ERR_NO_READ_PERMISSION: wrong permission to read
 *    - BK_ERR_OTP_ADDR_OUT_OF_RANGE: param size not match item real size
 *    - others: other errors.
 */
bk_err_t bk_otp_ahb_read(otp_id_t item, uint8_t* buf, uint32_t size);
/**
 * @brief     update OTP2 write with item type
 *
 * @param item the item to update
 * @param buf point to the buffer that updates the data
 * @param size length of buffer to update
 *
 * @return
 *    - BK_OK: succeed
 *    - BK_ERR_NO_WRITE_PERMISSION: wrong permission to write
 *    - BK_ERR_OTP_ADDR_OUT_OF_RANGE: param size exceeds item size
 *    - BK_ERR_OTP_UPDATE_NOT_EQUAL: updated value not match expectation
 *    - others: other errors.
 */
bk_err_t bk_otp_ahb_update(otp_id_t item, uint8_t* buf, uint32_t size);
/**
 * @}
 */
/**
 * @}
 */

#ifdef __cplusplus
}
#endif


