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
CMAKE_SOURCE_DIR = /root/unixwlbc/chapter_five/tcpcliserv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/unixwlbc/chapter_five/tcpcliserv/build

# Include any dependencies generated for this target.
include CMakeFiles/tcpcli02.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tcpcli02.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tcpcli02.dir/flags.make

CMakeFiles/tcpcli02.dir/tcpcli02.c.o: CMakeFiles/tcpcli02.dir/flags.make
CMakeFiles/tcpcli02.dir/tcpcli02.c.o: ../tcpcli02.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/unixwlbc/chapter_five/tcpcliserv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tcpcli02.dir/tcpcli02.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tcpcli02.dir/tcpcli02.c.o   -c /root/unixwlbc/chapter_five/tcpcliserv/tcpcli02.c

CMakeFiles/tcpcli02.dir/tcpcli02.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tcpcli02.dir/tcpcli02.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/unixwlbc/chapter_five/tcpcliserv/tcpcli02.c > CMakeFiles/tcpcli02.dir/tcpcli02.c.i

CMakeFiles/tcpcli02.dir/tcpcli02.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tcpcli02.dir/tcpcli02.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/unixwlbc/chapter_five/tcpcliserv/tcpcli02.c -o CMakeFiles/tcpcli02.dir/tcpcli02.c.s

CMakeFiles/tcpcli02.dir/tcpcli02.c.o.requires:

.PHONY : CMakeFiles/tcpcli02.dir/tcpcli02.c.o.requires

CMakeFiles/tcpcli02.dir/tcpcli02.c.o.provides: CMakeFiles/tcpcli02.dir/tcpcli02.c.o.requires
	$(MAKE) -f CMakeFiles/tcpcli02.dir/build.make CMakeFiles/tcpcli02.dir/tcpcli02.c.o.provides.build
.PHONY : CMakeFiles/tcpcli02.dir/tcpcli02.c.o.provides

CMakeFiles/tcpcli02.dir/tcpcli02.c.o.provides.build: CMakeFiles/tcpcli02.dir/tcpcli02.c.o


# Object files for target tcpcli02
tcpcli02_OBJECTS = \
"CMakeFiles/tcpcli02.dir/tcpcli02.c.o"

# External object files for target tcpcli02
tcpcli02_EXTERNAL_OBJECTS =

tcpcli02: CMakeFiles/tcpcli02.dir/tcpcli02.c.o
tcpcli02: CMakeFiles/tcpcli02.dir/build.make
tcpcli02: CMakeFiles/tcpcli02.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/unixwlbc/chapter_five/tcpcliserv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable tcpcli02"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcpcli02.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tcpcli02.dir/build: tcpcli02

.PHONY : CMakeFiles/tcpcli02.dir/build

CMakeFiles/tcpcli02.dir/requires: CMakeFiles/tcpcli02.dir/tcpcli02.c.o.requires

.PHONY : CMakeFiles/tcpcli02.dir/requires

CMakeFiles/tcpcli02.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tcpcli02.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tcpcli02.dir/clean

CMakeFiles/tcpcli02.dir/depend:
	cd /root/unixwlbc/chapter_five/tcpcliserv/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/unixwlbc/chapter_five/tcpcliserv /root/unixwlbc/chapter_five/tcpcliserv /root/unixwlbc/chapter_five/tcpcliserv/build /root/unixwlbc/chapter_five/tcpcliserv/build /root/unixwlbc/chapter_five/tcpcliserv/build/CMakeFiles/tcpcli02.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tcpcli02.dir/depend

