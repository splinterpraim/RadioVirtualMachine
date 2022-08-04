


.DEFUALT=rvm_build

RVM_SRC := $(CUR_DIR)/src
RVM_INC := $(CUR_DIR)/include
RVM_TESTS := $(CUR_DIR)/tests

RVM_OBJ := main.o
rvm_build: $(RVM_OBJ)
	g++ -o rvm_run $(RVM_OBJ)


‰.o: $(RVM_TESTS)/‰.cpp
	g++ -c $^ -o $@
.PHONY: rvm_build
