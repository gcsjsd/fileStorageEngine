# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_SOURCE_DIR = /Users/gechang/CLionProjects/filestorage

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/gechang/CLionProjects/filestorage/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/filestorage.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/filestorage.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/filestorage.dir/flags.make

CMakeFiles/filestorage.dir/main.cpp.o: CMakeFiles/filestorage.dir/flags.make
CMakeFiles/filestorage.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gechang/CLionProjects/filestorage/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/filestorage.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/filestorage.dir/main.cpp.o -c /Users/gechang/CLionProjects/filestorage/main.cpp

CMakeFiles/filestorage.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/filestorage.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gechang/CLionProjects/filestorage/main.cpp > CMakeFiles/filestorage.dir/main.cpp.i

CMakeFiles/filestorage.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/filestorage.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gechang/CLionProjects/filestorage/main.cpp -o CMakeFiles/filestorage.dir/main.cpp.s

CMakeFiles/filestorage.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/filestorage.dir/main.cpp.o.requires

CMakeFiles/filestorage.dir/main.cpp.o.provides: CMakeFiles/filestorage.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/filestorage.dir/build.make CMakeFiles/filestorage.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/filestorage.dir/main.cpp.o.provides

CMakeFiles/filestorage.dir/main.cpp.o.provides.build: CMakeFiles/filestorage.dir/main.cpp.o


CMakeFiles/filestorage.dir/file.cpp.o: CMakeFiles/filestorage.dir/flags.make
CMakeFiles/filestorage.dir/file.cpp.o: ../file.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gechang/CLionProjects/filestorage/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/filestorage.dir/file.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/filestorage.dir/file.cpp.o -c /Users/gechang/CLionProjects/filestorage/file.cpp

CMakeFiles/filestorage.dir/file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/filestorage.dir/file.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gechang/CLionProjects/filestorage/file.cpp > CMakeFiles/filestorage.dir/file.cpp.i

CMakeFiles/filestorage.dir/file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/filestorage.dir/file.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gechang/CLionProjects/filestorage/file.cpp -o CMakeFiles/filestorage.dir/file.cpp.s

CMakeFiles/filestorage.dir/file.cpp.o.requires:

.PHONY : CMakeFiles/filestorage.dir/file.cpp.o.requires

CMakeFiles/filestorage.dir/file.cpp.o.provides: CMakeFiles/filestorage.dir/file.cpp.o.requires
	$(MAKE) -f CMakeFiles/filestorage.dir/build.make CMakeFiles/filestorage.dir/file.cpp.o.provides.build
.PHONY : CMakeFiles/filestorage.dir/file.cpp.o.provides

CMakeFiles/filestorage.dir/file.cpp.o.provides.build: CMakeFiles/filestorage.dir/file.cpp.o


# Object files for target filestorage
filestorage_OBJECTS = \
"CMakeFiles/filestorage.dir/main.cpp.o" \
"CMakeFiles/filestorage.dir/file.cpp.o"

# External object files for target filestorage
filestorage_EXTERNAL_OBJECTS =

filestorage: CMakeFiles/filestorage.dir/main.cpp.o
filestorage: CMakeFiles/filestorage.dir/file.cpp.o
filestorage: CMakeFiles/filestorage.dir/build.make
filestorage: CMakeFiles/filestorage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/gechang/CLionProjects/filestorage/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable filestorage"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/filestorage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/filestorage.dir/build: filestorage

.PHONY : CMakeFiles/filestorage.dir/build

CMakeFiles/filestorage.dir/requires: CMakeFiles/filestorage.dir/main.cpp.o.requires
CMakeFiles/filestorage.dir/requires: CMakeFiles/filestorage.dir/file.cpp.o.requires

.PHONY : CMakeFiles/filestorage.dir/requires

CMakeFiles/filestorage.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/filestorage.dir/cmake_clean.cmake
.PHONY : CMakeFiles/filestorage.dir/clean

CMakeFiles/filestorage.dir/depend:
	cd /Users/gechang/CLionProjects/filestorage/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/gechang/CLionProjects/filestorage /Users/gechang/CLionProjects/filestorage /Users/gechang/CLionProjects/filestorage/cmake-build-debug /Users/gechang/CLionProjects/filestorage/cmake-build-debug /Users/gechang/CLionProjects/filestorage/cmake-build-debug/CMakeFiles/filestorage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/filestorage.dir/depend
