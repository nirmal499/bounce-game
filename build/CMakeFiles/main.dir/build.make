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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/app/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/app/main.cpp.o: ../app/main.cpp
CMakeFiles/main.dir/app/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/app/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/app/main.cpp.o -MF CMakeFiles/main.dir/app/main.cpp.o.d -o CMakeFiles/main.dir/app/main.cpp.o -c /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/app/main.cpp

CMakeFiles/main.dir/app/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/app/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/app/main.cpp > CMakeFiles/main.dir/app/main.cpp.i

CMakeFiles/main.dir/app/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/app/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/app/main.cpp -o CMakeFiles/main.dir/app/main.cpp.s

CMakeFiles/main.dir/app/Mesh.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/app/Mesh.cpp.o: ../app/Mesh.cpp
CMakeFiles/main.dir/app/Mesh.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/app/Mesh.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/app/Mesh.cpp.o -MF CMakeFiles/main.dir/app/Mesh.cpp.o.d -o CMakeFiles/main.dir/app/Mesh.cpp.o -c /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/app/Mesh.cpp

CMakeFiles/main.dir/app/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/app/Mesh.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/app/Mesh.cpp > CMakeFiles/main.dir/app/Mesh.cpp.i

CMakeFiles/main.dir/app/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/app/Mesh.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/app/Mesh.cpp -o CMakeFiles/main.dir/app/Mesh.cpp.s

CMakeFiles/main.dir/app/Renderer.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/app/Renderer.cpp.o: ../app/Renderer.cpp
CMakeFiles/main.dir/app/Renderer.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/app/Renderer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/app/Renderer.cpp.o -MF CMakeFiles/main.dir/app/Renderer.cpp.o.d -o CMakeFiles/main.dir/app/Renderer.cpp.o -c /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/app/Renderer.cpp

CMakeFiles/main.dir/app/Renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/app/Renderer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/app/Renderer.cpp > CMakeFiles/main.dir/app/Renderer.cpp.i

CMakeFiles/main.dir/app/Renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/app/Renderer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/app/Renderer.cpp -o CMakeFiles/main.dir/app/Renderer.cpp.s

CMakeFiles/main.dir/app/ShaderLoader.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/app/ShaderLoader.cpp.o: ../app/ShaderLoader.cpp
CMakeFiles/main.dir/app/ShaderLoader.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/app/ShaderLoader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/app/ShaderLoader.cpp.o -MF CMakeFiles/main.dir/app/ShaderLoader.cpp.o.d -o CMakeFiles/main.dir/app/ShaderLoader.cpp.o -c /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/app/ShaderLoader.cpp

CMakeFiles/main.dir/app/ShaderLoader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/app/ShaderLoader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/app/ShaderLoader.cpp > CMakeFiles/main.dir/app/ShaderLoader.cpp.i

CMakeFiles/main.dir/app/ShaderLoader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/app/ShaderLoader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/app/ShaderLoader.cpp -o CMakeFiles/main.dir/app/ShaderLoader.cpp.s

CMakeFiles/main.dir/app/Camera.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/app/Camera.cpp.o: ../app/Camera.cpp
CMakeFiles/main.dir/app/Camera.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/app/Camera.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/app/Camera.cpp.o -MF CMakeFiles/main.dir/app/Camera.cpp.o.d -o CMakeFiles/main.dir/app/Camera.cpp.o -c /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/app/Camera.cpp

CMakeFiles/main.dir/app/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/app/Camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/app/Camera.cpp > CMakeFiles/main.dir/app/Camera.cpp.i

CMakeFiles/main.dir/app/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/app/Camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/app/Camera.cpp -o CMakeFiles/main.dir/app/Camera.cpp.s

CMakeFiles/main.dir/glad/src/glad.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/glad/src/glad.c.o: ../glad/src/glad.c
CMakeFiles/main.dir/glad/src/glad.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/main.dir/glad/src/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/glad/src/glad.c.o -MF CMakeFiles/main.dir/glad/src/glad.c.o.d -o CMakeFiles/main.dir/glad/src/glad.c.o -c /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/glad/src/glad.c

CMakeFiles/main.dir/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/glad/src/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/glad/src/glad.c > CMakeFiles/main.dir/glad/src/glad.c.i

CMakeFiles/main.dir/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/glad/src/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/glad/src/glad.c -o CMakeFiles/main.dir/glad/src/glad.c.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/app/main.cpp.o" \
"CMakeFiles/main.dir/app/Mesh.cpp.o" \
"CMakeFiles/main.dir/app/Renderer.cpp.o" \
"CMakeFiles/main.dir/app/ShaderLoader.cpp.o" \
"CMakeFiles/main.dir/app/Camera.cpp.o" \
"CMakeFiles/main.dir/glad/src/glad.c.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/app/main.cpp.o
main: CMakeFiles/main.dir/app/Mesh.cpp.o
main: CMakeFiles/main.dir/app/Renderer.cpp.o
main: CMakeFiles/main.dir/app/ShaderLoader.cpp.o
main: CMakeFiles/main.dir/app/Camera.cpp.o
main: CMakeFiles/main.dir/glad/src/glad.c.o
main: CMakeFiles/main.dir/build.make
main: external/glfw/src/libglfw3.a
main: /usr/lib/x86_64-linux-gnu/librt.a
main: /usr/lib/x86_64-linux-gnu/libm.so
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/build /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/build /home/nbaskey/Documents/current_projects/doing/cpp_game_dev_packt/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend
