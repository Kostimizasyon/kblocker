#ifdef _WIN32

#include <stdio.h>

#include "fetcher.h"

int
fetcher_list(void) {
	puts("Device listing is not implemented on Windows yet.");
	return FETCHER_ERROR;
}

int
fetcher_check(const char* device_name) {
	(void) device_name;
	return FETCHER_ERROR;
}

#endif
