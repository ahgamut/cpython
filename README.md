# `datasette.com`

This repo contains the necessary changes to build Simon Willison's `datasette`,
and minimum dependencies, on CPython3.11.4, as an Actually Portable Executable.

tested to work on Windows/Linux.

## Build steps

On Linux, the build steps are as follows:

1. Build the Cosmopolitan Libc toolchain,following the README.

2. export the necessary environment variables:

```sh
export COSMO=/opt/cosmo     # cosmo repo
export COSMOS=/opt/cosmos   # where you plan to install deps like libyaml
export CC=$COSMO/tool/scripts/cosmocc 
export CXX=$COSMO/tool/scripts/cosmoc++
export LD=$COSMO/tool/scripts/cosmoc++
```

3. Build the external dependencies like `sqlite`, `libyaml`, `openssl` etc.
  (check `Modules/Setup` for the others) using `cosmocc` from the Cosmopolitan
  Libc monorepo and my superconfigure scripts:
  https://github.com/ahgamut/superconfigure

4. Clone this repo.

5. run `superconfigure` and `make`.

6. run via `python.com -m datasette`. tested to work on Windows and Linux.
