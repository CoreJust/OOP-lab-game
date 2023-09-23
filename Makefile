CC = g++

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir := $(dir $(mkfile_path))

# Directories and settings to be modified

SFML_INCLUDE_PATH = C:\libs\SFML-2.6.0-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.0\include
SFML_LIB_PATH = C:\libs\SFML-2.6.0-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.0\lib

GLFW_LIB_PATH = C:\libs\glfw-3.3.8.bin.WIN64\glfw-3.3.8.bin.WIN64\lib-vc2022

RM = del /s /q

# End of directories and settings to be modified

ADDITIONAL_INCLUDE_DIRS = -I $(mkfile_dir) -isystem $(SFML_INCLUDE_PATH)
ADDITIONAL_LIB_DIRS = -L $(SFML_LIB_PATH) -L $(GLFW_LIB_PATH)
ADDITIONAL_LINKED_FILES =-lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lsfml-network-s -luser32 -lgdi32 -lshell32 -lglfw3 -lopengl32 -lwinmm -lfreetype

CFLAGS = -Wall -std=c++20 -DSFML_STATIC $(ADDITIONAL_INCLUDE_DIRS)
LDFLAGS = $(ADDITIONAL_LIB_DIRS) $(ADDITIONAL_LINKED_FILES) -static-libstdc++

SRCS := $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp) $(wildcard */*/*/*.cpp)
OBJS := $(SRCS:%.cpp=%.o)

.PHONY: all clean

all: $(OBJS)
	$(CC) -o OOP_lab.exe $(OBJS) $(LDFLAGS)
	
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

rebuild: clean all

clean:
	$(RM) *.o