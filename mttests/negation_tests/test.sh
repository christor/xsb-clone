#! /bin/sh

XEMU=$1
NUM=$2
options=$3

echo "-------------------------------------------------------"
echo "--- Running negation_tests/test.sh w. $NUM threads    ---"
echo "-------------------------------------------------------"

#------------------------------------
# tests involving definite tabling
#------------------------------------
# XEMU and options must be together in quotes
# convention is that to use test_single, leave the last argument of test
# goal uninstantiated to unify with the stream.

../gentest.sh "$XEMU $options" untabchain "test(10000,_)" $NUM
../gentest.sh "$XEMU $options" tabchain "test(10000,_)" $NUM
../gentest.sh "$XEMU $options" tabcycle "test(10000,_)" $NUM
../gentest.sh "$XEMU $options" tabsimp "test(10000,_)" $NUM


