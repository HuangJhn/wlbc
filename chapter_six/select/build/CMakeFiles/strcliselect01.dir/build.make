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
CMAKE_SOURCE_DIR = /root/unixwlbc/chapter_six/select

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/unixwlbc/chapter_six/select/build

# Include any dependencies generated for this target.
include CMakeFiles/strcliselect01.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/strcliselect01.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/strcliselect01.dir/flags.make

CMakeFiles/strcliselect01.dir/strcliselect01.c.o: CMakeFiles/strcliselect01.dir/flags.make
CMakeFiles/strcliselect01.dir/strcliselect01.c.o: ../strcliselect01.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/unixwlbc/chapter_six/select/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/strcliselect01.dir/strcliselect01.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/strcliselect01.dir/strcliselect01.c.o   -c /root/unixwlbc/chapter_six/select/strcliselect01.c

CMakeFiles/strcliselect01.dir/strcliselect01.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/strcliselect01.dir/strcliselect01.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/unixwlbc/chapter_six/select/strcliselect01.c > CMakeFiles/strcliselect01.dir/strcliselect01.c.i

CMakeFiles/strcliselect01.dir/strcliselect01.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/strcliselect01.dir/strcliselect01.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/unixwlbc/chapter_six/select/strcliselect01.c -o CMakeFiles/strcliselect01.dir/strcliselect01.c.s

CMakeFiles/strcliselect01.dir/strcliselect01.c.o.requires:

.PHONY : CMakeFiles/strcliselect01.dir/strcliselect01.c.o.requires

CMakeFiles/strcliselect01.dir/strcliselect01.c.o.provides: CMakeFiles/strcliselect01.dir/strcliselect01.c.o.requires
	$(MAKE) -f CMakeFiles/strcliselect01.dir/build.make CMakeFiles/strcliselect01.dir/strcliselect01.c.o.provides.build
.PHONY : CMakeFiles/strcliselect01.dir/strcliselect01.c.o.provides

CMakeFiles/strcliselect01.dir/strcliselect01.c.o.provides.build: CMakeFiles/strcliselect01.dir/strcliselect01.c.o


# Object files for target strcliselect01
strcliselect01_OBJECTS = \
"CMakeFiles/strcliselect01.dir/strcliselect01.c.o"

# External object files for target strcliselect01
strcliselect01_EXTERNAL_OBJECTS =

strcliselect01: CMakeFiles/strcliselect01.dir/strcliselect01.c.o
strcliselect01: CMakeFiles/strcliselect01.dir/build.make
strcliselect01: CMakeFiles/strcliselect01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/unixwlbc/chapter_six/select/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable strcliselect01"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/strcliselect01.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/strcliselect01.dir/build: strcliselect01

.PHONY : CMakeFiles/strcliselect01.dir/build

CMakeFiles/strcliselect01.dir/requires: CMakeFiles/strcliselect01.dir/strcliselect01.c.o.requires

.PHONY : CMakeFiles/strcliselect01.dir/requires

CMakeFiles/strcliselect01.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/strcliselect01.dir/cmake_clean.cmake
.PHONY : CMakeFiles/strcliselect01.dir/clean

CMakeFiles/strcliselect01.dir/depend:
	cd /root/unixwlbc/chapter_six/select/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/unixwlbc/chapter_six/select /root/unixwlbc/chapter_six/select /root/unixwlbc/chapter_six/select/build /root/unixwlbc/chapter_six/select/build /root/unixwlbc/chapter_six/select/build/CMakeFiles/strcliselect01.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/strcliselect01.dir/depend

