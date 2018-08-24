/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-15     misonyo      first implementation.
 */

#include <rtthread.h>

#define UART_NAME       "uart2"
/* 用于接收消息的信号量 */
static struct rt_semaphore rx_sem;

/* 接收数据回调函数 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    /* 串口2接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

static void serial_thread_entry(void* parameter)
{
    char ch;
    rt_device_t serial2;
    char str[] = "hello RT-Thread!\r\n";

    /* 查找系统中的串口2设备 */
    serial2 = rt_device_find(UART_NAME);
    
    if (serial2 != RT_NULL)
    {
        rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
        /* 以读写及中断接收方式打开串口设备 */
        rt_device_open(serial2, RT_DEVICE_OFLAG_RDWR|RT_DEVICE_FLAG_INT_RX);
        /* 设置回调函数 */
        rt_device_set_rx_indicate(serial2, uart_input);
        /* 发送字符串 */
        rt_device_write(serial2, 0, str, (sizeof(str) - 1));
        
        while (1)
        {
            /* 从串口2读取一个字节的数据，没有读取到则等待接收信号量 */
            while (rt_device_read(serial2, -1, &ch, 1) != 1)
            {
                /* 阻塞等待 接收信号量，等到信号量后再次读取数据 */
                rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
            }
        /* 读取到的数据通过串口2错位输出 */
        ch = ch + 1;
        rt_device_write(serial2, 0, &ch, 1);
        }
    }
    else
    {
        rt_kprintf("open uart2 failed!\n");
    }
}

static void uart_sample(void)
{
    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("serial",serial_thread_entry, RT_NULL, 1024, 25, 10);
    /* 创建成功则启动线程 */
    if (thread!= RT_NULL)
    {
        rt_thread_startup(thread);
    }
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(uart_sample, uart device sample);
