# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/198/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/198/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/magdiel/Escritorio/MIA_P1_201801449

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MIA_P1_201801449.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MIA_P1_201801449.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MIA_P1_201801449.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MIA_P1_201801449.dir/flags.make

CMakeFiles/MIA_P1_201801449.dir/main.cpp.o: CMakeFiles/MIA_P1_201801449.dir/flags.make
CMakeFiles/MIA_P1_201801449.dir/main.cpp.o: ../main.cpp
CMakeFiles/MIA_P1_201801449.dir/main.cpp.o: CMakeFiles/MIA_P1_201801449.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MIA_P1_201801449.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MIA_P1_201801449.dir/main.cpp.o -MF CMakeFiles/MIA_P1_201801449.dir/main.cpp.o.d -o CMakeFiles/MIA_P1_201801449.dir/main.cpp.o -c /home/magdiel/Escritorio/MIA_P1_201801449/main.cpp

CMakeFiles/MIA_P1_201801449.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MIA_P1_201801449.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magdiel/Escritorio/MIA_P1_201801449/main.cpp > CMakeFiles/MIA_P1_201801449.dir/main.cpp.i

CMakeFiles/MIA_P1_201801449.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MIA_P1_201801449.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magdiel/Escritorio/MIA_P1_201801449/main.cpp -o CMakeFiles/MIA_P1_201801449.dir/main.cpp.s

CMakeFiles/MIA_P1_201801449.dir/Analizador/Analizador.cpp.o: CMakeFiles/MIA_P1_201801449.dir/flags.make
CMakeFiles/MIA_P1_201801449.dir/Analizador/Analizador.cpp.o: ../Analizador/Analizador.cpp
CMakeFiles/MIA_P1_201801449.dir/Analizador/Analizador.cpp.o: CMakeFiles/MIA_P1_201801449.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MIA_P1_201801449.dir/Analizador/Analizador.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MIA_P1_201801449.dir/Analizador/Analizador.cpp.o -MF CMakeFiles/MIA_P1_201801449.dir/Analizador/Analizador.cpp.o.d -o CMakeFiles/MIA_P1_201801449.dir/Analizador/Analizador.cpp.o -c /home/magdiel/Escritorio/MIA_P1_201801449/Analizador/Analizador.cpp

CMakeFiles/MIA_P1_201801449.dir/Analizador/Analizador.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MIA_P1_201801449.dir/Analizador/Analizador.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magdiel/Escritorio/MIA_P1_201801449/Analizador/Analizador.cpp > CMakeFiles/MIA_P1_201801449.dir/Analizador/Analizador.cpp.i

CMakeFiles/MIA_P1_201801449.dir/Analizador/Analizador.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MIA_P1_201801449.dir/Analizador/Analizador.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magdiel/Escritorio/MIA_P1_201801449/Analizador/Analizador.cpp -o CMakeFiles/MIA_P1_201801449.dir/Analizador/Analizador.cpp.s

CMakeFiles/MIA_P1_201801449.dir/Archivo/Archivo.cpp.o: CMakeFiles/MIA_P1_201801449.dir/flags.make
CMakeFiles/MIA_P1_201801449.dir/Archivo/Archivo.cpp.o: ../Archivo/Archivo.cpp
CMakeFiles/MIA_P1_201801449.dir/Archivo/Archivo.cpp.o: CMakeFiles/MIA_P1_201801449.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MIA_P1_201801449.dir/Archivo/Archivo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MIA_P1_201801449.dir/Archivo/Archivo.cpp.o -MF CMakeFiles/MIA_P1_201801449.dir/Archivo/Archivo.cpp.o.d -o CMakeFiles/MIA_P1_201801449.dir/Archivo/Archivo.cpp.o -c /home/magdiel/Escritorio/MIA_P1_201801449/Archivo/Archivo.cpp

CMakeFiles/MIA_P1_201801449.dir/Archivo/Archivo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MIA_P1_201801449.dir/Archivo/Archivo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magdiel/Escritorio/MIA_P1_201801449/Archivo/Archivo.cpp > CMakeFiles/MIA_P1_201801449.dir/Archivo/Archivo.cpp.i

CMakeFiles/MIA_P1_201801449.dir/Archivo/Archivo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MIA_P1_201801449.dir/Archivo/Archivo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magdiel/Escritorio/MIA_P1_201801449/Archivo/Archivo.cpp -o CMakeFiles/MIA_P1_201801449.dir/Archivo/Archivo.cpp.s

CMakeFiles/MIA_P1_201801449.dir/Comandos/exec.cpp.o: CMakeFiles/MIA_P1_201801449.dir/flags.make
CMakeFiles/MIA_P1_201801449.dir/Comandos/exec.cpp.o: ../Comandos/exec.cpp
CMakeFiles/MIA_P1_201801449.dir/Comandos/exec.cpp.o: CMakeFiles/MIA_P1_201801449.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MIA_P1_201801449.dir/Comandos/exec.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MIA_P1_201801449.dir/Comandos/exec.cpp.o -MF CMakeFiles/MIA_P1_201801449.dir/Comandos/exec.cpp.o.d -o CMakeFiles/MIA_P1_201801449.dir/Comandos/exec.cpp.o -c /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/exec.cpp

CMakeFiles/MIA_P1_201801449.dir/Comandos/exec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MIA_P1_201801449.dir/Comandos/exec.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/exec.cpp > CMakeFiles/MIA_P1_201801449.dir/Comandos/exec.cpp.i

CMakeFiles/MIA_P1_201801449.dir/Comandos/exec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MIA_P1_201801449.dir/Comandos/exec.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/exec.cpp -o CMakeFiles/MIA_P1_201801449.dir/Comandos/exec.cpp.s

CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdisk.cpp.o: CMakeFiles/MIA_P1_201801449.dir/flags.make
CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdisk.cpp.o: ../Comandos/mkdisk.cpp
CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdisk.cpp.o: CMakeFiles/MIA_P1_201801449.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdisk.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdisk.cpp.o -MF CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdisk.cpp.o.d -o CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdisk.cpp.o -c /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/mkdisk.cpp

CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdisk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdisk.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/mkdisk.cpp > CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdisk.cpp.i

CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdisk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdisk.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/mkdisk.cpp -o CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdisk.cpp.s

CMakeFiles/MIA_P1_201801449.dir/Comandos/rmdisk.cpp.o: CMakeFiles/MIA_P1_201801449.dir/flags.make
CMakeFiles/MIA_P1_201801449.dir/Comandos/rmdisk.cpp.o: ../Comandos/rmdisk.cpp
CMakeFiles/MIA_P1_201801449.dir/Comandos/rmdisk.cpp.o: CMakeFiles/MIA_P1_201801449.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MIA_P1_201801449.dir/Comandos/rmdisk.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MIA_P1_201801449.dir/Comandos/rmdisk.cpp.o -MF CMakeFiles/MIA_P1_201801449.dir/Comandos/rmdisk.cpp.o.d -o CMakeFiles/MIA_P1_201801449.dir/Comandos/rmdisk.cpp.o -c /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/rmdisk.cpp

CMakeFiles/MIA_P1_201801449.dir/Comandos/rmdisk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MIA_P1_201801449.dir/Comandos/rmdisk.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/rmdisk.cpp > CMakeFiles/MIA_P1_201801449.dir/Comandos/rmdisk.cpp.i

CMakeFiles/MIA_P1_201801449.dir/Comandos/rmdisk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MIA_P1_201801449.dir/Comandos/rmdisk.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/rmdisk.cpp -o CMakeFiles/MIA_P1_201801449.dir/Comandos/rmdisk.cpp.s

CMakeFiles/MIA_P1_201801449.dir/Comandos/fdisk.cpp.o: CMakeFiles/MIA_P1_201801449.dir/flags.make
CMakeFiles/MIA_P1_201801449.dir/Comandos/fdisk.cpp.o: ../Comandos/fdisk.cpp
CMakeFiles/MIA_P1_201801449.dir/Comandos/fdisk.cpp.o: CMakeFiles/MIA_P1_201801449.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/MIA_P1_201801449.dir/Comandos/fdisk.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MIA_P1_201801449.dir/Comandos/fdisk.cpp.o -MF CMakeFiles/MIA_P1_201801449.dir/Comandos/fdisk.cpp.o.d -o CMakeFiles/MIA_P1_201801449.dir/Comandos/fdisk.cpp.o -c /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/fdisk.cpp

CMakeFiles/MIA_P1_201801449.dir/Comandos/fdisk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MIA_P1_201801449.dir/Comandos/fdisk.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/fdisk.cpp > CMakeFiles/MIA_P1_201801449.dir/Comandos/fdisk.cpp.i

CMakeFiles/MIA_P1_201801449.dir/Comandos/fdisk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MIA_P1_201801449.dir/Comandos/fdisk.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/fdisk.cpp -o CMakeFiles/MIA_P1_201801449.dir/Comandos/fdisk.cpp.s

CMakeFiles/MIA_P1_201801449.dir/Comandos/mount.cpp.o: CMakeFiles/MIA_P1_201801449.dir/flags.make
CMakeFiles/MIA_P1_201801449.dir/Comandos/mount.cpp.o: ../Comandos/mount.cpp
CMakeFiles/MIA_P1_201801449.dir/Comandos/mount.cpp.o: CMakeFiles/MIA_P1_201801449.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/MIA_P1_201801449.dir/Comandos/mount.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MIA_P1_201801449.dir/Comandos/mount.cpp.o -MF CMakeFiles/MIA_P1_201801449.dir/Comandos/mount.cpp.o.d -o CMakeFiles/MIA_P1_201801449.dir/Comandos/mount.cpp.o -c /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/mount.cpp

CMakeFiles/MIA_P1_201801449.dir/Comandos/mount.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MIA_P1_201801449.dir/Comandos/mount.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/mount.cpp > CMakeFiles/MIA_P1_201801449.dir/Comandos/mount.cpp.i

CMakeFiles/MIA_P1_201801449.dir/Comandos/mount.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MIA_P1_201801449.dir/Comandos/mount.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/mount.cpp -o CMakeFiles/MIA_P1_201801449.dir/Comandos/mount.cpp.s

CMakeFiles/MIA_P1_201801449.dir/Comandos/rep.cpp.o: CMakeFiles/MIA_P1_201801449.dir/flags.make
CMakeFiles/MIA_P1_201801449.dir/Comandos/rep.cpp.o: ../Comandos/rep.cpp
CMakeFiles/MIA_P1_201801449.dir/Comandos/rep.cpp.o: CMakeFiles/MIA_P1_201801449.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/MIA_P1_201801449.dir/Comandos/rep.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MIA_P1_201801449.dir/Comandos/rep.cpp.o -MF CMakeFiles/MIA_P1_201801449.dir/Comandos/rep.cpp.o.d -o CMakeFiles/MIA_P1_201801449.dir/Comandos/rep.cpp.o -c /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/rep.cpp

CMakeFiles/MIA_P1_201801449.dir/Comandos/rep.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MIA_P1_201801449.dir/Comandos/rep.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/rep.cpp > CMakeFiles/MIA_P1_201801449.dir/Comandos/rep.cpp.i

CMakeFiles/MIA_P1_201801449.dir/Comandos/rep.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MIA_P1_201801449.dir/Comandos/rep.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/rep.cpp -o CMakeFiles/MIA_P1_201801449.dir/Comandos/rep.cpp.s

CMakeFiles/MIA_P1_201801449.dir/Comandos/unmount.cpp.o: CMakeFiles/MIA_P1_201801449.dir/flags.make
CMakeFiles/MIA_P1_201801449.dir/Comandos/unmount.cpp.o: ../Comandos/unmount.cpp
CMakeFiles/MIA_P1_201801449.dir/Comandos/unmount.cpp.o: CMakeFiles/MIA_P1_201801449.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/MIA_P1_201801449.dir/Comandos/unmount.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MIA_P1_201801449.dir/Comandos/unmount.cpp.o -MF CMakeFiles/MIA_P1_201801449.dir/Comandos/unmount.cpp.o.d -o CMakeFiles/MIA_P1_201801449.dir/Comandos/unmount.cpp.o -c /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/unmount.cpp

CMakeFiles/MIA_P1_201801449.dir/Comandos/unmount.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MIA_P1_201801449.dir/Comandos/unmount.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/unmount.cpp > CMakeFiles/MIA_P1_201801449.dir/Comandos/unmount.cpp.i

CMakeFiles/MIA_P1_201801449.dir/Comandos/unmount.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MIA_P1_201801449.dir/Comandos/unmount.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/unmount.cpp -o CMakeFiles/MIA_P1_201801449.dir/Comandos/unmount.cpp.s

CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfs.cpp.o: CMakeFiles/MIA_P1_201801449.dir/flags.make
CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfs.cpp.o: ../Comandos/mkfs.cpp
CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfs.cpp.o: CMakeFiles/MIA_P1_201801449.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfs.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfs.cpp.o -MF CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfs.cpp.o.d -o CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfs.cpp.o -c /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/mkfs.cpp

CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfs.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/mkfs.cpp > CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfs.cpp.i

CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfs.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/mkfs.cpp -o CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfs.cpp.s

CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdir.cpp.o: CMakeFiles/MIA_P1_201801449.dir/flags.make
CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdir.cpp.o: ../Comandos/mkdir.cpp
CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdir.cpp.o: CMakeFiles/MIA_P1_201801449.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdir.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdir.cpp.o -MF CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdir.cpp.o.d -o CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdir.cpp.o -c /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/mkdir.cpp

CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdir.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdir.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/mkdir.cpp > CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdir.cpp.i

CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdir.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdir.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/mkdir.cpp -o CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdir.cpp.s

CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfile.cpp.o: CMakeFiles/MIA_P1_201801449.dir/flags.make
CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfile.cpp.o: ../Comandos/mkfile.cpp
CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfile.cpp.o: CMakeFiles/MIA_P1_201801449.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfile.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfile.cpp.o -MF CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfile.cpp.o.d -o CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfile.cpp.o -c /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/mkfile.cpp

CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfile.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/mkfile.cpp > CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfile.cpp.i

CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfile.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/mkfile.cpp -o CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfile.cpp.s

CMakeFiles/MIA_P1_201801449.dir/Comandos/syncronice.cpp.o: CMakeFiles/MIA_P1_201801449.dir/flags.make
CMakeFiles/MIA_P1_201801449.dir/Comandos/syncronice.cpp.o: ../Comandos/syncronice.cpp
CMakeFiles/MIA_P1_201801449.dir/Comandos/syncronice.cpp.o: CMakeFiles/MIA_P1_201801449.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/MIA_P1_201801449.dir/Comandos/syncronice.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MIA_P1_201801449.dir/Comandos/syncronice.cpp.o -MF CMakeFiles/MIA_P1_201801449.dir/Comandos/syncronice.cpp.o.d -o CMakeFiles/MIA_P1_201801449.dir/Comandos/syncronice.cpp.o -c /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/syncronice.cpp

CMakeFiles/MIA_P1_201801449.dir/Comandos/syncronice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MIA_P1_201801449.dir/Comandos/syncronice.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/syncronice.cpp > CMakeFiles/MIA_P1_201801449.dir/Comandos/syncronice.cpp.i

CMakeFiles/MIA_P1_201801449.dir/Comandos/syncronice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MIA_P1_201801449.dir/Comandos/syncronice.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magdiel/Escritorio/MIA_P1_201801449/Comandos/syncronice.cpp -o CMakeFiles/MIA_P1_201801449.dir/Comandos/syncronice.cpp.s

# Object files for target MIA_P1_201801449
MIA_P1_201801449_OBJECTS = \
"CMakeFiles/MIA_P1_201801449.dir/main.cpp.o" \
"CMakeFiles/MIA_P1_201801449.dir/Analizador/Analizador.cpp.o" \
"CMakeFiles/MIA_P1_201801449.dir/Archivo/Archivo.cpp.o" \
"CMakeFiles/MIA_P1_201801449.dir/Comandos/exec.cpp.o" \
"CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdisk.cpp.o" \
"CMakeFiles/MIA_P1_201801449.dir/Comandos/rmdisk.cpp.o" \
"CMakeFiles/MIA_P1_201801449.dir/Comandos/fdisk.cpp.o" \
"CMakeFiles/MIA_P1_201801449.dir/Comandos/mount.cpp.o" \
"CMakeFiles/MIA_P1_201801449.dir/Comandos/rep.cpp.o" \
"CMakeFiles/MIA_P1_201801449.dir/Comandos/unmount.cpp.o" \
"CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfs.cpp.o" \
"CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdir.cpp.o" \
"CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfile.cpp.o" \
"CMakeFiles/MIA_P1_201801449.dir/Comandos/syncronice.cpp.o"

# External object files for target MIA_P1_201801449
MIA_P1_201801449_EXTERNAL_OBJECTS =

MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/main.cpp.o
MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/Analizador/Analizador.cpp.o
MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/Archivo/Archivo.cpp.o
MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/Comandos/exec.cpp.o
MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdisk.cpp.o
MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/Comandos/rmdisk.cpp.o
MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/Comandos/fdisk.cpp.o
MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/Comandos/mount.cpp.o
MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/Comandos/rep.cpp.o
MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/Comandos/unmount.cpp.o
MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfs.cpp.o
MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/Comandos/mkdir.cpp.o
MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/Comandos/mkfile.cpp.o
MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/Comandos/syncronice.cpp.o
MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/build.make
MIA_P1_201801449: CMakeFiles/MIA_P1_201801449.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX executable MIA_P1_201801449"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MIA_P1_201801449.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MIA_P1_201801449.dir/build: MIA_P1_201801449
.PHONY : CMakeFiles/MIA_P1_201801449.dir/build

CMakeFiles/MIA_P1_201801449.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MIA_P1_201801449.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MIA_P1_201801449.dir/clean

CMakeFiles/MIA_P1_201801449.dir/depend:
	cd /home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/magdiel/Escritorio/MIA_P1_201801449 /home/magdiel/Escritorio/MIA_P1_201801449 /home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug /home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug /home/magdiel/Escritorio/MIA_P1_201801449/cmake-build-debug/CMakeFiles/MIA_P1_201801449.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MIA_P1_201801449.dir/depend

