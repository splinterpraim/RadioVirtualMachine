# $(info START ROOT MAKEFILE)



.DEFUALT = main
# CONSTANTS ###################################
ROOT_MAKEFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
ROOT_DIR := $(patsubst %/,%,$(dir $(ROOT_MAKEFILE_PATH)))
BUILD_DIR := $(ROOT_DIR)/build
BIN_DIR := $(BUILD_DIR)/bin
INC_DIR := $(BUILD_DIR)/include
LIB_DIR := $(BUILD_DIR)/lib
OBJ_DIR := $(BUILD_DIR)/obj
SHARE_DIR := $(BUILD_DIR)/share
CONF_DIR := $(ROOT_DIR)/config


# INCLUDES ###################################
include $(CONF_DIR)/Makefile.colors
include $(CONF_DIR)/Makefile.settings
#--------------------------------------------------------

MKDIR_BUILD := $(BUILD_DIR) $(BIN_DIR) $(INC_DIR) $(LIB_DIR) $(OBJ_DIR) $(SHARE_DIR)

# RVM 
RVM_DIR := $(ROOT_DIR)/rvm
RVM_dep := $(MKDIR_BUILD) cmn

# FC
FC_DIR := $(ROOT_DIR)/fc
FC_dep := $(MKDIR_BUILD) cmn

# CMN
CMN_DIR := $(ROOT_DIR)/common
CMN_dep := $(MKDIR_BUILD)

#####################################
##################################### CONSTANTS




# PARAMS ###################################
MAIN_ARGS := ROOT_DIR=$(ROOT_DIR) BUILD_DIR=$(BUILD_DIR) BIN_DIR=$(BIN_DIR) INC_DIR=$(INC_DIR) LIB_DIR=$(LIB_DIR) OBJ_DIR=$(OBJ_DIR) SHARE_DIR=$(SHARE_DIR) CONF_DIR=$(CONF_DIR)
#####################################
##################################### PARAMS






# TARGETS ###################################


PHONY := main
main: $(MKDIR_BUILD) cmn rvm fc


# RVM
PHONY += rvm
rvm: $(RVM_dep) 
	@make  -C $(ROOT_DIR) -f $(RVM_DIR)/Makefile $(MAIN_ARGS)  CUR_DIR=$(RVM_DIR) --no-print-directory

PHONY += rvm-test
rvm-test: $(RVM_dep) 
	@make  rvm-build-test -C $(ROOT_DIR) -f $(RVM_DIR)/Makefile $(MAIN_ARGS)  CUR_DIR=$(RVM_DIR) --no-print-directory

PHONY += rvm-clean
rvm-clean:
	@make rvm-clean -C $(ROOT_DIR) -f $(RVM_DIR)/Makefile $(MAIN_ARGS) CUR_DIR=$(RVM_DIR) --no-print-directory

PHONY += rvm-test-clean
rvm-test-clean:
	@make rvm-test-clean -C $(ROOT_DIR) -f $(RVM_DIR)/Makefile $(MAIN_ARGS) CUR_DIR=$(RVM_DIR) --no-print-directory


#  FC
PHONY += fc
fc: $(FC_dep) 
	@make  -C $(ROOT_DIR) -f $(FC_DIR)/Makefile $(MAIN_ARGS)  CUR_DIR=$(FC_DIR) --no-print-directory

PHONY += fc-clean
fc-clean:
	@make fc-clean -C $(ROOT_DIR) -f $(FC_DIR)/Makefile $(MAIN_ARGS) CUR_DIR=$(FC_DIR) --no-print-directory


# CMN
PHONY += cmn
cmn: $(CMN_dep) 
	@make  -C $(ROOT_DIR) -f $(CMN_DIR)/Makefile $(MAIN_ARGS)  CUR_DIR=$(CMN_DIR) --no-print-directory

cmn-clean:
	@make cmn-clean -C $(ROOT_DIR) -f $(CMN_DIR)/Makefile $(MAIN_ARGS) CUR_DIR=$(CMN_DIR) --no-print-directory


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
	@echo -n "$(RED)[DL]$(RESET) "
	rm -rf $(BUILD_DIR)
.PHONY: $(PHONY)

#####################################
##################################### TARGETS

# $(info FINISH ROOT MAKEFILE)


test:
	@echo $(ROOT_DIR)
