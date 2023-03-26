#!/bin/bash
set -eu

declare -a args
args=()
for o in "$@" ; do
    case $o in
        "-lunwind") continue;;
        "-lutil") continue;;
        "-lrt") continue;;
        "-lc") continue;;
        "-lm") continue;;
        "-lpthread") continue;;
        "-lpthreads") continue;;
        "-lc_r") continue;;
        "-lcma") continue;;
        "-lgcc") continue;;
        "-lresolv") continue;;
        "-Wl,-Bdynamic") continue;;
        "-Wl,-Bstatic") continue;;
    esac
    args+=("$o")
done

gcc -fplugin=../portcosmo/portcosmo.so \
    "${args[@]}"
