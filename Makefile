PROJECT_NAME ?= bouncing_physics
BUILD_DIR ?= build

SOURCES := src/main.cpp src/ball.cpp
OBJECTS := $(SOURCES:src/%.cpp=$(BUILD_DIR)/%.o)

UNAME_S := $(shell uname -s 2>/dev/null)
CXX ?= g++
CXXFLAGS ?= -std=c++14 -Wall -Wextra -g
CPPFLAGS ?=
LDFLAGS ?=
LDLIBS ?=

ifeq ($(OS),Windows_NT)
    RAYLIB_PATH ?= C:/raylib
    CPPFLAGS += -I$(RAYLIB_PATH)/w64devkit/include
    LDFLAGS += -L$(RAYLIB_PATH)/w64devkit/lib
    LDLIBS += -lraylib -lopengl32 -lgdi32 -lwinmm
    TARGET := $(PROJECT_NAME).exe
else ifeq ($(UNAME_S),Darwin)
    CXX ?= clang++
    RAYLIB_PREFIX ?= $(shell brew --prefix raylib 2>/dev/null)
    ifeq ($(strip $(RAYLIB_PREFIX)),)
        RAYLIB_PREFIX := /opt/homebrew/opt/raylib
    endif
    CPPFLAGS += -I$(RAYLIB_PREFIX)/include
    LDFLAGS += -L$(RAYLIB_PREFIX)/lib
    LDLIBS += -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
    TARGET := $(PROJECT_NAME)
else
    CPPFLAGS += -I/usr/local/include
    LDLIBS += -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    TARGET := $(PROJECT_NAME)
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(PROJECT_NAME) $(PROJECT_NAME).exe
