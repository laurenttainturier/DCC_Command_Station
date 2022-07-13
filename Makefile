CC=g++
CFLAGS =-Wall -Weffc++ -Wextra -Wsign-conversion

all: main

INC_DIR := include
SRC_DIR := .
OBJ_DIR := output
SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS :=
CPPFLAGS:=-Wall -Weffc++ -Wextra -Wsign-conversion
CXXFLAGS:=-std=c++11

main: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -I$(INC_DIR) -c -o $@ $<

run: main
	./main

clean:
	rm -rf $(OBJ_DIR) main