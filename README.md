# Bass21

This VST3 is a virtual-analog simulation of the famous Bass Driver DI Version 1 preamp pedal from Tech21.
The discretization, while far from being exact, is moderately close to the original.

The potentiometers are identical to these physically present on the BDDI pedal, apart from the pregain
which is specific to this digital version.

## Download development builds

- [64-bit Windows VST3](https://nightly.link/jpcima/Bass21/workflows/build/master/Win64%20VST3.zip)  
- [32-bit Windows VST3](https://nightly.link/jpcima/Bass21/workflows/build/master/Win32%20VST3.zip)  
- [macOS Universal AU (**not signed**)](https://nightly.link/jpcima/Bass21/workflows/build/master/macOS%20AU.zip)  
- [macOS Universal VST3 (**not signed**)](https://nightly.link/jpcima/Bass21/workflows/build/master/macOS%20VST3.zip)
- [MOD devices LV2](https://nightly.link/jpcima/Bass21/workflows/build/master/MOD%20LV2.zip)

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
