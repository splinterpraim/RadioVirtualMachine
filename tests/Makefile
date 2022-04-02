
build_dir := build

gtest_dir := ./gtest_lib

gtest_cc := $(gtest_dir)/gtest-all.cc

outfile_name := unittest

tests_file := first_test.cpp

source := tested_file.cpp 


all: mkdir-build
	g++ -o $(build_dir)/$(outfile_name) $(source) $(tests_file)  -I$(gtest_dir)  $(gtest_cc) -pthread

mkdir-build:
	mkdir -p $(build_dir)

clean: 
	rm -rf $(build_dir)
