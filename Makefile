CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = lab6
OBJS = main.o lib.o

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c lib.h
    $(CC) $(CFLAGS) -c main.c

lib.o: lib.c lib.h
    $(CC) $(CFLAGS) -c lib.c

clean:
    rm -f $(OBJS) $(TARGET) output.txt data.bin
