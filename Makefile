CXX = g++
CXXFLAGS = -Wall
TARGET = main
SOURCE = src/main.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
