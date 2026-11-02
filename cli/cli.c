#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "cli.h"

int
match_arg(const char* arg) {
    if (!strcmp(arg, "-h")  || !strcmp(arg, "--help"))     return F_HELP;
    if (!strcmp(arg, "-a")  || !strcmp(arg, "--all"))      return F_LIST;
    if (!strcmp(arg, "-l")  || !strcmp(arg, "--lock"))     return F_LOCK;
    if (!strcmp(arg, "-u")  || !strcmp(arg, "--unlock"))   return F_UNLOCK;
    return F_UNKOWN;
}

void
print_help(void) {
    printf("Usage: program [options]\n\n"
           "Options:\n"
           "  -h, --help                     Show this help message and exit\n"
           "  -a, --all                      List all available devices\n"
           "  -l, --lock <listed_device>     Lock the specified device\n"
           "  -u, --unlock <listed_device>   Unlock the specified device\n");
}
