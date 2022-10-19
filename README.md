# Stack
This is a custom stack data structure implementation written in C (with some convinient C++ adjustments) that includes advanced security and debug features like head structure & data *canaries*, data *hashing*, constant state *validation* and expanded *html logs* with current state *dump* triggered by encountered error codes. User types for data are supported as well as user dump functions for user types.

## Building from source
#### Downloading
Download this repository with

```bash
git clone https://github.com/nerett/stack.git
```

#### Installing dependencies
Install required packages automatically with

```bash
make install-dependencies-pkg PACKAGEMANAGER=<your-package-manager-name> #apt is used if PACKAGEMANAGER is not defined
```

...or install them manually with your distro package manager (check list [here](https://github.com/nerett/stack#Dependencies)).

#### Building
Build `stack` as a standalone program with

```bash
make MODE=DEBUG #or MODE=RELEASE; MODE=RELEASE if not defined
```

You can also include `stack` in your project with the help of `stack.h` as a source code or as linkable library object files (note: object files `libstack.o` and `libstack_config.o` are created during the build process in any mode).

#### Running
You can run builded release/debug version of standalone `stack` with

```bash
make run MODE=DEBUG #MODE=RELEASE if MODE is not defined
```

Use `rund` instead of `run` to run with `valgrind`

...or run this binary with manually from project directory.

#### Rebuilding
To totally rebuild the project run

```bash
make clean
make MODE=<modename>
```

## Dependencies
This project actually depends on `libc` and building requires `make`, `g++` and `git` (it can also require `valgrind` installed to use `rund` target).


## Documentation
This section isn't done yet.

## About project
This programm was written during MIPT **Ded's** cource.
