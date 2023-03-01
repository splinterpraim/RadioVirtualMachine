
.DEFUALT=rvm-build
# INCLUDES ###################################
include $(CONF_DIR)/Makefile.colors
include $(CONF_DIR)/Makefile.settings

#--------------------------------------------------------


PHONY :=
# CONSTANTS ###################################
# BIN
RVM_BIN := $(BIN_DIR)/rvm
RVM_SRC := $(CUR_DIR)/src
RVM_INC := $(CUR_DIR)/include
RVM_INC_DIR := $(INC_DIR)/rvm
RVM_OBJ_DIR := $(OBJ_DIR)/rvm
RVM_CXXFLAGS := $(DEBUG_FLAGS) -std=c++14 -I$(INC_DIR)/common -I$(RVM_INC_DIR) 
RVM_LDFLAGS :=   -std=c++14 -L$(LIB_DIR) -lcommon $(LDFLAGS)

RVM_TEMPLATE_FIND_CPP := $(RVM_SRC)/*.cpp $(RVM_SRC)/*/*.cpp
RVM_ALL_CPP := $(wildcard $(RVM_TEMPLATE_FIND_CPP))
RVM_ALL_CPP_DIRS = $(subst $(RVM_SRC)/, ,$(dir $(RVM_ALL_CPP)))
RVM_ALL_CPP_WITH_DIRS = $(subst $(RVM_SRC)/, ,$(RVM_ALL_CPP))
RVM_CREATE_OBJ_SUBDIR := $(foreach d,$(RVM_ALL_CPP_DIRS),$(shell mkdir -p $(RVM_OBJ_DIR)/$(d)))
RVM_OBJ := $(patsubst %.cpp,%.o,$(RVM_ALL_CPP_WITH_DIRS))
RVM_OBJ := $(addprefix $(RVM_OBJ_DIR)/,$(RVM_OBJ))
#####################################
# TEST
RVM_TEST_BIN := $(BIN_DIR)/test_rvm
RVM_TEST_SRC := $(CUR_DIR)/tests
RVM_TEST_INC := $(CUR_DIR)/include

RVM_TEST_TEMPLATE_FIND_CPP := $(RVM_TEST_SRC)/*.cpp $(RVM_TEST_SRC)/*/*.cpp
RVM_TEST_ALL_CPP := $(wildcard $(RVM_TEST_TEMPLATE_FIND_CPP))
RVM_TEST_ALL_CPP_DIRS = $(subst $(RVM_TEST_SRC)/, ,$(dir $(RVM_TEST_ALL_CPP)))
RVM_TEST_ALL_CPP_WITH_DIRS = $(subst $(RVM_TEST_SRC)/, ,$(RVM_TEST_ALL_CPP))
RVM_TEST_CREATE_OBJ_SUBDIR := $(foreach d,$(RVM_TEST_ALL_CPP_DIRS),$(shell mkdir -p $(RVM_OBJ_DIR)/$(d)))
RVM_TEST_OBJ := $(patsubst %.cpp,%.o,$(RVM_TEST_ALL_CPP_WITH_DIRS))
RVM_TEST_OBJ := $(addprefix $(RVM_OBJ_DIR)/,$(RVM_TEST_OBJ))

RVM_OBJ_NO_MAIN := $(filter-out %main.o,$(RVM_OBJ))
##################################### CONSTANTS




RVM := rvm-build
RVM_TEST := rvm-build-test
ECHO_RVM_BUILD := echo-build-rvm
ECHO_RVM_BUILD_TEST := echo-build-rvm-test

# TARGETS ###################################
MKDIR_BUILD := $(RVM_OBJ_DIR) $(RVM_INC_DIR)
CP_INC  := copy-include

# RVM BUILD
PHONY += $(RVM)
$(RVM): $(ECHO_RVM_BUILD) $(MKDIR_BUILD) $(CP_INC) $(RVM_BIN)
	@echo "$(YELLOW)END BUILD RVM$(RESET)"

$(RVM_BIN):  $(RVM_OBJ)
	@echo "$(PURPLE)[LN]$(RESET) $@ <- ($(RVM_OBJ))"
	@g++ -o $@   $(RVM_OBJ) $(RVM_LDFLAGS)


$(RVM_OBJ_DIR)/%.o: $(RVM_SRC)/%.cpp
	@echo "$(GREEN)[CP]$(RESET) $@ <- $<"
	@g++ -c $< -o $@ $(RVM_CXXFLAGS)

$(ECHO_RVM_BUILD):
	@echo "$(YELLOW)BUILD RVM$(RESET)"

PHONY += rvm-clean
rvm-clean:
	@echo "$(YELLOW)CLEAN RVM$(RESET)"
	@echo -n "$(RED)[DL]$(RESET) "
	rm -rf $(RVM_BIN) $(RVM_INC_DIR) $(RVM_OBJ_DIR)



# RVM TEST
PHONY += $(RVM_TEST)
$(RVM_TEST): $(ECHO_RVM_BUILD_TEST) $(MKDIR_BUILD) $(CP_INC) $(RVM_TEST_BIN)
	@echo "$(YELLOW)END BUILD TEST RVM$(RESET)"

$(RVM_TEST_BIN):  $(RVM_TEST_OBJ) $(RVM_OBJ_NO_MAIN)
	@echo "$(PURPLE)[LN]$(RESET) $@ <- ($(RVM_TEST_OBJ))"
	@g++ -o $@ $(RVM_TEST_OBJ) $(RVM_OBJ_NO_MAIN)

$(RVM_OBJ_DIR)/%.o: $(RVM_TEST_SRC)/%.cpp
	@echo "$(GREEN)[CP]$(RESET) $@ <- $<"
	@g++ -c $< -o $@ $(RVM_CXXFLAGS)

$(ECHO_RVM_BUILD_TEST):
	@echo "$(YELLOW)BUILD TEST RVM$(RESET)"

PHONY += rvm-test-clean
rvm-test-clean:
	@echo "$(YELLOW)CLEAN TEST RVM$(RESET)"
	@echo -n "$(RED)[DL]$(RESET) "
	rm -rf $(RVM_TEST_BIN) $(RVM_INC_DIR) $(RVM_TEST_OBJ) 





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
	@echo $(RVM_MAIN)


.PHONY: $(PHONY)
#####################################
##################################### TARGETS
