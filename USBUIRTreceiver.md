# USB UIRT receiver configuration #

LIT9 was tested with a USB-UIRT receiver. In order to support it, you should configure the file /etc/lirc/hardware.conf as follows:

```
# /etc/lirc/hardware.conf
REMOTE="UIRT2 (receive and transmit)"
REMOTE_MODULES=""
REMOTE_DRIVER="uirt2_raw"
REMOTE_DEVICE="/dev/ttyUSB0"
REMOTE_SOCKET=""
REMOTE_LIRCD_CONF=""
REMOTE_LIRCD_ARGS=""
TRANSMITTER="Custom"
TRANSMITTER_MODULES=""
TRANSMITTER_DRIVER=""
TRANSMITTER_DEVICE=""
TRANSMITTER_SOCKET=""
TRANSMITTER_LIRCD_CONF=""
TRANSMITTER_LIRCD_ARGS=""
START_LIRCD="true"
LOAD_MODULES="true"
LIRCMD_CONF=""
FORCE_NONINTERACTIVE_RECONFIGURATION="false"
START_LIRCMD=""
```

More info about USB UIRT receiver are available on [this page](http://www.usbuirt.com)