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
CMAKE_SOURCE_DIR = /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build

# Include any dependencies generated for this target.
include lib/memory/CMakeFiles/memory.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/memory/CMakeFiles/memory.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/memory/CMakeFiles/memory.dir/progress.make

# Include the compile flags for this target's objects.
include lib/memory/CMakeFiles/memory.dir/flags.make

lib/memory/CMakeFiles/memory.dir/src/memory.c.o: lib/memory/CMakeFiles/memory.dir/flags.make
lib/memory/CMakeFiles/memory.dir/src/memory.c.o: /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/lib/memory/src/memory.c
lib/memory/CMakeFiles/memory.dir/src/memory.c.o: lib/memory/CMakeFiles/memory.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/memory/CMakeFiles/memory.dir/src/memory.c.o"
	cd /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/lib/memory && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lib/memory/CMakeFiles/memory.dir/src/memory.c.o -MF CMakeFiles/memory.dir/src/memory.c.o.d -o CMakeFiles/memory.dir/src/memory.c.o -c /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/lib/memory/src/memory.c

lib/memory/CMakeFiles/memory.dir/src/memory.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/memory.dir/src/memory.c.i"
	cd /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/lib/memory && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/lib/memory/src/memory.c > CMakeFiles/memory.dir/src/memory.c.i

lib/memory/CMakeFiles/memory.dir/src/memory.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/memory.dir/src/memory.c.s"
	cd /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/lib/memory && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/lib/memory/src/memory.c -o CMakeFiles/memory.dir/src/memory.c.s

# Object files for target memory
memory_OBJECTS = \
"CMakeFiles/memory.dir/src/memory.c.o"

# External object files for target memory
memory_EXTERNAL_OBJECTS =

lib/memory/libmemory.a: lib/memory/CMakeFiles/memory.dir/src/memory.c.o
lib/memory/libmemory.a: lib/memory/CMakeFiles/memory.dir/build.make
lib/memory/libmemory.a: lib/memory/CMakeFiles/memory.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libmemory.a"
	cd /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/lib/memory && $(CMAKE_COMMAND) -P CMakeFiles/memory.dir/cmake_clean_target.cmake
	cd /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/lib/memory && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/memory.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/memory/CMakeFiles/memory.dir/build: lib/memory/libmemory.a
.PHONY : lib/memory/CMakeFiles/memory.dir/build

lib/memory/CMakeFiles/memory.dir/clean:
	cd /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/lib/memory && $(CMAKE_COMMAND) -P CMakeFiles/memory.dir/cmake_clean.cmake
.PHONY : lib/memory/CMakeFiles/memory.dir/clean

lib/memory/CMakeFiles/memory.dir/depend:
	cd /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/lib/memory /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/lib/memory /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/lib/memory/CMakeFiles/memory.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/memory/CMakeFiles/memory.dir/depend

