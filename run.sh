set -e

cmake -S . -B build
cmake --build build --parallel
./build/application/OpenGL_Demo
