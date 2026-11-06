CC = gcc
CFLAGS = -O2 -Wall -Wextra -g

ifeq ($(OS),Windows_NT)
	PLATFORM_OBJS = src/fetcher/fetcher_windows.o src/locker/locker_windows.o
	TARGET = kblocker.exe
	LDLIBS =
else
	PLATFORM_OBJS = src/fetcher/fetcher_linux.o src/locker/locker_linux.o
	TARGET = kblocker
	CFLAGS += $(shell pkg-config --cflags libudev)
	LDLIBS = $(shell pkg-config --libs libudev)
endif

OBJS = src/main.o src/cli/cli.o $(PLATFORM_OBJS)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

