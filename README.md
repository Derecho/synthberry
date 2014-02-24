# synthberry

Synthberry is a software synthesizer written for the Raspberry Pi in C++11.
This is a personal project and currently work-in-progress, source may break at
any time.

My main motivation for carrying out this project is to gain knowledge about
(software) MIDI synthesizers in general.

## Compilation
After cloning the synthberry repository you need to retrieve the dependencies:

    git submodule update --init --recursive

Having done that, you can build the source by issuing:

    make

Now you can run synthberry as follows:

    LD_LIBRARY_PATH=externals/libserial/src/.libs bin/synthberry

## Cross complation
Cross-compiling the source on a PC is much faster than compiling it natively on
the Raspberry Pi. I recommend you to use this if you expect to make changes or
additions to the code as it will speed development up significantly.

Follow the above steps, but instead of simply running `make` run the following:

    make rpi

The raspberry pi toolchain consists of 32-bit executables, on Debian and
derivatives you may need to do:

    sudo apt-get install libc6-i386 lib32stdc++6 lib32z1

## Current status
Milestones:

- [x] Parse MIDI messages
- [ ] Implement a basic oscillator
- [ ] Implement some typical synthesizer modules

In order to accomplish these steps, the appropriate design decisions may have
to be made first. The goal is to have an easily extendable codebase which will
allow a user to quickly create his own software synthesizer setup.

Currently if you compile synthberry in debug mode (see the `help` target), you
will be able to see any parsed Note On and Note Off messages.

## Hardware setup
I'm using the Raspberry Pi's hardware UART to connect my MIDI keyboard (Yamaha
PSR-280). The UART clockrate has been adjusted with boot parameters so that data
can be received at 31250 baud (looks like 38400 to software).

This kind of setup seems to be quite common, for more information I'd like to
refer you to:
http://www.siliconstuff.com/2012/08/serial-port-midi-on-raspberry-pi.html
