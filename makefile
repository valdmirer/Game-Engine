# use cmake --build build/

TARGET  := program.exe
CXX     := g++
CXXFLAGS := -std=c++17

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, build/%.o, $(SRCS))

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
run: $(TARGET)
	$(TARGET)
clean:
	del /Q build\*.o $(TARGET)
