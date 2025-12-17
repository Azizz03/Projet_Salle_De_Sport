# Makefile simple pour compiler sans autoconf/automake
CC = gcc
CFLAGS = -Wall -g $(shell pkg-config --cflags gtk+-2.0)
LIBS = $(shell pkg-config --libs gtk+-2.0)

SRCS = main.c support.c interface.c callbacks.c event.c
OBJS = $(SRCS:.c=.o)
TARGET = project4

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

