
# .DEFUALT=rvm_build



PHONY :=
# CONSTANTS ###################################
RVM_BIN := $(BIN_DIR)/rvm
RVM_SRC := $(CUR_DIR)/src
RVM_INC := $(CUR_DIR)/include
RVM_TESTS := $(CUR_DIR)/tests
RVM_INC_DIR := $(INC_DIR)/rvm
RVM_OBJ_DIR := $(OBJ_DIR)/rvm
RVM_CXXFLAGS := -std=c++14 -I$(RVM_INC_DIR)

RVM_TEMPLATE_FIND_CPP := $(RVM_SRC)/*.cpp $(RVM_SRC)/*/*.cpp
RVM_ALL_CPP := $(wildcard $(RVM_TEMPLATE_FIND_CPP))
RVM_ALL_CPP_DIRS = $(subst $(RVM_SRC)/, ,$(dir $(RVM_ALL_CPP)))
RVM_ALL_CPP_WITH_DIRS = $(subst $(RVM_SRC)/, ,$(RVM_ALL_CPP))
RVM_CREATE_OBJ_SUBDIR := $(foreach d,$(RVM_ALL_CPP_DIRS),$(shell mkdir -p $(RVM_OBJ_DIR)/$(d)))
RVM_OBJ := $(patsubst %.cpp,%.o,$(RVM_ALL_CPP_WITH_DIRS))
RVM_OBJ := $(addprefix $(RVM_OBJ_DIR)/,$(RVM_OBJ))
#####################################
##################################### CONSTANTS

# INCLUDES ###################################
include $(CONF_DIR)/Makefile.colors

#--------------------------------------------------------



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

PHONY += rvm-clean
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
PHONY += copy-include
copy-include:
	@cp -r $(RVM_INC)/* $(RVM_INC_DIR)/

PHONY += ech
ech:
	@echo $(RVM_OBJ)


.PHONY: $(PHONY)
#####################################
##################################### TARGETS
