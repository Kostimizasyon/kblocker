#define FETCHER_ERROR     -1
#define FETCHER_SUCESS     1

#define DEV_PATH "/sys/class/input"
#define COMP_PATH "/sys/class/input/input"

#define MAX_PATH 256
#define MAX_NAME 256

int fetcher_list(void);

int fetcher_check(const char* device_name);
