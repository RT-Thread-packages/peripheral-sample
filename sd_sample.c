/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-25     misonyo      first edition.
 */
/*
 * 程序清单：这是一个SD卡设备的使用例程
 * 例程导出了 sd_sample 命令到控制终端
 * 命令调用格式：sd_sample sd0
 * 命令解释：命令第二个参数是要使用的SD设备的名称，为空则使用例程默认的SD设备。
 * 程序功能：程序会产生一个块大小的随机数，然后写入SD卡中，然后在读取这部分写入的数据。
 *            对比写入和读出的数据是否一致，一致则表示程序运行正确。
*/

#include <rtthread.h>
#include <rtdevice.h>
#include <stdlib.h>

#define SD_DEVICE_NAME    "sd0"

void fill_buffer(rt_uint8_t *buff, rt_uint32_t buff_length)
{
    rt_uint32_t index;
    /* 往缓冲区填充随机数 */
    for (index = 0; index < buff_length; index++)
    {
        buff[index] = ((rt_uint8_t)rand()) & 0xff;
    }
}

static int sd_sample(int argc, char *argv[])
{
    rt_err_t ret;
    rt_device_t sd_device;
    char sd_name[RT_NAME_MAX];
    rt_uint8_t *write_buff, *read_buff;
    struct rt_device_blk_geometry geo;
    rt_uint8_t block_num;
    /* 判断命令行参数是否给定了设备名称 */
    if (argc == 2)
    {
        rt_strncpy(sd_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(sd_name, SD_DEVICE_NAME, RT_NAME_MAX);
    }
    /* 查找设备获取设备句柄 */
    sd_device = rt_device_find(sd_name);
    if (sd_device == RT_NULL)
    {
        rt_kprintf("find device %s failed!\n", sd_name);
        return RT_ERROR;
    }
    /* 打开设备 */
    ret = rt_device_open(sd_device, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open device %s failed!\n", sd_name);
        return ret;
    }

    rt_memset(&geo, 0, sizeof(geo));
    /* 获取块设备信息 */
    ret = rt_device_control(sd_device, RT_DEVICE_CTRL_BLK_GETGEOME, &geo);
    if (ret != RT_EOK)
    {
        rt_kprintf("control device %s failed!\n", sd_name);
        return ret;
    }
    rt_kprintf("device information:\n");
    rt_kprintf("sector  size : %d byte\n", geo.bytes_per_sector);
    rt_kprintf("sector count : %d \n", geo.sector_count);
    rt_kprintf("block   size : %d byte\n", geo.block_size);
    /* 准备读写缓冲区空间，大小为一个块 */
    read_buff = rt_malloc(geo.block_size);
    if (read_buff == RT_NULL)
    {
        rt_kprintf("no memory for read buffer!\n");
        return RT_ERROR;
    }
    write_buff = rt_malloc(geo.block_size);
    if (write_buff == RT_NULL)
    {
        rt_kprintf("no memory for write buffer!\n");
        rt_free(read_buff);
        return RT_ERROR;
    }

    /* 填充写数据缓冲区，为写操作做准备 */
    fill_buffer(write_buff, geo.block_size);

    /* 把写数据缓冲的数据写入SD卡中，大小为一个块，size参数以块为单位 */
    block_num = rt_device_write(sd_device, 0, write_buff, 1);
    if (1 != block_num)
    {
        rt_kprintf("write device %s failed!\n", sd_name);
    }

    /* 从SD卡中读出数据，并保存在读数据缓冲区中 */
    block_num = rt_device_read(sd_device, 0, read_buff, 1);
    if (1 != block_num)
    {
        rt_kprintf("read %s device failed!\n", sd_name);
    }

    /* 比较写数据缓冲区和读数据缓冲区的内容是否完全一致 */
    if (rt_memcmp(write_buff, read_buff, geo.block_size) == 0)
    {
        rt_kprintf("Block test OK!\n");
    }
    else
    {
        rt_kprintf("Block test Fail!\n");
    }
    /* 释放缓冲区空间 */
    rt_free(read_buff);
    rt_free(write_buff);

    return RT_EOK;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(sd_sample, sd device sample);
