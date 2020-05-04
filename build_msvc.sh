mkdir build
cd build
mkdir msvc
cd msvc
cmake ../.. -G "Visual Studio 16 2019" -A x64
cmake --build .
