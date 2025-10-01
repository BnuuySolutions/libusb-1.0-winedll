#!/bin/bash

if [ -f "libusb-1.0.dll" ]; then
    rm libusb-1.0.dll
fi

winegcc -lusb-1.0 -lhidapi-hidraw -shared libusb-1.0.spec libusb-1.0.c -o libusb-1.0.dll

mv libusb-1.0.dll.so libusb-1.0.dll
cp libusb-1.0.dll hidapi.dll
