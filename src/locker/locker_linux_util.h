#ifndef __locker_linux_util_h__
#define __locker_linux_util_h__

#include <stdio.h>
#include <stdbool.h>
#include "locker.h"

#define MAX_PATH 256

static inline int
build_inhibited_path(char *out, size_t size, const char *dev_path)
{
	int n = snprintf(out, size, "%s/inhibited", dev_path);

	if (n < 0 || (size_t)n >= size) {
    		perror("Path too long");
		return -1;
	}
	return 0;
}

static inline int
get_inhibited(const char *dev_path)
{
	char inh_path[MAX_PATH];
	if (build_inhibited_path(inh_path, sizeof inh_path, dev_path) < 0)
		return -1;

	FILE *file = fopen(inh_path, "r");

	if (!file) {
		perror("fopen");
		return -1;
	}

	int c = getc(file);
	fclose(file);

	return c == EOF ? -1 : c - '0';
}

static inline int
set_inhibited(const char *dev_path, bool val)
{
	char inh_path[MAX_PATH];
	if (build_inhibited_path(inh_path, sizeof inh_path, dev_path) < 0)
		return -1;

	FILE *file = fopen(inh_path, "w");
	if (!file) {
		perror("fopen");
		return -1;
	}

	fputs(val ? "1\n" : "0\n", file);
	fclose(file);
	return 0;
}

#endif
