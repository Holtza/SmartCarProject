# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_SOURCE_DIR = /home/kristiyan/OpenDaVINCI/automotive/miniature/overtaker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kristiyan/OpenDaVINCI/automotive/miniature/overtaker/build

# Include any dependencies generated for this target.
include CMakeFiles/overtaker.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/overtaker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/overtaker.dir/flags.make

CMakeFiles/overtaker.dir/apps/overtaker.cpp.o: CMakeFiles/overtaker.dir/flags.make
CMakeFiles/overtaker.dir/apps/overtaker.cpp.o: ../apps/overtaker.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kristiyan/OpenDaVINCI/automotive/miniature/overtaker/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/overtaker.dir/apps/overtaker.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/overtaker.dir/apps/overtaker.cpp.o -c /home/kristiyan/OpenDaVINCI/automotive/miniature/overtaker/apps/overtaker.cpp

CMakeFiles/overtaker.dir/apps/overtaker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/overtaker.dir/apps/overtaker.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kristiyan/OpenDaVINCI/automotive/miniature/overtaker/apps/overtaker.cpp > CMakeFiles/overtaker.dir/apps/overtaker.cpp.i

CMakeFiles/overtaker.dir/apps/overtaker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/overtaker.dir/apps/overtaker.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kristiyan/OpenDaVINCI/automotive/miniature/overtaker/apps/overtaker.cpp -o CMakeFiles/overtaker.dir/apps/overtaker.cpp.s

CMakeFiles/overtaker.dir/apps/overtaker.cpp.o.requires:
.PHONY : CMakeFiles/overtaker.dir/apps/overtaker.cpp.o.requires

CMakeFiles/overtaker.dir/apps/overtaker.cpp.o.provides: CMakeFiles/overtaker.dir/apps/overtaker.cpp.o.requires
	$(MAKE) -f CMakeFiles/overtaker.dir/build.make CMakeFiles/overtaker.dir/apps/overtaker.cpp.o.provides.build
.PHONY : CMakeFiles/overtaker.dir/apps/overtaker.cpp.o.provides

CMakeFiles/overtaker.dir/apps/overtaker.cpp.o.provides.build: CMakeFiles/overtaker.dir/apps/overtaker.cpp.o

# Object files for target overtaker
overtaker_OBJECTS = \
"CMakeFiles/overtaker.dir/apps/overtaker.cpp.o"

# External object files for target overtaker
overtaker_EXTERNAL_OBJECTS =

overtaker: CMakeFiles/overtaker.dir/apps/overtaker.cpp.o
overtaker: CMakeFiles/overtaker.dir/build.make
overtaker: libovertakerlib-static.a
overtaker: /usr/local/lib/libopendavinci.so
overtaker: /usr/lib/x86_64-linux-gnu/librt.a
overtaker: /usr/local/lib/libautomotivedata.so
overtaker: CMakeFiles/overtaker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable overtaker"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/overtaker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/overtaker.dir/build: overtaker
.PHONY : CMakeFiles/overtaker.dir/build

CMakeFiles/overtaker.dir/requires: CMakeFiles/overtaker.dir/apps/overtaker.cpp.o.requires
.PHONY : CMakeFiles/overtaker.dir/requires

CMakeFiles/overtaker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/overtaker.dir/cmake_clean.cmake
.PHONY : CMakeFiles/overtaker.dir/clean

CMakeFiles/overtaker.dir/depend:
	cd /home/kristiyan/OpenDaVINCI/automotive/miniature/overtaker/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kristiyan/OpenDaVINCI/automotive/miniature/overtaker /home/kristiyan/OpenDaVINCI/automotive/miniature/overtaker /home/kristiyan/OpenDaVINCI/automotive/miniature/overtaker/build /home/kristiyan/OpenDaVINCI/automotive/miniature/overtaker/build /home/kristiyan/OpenDaVINCI/automotive/miniature/overtaker/build/CMakeFiles/overtaker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/overtaker.dir/depend
