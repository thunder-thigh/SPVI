################################
###### IRoC-U2026 Test Project
################################

CXX := g++
CXXFLAGS := -Wall -Wextra
SRC_DIR := src
BLD_DIR := build
OBJ_DIR := $(BLD_DIR)/obj
TARGET := $(BLD_DIR)/BFF_9

OPENCV_FLAGS := $(shell pkg-config --cflags opencv4)
OPENCV_LIBS  := $(shell pkg-config --libs opencv4)

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

.PHONY: build run clean dirs

build: dirs $(TARGET)

dirs:
	mkdir -p $(BLD_DIR) $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(OPENCV_FLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(OPENCV_LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BLD_DIR)
