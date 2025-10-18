CC = gcc
FLAGS = -Wall -Werror -Wextra
TARGET = ./main
LIB_SRCS = fixedpoint/*.c fixedpoint/utils/*.c fixedpoint/fixedtrig/*.c

# LUT generator
GEN_SRCS = ./fixedpoint/generators/*.c ./fixedpoint/convert.c
GEN_TARGET = ./fixedpoint/generators/fixedgenerators
GEN_LINKS = -lm

# tests
TEST_TARGET = ./tests/testFixed
TEST_FLAGS = -fsanitize=address -fsanitize=undefined
TEST_SRCS = ./tests/libtesting/*.c ./tests/libtesting/fileio/*.c

all:
	$(CC) $(FLAGS) -o $(GEN_TARGET) $(GEN_SRCS) $(GEN_LINKS)
	$(GEN_TARGET)
	clear
	$(CC) $(FLAGS) -g -o $(TARGET) main.c $(LIB_SRCS) -lm
	$(TARGET)

test:
	$(CC) $(FLAGS) -o $(GEN_TARGET) $(GEN_SRCS) $(GEN_LINKS)
	$(GEN_TARGET)
	clear
	$(CC) $(FLAGS) $(TEST_FLAGS) -g -o $(TEST_TARGET) ./tests/testFixed.c $(TEST_SRCS) $(LIB_SRCS) -lm
	$(TEST_TARGET)
