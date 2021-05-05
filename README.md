# s(imple)status

## About

sstatus is a lightweight, multi-threaded status line generator to be used with i3bar which comes bundled with the [i3](https://github.com/i3/i3) window manager.

We aim to follow the Unix philosophy of doing one thing well which is why sstatus does not come with *preset* status items. Each status item is intended to consist of style properties, a time interval specifying how often it should be refreshed, and a shell command specifying what should be displayed to the user. This helps to keep sstatus as lightweight and simple as possible while still allowing nearly infinite customization.

Each status item is assigned to a unique thread. This allows status items with long running shell commands (such as web requests) to not block the execution of other status items. This architecture also allows for only the relevant status item to be updated once its interval times out, cutting down on the performance impact of the status bar.

## Configuration
Configuration for sstatus is done via a simple TOML file where each individual status item is defined.

The default location for the config file is: `${XDG_CONFIG_HOME}/sstatus/config.toml`, though `/home/${USER}/sstatus/config.toml` will be used as a fallback location.

## Build
sstatus can be built from source by executing the below commands:
```
$ git clone https://github.com/JTriantafylos/sstatus.git
$ cd sstatus
$ git submodule update --init
$ mkdir build
$ cd build
$ cmake ..
$ make
```

The sstatus binary will then be located at `bin/sstatus` located in the sstatus repository root directory.

## Dependencies

- [tomlplusplus](https://github.com/marzer/tomlplusplus/) (Included as a git submodule)
- [concurrentqueue](https://github.com/cameron314/concurrentqueue) (Included as a git submodule)