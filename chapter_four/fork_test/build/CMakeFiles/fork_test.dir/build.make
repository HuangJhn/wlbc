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
CMAKE_SOURCE_DIR = /root/unixwlbc/chapter_four/fork_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/unixwlbc/chapter_four/fork_test/build

# Include any dependencies generated for this target.
include CMakeFiles/fork_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fork_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fork_test.dir/flags.make

CMakeFiles/fork_test.dir/main.c.o: CMakeFiles/fork_test.dir/flags.make
CMakeFiles/fork_test.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/unixwlbc/chapter_four/fork_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/fork_test.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/fork_test.dir/main.c.o   -c /root/unixwlbc/chapter_four/fork_test/main.c

CMakeFiles/fork_test.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fork_test.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/unixwlbc/chapter_four/fork_test/main.c > CMakeFiles/fork_test.dir/main.c.i

CMakeFiles/fork_test.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fork_test.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/unixwlbc/chapter_four/fork_test/main.c -o CMakeFiles/fork_test.dir/main.c.s

CMakeFiles/fork_test.dir/main.c.o.requires:

.PHONY : CMakeFiles/fork_test.dir/main.c.o.requires

CMakeFiles/fork_test.dir/main.c.o.provides: CMakeFiles/fork_test.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/fork_test.dir/build.make CMakeFiles/fork_test.dir/main.c.o.provides.build
.PHONY : CMakeFiles/fork_test.dir/main.c.o.provides

CMakeFiles/fork_test.dir/main.c.o.provides.build: CMakeFiles/fork_test.dir/main.c.o


# Object files for target fork_test
fork_test_OBJECTS = \
"CMakeFiles/fork_test.dir/main.c.o"

# External object files for target fork_test
fork_test_EXTERNAL_OBJECTS =

fork_test: CMakeFiles/fork_test.dir/main.c.o
fork_test: CMakeFiles/fork_test.dir/build.make
fork_test: CMakeFiles/fork_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/unixwlbc/chapter_four/fork_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable fork_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fork_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fork_test.dir/build: fork_test

.PHONY : CMakeFiles/fork_test.dir/build

CMakeFiles/fork_test.dir/requires: CMakeFiles/fork_test.dir/main.c.o.requires

.PHONY : CMakeFiles/fork_test.dir/requires

CMakeFiles/fork_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fork_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fork_test.dir/clean

CMakeFiles/fork_test.dir/depend:
	cd /root/unixwlbc/chapter_four/fork_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/unixwlbc/chapter_four/fork_test /root/unixwlbc/chapter_four/fork_test /root/unixwlbc/chapter_four/fork_test/build /root/unixwlbc/chapter_four/fork_test/build /root/unixwlbc/chapter_four/fork_test/build/CMakeFiles/fork_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fork_test.dir/depend

