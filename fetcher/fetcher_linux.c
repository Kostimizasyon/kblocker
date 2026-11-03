#ifdef __linux__

#include "fetcher.h"
#include <dirent.h>
#include <libudev.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>

// Returns 1 if keyboard, 0 if not, -1 on error.
// Pass exactly one of: path (sysfs path or /dev/input/eventN) or entry
// (a dirent from reading /sys/class/input).
bool is_keyboard(const char *path, struct dirent *entry) {
  if ((path != NULL) == (entry != NULL))
    return false;

  struct udev *udev = udev_new();

  if (!udev)
    return false;

  struct udev_device *dev = NULL;

  if (entry) {
    dev = udev_device_new_from_subsystem_sysname(udev, "input", entry->d_name);
  } else if (strncmp(path, "/sys/", 5) == 0) {
    dev = udev_device_new_from_syspath(udev, path);
  } else {
    struct stat st;
    if (stat(path, &st) == 0 && S_ISCHR(st.st_mode))
      dev = udev_device_new_from_devnum(udev, 'c', st.st_rdev);
  }

  bool result = false;
  if (dev) {
    const char *kb = udev_device_get_property_value(dev, "ID_INPUT_KEYBOARD");
    result = kb && strcmp(kb, "1") == 0;
    udev_device_unref(dev);
  }

  udev_unref(udev);
  return result;
}

int getname(const struct dirent *entry, char *out, size_t out_size) {

  if (!entry || !out || out_size == 0) {
    return -1;
  }

  // fallback
  snprintf(out, out_size, "Unknown Device");

  char filepath[PATH_MAX];
  int res = snprintf(filepath, sizeof(filepath), "%s/%s/name", DEV_PATH,
                     entry->d_name);
  if (res < 0 || (size_t)res >= sizeof(filepath)) {
    perror("Path error");
    return -1;
  }

  FILE *file = fopen(filepath, "r");
  if (!file) {
    // is event file
    return -1;
  }

  if (fgets(out, out_size, file) == NULL) {
    perror("fgets");
    fclose(file);
    return -1;
  }

  fclose(file);
  return 0;
}

int fetcher_list() {
  DIR *dir = opendir(DEV_PATH);

  if (!dir) {
    perror("opendir");
    return FETCHER_ERROR;
  }

  const int w_idx = 3, w_name = 32, w_dev = 14;
  struct dirent *entry;

  printf("\033[94mSearching keyboards...\033[0m\n\n");

  printf("┌");
  for (int i = 0; i < w_idx + 2; i++) printf("─");
  printf("┬");
  for (int i = 0; i < w_name + 2; i++) printf("─");
  printf("┬");
  for (int i = 0; i < w_dev + 2; i++) printf("─");
  printf("┐\n");

  printf("│ \033[1m%-*s\033[0m │ \033[1m%-*s\033[0m │ \033[1m%-*s\033[0m │\n",
         w_idx, "#", w_name, "Name", w_dev, "Device");

  printf("├");
  for (int i = 0; i < w_idx + 2; i++) printf("─");
  printf("┼");
  for (int i = 0; i < w_name + 2; i++) printf("─");
  printf("┼");
  for (int i = 0; i < w_dev + 2; i++) printf("─");
  printf("┤\n");

  int counter = 0;
  while ((entry = readdir(dir)) != NULL) {

    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 ||
        strncmp(entry->d_name, COMP_PATH, strlen(COMP_PATH)) == 1) {
      continue;
    }

    int res;

    if (is_keyboard(NULL, entry)) {

      char *name = (char *)malloc(MAX_NAME);

      res = getname(entry, name, MAX_NAME);

      if (res == -1) {
        free(name);
        continue;
      }

      if (!name) {
        perror("Error with fetching name of keyboard");
        closedir(dir);
        return FETCHER_ERROR;
      }

      name[strcspn(name, "\n")] = '\0';

      counter++;

      printf("│ \033[92m%-*d\033[0m │ %-*.*s │ \033[90m%-*.*s\033[0m │\n",
             w_idx, counter, w_name, w_name, name, w_dev, w_dev, entry->d_name);

      free(name);
    }
  }

  printf("└");
  for (int i = 0; i < w_idx + 2; i++) printf("─");
  printf("┴");
  for (int i = 0; i < w_name + 2; i++) printf("─");
  printf("┴");
  for (int i = 0; i < w_dev + 2; i++) printf("─");
  printf("┘\n");

  printf("\033[94m%d keyboard(s) found\033[0m\n", counter);

  if (closedir(dir) == -1) {
    perror("closedir");
    return FETCHER_ERROR;
  }

  return FETCHER_SUCESS;
}

int fetcher_check(const char *dev_path) {
  if (!is_keyboard(dev_path, NULL)) {
    return FETCHER_ERROR;
  }
  return FETCHER_SUCESS;
}

#endif
