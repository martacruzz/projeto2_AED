#!/usr/bin/env bash

cd ..
make &> /dev/null #don't appear
./GraphTester $1 $2 $3 $4 > GraphTester_tests/data.txt