# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /home/oguz/.local/lib/python3.8/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/oguz/.local/lib/python3.8/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/oguz/sensor_data_fusion/sensor_data_fusion/Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/oguz/sensor_data_fusion/sensor_data_fusion/Server/build

# Include any dependencies generated for this target.
include CMakeFiles/SensorServer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SensorServer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SensorServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SensorServer.dir/flags.make

CMakeFiles/SensorServer.dir/src/SensorServer.cpp.o: CMakeFiles/SensorServer.dir/flags.make
CMakeFiles/SensorServer.dir/src/SensorServer.cpp.o: ../src/SensorServer.cpp
CMakeFiles/SensorServer.dir/src/SensorServer.cpp.o: CMakeFiles/SensorServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oguz/sensor_data_fusion/sensor_data_fusion/Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SensorServer.dir/src/SensorServer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SensorServer.dir/src/SensorServer.cpp.o -MF CMakeFiles/SensorServer.dir/src/SensorServer.cpp.o.d -o CMakeFiles/SensorServer.dir/src/SensorServer.cpp.o -c /home/oguz/sensor_data_fusion/sensor_data_fusion/Server/src/SensorServer.cpp

CMakeFiles/SensorServer.dir/src/SensorServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SensorServer.dir/src/SensorServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oguz/sensor_data_fusion/sensor_data_fusion/Server/src/SensorServer.cpp > CMakeFiles/SensorServer.dir/src/SensorServer.cpp.i

CMakeFiles/SensorServer.dir/src/SensorServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SensorServer.dir/src/SensorServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oguz/sensor_data_fusion/sensor_data_fusion/Server/src/SensorServer.cpp -o CMakeFiles/SensorServer.dir/src/SensorServer.cpp.s

# Object files for target SensorServer
SensorServer_OBJECTS = \
"CMakeFiles/SensorServer.dir/src/SensorServer.cpp.o"

# External object files for target SensorServer
SensorServer_EXTERNAL_OBJECTS =

SensorServer: CMakeFiles/SensorServer.dir/src/SensorServer.cpp.o
SensorServer: CMakeFiles/SensorServer.dir/build.make
SensorServer: CMakeFiles/SensorServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oguz/sensor_data_fusion/sensor_data_fusion/Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SensorServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SensorServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SensorServer.dir/build: SensorServer
.PHONY : CMakeFiles/SensorServer.dir/build

CMakeFiles/SensorServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SensorServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SensorServer.dir/clean

CMakeFiles/SensorServer.dir/depend:
	cd /home/oguz/sensor_data_fusion/sensor_data_fusion/Server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oguz/sensor_data_fusion/sensor_data_fusion/Server /home/oguz/sensor_data_fusion/sensor_data_fusion/Server /home/oguz/sensor_data_fusion/sensor_data_fusion/Server/build /home/oguz/sensor_data_fusion/sensor_data_fusion/Server/build /home/oguz/sensor_data_fusion/sensor_data_fusion/Server/build/CMakeFiles/SensorServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SensorServer.dir/depend

