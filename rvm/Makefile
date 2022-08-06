
# .DEFUALT=rvm_build
ifneq (,$(findstring xterm,${TERM}))
	BLACK        := $(shell tput -Txterm setaf 0)
	RED          := $(shell tput -Txterm setaf 1)
	GREEN        := $(shell tput -Txterm setaf 2)
	YELLOW       := $(shell tput -Txterm setaf 3)
	LIGHTPURPLE  := $(shell tput -Txterm setaf 4)
	PURPLE       := $(shell tput -Txterm setaf 5)
	BLUE         := $(shell tput -Txterm setaf 6)
	WHITE        := $(shell tput -Txterm setaf 7)
	RESET := $(shell tput -Txterm sgr0)
else
	BLACK        := ""
	RED          := ""
	GREEN        := ""
	YELLOW       := ""
	LIGHTPURPLE  := ""
	PURPLE       := ""
	BLUE         := ""
	WHITE        := ""
	RESET        := ""
endif

PHONY :=
# CONSTANTS ###################################
RVM_BIN := $(BIN_DIR)/rvm
RVM_SRC := $(CUR_DIR)/src
RVM_INC := $(CUR_DIR)/include
RVM_TESTS := $(CUR_DIR)/tests
RVM_INC_DIR := $(INC_DIR)/rvm
RVM_OBJ_DIR := $(OBJ_DIR)/rvm
RVM_OBJ := main.o test1.o test2.o
RVM_OBJ := $(addprefix $(RVM_OBJ_DIR)/,$(RVM_OBJ))
RVM_CXXFLAGS := -I$(RVM_INC_DIR)

#####################################
##################################### CONSTANTS
ECHO_RVM_BUILD := echo-build-rvm

# TARGETS ###################################
MKDIR_BUILD := $(RVM_OBJ_DIR) $(RVM_INC_DIR)
CP_INC  := copy-include

PHONY += rvm-build
rvm-build: $(ECHO_RVM_BUILD) $(MKDIR_BUILD) $(CP_INC) $(RVM_BIN)
	@echo "$(YELLOW)END BUILD RVM$(RESET)"

$(RVM_BIN):  $(RVM_OBJ)
	@echo "$(PURPLE)[LN]$(RESET) $@ <- ($(RVM_OBJ))"
	@g++ -o $@ $(RVM_OBJ)


$(RVM_OBJ_DIR)/%.o: $(RVM_SRC)/%.cpp
	@echo "$(GREEN)[CP]$(RESET) $@ <- $<"
	@g++ $(RVM_CXXFLAGS) -c $< -o $@ 

$(ECHO_RVM_BUILD):
	@echo "$(YELLOW)BUILD RVM$(RESET)"

rvm-clean:
	@echo "$(YELLOW)CLEAN RVM$(RESET)"
	@echo -n "$(RED)[DL]$(RESET) "
	rm -rf $(RVM_BIN) $(RVM_INC_DIR) $(RVM_OBJ_DIR)

# MKDIR 
$(RVM_OBJ_DIR):
	@mkdir -p $(RVM_OBJ_DIR) 

$(RVM_INC_DIR):
	@mkdir -p $(RVM_INC_DIR)

# COPY
copy-include:
	@cp -r $(RVM_INC)/* $(RVM_INC_DIR)/

ech:
	@echo $(RVM_OBJ_DIR)
	@echo $(RVM_OBJ)
	@echo $(RVM_TESTS)

.PHONY: $(PHONY)
#####################################
##################################### TARGETS
