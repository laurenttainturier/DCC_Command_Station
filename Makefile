CC=g++
CFLAGS =-Wall -Weffc++ -Wextra -Wsign-conversion

all: main

LIB_NAME := libpacketmanager
INC_DIR := .
SRC_DIR := $(LIB_NAME)
BUILD_DIR := build
BIN_DIR := bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
LDFLAGS :=
CPPFLAGS:=-Wall -Weffc++ -Wextra -Wsign-conversion
CXXFLAGS:=-std=c++11

main: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -I$(INC_DIR) -c -o $@ $<

package: $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	ar rvs $(BIN_DIR)/$(LIB_NAME).a $(OBJ_FILES)

run: main
	./main

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)