# Bass21

This VST3 plugin is designed to simulate the famous Bass Driver DI Version 1 preamp pedal from Tech21.
It is discretized from an electronic schematic that is close to the original.

The potentiometers are the same as the ones that are physically on the physical BDDI pedal.
They have the same effect on the sound.

## Credits

- Jean Pierre Cimalando: circuit analysis and implementation
- Julien Taverna: circuit analysis and testing

## How to build

```
git clone --recursive https://github.com/jpcima/Bass21.git
mkdir Bass21/build
cd Bass21/build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```
