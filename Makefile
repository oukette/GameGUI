# Makefile proto_0 project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -O0 -g3 -Wall -fmessage-length=0

# SFML directories
SFML_INCLUDE = -I"D:/Documents/DEV/4_libs/SFML/include"
SFML_LIB = -L"D:/Documents/DEV/4_libs/SFML/lib"
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SOURCES = main.cpp

# Output executable
TARGET = game_gui2.exe

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) $^ -o $@ $(SFML_LIB) $(SFML_LIBS)

clean:
	rm -f $(TARGET)
