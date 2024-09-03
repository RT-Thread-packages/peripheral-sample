/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-23     Wangyuqiang  first version
 */
/*
 * 程序清单：这是一个 模拟test字符设备驱动使用例程
 * 例程导出了 drv_sample 命令到控制终端
 * 命令调用格式：drv_sample
 * 程序功能：模拟一个字符设备驱动，使开发者无需对接驱动框架即可体验RT-Thread设备驱动。
*/

#include <rtthread.h>
#include <rtdevice.h>

static rt_err_t drv_test_init(rt_device_t dev)
{
    rt_kprintf("Test drv init!\n");
    return RT_EOK;
}

static rt_err_t drv_test_open(rt_device_t dev, rt_uint16_t oflag)
{
    rt_kprintf("Test drv open flag = %d.\n", oflag);
    return RT_EOK;
}

static rt_err_t drv_test_close(rt_device_t dev)
{
    rt_kprintf("Test drv close!\n");
    return RT_EOK;
}

static rt_ssize_t drv_test_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_kprintf("Test drv read pos = %d, size = %d.\n", pos, size);
    return size;
}

static rt_ssize_t drv_test_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_kprintf("Test drv write pos = %d, size = %d.\n", pos, size);
    return size;
}

static rt_err_t drv_test_control(rt_device_t dev, int cmd, void *args)
{
    rt_kprintf("Test drv control cmd = %d.\n", cmd);
    return RT_EOK;
}

int rt_drv_test_init(void)
{
    rt_device_t test_dev = rt_device_create(RT_Device_Class_Char, 0);
    if(!test_dev)
    {
        rt_kprintf("Test drv create failed!\n");
        return -RT_ERROR;
    }

    test_dev->init    = drv_test_init;
    test_dev->open    = drv_test_open;
    test_dev->close   = drv_test_close;
    test_dev->read    = drv_test_read;
    test_dev->write   = drv_test_write;
    test_dev->control = drv_test_control;

    if(rt_device_register(test_dev, "test_drv", RT_DEVICE_FLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("Test drv register failed!\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_drv_test_init);

static int drv_sample(void)
{
    rt_device_t test_dev = rt_device_find("test_drv");
    if(test_dev == RT_NULL)
    {
        rt_kprintf("Can not find test drv!\n");
        return -RT_ERROR;
    }
    
    rt_device_open(test_dev, RT_DEVICE_OFLAG_RDWR);
    rt_device_control(test_dev, RT_DEVICE_CTRL_CONFIG, RT_NULL);
    rt_device_write(test_dev, 100, RT_NULL, 1024);
    rt_device_read(test_dev, 20, RT_NULL, 128);

    rt_device_close(test_dev);

    return RT_EOK;
}
MSH_CMD_EXPORT(drv_sample, enable test drv sample);
