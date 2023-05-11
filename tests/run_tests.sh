#!/bin/bash

TESTBIN="tests/bin"
COLOR_YELLOW="\033[38;5;11m"
COLOR_RESET="\033[0m"

error=0

for test in "$TESTBIN"/* ; do

	echo "\n"$COLOR_YELLOW"TEST:" $COLOR_RESET $test && "./$test" || error=1
done

exit $error
