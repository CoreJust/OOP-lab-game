CC = g++

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir := $(dir $(mkfile_path))

# Directories and settings to be modified

SFML_INCLUDE_PATH = C:\libs\SFML-2.6.0-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.0\include
SFML_LIB_PATH = C:\libs\SFML-2.6.0-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.0\lib

GLEW_INCLUDE_PATH = C:\libs\glew-2.1.0-win32\glew-2.1.0\include
GLEW_LIB_PATH = C:\libs\glew-2.1.0-win32\glew-2.1.0\lib\Release\x64

GLM_INCLUDE_PATH = C:\libs\glm

RM = del /s /q

# End of directories and settings to be modified

ADDITIONAL_INCLUDE_DIRS = -I $(mkfile_dir) -isystem $(SFML_INCLUDE_PATH) -isystem $(GLEW_INCLUDE_PATH) -isystem $(GLM_INCLUDE_PATH)
ADDITIONAL_LIB_DIRS = -L $(SFML_LIB_PATH) -L $(GLEW_LIB_PATH)
ADDITIONAL_LINKED_FILES =-lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lsfml-network-s -luser32 -lgdi32 -lshell32 -lglew32s -lopengl32 -lwinmm -lfreetype

CFLAGS = -Wall -g3 -o0 -std=c++20 -DSFML_STATIC -DGLEW_STATIC $(ADDITIONAL_INCLUDE_DIRS)
LDFLAGS = $(ADDITIONAL_LIB_DIRS) $(ADDITIONAL_LINKED_FILES) -static-libstdc++

SRCS := $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp) $(wildcard */*/*/*.cpp)
OBJS := $(SRCS:%.cpp=%.o)

.PHONY: all clean

build: all clean

rebuild: clean build

all: $(OBJS)
	$(CC) -o OOP_lab.exe $(OBJS) $(LDFLAGS)
	
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o