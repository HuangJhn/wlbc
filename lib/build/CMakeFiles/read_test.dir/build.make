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
CMAKE_SOURCE_DIR = /root/unixwlbc/lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/unixwlbc/lib/build

# Include any dependencies generated for this target.
include CMakeFiles/read_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/read_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/read_test.dir/flags.make

CMakeFiles/read_test.dir/read_test.cpp.o: CMakeFiles/read_test.dir/flags.make
CMakeFiles/read_test.dir/read_test.cpp.o: ../read_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/unixwlbc/lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/read_test.dir/read_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/read_test.dir/read_test.cpp.o -c /root/unixwlbc/lib/read_test.cpp

CMakeFiles/read_test.dir/read_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/read_test.dir/read_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/unixwlbc/lib/read_test.cpp > CMakeFiles/read_test.dir/read_test.cpp.i

CMakeFiles/read_test.dir/read_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/read_test.dir/read_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/unixwlbc/lib/read_test.cpp -o CMakeFiles/read_test.dir/read_test.cpp.s

CMakeFiles/read_test.dir/read_test.cpp.o.requires:

.PHONY : CMakeFiles/read_test.dir/read_test.cpp.o.requires

CMakeFiles/read_test.dir/read_test.cpp.o.provides: CMakeFiles/read_test.dir/read_test.cpp.o.requires
	$(MAKE) -f CMakeFiles/read_test.dir/build.make CMakeFiles/read_test.dir/read_test.cpp.o.provides.build
.PHONY : CMakeFiles/read_test.dir/read_test.cpp.o.provides

CMakeFiles/read_test.dir/read_test.cpp.o.provides.build: CMakeFiles/read_test.dir/read_test.cpp.o


CMakeFiles/read_test.dir/error.cpp.o: CMakeFiles/read_test.dir/flags.make
CMakeFiles/read_test.dir/error.cpp.o: ../error.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/unixwlbc/lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/read_test.dir/error.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/read_test.dir/error.cpp.o -c /root/unixwlbc/lib/error.cpp

CMakeFiles/read_test.dir/error.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/read_test.dir/error.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/unixwlbc/lib/error.cpp > CMakeFiles/read_test.dir/error.cpp.i

CMakeFiles/read_test.dir/error.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/read_test.dir/error.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/unixwlbc/lib/error.cpp -o CMakeFiles/read_test.dir/error.cpp.s

CMakeFiles/read_test.dir/error.cpp.o.requires:

.PHONY : CMakeFiles/read_test.dir/error.cpp.o.requires

CMakeFiles/read_test.dir/error.cpp.o.provides: CMakeFiles/read_test.dir/error.cpp.o.requires
	$(MAKE) -f CMakeFiles/read_test.dir/build.make CMakeFiles/read_test.dir/error.cpp.o.provides.build
.PHONY : CMakeFiles/read_test.dir/error.cpp.o.provides

CMakeFiles/read_test.dir/error.cpp.o.provides.build: CMakeFiles/read_test.dir/error.cpp.o


CMakeFiles/read_test.dir/read.cpp.o: CMakeFiles/read_test.dir/flags.make
CMakeFiles/read_test.dir/read.cpp.o: ../read.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/unixwlbc/lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/read_test.dir/read.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/read_test.dir/read.cpp.o -c /root/unixwlbc/lib/read.cpp

CMakeFiles/read_test.dir/read.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/read_test.dir/read.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/unixwlbc/lib/read.cpp > CMakeFiles/read_test.dir/read.cpp.i

CMakeFiles/read_test.dir/read.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/read_test.dir/read.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/unixwlbc/lib/read.cpp -o CMakeFiles/read_test.dir/read.cpp.s

CMakeFiles/read_test.dir/read.cpp.o.requires:

.PHONY : CMakeFiles/read_test.dir/read.cpp.o.requires

CMakeFiles/read_test.dir/read.cpp.o.provides: CMakeFiles/read_test.dir/read.cpp.o.requires
	$(MAKE) -f CMakeFiles/read_test.dir/build.make CMakeFiles/read_test.dir/read.cpp.o.provides.build
.PHONY : CMakeFiles/read_test.dir/read.cpp.o.provides

CMakeFiles/read_test.dir/read.cpp.o.provides.build: CMakeFiles/read_test.dir/read.cpp.o


# Object files for target read_test
read_test_OBJECTS = \
"CMakeFiles/read_test.dir/read_test.cpp.o" \
"CMakeFiles/read_test.dir/error.cpp.o" \
"CMakeFiles/read_test.dir/read.cpp.o"

# External object files for target read_test
read_test_EXTERNAL_OBJECTS =

read_test: CMakeFiles/read_test.dir/read_test.cpp.o
read_test: CMakeFiles/read_test.dir/error.cpp.o
read_test: CMakeFiles/read_test.dir/read.cpp.o
read_test: CMakeFiles/read_test.dir/build.make
read_test: CMakeFiles/read_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/unixwlbc/lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable read_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/read_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/read_test.dir/build: read_test

.PHONY : CMakeFiles/read_test.dir/build

CMakeFiles/read_test.dir/requires: CMakeFiles/read_test.dir/read_test.cpp.o.requires
CMakeFiles/read_test.dir/requires: CMakeFiles/read_test.dir/error.cpp.o.requires
CMakeFiles/read_test.dir/requires: CMakeFiles/read_test.dir/read.cpp.o.requires

.PHONY : CMakeFiles/read_test.dir/requires

CMakeFiles/read_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/read_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/read_test.dir/clean

CMakeFiles/read_test.dir/depend:
	cd /root/unixwlbc/lib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/unixwlbc/lib /root/unixwlbc/lib /root/unixwlbc/lib/build /root/unixwlbc/lib/build /root/unixwlbc/lib/build/CMakeFiles/read_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/read_test.dir/depend

