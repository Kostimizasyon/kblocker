# kblocker

A simple CLI tool to block the usage of the user's laptop keyboard (mainly) or any specific keyboard input device.

> **Note:** `kblocker` requires root privileges (`sudo`) to function.

## USAGE


### FLAGS

| Flag | Description |
|------|-------------|
| `--list` | List all input devices. |
| `--lock <device-path>` | Block the given input device. |
| `--unlock <device-path>` | Unblock the given input device. |

List available input devices:

```shell
sudo kblocker --list
```

Lock (block) a device:

```shell
sudo kblocker --lock device-path
```

Unlock a device:

```shell
sudo kblocker --unlock device-path
```

`device-path` is the path shown by `--list`, for example `/dev/input/event3`.

## EXAMPLE

```shell
sudo kblocker --list
sudo kblocker --lock /dev/input/event3
sudo kblocker --unlock /dev/input/event3
```
