
build_dir := build

includes := ../include

source_dir := ../src

gtest_dir := ./gtest_lib

gtest_cc := $(gtest_dir)/gtest-all.cc

outfile_name := unittest

tests_file := tests.cpp


sources := /DO/fake_data_object.cpp 

sources_with_full_path := $(addprefix $(source_dir), $(sources))

all: mkdir-build
	g++ -o $(build_dir)/$(outfile_name) $(sources_with_full_path) $(tests_file) -I$(includes) -I$(gtest_dir)  $(gtest_cc) -pthread




mkdir-build:
	mkdir -p $(build_dir)

clean: 
	rm -rf $(build_dir)
