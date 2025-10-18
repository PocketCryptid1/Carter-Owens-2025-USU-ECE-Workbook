CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
SRC_DIR = src
OBJ_DIR = obj

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/module.cpp $(SRC_DIR)/floorplan.cpp
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS = $(SRC_DIR)/module.h $(SRC_DIR)/floorplan.h

TARGET = floorplan

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean