# s(imple)status

sstatus is a lightweight, multi-threaded status line generator to be used with i3bar, which comes bundled with the [i3](https://github.com/i3/i3) window manager.

## Table of Contents

- [Goals](#goals)
- [Installation](#installation)
- [Usage](#usage)
- [Configuration](#configuration)
  - [Global Properties](#global-properties)
  - [Status Items](#status-items)
- [Dependencies](#dependencies)

## Goals

This project aims to follow the Unix philosophy of doing one thing well which is why sstatus does not come with *preset* status items. Each status item is intended to consist of style properties, a time interval specifying how often it should be refreshed, and a shell command specifying what should be displayed to the user. This helps to keep sstatus as lightweight and simple as possible while still allowing nearly infinite customization.

sstatus does not aim to implement all available features of the [i3bar protocol](https://i3wm.org/docs/i3bar-protocol.html). Instead, the goal is to provide a minimal, easy-to-use status line generator that allows users to display nearly whatever they desire within their status bar. 

## Installation

sstatus is packaged for the following distros:

- Arch Linux: [sstatus](https://aur.archlinux.org/packages/sstatus/) in the [AUR](https://aur.archlinux.org/)

sstatus can also be built from source by executing the below commands:

```shell
$ git clone https://github.com/JTriantafylos/sstatus.git
$ cd sstatus
$ cmake -B build
$ make -C build
$ make -C build install # Can be skipped if you intend to use the binary in ./bin/
```

## Usage

To use sstatus as your i3bar status line generator, simply install sstatus and add the following to your i3 configuration file. This will launch sstatus using the configuration file at the default location (see **Configuration**).

```
bar {
    status_command sstatus
}
```

If you would prefer to specify a custom configuration file location you can add that path as the first argument to sstatus as shown below.

```
bar {
    status_command sstatus -c ~/custom_config.toml
}
```

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

## Contributing

If there is a feature you would like to see in sstatus, please open an issue or even submit a pull request if you'd like to hack on sstatus yourself. I am always open to feedback!

## Dependencies

- [tomlplusplus](https://github.com/marzer/tomlplusplus/)
- [mpmcplusplus](https://github.com/JTriantafylos/mpmcplusplus)
