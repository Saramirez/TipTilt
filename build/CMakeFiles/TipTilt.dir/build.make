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
CMAKE_SOURCE_DIR = "/home/odroid/TipTilt Control"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/odroid/TipTilt Control/build"

# Include any dependencies generated for this target.
include CMakeFiles/TipTilt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TipTilt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TipTilt.dir/flags.make

CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.o: CMakeFiles/TipTilt.dir/flags.make
CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.o: ../src/CameraStreamHandling.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/odroid/TipTilt Control/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.o -c "/home/odroid/TipTilt Control/src/CameraStreamHandling.cpp"

CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/odroid/TipTilt Control/src/CameraStreamHandling.cpp" > CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.i

CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/odroid/TipTilt Control/src/CameraStreamHandling.cpp" -o CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.s

CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.o.requires:

.PHONY : CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.o.requires

CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.o.provides: CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.o.requires
	$(MAKE) -f CMakeFiles/TipTilt.dir/build.make CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.o.provides.build
.PHONY : CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.o.provides

CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.o.provides.build: CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.o


CMakeFiles/TipTilt.dir/src/TipTilt.cpp.o: CMakeFiles/TipTilt.dir/flags.make
CMakeFiles/TipTilt.dir/src/TipTilt.cpp.o: ../src/TipTilt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/odroid/TipTilt Control/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TipTilt.dir/src/TipTilt.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TipTilt.dir/src/TipTilt.cpp.o -c "/home/odroid/TipTilt Control/src/TipTilt.cpp"

CMakeFiles/TipTilt.dir/src/TipTilt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TipTilt.dir/src/TipTilt.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/odroid/TipTilt Control/src/TipTilt.cpp" > CMakeFiles/TipTilt.dir/src/TipTilt.cpp.i

CMakeFiles/TipTilt.dir/src/TipTilt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TipTilt.dir/src/TipTilt.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/odroid/TipTilt Control/src/TipTilt.cpp" -o CMakeFiles/TipTilt.dir/src/TipTilt.cpp.s

CMakeFiles/TipTilt.dir/src/TipTilt.cpp.o.requires:

.PHONY : CMakeFiles/TipTilt.dir/src/TipTilt.cpp.o.requires

CMakeFiles/TipTilt.dir/src/TipTilt.cpp.o.provides: CMakeFiles/TipTilt.dir/src/TipTilt.cpp.o.requires
	$(MAKE) -f CMakeFiles/TipTilt.dir/build.make CMakeFiles/TipTilt.dir/src/TipTilt.cpp.o.provides.build
.PHONY : CMakeFiles/TipTilt.dir/src/TipTilt.cpp.o.provides

CMakeFiles/TipTilt.dir/src/TipTilt.cpp.o.provides.build: CMakeFiles/TipTilt.dir/src/TipTilt.cpp.o


CMakeFiles/TipTilt.dir/src/main.cpp.o: CMakeFiles/TipTilt.dir/flags.make
CMakeFiles/TipTilt.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/odroid/TipTilt Control/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TipTilt.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TipTilt.dir/src/main.cpp.o -c "/home/odroid/TipTilt Control/src/main.cpp"

CMakeFiles/TipTilt.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TipTilt.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/odroid/TipTilt Control/src/main.cpp" > CMakeFiles/TipTilt.dir/src/main.cpp.i

CMakeFiles/TipTilt.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TipTilt.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/odroid/TipTilt Control/src/main.cpp" -o CMakeFiles/TipTilt.dir/src/main.cpp.s

CMakeFiles/TipTilt.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/TipTilt.dir/src/main.cpp.o.requires

CMakeFiles/TipTilt.dir/src/main.cpp.o.provides: CMakeFiles/TipTilt.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/TipTilt.dir/build.make CMakeFiles/TipTilt.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/TipTilt.dir/src/main.cpp.o.provides

CMakeFiles/TipTilt.dir/src/main.cpp.o.provides.build: CMakeFiles/TipTilt.dir/src/main.cpp.o


# Object files for target TipTilt
TipTilt_OBJECTS = \
"CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.o" \
"CMakeFiles/TipTilt.dir/src/TipTilt.cpp.o" \
"CMakeFiles/TipTilt.dir/src/main.cpp.o"

# External object files for target TipTilt
TipTilt_EXTERNAL_OBJECTS =

TipTilt: CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.o
TipTilt: CMakeFiles/TipTilt.dir/src/TipTilt.cpp.o
TipTilt: CMakeFiles/TipTilt.dir/src/main.cpp.o
TipTilt: CMakeFiles/TipTilt.dir/build.make
TipTilt: /usr/local/lib/libopencv_shape.so.3.2.0
TipTilt: /usr/local/lib/libopencv_stitching.so.3.2.0
TipTilt: /usr/local/lib/libopencv_superres.so.3.2.0
TipTilt: /usr/local/lib/libopencv_videostab.so.3.2.0
TipTilt: /usr/local/lib/libopencv_objdetect.so.3.2.0
TipTilt: /usr/local/lib/libopencv_calib3d.so.3.2.0
TipTilt: /usr/local/lib/libopencv_features2d.so.3.2.0
TipTilt: /usr/local/lib/libopencv_flann.so.3.2.0
TipTilt: /usr/local/lib/libopencv_highgui.so.3.2.0
TipTilt: /usr/local/lib/libopencv_ml.so.3.2.0
TipTilt: /usr/local/lib/libopencv_photo.so.3.2.0
TipTilt: /usr/local/lib/libopencv_video.so.3.2.0
TipTilt: /usr/local/lib/libopencv_videoio.so.3.2.0
TipTilt: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
TipTilt: /usr/local/lib/libopencv_imgproc.so.3.2.0
TipTilt: /usr/local/lib/libopencv_core.so.3.2.0
TipTilt: CMakeFiles/TipTilt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/odroid/TipTilt Control/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable TipTilt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TipTilt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TipTilt.dir/build: TipTilt

.PHONY : CMakeFiles/TipTilt.dir/build

CMakeFiles/TipTilt.dir/requires: CMakeFiles/TipTilt.dir/src/CameraStreamHandling.cpp.o.requires
CMakeFiles/TipTilt.dir/requires: CMakeFiles/TipTilt.dir/src/TipTilt.cpp.o.requires
CMakeFiles/TipTilt.dir/requires: CMakeFiles/TipTilt.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/TipTilt.dir/requires

CMakeFiles/TipTilt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TipTilt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TipTilt.dir/clean

CMakeFiles/TipTilt.dir/depend:
	cd "/home/odroid/TipTilt Control/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/odroid/TipTilt Control" "/home/odroid/TipTilt Control" "/home/odroid/TipTilt Control/build" "/home/odroid/TipTilt Control/build" "/home/odroid/TipTilt Control/build/CMakeFiles/TipTilt.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/TipTilt.dir/depend

