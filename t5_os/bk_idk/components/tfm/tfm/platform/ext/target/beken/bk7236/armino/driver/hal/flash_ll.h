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

#include <soc/soc.h>
#include "hal_port.h"
#include "flash_hw.h"
#include <driver/hal/hal_flash_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FLASH_LL_REG_BASE(_flash_unit_id)    (SOC_FLASH_REG_BASE)

static inline void flash_ll_soft_reset(flash_hw_t *hw)
{
	hw->global_ctrl.soft_reset = 1;
}

static inline void flash_ll_init(flash_hw_t *hw)
{
	flash_ll_soft_reset(hw);
}

static inline bool flash_ll_is_busy(flash_hw_t *hw)
{
	return hw->op_ctrl.busy_sw;
}

static inline void flash_ll_wait_op_done(flash_hw_t *hw)
{
	while (flash_ll_is_busy(hw));
}

static inline uint32_t flash_ll_read_flash_id(flash_hw_t *hw)
{
	return hw->rd_flash_id;
}

static inline void flash_ll_set_op_cmd(flash_hw_t *hw, flash_op_cmd_t cmd)
{
	hw->op_cmd.op_type_sw = cmd;
	hw->op_ctrl.op_sw = 1;
	hw->op_ctrl.wp_value = 1;
}

static inline uint32_t flash_ll_get_id(flash_hw_t *hw)
{
	flash_ll_set_op_cmd(hw, FLASH_OP_CMD_RDID);
	while (flash_ll_is_busy(hw));
	return flash_ll_read_flash_id(hw);
}

static inline uint32_t flash_ll_get_mid(flash_hw_t *hw)
{
	while (flash_ll_is_busy(hw));
	hw->op_cmd.op_type_sw = FLASH_OP_CMD_RDID;
	hw->op_ctrl.op_sw = 1;
	while (flash_ll_is_busy(hw));
	return flash_ll_read_flash_id(hw);
}

static inline void flash_ll_init_wrsr_cmd(flash_hw_t *hw, uint8_t wrsr_cmd)
{
	hw->cmd_cfg.wrsr_cmd_reg = wrsr_cmd;
	hw->cmd_cfg.wrsr_cmd_sel = 1;
	flash_ll_wait_op_done(hw);
}

static inline void flash_ll_init_rdsr_cmd(flash_hw_t *hw, uint8_t rdsr_cmd)
{
	hw->cmd_cfg.rdsr_cmd_reg = rdsr_cmd;
	hw->cmd_cfg.rdsr_cmd_sel = 1;
	flash_ll_wait_op_done(hw);
}

static inline void flash_ll_deinit_wrsr_cmd(flash_hw_t *hw)
{
	hw->cmd_cfg.wrsr_cmd_reg = 0x1;
	hw->cmd_cfg.wrsr_cmd_sel = 0;
	flash_ll_wait_op_done(hw);
}

static inline void flash_ll_deinit_rdsr_cmd(flash_hw_t *hw)
{
	hw->cmd_cfg.rdsr_cmd_reg = 0x5;
	hw->cmd_cfg.rdsr_cmd_sel = 0;
	flash_ll_wait_op_done(hw);
}


static inline void flash_ll_write_status_reg(flash_hw_t *hw, uint8_t sr_width, uint32_t sr_data)
{

		while (flash_ll_is_busy(hw));
		hw->config.wrsr_data = sr_data;
		while (flash_ll_is_busy(hw));
		if (sr_width == 1) {
			flash_ll_set_op_cmd(hw, FLASH_OP_CMD_WRSR);
		} else if (sr_width == 2) {
			if(FLASH_ID_GD25Q32C == flash_ll_get_id(hw)) {
				flash_ll_set_op_cmd(hw, FLASH_OP_CMD_WRSR);
				flash_ll_wait_op_done(hw);

				hw->config.wrsr_data = (sr_data >> LEN_WRSR_S0_S7);
				flash_ll_wait_op_done(hw);

				flash_ll_init_wrsr_cmd(hw, CMD_WRSR_S8_S15);
				flash_ll_wait_op_done(hw);

				flash_ll_set_op_cmd(hw, FLASH_OP_CMD_WRSR);
				flash_ll_wait_op_done(hw);

				flash_ll_deinit_wrsr_cmd(hw);
			} else {
				flash_ll_set_op_cmd(hw, FLASH_OP_CMD_WRSR2);
			}

		}

	while (flash_ll_is_busy(hw));
}

static inline void flash_ll_set_qe(flash_hw_t *hw, uint8_t qe_bit, uint8_t qe_bit_post)
{
	hw->config.v |= qe_bit << qe_bit_post;
}

static inline uint32_t flash_ll_read_status_reg(flash_hw_t *hw, uint8_t sr_width)
{
	uint32_t state_reg_data = 0;

	hw->cmd_cfg.v = 0;
	while (flash_ll_is_busy(hw));
	flash_ll_set_op_cmd(hw, FLASH_OP_CMD_RDSR);
	while (flash_ll_is_busy(hw));
	state_reg_data = hw->state.status_reg;

	if (sr_width ==1) return state_reg_data;

	flash_ll_set_op_cmd(hw, FLASH_OP_CMD_RDSR2);
	while (flash_ll_is_busy(hw));
	state_reg_data |= hw->state.status_reg << 8;

	if (sr_width ==2) return state_reg_data;

	hw->cmd_cfg.rdsr_cmd_sel = 1;
	hw->cmd_cfg.rdsr_cmd_reg = 0x15;
	flash_ll_set_op_cmd(hw, FLASH_OP_CMD_RDSR);
	while (flash_ll_is_busy(hw));
	state_reg_data |= hw->state.status_reg << 16;
	hw->cmd_cfg.v = 0;

	return state_reg_data;
}

static inline uint32_t flash_ll_get_crc_err_num(flash_hw_t *hw)
{
	return (uint32_t)hw->state.crc_err_num;
}

static inline void flash_ll_enable_cpu_data_wr(flash_hw_t *hw)
{
	hw->config.cpu_data_wr_en = 1;
}

static inline void flash_ll_disable_cpu_data_wr(flash_hw_t *hw)
{
	hw->config.cpu_data_wr_en = 0;
}

static inline void flash_ll_clear_qwfr(flash_hw_t *hw)
{
	hw->config.mode_sel = 0;
	hw->op_cmd.addr_sw_reg = 0;
	flash_ll_set_op_cmd(hw, FLASH_OP_CMD_CRMR);
	while (flash_ll_is_busy(hw));
}

static inline void flash_ll_set_mode(flash_hw_t *hw, uint8_t mode_sel)
{
	hw->config.mode_sel = mode_sel;
}

static inline void flash_ll_set_dual_mode(flash_hw_t *hw)
{
	hw->config.mode_sel = FLASH_MODE_DUAL;
}

static inline void flash_ll_set_quad_m_value(flash_hw_t *hw, uint32_t m_value)
{
	hw->state.m_value = m_value;
}

static inline void flash_ll_erase_block(flash_hw_t *hw, uint32_t erase_addr, int type)
{
	while (flash_ll_is_busy(hw));
	hw->op_cmd.addr_sw_reg = erase_addr;
	hw->op_cmd.op_type_sw = type;
	hw->op_ctrl.op_sw = 1;
	while (flash_ll_is_busy(hw));
}

static inline void flash_ll_set_op_cmd_read(flash_hw_t *hw, uint32_t read_addr)
{
	hw->op_cmd.addr_sw_reg = read_addr;
	hw->op_cmd.op_type_sw = FLASH_OP_CMD_READ;
	hw->op_ctrl.op_sw = 1;
	while (flash_ll_is_busy(hw));
}

static inline uint32_t flash_ll_read_data(flash_hw_t *hw)
{
	return hw->data_flash_sw;
}

static inline void flash_ll_set_op_cmd_write(flash_hw_t *hw, uint32_t write_addr)
{
	hw->op_cmd.addr_sw_reg = write_addr;
	hw->op_cmd.op_type_sw = FLASH_OP_CMD_PP;
	hw->op_ctrl.op_sw = 1;
	while (flash_ll_is_busy(hw));
}

static inline void flash_ll_write_data(flash_hw_t *hw, uint32_t data)
{
	hw->data_sw_flash = data;
}

static inline void flash_ll_set_clk(flash_hw_t *hw, uint8_t clk_cfg)
{
	hw->config.clk_cfg = clk_cfg;

#if CONFIG_JTAG
	hw->config.crc_en = 0;
#endif
}

static inline void flash_ll_set_default_clk(flash_hw_t *hw)
{
	flash_ll_set_clk(hw, 0x5);
}

static inline void flash_ll_set_clk_dpll(flash_hw_t *hw)
{
	hw->config.clk_cfg = 5;
}

static inline void flash_ll_set_clk_dco(flash_hw_t *hw, bool ate_enabled)
{
	if (ate_enabled) {
		hw->config.clk_cfg = 0xB;
	} else {
		hw->config.clk_cfg = 0x9;
	}
}

static inline void flash_ll_write_enable(flash_hw_t *hw)
{
	flash_ll_set_op_cmd(hw, FLASH_OP_CMD_WREN);
	while (flash_ll_is_busy(hw));
}

static inline void flash_ll_write_disable(flash_hw_t *hw)
{
	flash_ll_set_op_cmd(hw, FLASH_OP_CMD_WRDI);
	while (flash_ll_is_busy(hw));
}

static inline void flash_ll_set_dbus_region(flash_hw_t *hw, uint32_t id, uint32_t start, uint32_t end, bool secure)
{
	hw->sec_addr[id].sec_addr_start.flash_sec_start_addr = start;
	hw->sec_addr[id].sec_addr_end.flash_sec_end_addr = end;
	if (secure) {
		hw->sec_addr[id].sec_addr_start.flash_sec_addr_sec = 0;
	} else {
		hw->sec_addr[id].sec_addr_start.flash_sec_addr_sec = 1;
	}
	hw->sec_addr[id].sec_addr_start.flash_sec_addr_en = 1;
}

static inline void flash_ll_set_offset_begin(flash_hw_t *hw, uint32_t value)
{
	hw->offset_addr_begin = value;
}

static inline void flash_ll_set_offset_end(flash_hw_t *hw, uint32_t value)
{
	hw->offset_addr_end = value;
}

static inline void flash_ll_set_addr_offset(flash_hw_t *hw, uint32_t value)
{
	hw->flash_addr_offset = value;
}

static inline void flash_ll_set_offset_enable(flash_hw_t *hw, bool value)
{
	hw->flash_ctrl.flash_offset_enable = value;
}

static inline uint32_t flash_ll_read_offset_enable(flash_hw_t *hw)
{
	return hw->flash_ctrl.flash_offset_enable & 0x1;
}

static inline void flash_ll_set_volatile_status_write(flash_hw_t *hw)
{
	hw->cmd_cfg.wrsr_cmd_reg = 0x50;
	hw->cmd_cfg.wrsr_cmd_sel = 0x1;
	flash_ll_set_op_cmd(hw, FLASH_OP_CMD_WRSR);
	while (flash_ll_is_busy(hw));
	hw->cmd_cfg.wrsr_cmd_reg = 0x0;
	hw->cmd_cfg.wrsr_cmd_sel = 0x0;
}

#ifdef __cplusplus
}
#endif


