# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = "/home/odroid/TipTilt Control/JustTT"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/odroid/TipTilt Control/JustTT"

# Include any dependencies generated for this target.
include CMakeFiles/wasd.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wasd.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wasd.dir/flags.make

CMakeFiles/wasd.dir/TipTilt.cpp.o: CMakeFiles/wasd.dir/flags.make
CMakeFiles/wasd.dir/TipTilt.cpp.o: TipTilt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/odroid/TipTilt Control/JustTT/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wasd.dir/TipTilt.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wasd.dir/TipTilt.cpp.o -c "/home/odroid/TipTilt Control/JustTT/TipTilt.cpp"

CMakeFiles/wasd.dir/TipTilt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wasd.dir/TipTilt.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/odroid/TipTilt Control/JustTT/TipTilt.cpp" > CMakeFiles/wasd.dir/TipTilt.cpp.i

CMakeFiles/wasd.dir/TipTilt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wasd.dir/TipTilt.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/odroid/TipTilt Control/JustTT/TipTilt.cpp" -o CMakeFiles/wasd.dir/TipTilt.cpp.s

CMakeFiles/wasd.dir/TipTilt.cpp.o.requires:

.PHONY : CMakeFiles/wasd.dir/TipTilt.cpp.o.requires

CMakeFiles/wasd.dir/TipTilt.cpp.o.provides: CMakeFiles/wasd.dir/TipTilt.cpp.o.requires
	$(MAKE) -f CMakeFiles/wasd.dir/build.make CMakeFiles/wasd.dir/TipTilt.cpp.o.provides.build
.PHONY : CMakeFiles/wasd.dir/TipTilt.cpp.o.provides

CMakeFiles/wasd.dir/TipTilt.cpp.o.provides.build: CMakeFiles/wasd.dir/TipTilt.cpp.o


CMakeFiles/wasd.dir/main.cpp.o: CMakeFiles/wasd.dir/flags.make
CMakeFiles/wasd.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/odroid/TipTilt Control/JustTT/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/wasd.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wasd.dir/main.cpp.o -c "/home/odroid/TipTilt Control/JustTT/main.cpp"

CMakeFiles/wasd.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wasd.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/odroid/TipTilt Control/JustTT/main.cpp" > CMakeFiles/wasd.dir/main.cpp.i

CMakeFiles/wasd.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wasd.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/odroid/TipTilt Control/JustTT/main.cpp" -o CMakeFiles/wasd.dir/main.cpp.s

CMakeFiles/wasd.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/wasd.dir/main.cpp.o.requires

CMakeFiles/wasd.dir/main.cpp.o.provides: CMakeFiles/wasd.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/wasd.dir/build.make CMakeFiles/wasd.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/wasd.dir/main.cpp.o.provides

CMakeFiles/wasd.dir/main.cpp.o.provides.build: CMakeFiles/wasd.dir/main.cpp.o


# Object files for target wasd
wasd_OBJECTS = \
"CMakeFiles/wasd.dir/TipTilt.cpp.o" \
"CMakeFiles/wasd.dir/main.cpp.o"

# External object files for target wasd
wasd_EXTERNAL_OBJECTS =

wasd: CMakeFiles/wasd.dir/TipTilt.cpp.o
wasd: CMakeFiles/wasd.dir/main.cpp.o
wasd: CMakeFiles/wasd.dir/build.make
wasd: CMakeFiles/wasd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/odroid/TipTilt Control/JustTT/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable wasd"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wasd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wasd.dir/build: wasd

.PHONY : CMakeFiles/wasd.dir/build

CMakeFiles/wasd.dir/requires: CMakeFiles/wasd.dir/TipTilt.cpp.o.requires
CMakeFiles/wasd.dir/requires: CMakeFiles/wasd.dir/main.cpp.o.requires

.PHONY : CMakeFiles/wasd.dir/requires

CMakeFiles/wasd.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wasd.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wasd.dir/clean

CMakeFiles/wasd.dir/depend:
	cd "/home/odroid/TipTilt Control/JustTT" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/odroid/TipTilt Control/JustTT" "/home/odroid/TipTilt Control/JustTT" "/home/odroid/TipTilt Control/JustTT" "/home/odroid/TipTilt Control/JustTT" "/home/odroid/TipTilt Control/JustTT/CMakeFiles/wasd.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/wasd.dir/depend
