CXX = g++
CXXFLAGS = -Isrc/hpp
LDFLAGS = -lncurses

SRC_DIR = src/cpp/
SRC_FILES = $(wildcard $(SRC_DIR)*.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)

TARGET = output

$(TARGET): $(OBJ_FILES)
	$(CXX) $^ $(LDFLAGS) -o $@

$(SRC_DIR)%.o: $(SRC_DIR)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET)