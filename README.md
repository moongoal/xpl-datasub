## Required external libraries

* xxhash

## Development environment set-up

The preferred way to initialize the build system is with:
    cmake
        -S .
        -B build
        -D CMAKE_EXPORT_COMPILE_COMMANDS=1
        -G Ninja

When using vcpkg, `-DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake` may be needed, where `VCPKG_ROOT` is the path to the installation of vcpkg.

To build the project, run `cmake --build build`.
