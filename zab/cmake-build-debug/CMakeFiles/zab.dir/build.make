# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/osobiehl/CLionProjects/zab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/osobiehl/CLionProjects/zab/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/zab.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/zab.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/zab.dir/flags.make

CMakeFiles/zab.dir/main.c.o: CMakeFiles/zab.dir/flags.make
CMakeFiles/zab.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/osobiehl/CLionProjects/zab/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/zab.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zab.dir/main.c.o   -c /Users/osobiehl/CLionProjects/zab/main.c

CMakeFiles/zab.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zab.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/osobiehl/CLionProjects/zab/main.c > CMakeFiles/zab.dir/main.c.i

CMakeFiles/zab.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zab.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/osobiehl/CLionProjects/zab/main.c -o CMakeFiles/zab.dir/main.c.s

# Object files for target zab
zab_OBJECTS = \
"CMakeFiles/zab.dir/main.c.o"

# External object files for target zab
zab_EXTERNAL_OBJECTS =

zab: CMakeFiles/zab.dir/main.c.o
zab: CMakeFiles/zab.dir/build.make
zab: CMakeFiles/zab.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/osobiehl/CLionProjects/zab/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable zab"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zab.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/zab.dir/build: zab

.PHONY : CMakeFiles/zab.dir/build

CMakeFiles/zab.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/zab.dir/cmake_clean.cmake
.PHONY : CMakeFiles/zab.dir/clean

CMakeFiles/zab.dir/depend:
	cd /Users/osobiehl/CLionProjects/zab/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/osobiehl/CLionProjects/zab /Users/osobiehl/CLionProjects/zab /Users/osobiehl/CLionProjects/zab/cmake-build-debug /Users/osobiehl/CLionProjects/zab/cmake-build-debug /Users/osobiehl/CLionProjects/zab/cmake-build-debug/CMakeFiles/zab.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/zab.dir/depend

