# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/niklaus/Desktop/graphics/clion/CG1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/niklaus/Desktop/graphics/clion/CG1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CG1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CG1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CG1.dir/flags.make

CMakeFiles/CG1.dir/main.cpp.o: CMakeFiles/CG1.dir/flags.make
CMakeFiles/CG1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/niklaus/Desktop/graphics/clion/CG1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CG1.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CG1.dir/main.cpp.o -c /Users/niklaus/Desktop/graphics/clion/CG1/main.cpp

CMakeFiles/CG1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CG1.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/niklaus/Desktop/graphics/clion/CG1/main.cpp > CMakeFiles/CG1.dir/main.cpp.i

CMakeFiles/CG1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CG1.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/niklaus/Desktop/graphics/clion/CG1/main.cpp -o CMakeFiles/CG1.dir/main.cpp.s

CMakeFiles/CG1.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/CG1.dir/main.cpp.o.requires

CMakeFiles/CG1.dir/main.cpp.o.provides: CMakeFiles/CG1.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/CG1.dir/build.make CMakeFiles/CG1.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/CG1.dir/main.cpp.o.provides

CMakeFiles/CG1.dir/main.cpp.o.provides.build: CMakeFiles/CG1.dir/main.cpp.o


# Object files for target CG1
CG1_OBJECTS = \
"CMakeFiles/CG1.dir/main.cpp.o"

# External object files for target CG1
CG1_EXTERNAL_OBJECTS =

CG1: CMakeFiles/CG1.dir/main.cpp.o
CG1: CMakeFiles/CG1.dir/build.make
CG1: /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib
CG1: /usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.dylib
CG1: CMakeFiles/CG1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/niklaus/Desktop/graphics/clion/CG1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable CG1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CG1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CG1.dir/build: CG1

.PHONY : CMakeFiles/CG1.dir/build

CMakeFiles/CG1.dir/requires: CMakeFiles/CG1.dir/main.cpp.o.requires

.PHONY : CMakeFiles/CG1.dir/requires

CMakeFiles/CG1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CG1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CG1.dir/clean

CMakeFiles/CG1.dir/depend:
	cd /Users/niklaus/Desktop/graphics/clion/CG1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/niklaus/Desktop/graphics/clion/CG1 /Users/niklaus/Desktop/graphics/clion/CG1 /Users/niklaus/Desktop/graphics/clion/CG1/cmake-build-debug /Users/niklaus/Desktop/graphics/clion/CG1/cmake-build-debug /Users/niklaus/Desktop/graphics/clion/CG1/cmake-build-debug/CMakeFiles/CG1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CG1.dir/depend

