CXX      := -c++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror
LDFLAGS  := # -L/usr/lib -lstdc++ -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/obj
BIN_DIR  := $(BUILD)/bin
TARGET   := sstatus
INCLUDE  := -I include/
SRC      :=                      \
	$(wildcard src/*.cpp)         \

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(BIN_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ $(LDFLAGS)

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$(TARGET) $^ $(LDFLAGS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(BIN_DIR)/*
