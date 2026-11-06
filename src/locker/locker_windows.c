#ifdef _WIN32

#include "locker.h"

int
locker_lockdevice(const char* dev_path) {
	(void) dev_path;
	return LOCKER_ERROR;
}

int
locker_unlockdevice(const char* dev_path) {
	(void) dev_path;
	return LOCKER_ERROR;
}

#endif
