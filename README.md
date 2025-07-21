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
