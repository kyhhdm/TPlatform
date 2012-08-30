#!/bin/sh
echo $1
cat ../src/app/CMakeLists.examples.txt >> $1/examples/CMakeLists.txt
