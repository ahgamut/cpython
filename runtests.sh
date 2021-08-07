#! /bin/sh
set -eux

./python.com.dbg -E -Wd -m test -L --slowest -f ./testlist.txt 2>&1
