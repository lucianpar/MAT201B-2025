# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lucian/Desktop/201B/allolib_playground

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lucian/Desktop/201B/allolib_playground/Lucian201B

# Include any dependencies generated for this target.
include CMakeFiles/simulation_gravityWell.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/simulation_gravityWell.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/simulation_gravityWell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simulation_gravityWell.dir/flags.make

CMakeFiles/simulation_gravityWell.dir/cookbook/simulation/gravityWell.cpp.o: CMakeFiles/simulation_gravityWell.dir/flags.make
CMakeFiles/simulation_gravityWell.dir/cookbook/simulation/gravityWell.cpp.o: /Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/gravityWell.cpp
CMakeFiles/simulation_gravityWell.dir/cookbook/simulation/gravityWell.cpp.o: CMakeFiles/simulation_gravityWell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lucian/Desktop/201B/allolib_playground/Lucian201B/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/simulation_gravityWell.dir/cookbook/simulation/gravityWell.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/simulation_gravityWell.dir/cookbook/simulation/gravityWell.cpp.o -MF CMakeFiles/simulation_gravityWell.dir/cookbook/simulation/gravityWell.cpp.o.d -o CMakeFiles/simulation_gravityWell.dir/cookbook/simulation/gravityWell.cpp.o -c /Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/gravityWell.cpp

CMakeFiles/simulation_gravityWell.dir/cookbook/simulation/gravityWell.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/simulation_gravityWell.dir/cookbook/simulation/gravityWell.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/gravityWell.cpp > CMakeFiles/simulation_gravityWell.dir/cookbook/simulation/gravityWell.cpp.i

CMakeFiles/simulation_gravityWell.dir/cookbook/simulation/gravityWell.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/simulation_gravityWell.dir/cookbook/simulation/gravityWell.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/gravityWell.cpp -o CMakeFiles/simulation_gravityWell.dir/cookbook/simulation/gravityWell.cpp.s

# Object files for target simulation_gravityWell
simulation_gravityWell_OBJECTS = \
"CMakeFiles/simulation_gravityWell.dir/cookbook/simulation/gravityWell.cpp.o"

# External object files for target simulation_gravityWell
simulation_gravityWell_EXTERNAL_OBJECTS =

/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: CMakeFiles/simulation_gravityWell.dir/cookbook/simulation/gravityWell.cpp.o
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: CMakeFiles/simulation_gravityWell.dir/build.make
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /Users/lucian/Desktop/201B/allolib_playground/allolib/build/Release/libal.a
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /Users/lucian/Desktop/201B/allolib_playground/allolib/build/al_ext/assets3d/libal_assets3d.a
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /Users/lucian/Desktop/201B/allolib_playground/allolib/build/al_ext/openvr/libal_openvr.a
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /Users/lucian/Desktop/201B/allolib_playground/allolib/build/al_ext/soundfile/libal_soundfile.a
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /Users/lucian/Desktop/201B/allolib_playground/allolib/build/al_ext/statedistribution/libal_statedistribution.a
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /opt/homebrew/lib/libassimp.dylib
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /Users/lucian/Desktop/201B/allolib_playground/allolib/build/Release/libal.a
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /Users/lucian/Desktop/201B/allolib_playground/allolib/build/Release/external/rtaudio/librtaudio.a
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /Users/lucian/Desktop/201B/allolib_playground/allolib/build/Release/external/Gamma/lib/libGamma.a
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /opt/homebrew/lib/libsndfile.dylib
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /Users/lucian/Desktop/201B/allolib_playground/allolib/build/Release/external/glfw/src/libglfw3.a
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /Users/lucian/Desktop/201B/allolib_playground/allolib/build/Release/external/glad/libglad.a
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /Users/lucian/Desktop/201B/allolib_playground/allolib/build/Release/external/rtmidi/librtmidi.a
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /Users/lucian/Desktop/201B/allolib_playground/allolib/build/Release/external/libimgui.a
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /Users/lucian/Desktop/201B/allolib_playground/allolib/build/Release/external/liboscpack.a
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: /Users/lucian/Desktop/201B/allolib_playground/allolib/build/Release/external/libserial.a
/Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell: CMakeFiles/simulation_gravityWell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/lucian/Desktop/201B/allolib_playground/Lucian201B/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simulation_gravityWell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simulation_gravityWell.dir/build: /Users/lucian/Desktop/201B/allolib_playground/cookbook/simulation/bin/simulation_gravityWell
.PHONY : CMakeFiles/simulation_gravityWell.dir/build

CMakeFiles/simulation_gravityWell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/simulation_gravityWell.dir/cmake_clean.cmake
.PHONY : CMakeFiles/simulation_gravityWell.dir/clean

CMakeFiles/simulation_gravityWell.dir/depend:
	cd /Users/lucian/Desktop/201B/allolib_playground/Lucian201B && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lucian/Desktop/201B/allolib_playground /Users/lucian/Desktop/201B/allolib_playground /Users/lucian/Desktop/201B/allolib_playground/Lucian201B /Users/lucian/Desktop/201B/allolib_playground/Lucian201B /Users/lucian/Desktop/201B/allolib_playground/Lucian201B/CMakeFiles/simulation_gravityWell.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/simulation_gravityWell.dir/depend

