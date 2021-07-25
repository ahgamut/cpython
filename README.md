# Compiling Python3.6 with Cosmopolitan

This repo contains the source code of [Python 3.6.14][py36] customized to
compile with [Cosmopolitan][cosmo] libc.  Meant for experimental purposes only.

The `header_stubs` folder contains dummy headers corresponding to the [C
stdlib][cstdlib]. The `libcosmo` folder should contain the required files for
compiling an executable using Cosmopolitan on Linux.

The compiled APE runs on Linux and Windows -- the Python standard library,
platform dependent files, `pip`, and `setuptools` are all contained *within* the
executable, (APEs are also valid ZIP files!!!).  **Note:** `PYTHONPATH`,
`PYTHONHOME`, and `pyvenv.cfg` are NOT read during interpreter startup.

### stdlib modules

The following modules of the Python stdlib are currently NOT compiled:

```
_bz2   _crypt   _ctypes
_ctypes_test   _curses   _curses_panel
_dbm   _decimal   _gdbm
_hashlib   _lzma   _multiprocessing
_sqlite3   _ssl   _testbuffer
_testcapi   _testimportmultiple   _testmultiphase
_tkinter   audioop   nis
ossaudiodev   readline   spwd
termios   xxlimited   
```

The below modules are available for use (untested).

```
_asyncio   _bisect   _blake2
_codecs_cn   _codecs_hk   _codecs_iso2022
_codecs_jp   _codecs_kr   _codecs_tw
_csv   _datetime   _elementtree
_heapq   _json   _lsprof
_md5   _multibytecodec   _opcode
_pickle   _posixsubprocess   _random
_sha1   _sha256   _sha3
_sha512   _socket   _struct
array   atexit   binascii
cmath   fcntl   grp
math   mmap   parser
pwd   pyexpat   resource
select   syslog   time
unicodedata   zlib   
```

The APE does not use threads, and `_dummy_thread` is used to pacify the high
level `threading` module.  Even so, sometimes the interpreter may throw errors
related to this during exit.


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

Also needs `sh`, `make`, `objcopy`, `find`, `zip`, and `xargs`.

## Basic Usage

1. Obtain `cosmopolitan.zip` amalgamation or compile any version of Cosmopolitan
   after (`8c4cce0` July 11 2021), preferably the latest stable version.
2. Copy `cosmopolitan.h` (and `crt.o`, `ape.o`, `ape.lds`, `cosmopolitan.a`) to
   the `libcosmo/` folder.
3. Run `superconfigure` with the appropriate `$CC` (calls `configure` with a bunch of parameters, followed
   by `make` and then `objcopy` to produce `python.com`)
4. Copy `python.com` to wherever and run it

```bash
cd libcosmo/
# use the latest version
wget https://justine.lol/cosmopolitan/cosmopolitan.zip
unzip cosmopolitan.zip
cd ../
CC=gcc ./superconfigure # or clang
./python.com
```

## How to use packages from `pip`?

As of right now `python.com -m pip download/install` from the web doesn't work
nicely because the APE does not currently have SSL support. So find some other
way to get the wheels. Create a folder called `Lib` in the same location as
`python.com` and unzip all necessary packages there. 

```bash

./python.com -V
mkdir -p Lib/site-packages # Lib is also okay

# need to download packages from pip first, so using system python
/usr/bin/python3 -m pip download dataclasses --python-version 36 --only-binary=:all:

# dataclasses are not included in Python3.6 by default
./python.com -m pip --help
./python.com -m pip install ./dataclasses.whl -t ./Lib/site-packages

# or if pip complains for whatever reason
unzip ./dataclasses.whl -d ./Lib/site-packages

# check if importing works
./python.com -c 'import dataclasses'

```

Of course, only packages with the `py3-none-any.whl` (ie no C extensions) will
import properly.

# What about C extensions?

APEs are statically compiled, so no `dlopen`, which means you currently can't
have shared objects as part of your setup. However, it is still possible to
use *some* C extensions by compiling them like stdlib modules:

* Obtain the source for a given package `my_package` with an extension
    `my_package.ext`
* Move all C source files to a subfolder of `Modules` called `my_package_ext`
* Move all Python source files to a subfolder `Lib` (ensure directory structure
    is valid for the Python files).
* Change the name of C extensions (in the `struct PyModuleDef`) and replace dots
    with underscores. For example, if the extension name is `my_package.ext`, 
    it should now be `my_package_ext` in the `PyModuleDef`. Also, there must be a function
    called `PyInit_my_package_ext` which initializes the extension.
* Change the necessary imports in the Python source files to use
    `my_package_ext` correctly. For example, `import func from .ext` in
    `my_package.__init__` would become `import func from my_package_ext` (no
    dot).
* Add the compilation recipe for the package into `Modules/Setup.local`. 
    * The recipe format is described in `Modules/Setup`, and it is used to compile the C
    extensions for the standard library. It's basically 
    `[<extension_name> <source-files> <includes> <links>]` (imagine it with `gcc -o` 
    added at the start), but a little finicky, especially if you're passing stuff 
    like `-DMY_FLAG=1` (check `pyexpat` in `Modules/Setup` to see how
    to do it right).
* If you didn't add the recipe correctly, the Makefile will complain. Delete the
    makefile and run `superconfigure` again.
* If you added the recipe correctly, run `make` to check successful compilation,
    and then try importing the package with the `./python -c 'import my_package'`.

For example, the APE includes [MarkupSafe 2.0.1][markupsafe] and
[greenlet][greenlet] alongside the stdlib, because I wanted to try
[Flask][flask].  `Modules/Setup.local` contains the recipe to compile the
`_speedup` component of the MarkupSafe package.

[py36]: https://docs.python.org/3.6/
[cosmo]: https://github.com/jart/cosmopolitan
[cstdlib]: https://en.cppreference.com/w/c/header
[markupsafe]: https://github.com/pallets/markupsafe/
[greenlet]: https://pypi.org/project/greenlet/
[flask]: https://github.com/pallets/flask/
