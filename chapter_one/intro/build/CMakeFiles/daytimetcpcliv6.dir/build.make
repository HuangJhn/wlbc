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
CMAKE_SOURCE_DIR = /root/unixwlbc/chapter_one/intro

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/unixwlbc/chapter_one/intro/build

# Include any dependencies generated for this target.
include CMakeFiles/daytimetcpcliv6.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/daytimetcpcliv6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/daytimetcpcliv6.dir/flags.make

CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.o: CMakeFiles/daytimetcpcliv6.dir/flags.make
CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.o: ../daytimetcpcliv6.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/unixwlbc/chapter_one/intro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.o   -c /root/unixwlbc/chapter_one/intro/daytimetcpcliv6.c

CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/unixwlbc/chapter_one/intro/daytimetcpcliv6.c > CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.i

CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/unixwlbc/chapter_one/intro/daytimetcpcliv6.c -o CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.s

CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.o.requires:

.PHONY : CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.o.requires

CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.o.provides: CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.o.requires
	$(MAKE) -f CMakeFiles/daytimetcpcliv6.dir/build.make CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.o.provides.build
.PHONY : CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.o.provides

CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.o.provides.build: CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.o


# Object files for target daytimetcpcliv6
daytimetcpcliv6_OBJECTS = \
"CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.o"

# External object files for target daytimetcpcliv6
daytimetcpcliv6_EXTERNAL_OBJECTS =

daytimetcpcliv6: CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.o
daytimetcpcliv6: CMakeFiles/daytimetcpcliv6.dir/build.make
daytimetcpcliv6: CMakeFiles/daytimetcpcliv6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/unixwlbc/chapter_one/intro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable daytimetcpcliv6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/daytimetcpcliv6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/daytimetcpcliv6.dir/build: daytimetcpcliv6

.PHONY : CMakeFiles/daytimetcpcliv6.dir/build

CMakeFiles/daytimetcpcliv6.dir/requires: CMakeFiles/daytimetcpcliv6.dir/daytimetcpcliv6.c.o.requires

.PHONY : CMakeFiles/daytimetcpcliv6.dir/requires

CMakeFiles/daytimetcpcliv6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/daytimetcpcliv6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/daytimetcpcliv6.dir/clean

CMakeFiles/daytimetcpcliv6.dir/depend:
	cd /root/unixwlbc/chapter_one/intro/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/unixwlbc/chapter_one/intro /root/unixwlbc/chapter_one/intro /root/unixwlbc/chapter_one/intro/build /root/unixwlbc/chapter_one/intro/build /root/unixwlbc/chapter_one/intro/build/CMakeFiles/daytimetcpcliv6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/daytimetcpcliv6.dir/depend

