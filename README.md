# s(imple)status

## About

sstatus is a lightweight, multi-threaded status line generator to be used with i3bar, which comes bundled with the [i3](https://github.com/i3/i3) window manager.

This project aims to follow the Unix philosophy of doing one thing well which is why sstatus does not come with *preset* status items. Each status item is intended to consist of style properties, a time interval specifying how often it should be refreshed, and a shell command specifying what should be displayed to the user. This helps to keep sstatus as lightweight and simple as possible while still allowing nearly infinite customization.

Each status item is assigned to a unique execution thread. This allows status items with long running shell commands (such as web requests) to not block the execution of other status items. This architecture also allows for only the relevant status item to be updated once its interval times out, cutting down on the performance impact of the status bar.

## Configuration
Configuration for sstatus is done via a TOML file where each individual status item is defined.

An example configuration can be found in `config.example.toml`.

The default location for the configuration file is `${XDG_CONFIG_HOME}/sstatus/config.toml`, though `${HOME}/.config/sstatus/config.toml` will be used as a fallback location.

### Global Properties

In the configuration file, a global `Order` [array](https://toml.io/en/v1.0.0#array) is used to define the order in which status items will be displayed in i3bar. Status items listed earlier in the order array will be further left, while status items listed later will be further right.

Status items are identified in the order array by their `name` property (see **Status Items** for more information).

Status items can also be listed multiple times within the order array if multiple instances of that status item are desired.

**Example:**

```toml
Order = [ "StatusItem1", "StatusItem2", "StatusItem3" ]
```

### Status Items

An individual status item is defined as a [TOML table](https://toml.io/en/v1.0.0#table).

Each status item's `name` property (table header) should be unique as to avoid conflicting status item definitions.

**Example:**

```toml
[Date] # Table Header, Name property
Script = "date +\"%l:%M:%S%p %Y-%m-%d\"" # String, Shell script which generates the text of the status item
Interval = 1000 # Integer, Refresh interval in milliseconds
ForegroundColor = "#cc99cc" # String, Foreground color as a hex code
BackgroundColor = "#ffffff" # String, Background color as a hex code
BorderColor = "#fe0000" # String, Border color as a hex code
SeparatorAfter = true # Boolean, Whether or not a separator is placed after the status item
```

> **Note:** Quotes should be escaped with a backslash (\\) where necessary.

## Build
sstatus can be built from source by executing the below commands:

```shell
$ git clone https://github.com/JTriantafylos/sstatus.git
$ cd sstatus
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make install # Can be omitted if you intend to use the binary in ../bin/
```

## Dependencies

- [tomlplusplus](https://github.com/marzer/tomlplusplus/)
- [concurrentqueue](https://github.com/cameron314/concurrentqueue)
