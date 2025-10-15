CC = gcc
FLAGS = -Wall -Werror -Wextra
TARGET = ./main
LIB_SRCS = fixedpoint/*.c fixedpoint/utils/*.c fixedpoint/fixedtrig/*.c

# LUT generator
GEN_SRCS = ./fixedpoint/generators/*.c ./fixedpoint/convert.c
GEN_TARGET = ./fixedpoint/generators/fixedgenerators
GEN_LINKS = -lm

all:
	$(CC) $(FLAGS) -o $(GEN_TARGET) $(GEN_SRCS) $(GEN_LINKS)
	$(GEN_TARGET)
	clear
	$(CC) $(FLAGS) $(FLAGS_TEST) -g -o $(TARGET) main.c $(LIB_SRCS) -lm
	$(TARGET)
