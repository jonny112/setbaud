# setbaud
Set custom baud rates on a Linux terminal device.

Many UART devices like those integrated with SBCs, like Raspberry Pi, Odroid, etc. or the FTDI232 USB converter used on Arduino boards, actually support a much larger set of baud rates than those which can be selected using standard terminal tools like *stty*.

This tool provides a simple frontend to the Linux *termios2* API, allowing to set arbitrary input and output rates on a TTY device.

Several non-traditional terminal rates, which are however commonly used on automation busses and for microcontroller communication, like 125k, 250k, 500k are well supported by many devices and drivers.

## Usage
```sh
setbaud DEVICE [INRATE/OUTRATE] [OUTRATE]
```
See [manpage](doc/setbaud.man.txt) for full documentation.

## How to build

With **gcc**, **glibc** and the **Linux API headers** available, just run **make**.

## Bugs

Feel free to report issues and sugestions at:
https://github.com/jonny112/setbaud/issues
