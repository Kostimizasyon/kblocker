CC = gcc
CFLAGS = -O2 -Wall -Wextra -g

ifeq ($(OS),Windows_NT)
	PLATFORM_OBJS = fetcher/fetcher_windows.o locker/locker_windows.o
	TARGET = kblocker.exe
	LDLIBS =
else
	PLATFORM_OBJS = fetcher/fetcher_linux.o locker/locker_linux.o
	TARGET = kblocker
	CFLAGS += $(shell pkg-config --cflags libudev)
	LDLIBS = $(shell pkg-config --libs libudev)
endif

OBJS = main.o cli/cli.o $(PLATFORM_OBJS)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

install: $(TARGET)
	install -m 755 $(TARGET) /usr/local/bin/$(TARGET)

.PHONY: clean install
