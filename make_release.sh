#!/bin/bash

mkdir -p bin
mkdir -p obj
mkdir -p obj/Release
make --directory=./obj/Release --makefile=../../Makefile build_flags="-O2 -fomit-frame-pointer" program_name=../../bin/application