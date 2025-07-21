# ExaKey

## Build System

The project uses CMake to manage the build system. A bash script (`init.sh`) is provided to initialize build systems for
a variety of targets. To initialize the build environment, run:

```
./init.sh
```

Then change to the relevant build directory and run `make` to build the executables:

```
cd build/atmega328p
make
```

## Uploading

The executables may be uploaded to an Arduino using `avrdude`.

```
avrdude -c arduino -p [mcu] -P [port] -b [bitrate] -U flash:w:[filename].ihex
```

For example, on my computer, to upload `exakey.ihex` to the Uno 3, I use the command:

```
avrdude -c arduino -p m328p -P COM7 -b 115200 -U flash:w:exakey.ihex
```
