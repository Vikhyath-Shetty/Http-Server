#port
PORT = 5000

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Wpedantic -g -MMD

# Linker flags (Winsock for Windows)
LDFLAGS = -lws2_32

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source and Object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

# Output binary
TARGET = $(BUILD_DIR)/http-server.exe

# Default target: Build the server
all: $(TARGET)

# Rule to build the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to compile .c files into .o files, tracking dependencies
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean up compiled files (keep build/ but remove compiled files)
clean:
	rm -rf $(BUILD_DIR)
	


# Run the server (usage: make run PORT=5000)
run: $(TARGET)
	./$(TARGET) $(PORT)

