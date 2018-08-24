# peripheral samples package

## 1、介绍

这个软件包包含一些外设设备操作的例程。

### 1.1 目录结构

| 目录             | 例程                            |
| ---------------- | ------------------------------- |
| i2c              | i2c 设备的使用                  |
| pin              | pin 设备的使用                  |
| serial           | serial 设备的使用               |
| spi              | spi 设备的使用                  |

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

* 维护：name
* 主页：https://github.com/RT-Thread-packages/peripheral-sample.git
