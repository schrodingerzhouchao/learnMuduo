# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/tests/build

# Include any dependencies generated for this target.
include CMakeFiles/blockingqueue_bench.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/blockingqueue_bench.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/blockingqueue_bench.dir/flags.make

CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.o: CMakeFiles/blockingqueue_bench.dir/flags.make
CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.o: ../BlockingQueue_bench.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/tests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.o -c /home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/tests/BlockingQueue_bench.cpp

CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/tests/BlockingQueue_bench.cpp > CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.i

CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/tests/BlockingQueue_bench.cpp -o CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.s

CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.o.requires:

.PHONY : CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.o.requires

CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.o.provides: CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.o.requires
	$(MAKE) -f CMakeFiles/blockingqueue_bench.dir/build.make CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.o.provides.build
.PHONY : CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.o.provides

CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.o.provides.build: CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.o


# Object files for target blockingqueue_bench
blockingqueue_bench_OBJECTS = \
"CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.o"

# External object files for target blockingqueue_bench
blockingqueue_bench_EXTERNAL_OBJECTS =

blockingqueue_bench: CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.o
blockingqueue_bench: CMakeFiles/blockingqueue_bench.dir/build.make
blockingqueue_bench: CMakeFiles/blockingqueue_bench.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/tests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable blockingqueue_bench"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/blockingqueue_bench.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/blockingqueue_bench.dir/build: blockingqueue_bench

.PHONY : CMakeFiles/blockingqueue_bench.dir/build

CMakeFiles/blockingqueue_bench.dir/requires: CMakeFiles/blockingqueue_bench.dir/BlockingQueue_bench.cpp.o.requires

.PHONY : CMakeFiles/blockingqueue_bench.dir/requires

CMakeFiles/blockingqueue_bench.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/blockingqueue_bench.dir/cmake_clean.cmake
.PHONY : CMakeFiles/blockingqueue_bench.dir/clean

CMakeFiles/blockingqueue_bench.dir/depend:
	cd /home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/tests/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/tests /home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/tests /home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/tests/build /home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/tests/build /home/chaos/cppwork/muduo_learn/learnMuduo/muduo/base/tests/build/CMakeFiles/blockingqueue_bench.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/blockingqueue_bench.dir/depend

