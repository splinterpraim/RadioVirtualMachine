# $(info START ROOT MAKEFILE)

.DEFUALT = main

# CONSTANTS ###################################
ROOT_DIR := .
BUILD_DIR := $(ROOT_DIR)/build
BIN_DIR := $(BUILD_DIR)/bin
INC_DIR := $(BUILD_DIR)/include
LIB_DIR := $(BUILD_DIR)/lib
OBJ_DIR := $(BUILD_DIR)/obj
SHARE_DIR := $(BUILD_DIR)/share


# RVM 
RVM_DIR := $(ROOT_DIR)/rvm
RVM_dep := 

#FC



#####################################
##################################### CONSTANTS


# PARAMS ###################################
MAIN_ARGS := ROOT_DIR=$(ROOT_DIR) BUILD_DIR=$(BUILD_DIR) BIN_DIR=$(BIN_DIR) INC_DIR=$(INC_DIR) LIB_DIR=$(LIB_DIR) OBJ_DIR=$(OBJ_DIR) SHARE_DIR=$(SHARE_DIR)
#####################################
##################################### PARAMS






# TARGETS ###################################
MKDIR_BUILD := $(BUILD_DIR) $(BIN_DIR) $(INC_DIR) $(LIB_DIR) $(OBJ_DIR) $(SHARE_DIR)

PHONY := main
main: $(MKDIR_BUILD) rvm 



PHONY += rvm
rvm: $(RVM_dep) 
	@make -C $(ROOT_DIR) -f $(RVM_DIR)/Makefile $(MAIN_ARGS) CUR_DIR=$(RVM_DIR) --no-print-directory






#MKDIR
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(INC_DIR):
	@mkdir -p $(INC_DIR)

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(SHARE_DIR):
	@mkdir -p $(SHARE_DIR)


# CLEAN
clean:
	rm -rf $(BUILD_DIR)
.PHONY: $(PHONY)

#####################################
##################################### TARGETS

# $(info FINISH ROOT MAKEFILE)
