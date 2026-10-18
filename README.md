# gguid

`gguid` is a small command-line utility for generating GUIDs/UUIDs. It can
also print the empty GUID and generate more than one value at a time.

## Current status

The project is managed with CMake and uses [CLI11](https://github.com/CLIUtils/CLI11)
for command-line parsing. It has separate GUID implementations for Windows
(Windows COM APIs) and Linux (libuuid). The Linux implementation generates
random version 4 UUIDs and formats them in lowercase.

Linux generation is working. The Windows implementation is retained but needs
retesting after the recent changes. macOS support is not implemented yet.

## Features

- Generate one or more GUIDs/UUIDs.
- Generate the empty GUID (`00000000-0000-0000-0000-000000000000`).
- Write results to standard output, making the tool easy to use in scripts.
- Build with CMake.

## Command-line usage

```text
gguid [OPTIONS]
```

| Option | Description |
| --- | --- |
| `-c, --count <number>` | Number of GUIDs to generate. Defaults to `1`. |
| `-e, --empty` | Generate the empty GUID instead of random GUIDs. |
| `-h, --help` | Show help from CLI11. |

Examples:

```sh
# Generate one GUID (the default)
gguid

# Generate one GUID
gguid --count 1

# Generate five GUIDs
gguid -c 5

# Generate three empty GUIDs
gguid --empty --count 3
```

Because output is written to standard output, it can be redirected or piped:

```sh
gguid --count 1 > id.txt
gguid --count 10 | sort
```

## Requirements

- CMake 3.10 or newer.
- A C++ compiler supporting C++20 for builds with CMake newer than 3.12.
- Git, if the CLI11 dependency has not been initialized.

The repository includes CLI11 as a Git submodule.

The CMake project declares a minimum of 3.10, but the `-S`/`-B` commands below
require CMake 3.13 or newer. The current configuration selects C++11 with
CMake 3.12 or older and C++20 with newer CMake versions.

## Build

Initialize the dependency once after cloning:

```sh
git submodule update --init --recursive
```

### Windows

From a Developer PowerShell, Command Prompt, or a terminal with CMake on
`PATH`:

```powershell
cmake -S . -B build
cmake --build build --config Release
```

Run the executable from the single-configuration or Visual Studio build tree:

```powershell
.\build\gguid.exe
```

For a Visual Studio multi-configuration generator, the executable may instead
be located at:

```powershell
.\build\Release\gguid.exe
```

### Ubuntu Linux

Install the compiler, build tools, and libuuid development files:

```sh
sudo apt update
sudo apt install build-essential cmake git uuid-dev
```

From the repository root, after initializing the submodule:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/gguid
```

### macOS

The macOS branch in CMake is currently empty and there is no macOS GUID
implementation. Building on macOS requires completing that port first.

## Installing the CLI

### Windows: run by name

Add the directory containing `gguid.exe` to your user `PATH`, then open a new
terminal. Building alone does not add the executable to `PATH`.

### Linux: install system-wide

From the repository root, configure and build, then install with CMake:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
sudo cmake --install build --prefix /usr/local
gguid -c 3
```

The install rule places the executable at `/usr/local/bin/gguid`, which is
usually already on `PATH`. Administrator permissions are needed for the
installation step, not for building or running the tool.

After rebuilding, repeat the CMake install command to update the installed
copy. A dynamically linked executable still needs the libuuid runtime library
on the machine where it runs.

Installation is optional: on Linux too, you can add the build directory to
`PATH` instead. In that case, rebuilding updates the command directly, but
moving or deleting the build directory makes it unavailable.

### macOS

Installation instructions will follow once the macOS implementation is ready.

## Known limitations

- Count validation intends to enforce 1–100, but currently uses an OR condition
  that accepts every representable integer. Use positive counts; enforcement
  still needs fixing.
- GUID strings currently use manually managed character buffers.

## Development roadmap

1. Fix count validation and verify command-line behavior.
2. Verify CMake installation and document platform packaging.
3. Implement macOS generation and verify builds on all three platforms.
4. Add tests for formatting, count validation, empty GUID output, and exit
   codes.
5. Verify the existing CI workflow covers each supported platform and document
   packaging options.

## License

See [LICENSE](LICENSE).
