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
include CMakeFiles/SADS_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SADS_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SADS_1.dir/flags.make

CMakeFiles/SADS_1.dir/main.c.o: CMakeFiles/SADS_1.dir/flags.make
CMakeFiles/SADS_1.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/osobiehl/CLionProjects/SADS-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SADS_1.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SADS_1.dir/main.c.o   -c /home/osobiehl/CLionProjects/SADS-1/main.c

CMakeFiles/SADS_1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SADS_1.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/osobiehl/CLionProjects/SADS-1/main.c > CMakeFiles/SADS_1.dir/main.c.i

CMakeFiles/SADS_1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SADS_1.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/osobiehl/CLionProjects/SADS-1/main.c -o CMakeFiles/SADS_1.dir/main.c.s

CMakeFiles/SADS_1.dir/rpn.c.o: CMakeFiles/SADS_1.dir/flags.make
CMakeFiles/SADS_1.dir/rpn.c.o: ../rpn.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/osobiehl/CLionProjects/SADS-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/SADS_1.dir/rpn.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SADS_1.dir/rpn.c.o   -c /home/osobiehl/CLionProjects/SADS-1/rpn.c

CMakeFiles/SADS_1.dir/rpn.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SADS_1.dir/rpn.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/osobiehl/CLionProjects/SADS-1/rpn.c > CMakeFiles/SADS_1.dir/rpn.c.i

CMakeFiles/SADS_1.dir/rpn.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SADS_1.dir/rpn.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/osobiehl/CLionProjects/SADS-1/rpn.c -o CMakeFiles/SADS_1.dir/rpn.c.s

CMakeFiles/SADS_1.dir/rpn_stack.c.o: CMakeFiles/SADS_1.dir/flags.make
CMakeFiles/SADS_1.dir/rpn_stack.c.o: ../rpn_stack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/osobiehl/CLionProjects/SADS-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/SADS_1.dir/rpn_stack.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SADS_1.dir/rpn_stack.c.o   -c /home/osobiehl/CLionProjects/SADS-1/rpn_stack.c

CMakeFiles/SADS_1.dir/rpn_stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SADS_1.dir/rpn_stack.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/osobiehl/CLionProjects/SADS-1/rpn_stack.c > CMakeFiles/SADS_1.dir/rpn_stack.c.i

CMakeFiles/SADS_1.dir/rpn_stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SADS_1.dir/rpn_stack.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/osobiehl/CLionProjects/SADS-1/rpn_stack.c -o CMakeFiles/SADS_1.dir/rpn_stack.c.s

# Object files for target SADS_1
SADS_1_OBJECTS = \
"CMakeFiles/SADS_1.dir/main.c.o" \
"CMakeFiles/SADS_1.dir/rpn.c.o" \
"CMakeFiles/SADS_1.dir/rpn_stack.c.o"

# External object files for target SADS_1
SADS_1_EXTERNAL_OBJECTS =

SADS_1: CMakeFiles/SADS_1.dir/main.c.o
SADS_1: CMakeFiles/SADS_1.dir/rpn.c.o
SADS_1: CMakeFiles/SADS_1.dir/rpn_stack.c.o
SADS_1: CMakeFiles/SADS_1.dir/build.make
SADS_1: CMakeFiles/SADS_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/osobiehl/CLionProjects/SADS-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable SADS_1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SADS_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SADS_1.dir/build: SADS_1

.PHONY : CMakeFiles/SADS_1.dir/build

CMakeFiles/SADS_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SADS_1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SADS_1.dir/clean

CMakeFiles/SADS_1.dir/depend:
	cd /home/osobiehl/CLionProjects/SADS-1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/osobiehl/CLionProjects/SADS-1 /home/osobiehl/CLionProjects/SADS-1 /home/osobiehl/CLionProjects/SADS-1/cmake-build-debug /home/osobiehl/CLionProjects/SADS-1/cmake-build-debug /home/osobiehl/CLionProjects/SADS-1/cmake-build-debug/CMakeFiles/SADS_1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SADS_1.dir/depend
