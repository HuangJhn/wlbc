# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/unixwlbc/chapter_three/intro

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/unixwlbc/chapter_three/intro/build

# Include any dependencies generated for this target.
include CMakeFiles/byte.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/byte.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/byte.dir/flags.make

CMakeFiles/byte.dir/byteorder.c.o: CMakeFiles/byte.dir/flags.make
CMakeFiles/byte.dir/byteorder.c.o: ../byteorder.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/unixwlbc/chapter_three/intro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/byte.dir/byteorder.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/byte.dir/byteorder.c.o   -c /root/unixwlbc/chapter_three/intro/byteorder.c

CMakeFiles/byte.dir/byteorder.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/byte.dir/byteorder.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/unixwlbc/chapter_three/intro/byteorder.c > CMakeFiles/byte.dir/byteorder.c.i

CMakeFiles/byte.dir/byteorder.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/byte.dir/byteorder.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/unixwlbc/chapter_three/intro/byteorder.c -o CMakeFiles/byte.dir/byteorder.c.s

CMakeFiles/byte.dir/byteorder.c.o.requires:

.PHONY : CMakeFiles/byte.dir/byteorder.c.o.requires

CMakeFiles/byte.dir/byteorder.c.o.provides: CMakeFiles/byte.dir/byteorder.c.o.requires
	$(MAKE) -f CMakeFiles/byte.dir/build.make CMakeFiles/byte.dir/byteorder.c.o.provides.build
.PHONY : CMakeFiles/byte.dir/byteorder.c.o.provides

CMakeFiles/byte.dir/byteorder.c.o.provides.build: CMakeFiles/byte.dir/byteorder.c.o


# Object files for target byte
byte_OBJECTS = \
"CMakeFiles/byte.dir/byteorder.c.o"

# External object files for target byte
byte_EXTERNAL_OBJECTS =

byte: CMakeFiles/byte.dir/byteorder.c.o
byte: CMakeFiles/byte.dir/build.make
byte: CMakeFiles/byte.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/unixwlbc/chapter_three/intro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable byte"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/byte.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/byte.dir/build: byte

.PHONY : CMakeFiles/byte.dir/build

CMakeFiles/byte.dir/requires: CMakeFiles/byte.dir/byteorder.c.o.requires

.PHONY : CMakeFiles/byte.dir/requires

CMakeFiles/byte.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/byte.dir/cmake_clean.cmake
.PHONY : CMakeFiles/byte.dir/clean

CMakeFiles/byte.dir/depend:
	cd /root/unixwlbc/chapter_three/intro/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/unixwlbc/chapter_three/intro /root/unixwlbc/chapter_three/intro /root/unixwlbc/chapter_three/intro/build /root/unixwlbc/chapter_three/intro/build /root/unixwlbc/chapter_three/intro/build/CMakeFiles/byte.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/byte.dir/depend
