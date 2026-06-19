CXX := g++
CXXFLAGS := -std=c++17 -Wall
SRC := main_mst.cpp Graph.cpp utils/DisjointSet.cpp
DEBUG_OUT := build/debug/mst
RELEASE_OUT := build/release/mst

.PHONY: debug release clean

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
