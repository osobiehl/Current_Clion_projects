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
include CMakeFiles/rpn_stack.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rpn_stack.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rpn_stack.dir/flags.make

CMakeFiles/rpn_stack.dir/rpn_stack.c.o: CMakeFiles/rpn_stack.dir/flags.make
CMakeFiles/rpn_stack.dir/rpn_stack.c.o: ../rpn_stack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/osobiehl/CLionProjects/SADS-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/rpn_stack.dir/rpn_stack.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/rpn_stack.dir/rpn_stack.c.o   -c /home/osobiehl/CLionProjects/SADS-1/rpn_stack.c

CMakeFiles/rpn_stack.dir/rpn_stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rpn_stack.dir/rpn_stack.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/osobiehl/CLionProjects/SADS-1/rpn_stack.c > CMakeFiles/rpn_stack.dir/rpn_stack.c.i

CMakeFiles/rpn_stack.dir/rpn_stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rpn_stack.dir/rpn_stack.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/osobiehl/CLionProjects/SADS-1/rpn_stack.c -o CMakeFiles/rpn_stack.dir/rpn_stack.c.s

# Object files for target rpn_stack
rpn_stack_OBJECTS = \
"CMakeFiles/rpn_stack.dir/rpn_stack.c.o"

# External object files for target rpn_stack
rpn_stack_EXTERNAL_OBJECTS =

librpn_stack.a: CMakeFiles/rpn_stack.dir/rpn_stack.c.o
librpn_stack.a: CMakeFiles/rpn_stack.dir/build.make
librpn_stack.a: CMakeFiles/rpn_stack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/osobiehl/CLionProjects/SADS-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library librpn_stack.a"
	$(CMAKE_COMMAND) -P CMakeFiles/rpn_stack.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rpn_stack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rpn_stack.dir/build: librpn_stack.a

.PHONY : CMakeFiles/rpn_stack.dir/build

CMakeFiles/rpn_stack.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rpn_stack.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rpn_stack.dir/clean

CMakeFiles/rpn_stack.dir/depend:
	cd /home/osobiehl/CLionProjects/SADS-1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/osobiehl/CLionProjects/SADS-1 /home/osobiehl/CLionProjects/SADS-1 /home/osobiehl/CLionProjects/SADS-1/cmake-build-debug /home/osobiehl/CLionProjects/SADS-1/cmake-build-debug /home/osobiehl/CLionProjects/SADS-1/cmake-build-debug/CMakeFiles/rpn_stack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rpn_stack.dir/depend
