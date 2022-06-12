cmake_minimum_required(VERSION 3.22)
project(MIA_P1_201801449)

set(CMAKE_CXX_STANDARD 14)

add_executable(MIA_P1_201801449 main.cpp Analizador/Analizador.cpp Archivo/Archivo.cpp Comandos/exec.cpp Comandos/mkdisk.cpp Comandos/rmdisk.cpp Comandos/fdisk.cpp Comandos/mount.cpp Comandos/rep.cpp Comandos/unmount.cpp)
