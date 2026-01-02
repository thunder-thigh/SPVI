# Variables
CXX = g++
CXXFLAGS = -Wall -g pkg-config --libs opencv4
TARGET = main
SRCS = main.cpp square.cpp point.cpp
OBJS = $(SRCS:.cpp=.o) # Replaces .cpp extensions with .o
RM = rm -f

# Default target
all: $(TARGET)

# Rule to link object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Pattern rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Phony targets don't represent actual files, so 'make' doesn't get confused by a file named 'clean'
.PHONY: clean all

clean:
	$(RM) $(TARGET) $(OBJS)
