from building import *

src   = []
cwd   = GetCurrentDir()
include_path = [cwd]

if GetDepend('PERIPHERAL_SAMPLES_USING_ADC'):
    src += ['adc_vol_sample.c']

if GetDepend('PERIPHERAL_SAMPLES_USING_HWTIMER'):
    src += ['hwtimer_sample.c']

if GetDepend('PERIPHERAL_SAMPLES_USING_I2C'):
    src += ['i2c_aht10_sample.c']

if GetDepend('PERIPHERAL_SAMPLES_USING_IWDG'):
    src += ['iwdg_sample.c']

if GetDepend('PERIPHERAL_SAMPLES_USING_LED_BLINK'):
    src += ['led_blink_sample.c']

if GetDepend('PERIPHERAL_SAMPLES_USING_PIN'):
    src += Glob('pin_beep_sample.c')

if GetDepend('PERIPHERAL_SAMPLES_USING_PWM'):
    src += ['pwm_led_sample.c']

if GetDepend('PERIPHERAL_SAMPLES_USING_RTC'):
    src += ['rtc_sample.c']

if GetDepend('PERIPHERAL_SAMPLES_USING_SD'):
    src += ['sd_sample.c']

if GetDepend('PERIPHERAL_SAMPLES_USING_SERIAL'):
    src += Glob('uart_sample.c')

if GetDepend('PERIPHERAL_SAMPLES_USING_SERIAL_DMA'):
    src += Glob('uart_dma_sample.c')

if GetDepend('PERIPHERAL_SAMPLES_USING_SPI'):
    src += Glob('spi_w25q_sample.c')

group = DefineGroup('peripheral-samples', src, depend = ['PKG_USING_PERIPHERAL_SAMPLES'], CPPPATH = include_path)

Return('group')
