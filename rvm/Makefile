


.DEFUALT=rvm_build

RVM_SRC := $(CUR_DIR)/src
RVM_INC := $(CUR_DIR)/include
RVM_TESTS := $(CUR_DIR)/tests
RVM_OBJ_DIR := $(OBJ_DIR)/rvm
RVM_OBJ := main.o
rvm_build: $(RVM_OBJ_DIR) $(RVM_OBJ)
	g++ -o rvm_run $(RVM_OBJ)


$(RVM_OBJ_DIR)/‰.o: $(RVM_TESTS)/‰.cpp
	g++ -c $^ -o $@
.PHONY: rvm_build
