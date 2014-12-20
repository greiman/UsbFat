This is a preview of UsbFat, an Arduino library for USB flash drives
and USB hard drives.

The library has been tested with Arduino Uno, Mega, and Due boards using
the Circuits@Home USB Host Shield 2.0. Teensy 3.1 will be supported using
the USB Host Shield for Arduino Pro Mini.

The library also has been tested on the Arduino Mega ADK using 1.5.8.

This library is under development and anything in the library
may change.

The Arduino UsbFat library provides read/write access to FAT32/FAT16/FAT12
file systems on USB flash drives and USB hard drives.

It is best to use Arduino 1.5.8 or greater. Arduino 1.0.6 may
be used with the USB Host Shield 2.0.  

If you are using Arduino 1.5.5 or newer there is no need to activate the
Arduino Mega ADK manually.  Otherwise you must edit the settings.h file
in the USB_Host_Shield_2.0 library.

A modified version of USB_HostShield_2.0 is included.  The modifications
decrease the initialization time for most USB flash drives.  See
USB_host_Shield_diff.txt for details.  The unmodified library is here:

https://github.com/felis/USB_Host_Shield_2.0

Please read the html documentation for this library.  Start with
html/index.html and read the Main Page.  Next go to the Classes tab and
read the documentation for the classes SdFat, SdBaseFile, SdFile, File,
StdioStream, ifstream, ofstream, and others.

Please see the included examples.