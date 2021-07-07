# Bass21

This VST3 is a virtual-analog simulation of the famous Bass Driver DI Version 1 preamp pedal from Tech21.
The discretization, while far from being exact, is moderately close to the original.

The potentiometers are identical to these physically present on the BDDI pedal, apart from the pregain
which is specific to this digital version.

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
