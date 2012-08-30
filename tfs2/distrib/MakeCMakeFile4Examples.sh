#!/bin/sh

cp ../distrib/CMakeLists.txt.examples ../distrib/CMakeLists.txt.examples.ok
cat ../src/app/CMakeLists.examples.txt >> ../distrib/CMakeLists.txt.examples.ok
