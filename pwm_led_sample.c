/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-25     misonyo      first implementation.
 */
/*
 * 程序清单：这是一个 PWM 设备使用例程
 * 例程导出了 pwm_led_sample 命令到控制终端
 * 命令调用格式：pwm_led_sample
 * 程序功能：通过 PWM 设备控制 LED 灯的亮度，可以看到LED不停的由暗变到亮，然后又从亮变到暗。
*/

#include <rtthread.h>
#include <rtdevice.h>

/* LED PIN脚编号，查看驱动文件drv_gpio.c确定 */
#define LED_PIN_NUM         57
#define PWM_DEV_NAME        "pwm3"
#define PWM_DEV_CHANNEL     4

static void pwm_led_entry(void *parameter)
{
    rt_uint32_t period, pulse, dir;
    struct rt_device_pwm *pwm_dev;
    /* 设置LED引脚脚模式为输出 */
    rt_pin_mode(LED_PIN_NUM, PIN_MODE_OUTPUT);
    /* 拉高LED引脚 */
    rt_pin_write(LED_PIN_NUM, PIN_HIGH);

    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);

    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);

    period = 500000;    /* 0.5ms周期，单位为纳秒ns */
    dir = 1;            /* PWM脉冲宽度值的增减方向 */
    pulse = 0;          /* PWM脉冲宽度值，单位为纳秒ns */
    while (1)
    {
        rt_thread_mdelay(50);
        if (dir)
        {
            pulse += 5000;      /* 从0值开始每次增加5000ns */
        }
        else
        {
            pulse -= 5000;      /* 从最大值开始每次减少5000ns */
        }
        if (pulse >= 500000)
        {
            dir = 0;
        }
        if (0 == pulse)
        {
            dir = 1;
        }

        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    }
}

static void pwm_led_sample(int argc, char *argv[])
{
    rt_thread_t tid;

    tid = rt_thread_create("pwm",
                           pwm_led_entry,
                           RT_NULL,
                           512,
                           RT_THREAD_PRIORITY_MAX / 3,
                           20);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(pwm_led_sample, pwm sample);
