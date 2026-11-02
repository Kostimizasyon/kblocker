#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "locker/locker.h"
#include "fetcher/fetcher.h"
#include "cli/cli.h"

int
main(int argc, char** argv) {

	int res_temp;
	int res;

	if (argc == 2) {

		res = match_arg(argv[1]);

		if (res == F_HELP) {
			print_help();
			return 0;
		}
		else if (res == F_LIST) {
			fetcher_list();
			return 0;
		}
		else if (res == F_LOCK || res == F_UNLOCK) {
			puts("Pass a valid device name after the flag");
			return -1;
		}
		else {
			puts("Bad args use -h or --help to view usage");
			return -1;
		}

	}

	else if (argc == 3) {

		res = match_arg(argv[1]);

		if (res == F_LOCK || res == F_UNLOCK) {

			char* device_name = (char* ) malloc(MAX_NAME);

			if (strlen(argv[2]) + strlen(DEV_PATH) >= MAX_NAME - 1 ) {
				perror("Device name too long");
				return -1;
			}

			snprintf(device_name, MAX_NAME, "%s/%s",DEV_PATH,argv[2]);

			res_temp = res;
			res = fetcher_check(device_name);

			if (res != FETCHER_SUCESS) {
				puts("Device was unable to be found, use the -a flag to list all devices.");
			}

			if (res_temp == F_LOCK) {

				res = locker_lockdevice(device_name);

				if (res != LOCKER_SUCESS) {
					return -1;
				}
			}

			else if (res_temp == F_UNLOCK) {
				res = locker_unlockdevice(device_name);
				if (res != LOCKER_SUCESS) {
					if (res == LOCKER_UNLOCKED) {
						puts("This device is not locked");
						return -1;
					}
					return -1;
				}
			}

		}
	}

	else {
		puts("Bad args use -h or --help to view usage");
		return -1;
	}

}
