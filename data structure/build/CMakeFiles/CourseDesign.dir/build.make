# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/entropy/Documents/CPP-Practice/CourseDesign/build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/entropy/Documents/CPP-Practice/build

# Include any dependencies generated for this target.
include CMakeFiles/CourseDesign.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CourseDesign.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CourseDesign.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CourseDesign.dir/flags.make

CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp.o: CMakeFiles/CourseDesign.dir/flags.make
CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp.o: /home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp
CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp.o: CMakeFiles/CourseDesign.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/entropy/Documents/CPP-Practice/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp.o -MF CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp.o.d -o CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp.o -c /home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp

CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp > CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp.i

CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp -o CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp.s

CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp.o: CMakeFiles/CourseDesign.dir/flags.make
CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp.o: /home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp
CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp.o: CMakeFiles/CourseDesign.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/entropy/Documents/CPP-Practice/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp.o -MF CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp.o.d -o CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp.o -c /home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp

CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp > CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp.i

CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp -o CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp.s

CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp.o: CMakeFiles/CourseDesign.dir/flags.make
CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp.o: /home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp
CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp.o: CMakeFiles/CourseDesign.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/entropy/Documents/CPP-Practice/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp.o -MF CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp.o.d -o CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp.o -c /home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp

CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp > CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp.i

CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp -o CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp.s

# Object files for target CourseDesign
CourseDesign_OBJECTS = \
"CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp.o" \
"CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp.o" \
"CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp.o"

# External object files for target CourseDesign
CourseDesign_EXTERNAL_OBJECTS =

CourseDesign: CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/main.cpp.o
CourseDesign: CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/rb_tree.cpp.o
CourseDesign: CMakeFiles/CourseDesign.dir/home/entropy/Documents/CPP-Practice/CourseDesign/src/user_data.cpp.o
CourseDesign: CMakeFiles/CourseDesign.dir/build.make
CourseDesign: CMakeFiles/CourseDesign.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/entropy/Documents/CPP-Practice/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable CourseDesign"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CourseDesign.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CourseDesign.dir/build: CourseDesign
.PHONY : CMakeFiles/CourseDesign.dir/build

CMakeFiles/CourseDesign.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CourseDesign.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CourseDesign.dir/clean

CMakeFiles/CourseDesign.dir/depend:
	cd /home/entropy/Documents/CPP-Practice/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/entropy/Documents/CPP-Practice/CourseDesign/build /home/entropy/Documents/CPP-Practice/CourseDesign/build /home/entropy/Documents/CPP-Practice/build /home/entropy/Documents/CPP-Practice/build /home/entropy/Documents/CPP-Practice/build/CMakeFiles/CourseDesign.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CourseDesign.dir/depend
