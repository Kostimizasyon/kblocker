#define LOCKER_ERROR   -1
#define LOCKER_LOCKED   0
#define LOCKER_UNLOCKED 1
#define LOCKER_SUCESS   2

int locker_lockdevice(const char* dev_path);

int locker_unlockdevice(const char* dev_path);
