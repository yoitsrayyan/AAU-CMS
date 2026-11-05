CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic
TARGET := bin/aau-cms
SOURCES := src/main.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -rf bin
