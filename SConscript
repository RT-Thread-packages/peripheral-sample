from building import *

src   = []
cwd   = GetCurrentDir()
include_path = [cwd]

# add kernel samples.

if GetDepend('PERIPHERAL_SAMPLES_USING_I2C'):
    src += ['i2c_aht10_sample.c']

if GetDepend('PERIPHERAL_SAMPLES_USING_PIN'):
    src += Glob('pin_beep_sample.c')

if GetDepend('PERIPHERAL_SAMPLES_USING_SERIAL'):
    src += Glob('uart_sample.c')

if GetDepend('PERIPHERAL_SAMPLES_USING_SPI'):
    src += Glob('spi_w25q_sample.c')

group = DefineGroup('peripheral-samples', src, depend = ['PKG_USING_PERIPHERAL_SAMPLES'], CPPPATH = include_path)

Return('group')
