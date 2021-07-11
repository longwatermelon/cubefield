# cubefield
Cubefield clone

# Building
```
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
make
cd .. && build/cubefield # So that cubefield can find the font file
```
