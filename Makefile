
ROOT_DIR := ./



MAIN_ARGS := ROOT_DIR=ROOT_DIR

rvm: 
	make -f rvm/Makefile $(MAIN_ARGS)
