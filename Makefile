################################
###### This is a test project for IRoC-U2026
################################


CXX := g++
CXXFLAGS = -Wall -Wextra
SRC_DIR := src
BLD_DIR := build
OBJ_DIR := $(BLD_DIR)/obj 

OPENCV_FLAGS := $(shell pkg-config --cflags opencv4)
OPENCV_LIBS := $(shell pkg-config --libs opencv4)

DIRS :
	mkdir -p $(BLD_DIR) $(OBJ_DIR)

build : $(DIRS)
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/%.cpp -o $(OBJ_DIR)/%.o $(OPENCV_FLAGS) $(OPENCV_LIBS)
	$(CXX) $(OBJ_DIR)/*.o -o $(BLD_DIR)/BFF_9

run : $(BLD_DIR)/BFF_9
	./$(BLD_DIR)/BFF_9

clean :
	rm -rf ./$(BLD_DIR)/