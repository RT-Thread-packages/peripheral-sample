# peripheral samples package

[中文页](README_ZH.md) | English

## 1. Introduction

This package contains some routines for the operation of peripheral devices.

### 1.1 Example description

| File | Description |
| ---------------- | ------------------------------- |
| adc_vol_sample.c | Use ADC device to convert voltage data |
| hwtimer_sample.c | Use hardware timer timing |
| i2c_aht10_sample.c | Use i2c device to obtain aht10 temperature and humidity sensor data |
| iwdg_sample.c | Watchdog device usage example |
| led_blink_sample.c | Use pin device to control LED blinking |
| pin_beep_sample.c | Use pin device to control buzzer |
| pwm_led_sample.c | Use pwm device to control LED brightness |
| rtc_sample.c | Use rtc device to set year, month, day, hour, minute and second information |
| sd_sample.c | Block device SD card usage example |
| spi_w25q_sample.c | Use spi device to read W25Q ID |
| uart_sample.c | Send and receive data using serial device interrupt receiving and polling sending mode |
| uart_dma_sample.c | Use serial device DMA reception and polling transmission mode to send and receive data |

### 1.2 License

The peripheral samples package complies with the Apache license v2.0, see the `LICENSE` file for details.

### 1.3 Dependency

Depend on the device driver provided by the device management module.

## 2. How to open the peripheral samples package

To use the peripheral samples package, you need to select it in the RT-Thread package manager. The specific path is as follows:

```
RT-Thread online packages
    miscellaneous packages --->
        samples: kernel and components samples --->
            a peripheral_samples package for rt-thread --->
```

Then let the RT-Thread package manager automatically update, or use the `pkgs --update` command to update the package to the BSP.

## 3. Use peripheral samples package

After opening the peripheral samples package, when the BSP is compiled, the relevant source code of the selected software package will be added to the BSP project for compilation.

## 4. Matters needing attention

Nothing.

## 5. Contact & Thanks

* Maintenance: [misonyo](https://github.com/misonyo)
* Homepage: https://github.com/RT-Thread-packages/peripheral-sample
