#ifdef __linux__

#include <stdio.h>
#include <stdbool.h>

#include "locker.h"
#include "locker_linux_util.h"

int
locker_lockdevice(const char* dev_path) {
	
	int res;

	res = get_inhibited(dev_path);

	if (res == 1) {
		return LOCKER_LOCKED;
	}

	res = set_inhibited(dev_path, true);

	if (res == -1) {
		return LOCKER_ERROR;
	}

	return LOCKER_SUCESS;
}

int
locker_unlockdevice(const char *dev_path) {
	
	int res;

	res = get_inhibited(dev_path);

	if (res == 0) {
		return LOCKER_UNLOCKED;
	}

	res = set_inhibited(dev_path, false);

	if (res == -1) {
		return LOCKER_ERROR;
	}
	
	return LOCKER_SUCESS;
}

#endif
