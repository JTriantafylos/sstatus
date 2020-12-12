# s(imple)status

## A simple, lightweight status line utility.

## Configuration
The default location for the config file is:
```
${XDG_CONGFIG_HOME}/sstatus/config.toml
````

## Build
To build using `make`:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```
Alternatively, to build using `ninja`:
```
$ mkdir build
$ cd build
$ cmake -GNinja ..
$ ninja
```

Generate `compile_commands.json` for `ccls` with `bear`.

## Dependencies

- [TOML++](https://github.com/marzer/tomlplusplus/) (Included with the project)
