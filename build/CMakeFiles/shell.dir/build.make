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
include CMakeFiles/shell.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/shell.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/shell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shell.dir/flags.make

CMakeFiles/shell.dir/src/commands.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/commands.c.o: /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/commands.c
CMakeFiles/shell.dir/src/commands.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/shell.dir/src/commands.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/src/commands.c.o -MF CMakeFiles/shell.dir/src/commands.c.o.d -o CMakeFiles/shell.dir/src/commands.c.o -c /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/commands.c

CMakeFiles/shell.dir/src/commands.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/commands.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/commands.c > CMakeFiles/shell.dir/src/commands.c.i

CMakeFiles/shell.dir/src/commands.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/commands.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/commands.c -o CMakeFiles/shell.dir/src/commands.c.s

CMakeFiles/shell.dir/src/file_finder.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/file_finder.c.o: /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/file_finder.c
CMakeFiles/shell.dir/src/file_finder.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/shell.dir/src/file_finder.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/src/file_finder.c.o -MF CMakeFiles/shell.dir/src/file_finder.c.o.d -o CMakeFiles/shell.dir/src/file_finder.c.o -c /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/file_finder.c

CMakeFiles/shell.dir/src/file_finder.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/file_finder.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/file_finder.c > CMakeFiles/shell.dir/src/file_finder.c.i

CMakeFiles/shell.dir/src/file_finder.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/file_finder.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/file_finder.c -o CMakeFiles/shell.dir/src/file_finder.c.s

CMakeFiles/shell.dir/src/main.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/main.c.o: /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/main.c
CMakeFiles/shell.dir/src/main.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/shell.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/src/main.c.o -MF CMakeFiles/shell.dir/src/main.c.o.d -o CMakeFiles/shell.dir/src/main.c.o -c /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/main.c

CMakeFiles/shell.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/main.c > CMakeFiles/shell.dir/src/main.c.i

CMakeFiles/shell.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/main.c -o CMakeFiles/shell.dir/src/main.c.s

CMakeFiles/shell.dir/src/monitorHandle.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/monitorHandle.c.o: /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/monitorHandle.c
CMakeFiles/shell.dir/src/monitorHandle.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/shell.dir/src/monitorHandle.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/src/monitorHandle.c.o -MF CMakeFiles/shell.dir/src/monitorHandle.c.o.d -o CMakeFiles/shell.dir/src/monitorHandle.c.o -c /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/monitorHandle.c

CMakeFiles/shell.dir/src/monitorHandle.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/monitorHandle.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/monitorHandle.c > CMakeFiles/shell.dir/src/monitorHandle.c.i

CMakeFiles/shell.dir/src/monitorHandle.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/monitorHandle.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/monitorHandle.c -o CMakeFiles/shell.dir/src/monitorHandle.c.s

CMakeFiles/shell.dir/src/parser.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/parser.c.o: /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/parser.c
CMakeFiles/shell.dir/src/parser.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/shell.dir/src/parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/src/parser.c.o -MF CMakeFiles/shell.dir/src/parser.c.o.d -o CMakeFiles/shell.dir/src/parser.c.o -c /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/parser.c

CMakeFiles/shell.dir/src/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/parser.c > CMakeFiles/shell.dir/src/parser.c.i

CMakeFiles/shell.dir/src/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/parser.c -o CMakeFiles/shell.dir/src/parser.c.s

CMakeFiles/shell.dir/src/pipes.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/pipes.c.o: /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/pipes.c
CMakeFiles/shell.dir/src/pipes.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/shell.dir/src/pipes.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/src/pipes.c.o -MF CMakeFiles/shell.dir/src/pipes.c.o.d -o CMakeFiles/shell.dir/src/pipes.c.o -c /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/pipes.c

CMakeFiles/shell.dir/src/pipes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/pipes.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/pipes.c > CMakeFiles/shell.dir/src/pipes.c.i

CMakeFiles/shell.dir/src/pipes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/pipes.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/pipes.c -o CMakeFiles/shell.dir/src/pipes.c.s

CMakeFiles/shell.dir/src/prompt.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/prompt.c.o: /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/prompt.c
CMakeFiles/shell.dir/src/prompt.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/shell.dir/src/prompt.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/src/prompt.c.o -MF CMakeFiles/shell.dir/src/prompt.c.o.d -o CMakeFiles/shell.dir/src/prompt.c.o -c /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/prompt.c

CMakeFiles/shell.dir/src/prompt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/prompt.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/prompt.c > CMakeFiles/shell.dir/src/prompt.c.i

CMakeFiles/shell.dir/src/prompt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/prompt.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/prompt.c -o CMakeFiles/shell.dir/src/prompt.c.s

CMakeFiles/shell.dir/src/signals.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/signals.c.o: /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/signals.c
CMakeFiles/shell.dir/src/signals.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/shell.dir/src/signals.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/src/signals.c.o -MF CMakeFiles/shell.dir/src/signals.c.o.d -o CMakeFiles/shell.dir/src/signals.c.o -c /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/signals.c

CMakeFiles/shell.dir/src/signals.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/signals.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/signals.c > CMakeFiles/shell.dir/src/signals.c.i

CMakeFiles/shell.dir/src/signals.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/signals.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/signals.c -o CMakeFiles/shell.dir/src/signals.c.s

CMakeFiles/shell.dir/src/utils.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/src/utils.c.o: /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/utils.c
CMakeFiles/shell.dir/src/utils.c.o: CMakeFiles/shell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/shell.dir/src/utils.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/shell.dir/src/utils.c.o -MF CMakeFiles/shell.dir/src/utils.c.o.d -o CMakeFiles/shell.dir/src/utils.c.o -c /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/utils.c

CMakeFiles/shell.dir/src/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/src/utils.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/utils.c > CMakeFiles/shell.dir/src/utils.c.i

CMakeFiles/shell.dir/src/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/src/utils.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/src/utils.c -o CMakeFiles/shell.dir/src/utils.c.s

# Object files for target shell
shell_OBJECTS = \
"CMakeFiles/shell.dir/src/commands.c.o" \
"CMakeFiles/shell.dir/src/file_finder.c.o" \
"CMakeFiles/shell.dir/src/main.c.o" \
"CMakeFiles/shell.dir/src/monitorHandle.c.o" \
"CMakeFiles/shell.dir/src/parser.c.o" \
"CMakeFiles/shell.dir/src/pipes.c.o" \
"CMakeFiles/shell.dir/src/prompt.c.o" \
"CMakeFiles/shell.dir/src/signals.c.o" \
"CMakeFiles/shell.dir/src/utils.c.o"

# External object files for target shell
shell_EXTERNAL_OBJECTS =

bin/shell: CMakeFiles/shell.dir/src/commands.c.o
bin/shell: CMakeFiles/shell.dir/src/file_finder.c.o
bin/shell: CMakeFiles/shell.dir/src/main.c.o
bin/shell: CMakeFiles/shell.dir/src/monitorHandle.c.o
bin/shell: CMakeFiles/shell.dir/src/parser.c.o
bin/shell: CMakeFiles/shell.dir/src/pipes.c.o
bin/shell: CMakeFiles/shell.dir/src/prompt.c.o
bin/shell: CMakeFiles/shell.dir/src/signals.c.o
bin/shell: CMakeFiles/shell.dir/src/utils.c.o
bin/shell: CMakeFiles/shell.dir/build.make
bin/shell: /home/mateo/.conan2/p/b/cjson7a50c7aaf7f1b/p/lib/libcjson.a
bin/shell: /home/mateo/.conan2/p/b/unitydedff9f7f2597/p/lib/libunity.a
bin/shell: CMakeFiles/shell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C executable bin/shell"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shell.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/config.json /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/bin/config.json

# Rule to build all files generated by this target.
CMakeFiles/shell.dir/build: bin/shell
.PHONY : CMakeFiles/shell.dir/build

CMakeFiles/shell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shell.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shell.dir/clean

CMakeFiles/shell.dir/depend:
	cd /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build /home/mateo/FacultadMate/Sistemas/Lab3/so-i-24-chp3-mateoUNC/shell/build/CMakeFiles/shell.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shell.dir/depend

