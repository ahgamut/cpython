# Compiling Python2.7 with Cosmopolitan

This repo contains the source code of [Python 2.7.18][py27] customized to
compile with [Cosmopolitan][cosmo] libc.  Meant for experimental purposes only.

The `header_stubs` folder contains dummy headers corresponding to the [C
stdlib][cstdlib]. The `libcosmo` folder should contain the required files for
compiling an executable using Cosmopolitan on Linux.

The compiled APE runs on Linux and Windows -- the interpreter uses *relative
paths* to find the Python standard library (and other platform dependent files):
copy `python.com` and the `Lib/` directory to the same location and Python
should run as expected. **Note:** Ensure that the `PYTHONPATH` or `PYTHONHOME`
environment variables are not set.

Finding the standard library requires changing `Modules/getpath.c`: it would be
nice to gracefully handle OS-specific stuff at the C level so that files like
`Lib/os.py` don't have any confusion.

### Missing modules

The following modules of the Python stdlib are currently not compiled:

```
_ctypes         _ctypes_test    _curses
_curses_panel   _hashlib        _locale
_socket         _ssl            audioop
bz2             crypt           linuxaudiodev
nis             ossaudiodev     readline
resource        termios

_bsddb          _multiprocessing   _sqlite3
_tkinter        bsddb185        dbm
dl              gdbm            imageop
spwd            sunaudiodev
```

`Modules/Setup.local` contains recipes to compile the `_ctypes` and `_sqlite3`
modules.


Compiled on:

```bash
# Debian Buster (Linux 4.19.0-12-amd64)
$ gcc --version
gcc (Debian 8.3.0-6) 8.3.0
Copyright (C) 2018 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
$ clang --version
Debian clang version 11.0.1-++20201103062553+ef4ffcafbb2-1~exp1~20201103053214.125
Target: x86_64-pc-linux-gnu
Thread model: posix
```


## Usage Instructions

1. Compile the latest commit in the `master` branch of `Cosmopolitan`.
2. Copy `cosmopolitan.h` (and `crt.o`, `ape.o`, `ape.lds`, `cosmopolitan.a`) to
   the `libcosmo/` folder.
3. Run `superconfigure` with the appropriate `$CC` (calls `configure` with a bunch of parameters, followed
   by `make` and then `objcopy` to produce `python.com`)
4. Run `python.exe`

```bash
cd libcosmo/
# use the latest version
wget https://justine.lol/cosmopolitan/cosmopolitan.zip
unzip cosmopolitan.zip
cd ../
CC=gcc ./superconfigure # or clang
./python.com
```

[py27]: https://www.python.org/downloads/release/python-2718/
[cosmo]: https://github.com/jart/cosmopolitan
[cstdlib]: https://en.cppreference.com/w/c/header
