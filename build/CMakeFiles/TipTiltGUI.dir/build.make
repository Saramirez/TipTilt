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
include CMakeFiles/TipTiltGUI.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TipTiltGUI.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TipTiltGUI.dir/flags.make

CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.o: CMakeFiles/TipTiltGUI.dir/flags.make
CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.o: ../src/SystemControl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/odroid/TipTilt Control/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.o -c "/home/odroid/TipTilt Control/src/SystemControl.cpp"

CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/odroid/TipTilt Control/src/SystemControl.cpp" > CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.i

CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/odroid/TipTilt Control/src/SystemControl.cpp" -o CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.s

CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.o.requires:

.PHONY : CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.o.requires

CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.o.provides: CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.o.requires
	$(MAKE) -f CMakeFiles/TipTiltGUI.dir/build.make CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.o.provides.build
.PHONY : CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.o.provides

CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.o.provides.build: CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.o


CMakeFiles/TipTiltGUI.dir/src/gui.cpp.o: CMakeFiles/TipTiltGUI.dir/flags.make
CMakeFiles/TipTiltGUI.dir/src/gui.cpp.o: ../src/gui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/odroid/TipTilt Control/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TipTiltGUI.dir/src/gui.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TipTiltGUI.dir/src/gui.cpp.o -c "/home/odroid/TipTilt Control/src/gui.cpp"

CMakeFiles/TipTiltGUI.dir/src/gui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TipTiltGUI.dir/src/gui.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/odroid/TipTilt Control/src/gui.cpp" > CMakeFiles/TipTiltGUI.dir/src/gui.cpp.i

CMakeFiles/TipTiltGUI.dir/src/gui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TipTiltGUI.dir/src/gui.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/odroid/TipTilt Control/src/gui.cpp" -o CMakeFiles/TipTiltGUI.dir/src/gui.cpp.s

CMakeFiles/TipTiltGUI.dir/src/gui.cpp.o.requires:

.PHONY : CMakeFiles/TipTiltGUI.dir/src/gui.cpp.o.requires

CMakeFiles/TipTiltGUI.dir/src/gui.cpp.o.provides: CMakeFiles/TipTiltGUI.dir/src/gui.cpp.o.requires
	$(MAKE) -f CMakeFiles/TipTiltGUI.dir/build.make CMakeFiles/TipTiltGUI.dir/src/gui.cpp.o.provides.build
.PHONY : CMakeFiles/TipTiltGUI.dir/src/gui.cpp.o.provides

CMakeFiles/TipTiltGUI.dir/src/gui.cpp.o.provides.build: CMakeFiles/TipTiltGUI.dir/src/gui.cpp.o


CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.o: CMakeFiles/TipTiltGUI.dir/flags.make
CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.o: ../src/CameraStreamHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/odroid/TipTilt Control/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.o -c "/home/odroid/TipTilt Control/src/CameraStreamHandler.cpp"

CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/odroid/TipTilt Control/src/CameraStreamHandler.cpp" > CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.i

CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/odroid/TipTilt Control/src/CameraStreamHandler.cpp" -o CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.s

CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.o.requires:

.PHONY : CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.o.requires

CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.o.provides: CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.o.requires
	$(MAKE) -f CMakeFiles/TipTiltGUI.dir/build.make CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.o.provides.build
.PHONY : CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.o.provides

CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.o.provides.build: CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.o


CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.o: CMakeFiles/TipTiltGUI.dir/flags.make
CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.o: ../src/wxStreamPlayer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/odroid/TipTilt Control/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.o -c "/home/odroid/TipTilt Control/src/wxStreamPlayer.cpp"

CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/odroid/TipTilt Control/src/wxStreamPlayer.cpp" > CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.i

CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/odroid/TipTilt Control/src/wxStreamPlayer.cpp" -o CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.s

CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.o.requires:

.PHONY : CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.o.requires

CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.o.provides: CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.o.requires
	$(MAKE) -f CMakeFiles/TipTiltGUI.dir/build.make CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.o.provides.build
.PHONY : CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.o.provides

CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.o.provides.build: CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.o


CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.o: CMakeFiles/TipTiltGUI.dir/flags.make
CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.o: ../src/TipTilt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/odroid/TipTilt Control/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.o -c "/home/odroid/TipTilt Control/src/TipTilt.cpp"

CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/odroid/TipTilt Control/src/TipTilt.cpp" > CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.i

CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/odroid/TipTilt Control/src/TipTilt.cpp" -o CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.s

CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.o.requires:

.PHONY : CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.o.requires

CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.o.provides: CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.o.requires
	$(MAKE) -f CMakeFiles/TipTiltGUI.dir/build.make CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.o.provides.build
.PHONY : CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.o.provides

CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.o.provides.build: CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.o


CMakeFiles/TipTiltGUI.dir/src/main.cpp.o: CMakeFiles/TipTiltGUI.dir/flags.make
CMakeFiles/TipTiltGUI.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/odroid/TipTilt Control/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/TipTiltGUI.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TipTiltGUI.dir/src/main.cpp.o -c "/home/odroid/TipTilt Control/src/main.cpp"

CMakeFiles/TipTiltGUI.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TipTiltGUI.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/odroid/TipTilt Control/src/main.cpp" > CMakeFiles/TipTiltGUI.dir/src/main.cpp.i

CMakeFiles/TipTiltGUI.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TipTiltGUI.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/odroid/TipTilt Control/src/main.cpp" -o CMakeFiles/TipTiltGUI.dir/src/main.cpp.s

CMakeFiles/TipTiltGUI.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/TipTiltGUI.dir/src/main.cpp.o.requires

CMakeFiles/TipTiltGUI.dir/src/main.cpp.o.provides: CMakeFiles/TipTiltGUI.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/TipTiltGUI.dir/build.make CMakeFiles/TipTiltGUI.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/TipTiltGUI.dir/src/main.cpp.o.provides

CMakeFiles/TipTiltGUI.dir/src/main.cpp.o.provides.build: CMakeFiles/TipTiltGUI.dir/src/main.cpp.o


# Object files for target TipTiltGUI
TipTiltGUI_OBJECTS = \
"CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.o" \
"CMakeFiles/TipTiltGUI.dir/src/gui.cpp.o" \
"CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.o" \
"CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.o" \
"CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.o" \
"CMakeFiles/TipTiltGUI.dir/src/main.cpp.o"

# External object files for target TipTiltGUI
TipTiltGUI_EXTERNAL_OBJECTS =

TipTiltGUI: CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.o
TipTiltGUI: CMakeFiles/TipTiltGUI.dir/src/gui.cpp.o
TipTiltGUI: CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.o
TipTiltGUI: CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.o
TipTiltGUI: CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.o
TipTiltGUI: CMakeFiles/TipTiltGUI.dir/src/main.cpp.o
TipTiltGUI: CMakeFiles/TipTiltGUI.dir/build.make
TipTiltGUI: /usr/local/lib/libopencv_shape.so.3.2.0
TipTiltGUI: /usr/local/lib/libopencv_stitching.so.3.2.0
TipTiltGUI: /usr/local/lib/libopencv_superres.so.3.2.0
TipTiltGUI: /usr/local/lib/libopencv_videostab.so.3.2.0
TipTiltGUI: /usr/local/lib/libopencv_objdetect.so.3.2.0
TipTiltGUI: /usr/local/lib/libopencv_calib3d.so.3.2.0
TipTiltGUI: /usr/local/lib/libopencv_features2d.so.3.2.0
TipTiltGUI: /usr/local/lib/libopencv_flann.so.3.2.0
TipTiltGUI: /usr/local/lib/libopencv_highgui.so.3.2.0
TipTiltGUI: /usr/local/lib/libopencv_ml.so.3.2.0
TipTiltGUI: /usr/local/lib/libopencv_photo.so.3.2.0
TipTiltGUI: /usr/local/lib/libopencv_video.so.3.2.0
TipTiltGUI: /usr/local/lib/libopencv_videoio.so.3.2.0
TipTiltGUI: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
TipTiltGUI: /usr/local/lib/libopencv_imgproc.so.3.2.0
TipTiltGUI: /usr/local/lib/libopencv_core.so.3.2.0
TipTiltGUI: CMakeFiles/TipTiltGUI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/odroid/TipTilt Control/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable TipTiltGUI"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TipTiltGUI.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TipTiltGUI.dir/build: TipTiltGUI

.PHONY : CMakeFiles/TipTiltGUI.dir/build

CMakeFiles/TipTiltGUI.dir/requires: CMakeFiles/TipTiltGUI.dir/src/SystemControl.cpp.o.requires
CMakeFiles/TipTiltGUI.dir/requires: CMakeFiles/TipTiltGUI.dir/src/gui.cpp.o.requires
CMakeFiles/TipTiltGUI.dir/requires: CMakeFiles/TipTiltGUI.dir/src/CameraStreamHandler.cpp.o.requires
CMakeFiles/TipTiltGUI.dir/requires: CMakeFiles/TipTiltGUI.dir/src/wxStreamPlayer.cpp.o.requires
CMakeFiles/TipTiltGUI.dir/requires: CMakeFiles/TipTiltGUI.dir/src/TipTilt.cpp.o.requires
CMakeFiles/TipTiltGUI.dir/requires: CMakeFiles/TipTiltGUI.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/TipTiltGUI.dir/requires

CMakeFiles/TipTiltGUI.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TipTiltGUI.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TipTiltGUI.dir/clean

CMakeFiles/TipTiltGUI.dir/depend:
	cd "/home/odroid/TipTilt Control/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/odroid/TipTilt Control" "/home/odroid/TipTilt Control" "/home/odroid/TipTilt Control/build" "/home/odroid/TipTilt Control/build" "/home/odroid/TipTilt Control/build/CMakeFiles/TipTiltGUI.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/TipTiltGUI.dir/depend

