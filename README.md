# libserial
This simple library provides the basic operations needed for serial communication under Linux OSs.

## Features:
- open & init device (*init_device* function)
- provided functions to manually set-up device
- send commands to device (*send* function)
- receive response from device (*receive* function)
- query device: send command & read response (*query* function)

### Testing:
Library was tested on HAMEG HM8118 device (usb-serial interface): [source](./test/test.c)
