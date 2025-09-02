echo "Configuring CMake..."

cmake --version || apt install cmake

mkdir build
cd build

cmake ..