# synthberry

Synthberry is a software synthesizer written for the Raspberry Pi in C++11.
This is a personal project and currently work-in-progress, source may break at
any time.

## Compilation
After cloning the synthberry repository you need to retrieve the dependencies:

    git submodule update --init --recursive

Having done that, you can build the source by issuing:

    make

Now you can run synthberry as follows:

    LD_LIBRARY_PATH=externals/libserial/src/.libs bin/synthberry

## Cross complation
Follow the above steps, but instead of simply running `make` run the following:

    make rpi

The raspberry pi toolchain consists of 32-bit executables, on Debian and
derivatives you may need to do:

    sudo apt-get install libc6-i386 lib32stdc++6 lib32z1
