CC = gcc
CFLAGS = -Wall -g

# Output executable definition
EXECUTABLE = bin/file_manager

# Source files
SRC = src/main.c \
      src/file_operations.c \
      src/directory_ops.c \
      src/permissions.c \
      src/logger.c

# Build command
$(EXECUTABLE): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SRC)

# Clean command
clean:
	rm -rf bin/* a.out

