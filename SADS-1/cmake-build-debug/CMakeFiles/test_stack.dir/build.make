# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/osobiehl/Downloads/clion-2020.2.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/osobiehl/Downloads/clion-2020.2.1/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/osobiehl/CLionProjects/SADS-1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/osobiehl/CLionProjects/SADS-1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/test_stack.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_stack.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_stack.dir/flags.make

CMakeFiles/test_stack.dir/test/test_stack.c.o: CMakeFiles/test_stack.dir/flags.make
CMakeFiles/test_stack.dir/test/test_stack.c.o: ../test/test_stack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/osobiehl/CLionProjects/SADS-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/test_stack.dir/test/test_stack.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_stack.dir/test/test_stack.c.o   -c /home/osobiehl/CLionProjects/SADS-1/test/test_stack.c

CMakeFiles/test_stack.dir/test/test_stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_stack.dir/test/test_stack.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/osobiehl/CLionProjects/SADS-1/test/test_stack.c > CMakeFiles/test_stack.dir/test/test_stack.c.i

CMakeFiles/test_stack.dir/test/test_stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_stack.dir/test/test_stack.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/osobiehl/CLionProjects/SADS-1/test/test_stack.c -o CMakeFiles/test_stack.dir/test/test_stack.c.s

# Object files for target test_stack
test_stack_OBJECTS = \
"CMakeFiles/test_stack.dir/test/test_stack.c.o"

# External object files for target test_stack
test_stack_EXTERNAL_OBJECTS =

test_stack: CMakeFiles/test_stack.dir/test/test_stack.c.o
test_stack: CMakeFiles/test_stack.dir/build.make
test_stack: librpn_stack.a
test_stack: librpn.a
test_stack: libinfix.a
test_stack: CMakeFiles/test_stack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/osobiehl/CLionProjects/SADS-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_stack"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_stack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_stack.dir/build: test_stack

.PHONY : CMakeFiles/test_stack.dir/build

CMakeFiles/test_stack.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_stack.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_stack.dir/clean

CMakeFiles/test_stack.dir/depend:
	cd /home/osobiehl/CLionProjects/SADS-1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/osobiehl/CLionProjects/SADS-1 /home/osobiehl/CLionProjects/SADS-1 /home/osobiehl/CLionProjects/SADS-1/cmake-build-debug /home/osobiehl/CLionProjects/SADS-1/cmake-build-debug /home/osobiehl/CLionProjects/SADS-1/cmake-build-debug/CMakeFiles/test_stack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_stack.dir/depend

