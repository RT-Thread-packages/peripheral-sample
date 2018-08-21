/*
 * File      : drv_qspi_flash.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-17     zylx         first implementation.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>

#define SPI_DEVICE_NAME     "qspi10"

static void spi_sample(int argc,char *argv[])
{
    struct rt_spi_device *spi_dev_w25q128;
    rt_uint8_t w25x_read_id = 0x90;
    rt_uint8_t id[5] = {0};

    /* find qspi10 device */
    spi_dev_w25q128 = (struct rt_spi_device *)rt_device_find(SPI_DEVICE_NAME);
    if (!spi_dev_w25q128)
    {
        rt_kprintf("spi sample run failed! can't find qspi device!");
    }
    else
    {
        if ((argc >= 2) && (strcmp(argv[1], "method1") == 0))
        {
            rt_spi_send_then_recv(spi_dev_w25q128, &w25x_read_id, 1, id, 5);
            rt_kprintf("use method1 read w25q128 ID is:%x%x\n", id[3], id[4]);
        }
        else    /* 使用 rt_spi_transfer_message()*/
        {
            struct rt_spi_message msg1,msg2;

            msg1.send_buf   = &w25x_read_id;
            msg1.recv_buf   = RT_NULL;
            msg1.length     = 1;
            msg1.cs_take    = 1;
            msg1.cs_release = 0;
            msg1.next       = &msg2;

            msg2.send_buf   = RT_NULL;
            msg2.recv_buf   = id;
            msg2.length     = 5;
            msg2.cs_take    = 0;
            msg2.cs_release = 1;
            msg2.next       = RT_NULL;
            
            rt_spi_transfer_message(spi_dev_w25q128, &msg1);
            rt_kprintf("use method2 read w25q128 ID is:%x%x\n", id[3], id[4]);
        }
    }
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(spi_sample, spi device sample);
