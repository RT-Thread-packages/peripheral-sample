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
#include <rtdevice.h>

/* 引脚编号，通过查看drv_gpio.c确定 */
#define BEEP_PIN        37  /* PB2 */
#define KEY0            55  /* PD8 */
#define KEY1            56  /* PD9 */

void beep_on(void *args)
{
    rt_kprintf("turn on beep!\n");
    
    rt_pin_write(BEEP_PIN, PIN_HIGH);
}

void beep_off(void *args)
{
    rt_kprintf("turn off beep!\n");
    
    rt_pin_write(BEEP_PIN, PIN_LOW);
}

static void pin_sample(void)
{
    /* 按键0引脚为输入模式 */
    rt_pin_mode(KEY0, PIN_MODE_INPUT_PULLUP);
    /* 绑定中断，上升沿模式，回调函数名为beep_on */
    rt_pin_attach_irq(KEY0, PIN_IRQ_MODE_FALLING, beep_on, RT_NULL);
    /* 使能中断 */
    rt_pin_irq_enable(KEY0, PIN_IRQ_ENABLE); 
    
    /* 按键1引脚为输入模式 */
    rt_pin_mode(KEY1, PIN_MODE_INPUT_PULLUP);
    /* 绑定中断，上升沿模式，回调函数名为beep_off */
    rt_pin_attach_irq(KEY1, PIN_IRQ_MODE_FALLING, beep_off, RT_NULL);
    /* 使能中断 */
    rt_pin_irq_enable(KEY1, PIN_IRQ_ENABLE);
    /* 蜂鸣器引脚为输出模式 */
    rt_pin_mode(BEEP_PIN, PIN_MODE_OUTPUT);

}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(pin_sample, pin device sample);
