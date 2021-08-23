#! /bin/sh
set -eux

./python.com -E -Wd -m test -L --slowest -f ./testlist.txt 2>&1
