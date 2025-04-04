/*************************************************************
 * @file        driver_uart0.h
 * @brief       Header file of driver_uart0.c
 * @author      GuWenFu
 * @version     V1.0
 * @date        2016-09-29
 * @par
 * @attention
 *
 * @history     2016-09-29 gwf    create this file
 */

#ifndef __DRIVER_UART0_H__

#define __DRIVER_UART0_H__


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


//#include "BK_System.h"
#include "types.h"


#define REG_UART0_BASE_ADDR                 (0x44820000UL)

#define REG_UART0_GBL_CONTROL				(REG_UART0_BASE_ADDR + 0x2 * 4)
#define REG_UART0_SOFT_RESET_ENABLE         (*((volatile unsigned long *) REG_UART0_GBL_CONTROL))
#define REG_UART0_SOFT_RESET_POSI			0
#define REG_UART0_SOFT_RESET_MASK 			(0x01UL << REG_UART0_SOFT_RESET_POSI)

#define REG_UART0_CONFIG_ADDR               (REG_UART0_BASE_ADDR + 4 * 4)
#define REG_UART0_CONFIG_MASK               0x001FFFFF
#define REG_UART0_CONFIG                    (*((volatile unsigned long *) REG_UART0_CONFIG_ADDR))

#define UART0_CONFIG_TX_ENABLE_POSI         0
#define UART0_CONFIG_TX_ENABLE_MASK         (0x01UL << UART0_CONFIG_TX_ENABLE_POSI)
#define UART0_CONFIG_TX_ENABLE_CLEAR        (0x00UL << UART0_CONFIG_TX_ENABLE_POSI)
#define UART0_CONFIG_TX_ENABLE_SET          (0x01UL << UART0_CONFIG_TX_ENABLE_POSI)

#define UART0_CONFIG_RX_ENABLE_POSI         1
#define UART0_CONFIG_RX_ENABLE_MASK         (0x01UL << UART0_CONFIG_RX_ENABLE_POSI)
#define UART0_CONFIG_RX_ENABLE_CLEAR        (0x00UL << UART0_CONFIG_RX_ENABLE_POSI)
#define UART0_CONFIG_RX_ENABLE_SET          (0x01UL << UART0_CONFIG_RX_ENABLE_POSI)

#define UART0_CONFIG_IRDA_MODE_POSI         2
#define UART0_CONFIG_IRDA_MODE_MASK         (0x01UL << UART0_CONFIG_IRDA_MODE_POSI)
#define UART0_CONFIG_IRDA_MODE_CLEAR        (0x00UL << UART0_CONFIG_IRDA_MODE_POSI)
#define UART0_CONFIG_IRDA_MODE_SET          (0x01UL << UART0_CONFIG_IRDA_MODE_POSI)

#define UART0_CONFIG_LENGTH_POSI            3
#define UART0_CONFIG_LENGTH_MASK            (0x03UL << UART0_CONFIG_LENGTH_POSI)
#define UART0_CONFIG_LENGTH_5_BIT           (0x00UL << UART0_CONFIG_LENGTH_POSI)
#define UART0_CONFIG_LENGTH_6_BIT           (0x01UL << UART0_CONFIG_LENGTH_POSI)
#define UART0_CONFIG_LENGTH_7_BIT           (0x02UL << UART0_CONFIG_LENGTH_POSI)
#define UART0_CONFIG_LENGTH_8_BIT           (0x03UL << UART0_CONFIG_LENGTH_POSI)

#define UART0_CONFIG_PAR_ENABLE_POSI        5
#define UART0_CONFIG_PAR_ENABLE_MASK        (0x01UL << UART0_CONFIG_PAR_ENABLE_POSI)
#define UART0_CONFIG_PAR_ENABLE_CLEAR       (0x00UL << UART0_CONFIG_PAR_ENABLE_POSI)
#define UART0_CONFIG_PAR_ENABLE_SET         (0x01UL << UART0_CONFIG_PAR_ENABLE_POSI)

#define UART0_CONFIG_PAR_MODE_POSI          6
#define UART0_CONFIG_PAR_MODE_MASK          (0x01UL << UART0_CONFIG_PAR_MODE_POSI)
#define UART0_CONFIG_PAR_MODE_EVEN          (0x00UL << UART0_CONFIG_PAR_MODE_POSI)
#define UART0_CONFIG_PAR_MODE_ODD           (0x01UL << UART0_CONFIG_PAR_MODE_POSI)

#define UART0_CONFIG_STOP_LEN_POSI          7
#define UART0_CONFIG_STOP_LEN_MASK          (0x01UL << UART0_CONFIG_STOP_LEN_POSI)
#define UART0_CONFIG_STOP_LEN_1_BIT         (0x00UL << UART0_CONFIG_STOP_LEN_POSI)
#define UART0_CONFIG_STOP_LEN_2_BIT         (0x01UL << UART0_CONFIG_STOP_LEN_POSI)

#define UART0_CONFIG_CLK_DIVID_POSI         8
#define UART0_CONFIG_CLK_DIVID_MASK         (0x1FFFUL << UART0_CONFIG_CLK_DIVID_POSI)


#define REG_UART0_FIFO_CONFIG_ADDR          (REG_UART0_BASE_ADDR + 5 * 4)
#define REG_UART0_FIFO_CONFIG_MASK          0x0003FFFF
#define REG_UART0_FIFO_CONFIG               (*((volatile unsigned long *) REG_UART0_FIFO_CONFIG_ADDR))

#define UART0_FIFO_CONFIG_TX_THRESHOLD_POSI     0
#define UART0_FIFO_CONFIG_TX_THRESHOLD_MASK     (0x00FFUL << UART0_FIFO_CONFIG_TX_THRESHOLD_POSI)

#define UART0_FIFO_CONFIG_RX_THRESHOLD_POSI     8
#define UART0_FIFO_CONFIG_RX_THRESHOLD_MASK     (0x00FFUL << UART0_FIFO_CONFIG_RX_THRESHOLD_POSI)

#define UART0_FIFO_CONFIG_RX_STOP_TIME_POSI     16
#define UART0_FIFO_CONFIG_RX_STOP_TIME_MASK     (0x0003UL << UART0_FIFO_CONFIG_RX_STOP_TIME_POSI)


#define REG_UART0_FIFO_STATUS_ADDR              (REG_UART0_BASE_ADDR + 0x6 * 4)
#define REG_UART0_FIFO_STATUS_MASK              0x003FFFFF
#define REG_UART0_FIFO_STATUS                   (*((volatile unsigned long *) REG_UART0_FIFO_STATUS_ADDR))

#define UART0_FIFO_STATUS_TX_FIFO_CNT_POSI      0
#define UART0_FIFO_STATUS_TX_FIFO_CNT_MASK      (0x00FFUL << UART0_FIFO_STATUS_TX_FIFO_CNT_POSI)
#define UART0_FIFO_STATUS_TX_FIFO_CNT_GET       (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_TX_FIFO_CNT_MASK)

#define UART0_FIFO_STATUS_RX_FIFO_CNT_POSI      8
#define UART0_FIFO_STATUS_RX_FIFO_CNT_MASK      (0x00FFUL << UART0_FIFO_STATUS_RX_FIFO_CNT_POSI)
#define UART0_FIFO_STATUS_RX_FIFO_CNT_GET       (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_RX_FIFO_CNT_MASK)

#define UART0_FIFO_STATUS_TX_FIFO_FULL_POSI     16
#define UART0_FIFO_STATUS_TX_FIFO_FULL_MASK     (0x01UL << UART0_FIFO_STATUS_TX_FIFO_FULL_POSI)
#define UART0_FIFO_STATUS_TX_FIFO_FULL_GET      (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_TX_FIFO_FULL_MASK)

#define UART0_FIFO_STATUS_TX_FIFO_EMPTY_POSI    17
#define UART0_FIFO_STATUS_TX_FIFO_EMPTY_MASK    (0x01UL << UART0_FIFO_STATUS_TX_FIFO_EMPTY_POSI)
#define UART0_FIFO_STATUS_TX_FIFO_EMPTY_GET     (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_TX_FIFO_EMPTY_MASK)

#define UART0_FIFO_STATUS_RX_FIFO_FULL_POSI     18
#define UART0_FIFO_STATUS_RX_FIFO_FULL_MASK     (0x01UL << UART0_FIFO_STATUS_RX_FIFO_FULL_POSI)
#define UART0_FIFO_STATUS_RX_FIFO_FULL_GET      (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_RX_FIFO_FULL_MASK)

#define UART0_FIFO_STATUS_RX_FIFO_EMPTY_POSI    19
#define UART0_FIFO_STATUS_RX_FIFO_EMPTY_MASK    (0x01UL << UART0_FIFO_STATUS_RX_FIFO_EMPTY_POSI)
#define UART0_FIFO_STATUS_RX_FIFO_EMPTY_GET     (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_RX_FIFO_EMPTY_MASK)

#define UART0_FIFO_STATUS_WR_READY_POSI         20
#define UART0_FIFO_STATUS_WR_READY_MASK         (0x01UL << UART0_FIFO_STATUS_WR_READY_POSI)
#define UART0_FIFO_STATUS_WR_READY_GET          (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_WR_READY_MASK)

#define UART0_FIFO_STATUS_RD_READY_POSI         21
#define UART0_FIFO_STATUS_RD_READY_MASK         (0x01UL << UART0_FIFO_STATUS_RD_READY_POSI)
#define UART0_FIFO_STATUS_RD_READY_GET          (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_RD_READY_MASK)


#define REG_UART0_FIFO_PORT_ADDR                (REG_UART0_BASE_ADDR + 0x7 * 4)
#define REG_UART0_FIFO_PORT_MASK                0x00FFUL
#define REG_UART0_FIFO_PORT                     (*((volatile unsigned long *) REG_UART0_FIFO_PORT_ADDR))

#define UART0_FIFO_PORT_TX_DATA_POSI            0
#define UART0_FIFO_PORT_TX_DATA_MASK            (0x00FFUL << UART0_FIFO_PORT_TX_DATA_POSI)

#define UART0_FIFO_PORT_RX_DATA_POSI            0
#define UART0_FIFO_PORT_RX_DATA_MASK            (0x00FFUL << UART0_FIFO_PORT_RX_DATA_POSI)
#define UART0_FIFO_PORT_RX_DATA                 (REG_UART0_FIFO_PORT & UART0_FIFO_PORT_RX_DATA_MASK)


#define REG_UART0_INT_ENABLE_ADDR               (REG_UART0_BASE_ADDR + 0x8 * 4)
#define REG_UART0_INT_ENABLE_MASK               0x00FFUL
#define REG_UART0_INT_ENABLE                    (*((volatile unsigned long *) REG_UART0_INT_ENABLE_ADDR))

#define UART0_INT_ENABLE_TX_NEED_WR_POSI        0
#define UART0_INT_ENABLE_TX_NEED_WR_MASK        (0x01UL << UART0_INT_ENABLE_TX_NEED_WR_POSI)
#define UART0_INT_ENABLE_TX_NEED_WR_CLEAR       (0x00UL << UART0_INT_ENABLE_TX_NEED_WR_POSI)
#define UART0_INT_ENABLE_TX_NEED_WR_SET         (0x01UL << UART0_INT_ENABLE_TX_NEED_WR_POSI)

#define UART0_INT_ENABLE_RX_NEED_RD_POSI        1
#define UART0_INT_ENABLE_RX_NEED_RD_MASK        (0x01UL << UART0_INT_ENABLE_RX_NEED_RD_POSI)
#define UART0_INT_ENABLE_RX_NEED_RD_CLEAR       (0x00UL << UART0_INT_ENABLE_RX_NEED_RD_POSI)
#define UART0_INT_ENABLE_RX_NEED_RD_SET         (0x01UL << UART0_INT_ENABLE_RX_NEED_RD_POSI)

#define UART0_INT_ENABLE_RX_OVER_FLOW_POSI      2
#define UART0_INT_ENABLE_RX_OVER_FLOW_MASK      (0x01UL << UART0_INT_ENABLE_RX_OVER_FLOW_POSI)
#define UART0_INT_ENABLE_RX_OVER_FLOW_CLEAR     (0x00UL << UART0_INT_ENABLE_RX_OVER_FLOW_POSI)
#define UART0_INT_ENABLE_RX_OVER_FLOW_SET       (0x01UL << UART0_INT_ENABLE_RX_OVER_FLOW_POSI)

#define UART0_INT_ENABLE_RX_PARITY_ERR_POSI     3
#define UART0_INT_ENABLE_RX_PARITY_ERR_MASK     (0x01UL << UART0_INT_ENABLE_RX_PARITY_ERR_POSI)
#define UART0_INT_ENABLE_RX_PARITY_ERR_CLEAR    (0x00UL << UART0_INT_ENABLE_RX_PARITY_ERR_POSI)
#define UART0_INT_ENABLE_RX_PARITY_ERR_SET      (0x01UL << UART0_INT_ENABLE_RX_PARITY_ERR_POSI)

#define UART0_INT_ENABLE_RX_STOP_ERR_POSI       4
#define UART0_INT_ENABLE_RX_STOP_ERR_MASK       (0x01UL << UART0_INT_ENABLE_RX_STOP_ERR_POSI)
#define UART0_INT_ENABLE_RX_STOP_ERR_CLEAR      (0x00UL << UART0_INT_ENABLE_RX_STOP_ERR_POSI)
#define UART0_INT_ENABLE_RX_STOP_ERR_SET        (0x01UL << UART0_INT_ENABLE_RX_STOP_ERR_POSI)

#define UART0_INT_ENABLE_TX_STOP_END_POSI       5
#define UART0_INT_ENABLE_TX_STOP_END_MASK       (0x01UL << UART0_INT_ENABLE_TX_STOP_END_POSI)
#define UART0_INT_ENABLE_TX_STOP_END_CLEAR      (0x00UL << UART0_INT_ENABLE_TX_STOP_END_POSI)
#define UART0_INT_ENABLE_TX_STOP_END_SET        (0x01UL << UART0_INT_ENABLE_TX_STOP_END_POSI)

#define UART0_INT_ENABLE_RX_STOP_END_POSI       6
#define UART0_INT_ENABLE_RX_STOP_END_MASK       (0x01UL << UART0_INT_ENABLE_RX_STOP_END_POSI)
#define UART0_INT_ENABLE_RX_STOP_END_CLEAR      (0x00UL << UART0_INT_ENABLE_RX_STOP_END_POSI)
#define UART0_INT_ENABLE_RX_STOP_END_SET        (0x01UL << UART0_INT_ENABLE_RX_STOP_END_POSI)

#define UART0_INT_ENABLE_RXD_WAKEUP_POSI        7
#define UART0_INT_ENABLE_RXD_WAKEUP_MASK        (0x01UL << UART0_INT_ENABLE_RXD_WAKEUP_POSI)
#define UART0_INT_ENABLE_RXD_WAKEUP_CLEAR       (0x00UL << UART0_INT_ENABLE_RXD_WAKEUP_POSI)
#define UART0_INT_ENABLE_RXD_WAKEUP_SET         (0x01UL << UART0_INT_ENABLE_RXD_WAKEUP_POSI)


#define REG_UART0_INT_STATUS_ADDR               (REG_UART0_BASE_ADDR + 0x9 * 4)  //cyg
#define REG_UART0_INT_STATUS_MASK               0x00FFUL
#define REG_UART0_INT_STATUS                    (*((volatile unsigned long *) REG_UART0_INT_STATUS_ADDR))


#define REG_UART0_FLOW_CONTROL_ADDR             (REG_UART0_BASE_ADDR + 0xA * 4)
#define REG_UART0_FLOW_CONTROL_MASK             0x0001FFFF
#define REG_UART0_FLOW_CONTROL                  (*((volatile unsigned long *) REG_UART0_FLOW_CONTROL_ADDR))

#define UART0_FLOW_CONTROL_LOW_CNT_POSI         0
#define UART0_FLOW_CONTROL_LOW_CNT_MASK         (0x00FFUL << UART0_FLOW_CONTROL_LOW_CNT_POSI)

#define UART0_FLOW_CONTROL_HIGH_CNT_POSI        8
#define UART0_FLOW_CONTROL_HIGH_CNT_MASK        (0x00FFUL << UART0_FLOW_CONTROL_HIGH_CNT_POSI)

#define UART0_FLOW_CONTROL_ENABLE_POSI          16
#define UART0_FLOW_CONTROL_ENABLE_MASK          (0x0001UL << UART0_FLOW_CONTROL_ENABLE_POSI)


#define REG_UART0_WAKEUP_CONFIG_ADDR            (REG_UART0_BASE_ADDR + 0xB * 4)
#define REG_UART0_WAKEUP_CONFIG_MASK            0x007FFFFF
#define REG_UART0_WAKEUP_CONFIG                 (*((volatile unsigned long *) REG_UART0_WAKEUP_CONFIG_ADDR))

#define UART0_WAKEUP_CONFIG_DELAY_CNT_POSI      0
#define UART0_WAKEUP_CONFIG_DELAY_CNT_MASK      (0x03FF << UART0_WAKEUP_CONFIG_DELAY_CNT_POSI)

#define UART0_WAKEUP_CONFIG_TX_WAIT_CNT_POSI    10
#define UART0_WAKEUP_CONFIG_TX_WAIT_CNT_MASK    (0x03FF << UART0_WAKEUP_CONFIG_TX_WAIT_CNT_POSI)

#define UART0_WAKEUP_CONFIG_RX_WAKE_EN_POSI     20
#define UART0_WAKEUP_CONFIG_RX_WAKE_EN_MASK     (0x01UL << UART0_WAKEUP_CONFIG_RX_WAKE_EN_POSI)
#define UART0_WAKEUP_CONFIG_RX_WAKE_EN_SET      (0x01UL << UART0_WAKEUP_CONFIG_RX_WAKE_EN_POSI)

#define UART0_WAKEUP_CONFIG_TX_WAKE_EN_POSI     21
#define UART0_WAKEUP_CONFIG_TX_WAKE_EN_MASK     (0x01UL << UART0_WAKEUP_CONFIG_TX_WAKE_EN_POSI)
#define UART0_WAKEUP_CONFIG_TX_WAKE_EN_SET      (0x01UL << UART0_WAKEUP_CONFIG_TX_WAKE_EN_POSI)

#define UART0_WAKEUP_CONFIG_RX_NEGEDGE_WAKE_EN_POSI     22
#define UART0_WAKEUP_CONFIG_RX_NEGEDGE_WAKE_EN_MASK     (0x01UL << UART0_WAKEUP_CONFIG_RX_NEGEDGE_WAKE_EN_POSI)
#define UART0_WAKEUP_CONFIG_RX_NEGEDGE_WAKE_EN_SET      (0x01UL << UART0_WAKEUP_CONFIG_RX_NEGEDGE_WAKE_EN_POSI)

#define UART0_RX_FIFO_MAX_COUNT           128
#define UART0_TX_FIFO_MAX_COUNT           128

#define DEBUG_POLLING_PRINT(buff, len)      uart0_send(buff, len)

#define UART0_DEFAULT_CLK           PER_CLK
#define UART0_BAUD_115200           115200
#define UART0_DEFAULT_BAUD          UART0_BAUD_115200
#define UART0_CLK_DIVID_SET         MAX((NUMBER_ROUND_UP(UART0_DEFAULT_CLK, UART0_DEFAULT_BAUD) - 1), 4)

#define UART0_WRITE_BYTE(v)         (REG_UART0_FIFO_PORT = (v) & 0x00ff)
#define UART0_READ_BYTE()           ((REG_UART0_FIFO_PORT & 0xff00) >> 0x8)
#define UART0_TX_FIFO_EMPTY         (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_TX_FIFO_EMPTY_MASK)
#define UART0_TX_WRITE_READY        (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_WR_READY_MASK)
#define UART0_RX_READ_READY         (REG_UART0_FIFO_STATUS & UART0_FIFO_STATUS_RD_READY_MASK)

extern volatile bool   uart0_rx_done;
extern volatile uint32 uart0_rx_index;
//extern uint8 uart0_rx_buf[UART0_RX_FIFO_MAX_COUNT];
//extern uint8 uart0_tx_buf[UART0_TX_FIFO_MAX_COUNT];


#define DEBUG_PORT_UART0        (1)
#define DEBUG_PORT_UART1        (2)
#define DEBUG_PORT_SPI          (3)
#define DEBUG_PORT_I2C0         (4)
#define DEBUG_PORT_I2C1         (5)
#define DEBUG_PORT_UART2        (6)
#define DEBUG_PORT_IO_SIM_UART  (10)
#define PRINT_PORT              DEBUG_PORT_UART1

extern void uart0_init(unsigned long ulBaudRate);
extern void uart0_disable(void);
extern void uart0_send(u8 *buff, int len);
extern void uart0_send_string(const char *buff);
extern void uart0_wait_tx_finish(void);

extern void UART0_InterruptHandler(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __DRIVER_UART0_H__ */
