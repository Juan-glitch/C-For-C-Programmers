CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic
SRC := main_mst.cpp Graph.cpp utils/DisjointSet.cpp
DEBUG_OUT := build/debug/mst
RELEASE_OUT := build/release/mst

.PHONY: all debug release clean

all: release

debug: CXXFLAGS += -g -O0 -DDEBUG
debug: $(DEBUG_OUT)

release: CXXFLAGS += -O2
release: $(RELEASE_OUT)

$(DEBUG_OUT): $(SRC)
	mkdir -p build/debug
	$(CXX) $(CXXFLAGS) $(SRC) -o $(DEBUG_OUT)

$(RELEASE_OUT): $(SRC)
	mkdir -p build/release
	$(CXX) $(CXXFLAGS) $(SRC) -o $(RELEASE_OUT)

clean:
	rm -rf build
