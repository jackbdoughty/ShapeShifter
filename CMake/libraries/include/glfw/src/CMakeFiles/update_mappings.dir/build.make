# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/jdoughty/Documents/Projects/Jack Doughty 2022 NEA/ShapeShifter"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/jdoughty/Documents/Projects/Jack Doughty 2022 NEA/ShapeShifter/CMake"

# Utility rule file for update_mappings.

# Include any custom commands dependencies for this target.
include libraries/include/glfw/src/CMakeFiles/update_mappings.dir/compiler_depend.make

# Include the progress variables for this target.
include libraries/include/glfw/src/CMakeFiles/update_mappings.dir/progress.make

libraries/include/glfw/src/CMakeFiles/update_mappings:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir="/home/jdoughty/Documents/Projects/Jack Doughty 2022 NEA/ShapeShifter/CMake/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Updating gamepad mappings from upstream repository"
	cd "/home/jdoughty/Documents/Projects/Jack Doughty 2022 NEA/ShapeShifter/libraries/include/glfw/src" && /usr/local/bin/cmake -P "/home/jdoughty/Documents/Projects/Jack Doughty 2022 NEA/ShapeShifter/libraries/include/glfw/CMake/GenerateMappings.cmake" mappings.h.in mappings.h

update_mappings: libraries/include/glfw/src/CMakeFiles/update_mappings
update_mappings: libraries/include/glfw/src/CMakeFiles/update_mappings.dir/build.make
.PHONY : update_mappings

# Rule to build all files generated by this target.
libraries/include/glfw/src/CMakeFiles/update_mappings.dir/build: update_mappings
.PHONY : libraries/include/glfw/src/CMakeFiles/update_mappings.dir/build

libraries/include/glfw/src/CMakeFiles/update_mappings.dir/clean:
	cd "/home/jdoughty/Documents/Projects/Jack Doughty 2022 NEA/ShapeShifter/CMake/libraries/include/glfw/src" && $(CMAKE_COMMAND) -P CMakeFiles/update_mappings.dir/cmake_clean.cmake
.PHONY : libraries/include/glfw/src/CMakeFiles/update_mappings.dir/clean

libraries/include/glfw/src/CMakeFiles/update_mappings.dir/depend:
	cd "/home/jdoughty/Documents/Projects/Jack Doughty 2022 NEA/ShapeShifter/CMake" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/jdoughty/Documents/Projects/Jack Doughty 2022 NEA/ShapeShifter" "/home/jdoughty/Documents/Projects/Jack Doughty 2022 NEA/ShapeShifter/libraries/include/glfw/src" "/home/jdoughty/Documents/Projects/Jack Doughty 2022 NEA/ShapeShifter/CMake" "/home/jdoughty/Documents/Projects/Jack Doughty 2022 NEA/ShapeShifter/CMake/libraries/include/glfw/src" "/home/jdoughty/Documents/Projects/Jack Doughty 2022 NEA/ShapeShifter/CMake/libraries/include/glfw/src/CMakeFiles/update_mappings.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : libraries/include/glfw/src/CMakeFiles/update_mappings.dir/depend

