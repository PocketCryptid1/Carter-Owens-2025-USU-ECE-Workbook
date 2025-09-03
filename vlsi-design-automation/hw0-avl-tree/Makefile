CXX = g++
TARGET = target/tree
SRCS = src/main.cpp src/lib.cpp src/lib.h
OBJS = $(SRCS:src=target, .cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o