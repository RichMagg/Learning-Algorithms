CXX = g++

CXXFLAGS = -std=c++20 -Wall

TARGET = build/main

SRCS = main.cpp

OBJS = build/main.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJS): $(SRCS) | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

run: $(TARGET)
	clear && ./$(TARGET)

clean:
	clear && rm -rf build