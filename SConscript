
from building import *
Import('rtconfig')

src   = []
cwd   = GetCurrentDir()
group = []
CPPPATH = []

# add kernel samples.

if GetDepend('PERIPHERAL_SAMPLES_USING_I2C'):
    src += Glob('i2c/*.c')
    CPPPATH += [cwd + '/i2c']

if GetDepend('PERIPHERAL_SAMPLES_USING_PIN'):
    src += Glob('pin/*.c')
    CPPPATH += [cwd + '/pin']

if GetDepend('PERIPHERAL_SAMPLES_USING_SERIAL'):
    src += Glob('serial/*.c')
    CPPPATH += [cwd + '/serial']

if GetDepend('PERIPHERAL_SAMPLES_USING_SPI'):
    src += Glob('spi/*.c')
    CPPPATH += [cwd + '/spi']

group = DefineGroup('peripheral-samples', src, depend = ['PKG_USING_PERIPHERAL_SAMPLES'], CPPPATH = CPPPATH)

Return('group')
