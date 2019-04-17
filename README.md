# peripheral samples package

## 1、介绍

这个软件包包含一些外设设备操作的例程。

### 1.1 例程说明

| 文件             | 说明                            |
| ---------------- | ------------------------------- |
| adc_vol_sample.c       | 使用 ADC 设备转换电压数据 |
| hwtimer_sample.c       | 使用 硬件定时器定时 |
| i2c_aht10_sample.c     | 使用 i2c 设备获取 aht10 温湿度传感器数据 |
| iwdg_sample.c          | 看门狗设备使用示例 |
| led_blink_sample.c     |  使用 pin 设备控制 LED 闪烁 |
| pin_beep_sample.c      | 使用 pin 设备控制蜂鸣器 |
| pwm_led_sample.c       | 使用 pwm 设备控制 LED 的亮度 |
| rtc_sample.c           | 使用 rtc 设备设置年月日时分秒信息 |
| sd_sample.c            | 块设备 SD 卡使用示例  |
| spi_w25q_sample.c      | 使用 spi 设备读取 W25Q ID |
| uart_sample.c          | 使用 serial 设备中断接收及轮询发送模式收发数据 |
| uart_dma_sample.c      | 使用 serial 设备 DMA 接收及轮询发送模式收发数据 |

### 1.2 许可证

peripheral samples package 遵循 Apache license v2.0 许可，详见 `LICENSE` 文件。

### 1.3 依赖

依赖设备管理模块提供的设备驱动。

## 2、如何打开 peripheral samples package

使用 peripheral samples package 需要在 RT-Thread 的包管理器中选择它，具体路径如下：

```
RT-Thread online packages
    miscellaneous packages --->
        samples: kernel and components samples --->
            a peripheral_samples package for rt-thread --->
```

然后让 RT-Thread 的包管理器自动更新，或者使用 `pkgs --update` 命令更新包到 BSP 中。

## 3、使用 peripheral samples package

在打开 peripheral samples package 后，当进行 BSP 编译时，选择的软件包相关源代码会被加入到 BSP 工程中进行编译。

## 4、注意事项

暂无。

## 5、联系方式 & 感谢

* 维护：[misonyo](https://github.com/misonyo)
* 主页：https://github.com/RT-Thread-packages/peripheral-sample
