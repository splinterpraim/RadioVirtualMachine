
# .DEFUALT=rvm_build



PHONY :=
# CONSTANTS ###################################
# CMN_BIN := $(BIN_DIR)/rvm
# RVM_SRC := $(CUR_DIR)/src
CMN_INC := $(CUR_DIR)/include
# RVM_TESTS := $(CUR_DIR)/tests
CMN_INC_DIR := $(INC_DIR)/common
CMN_OBJ_DIR := $(OBJ_DIR)/common
CMN_CXXFLAGS := -std=c++14 -I$(CMN_INC_DIR)

# RVM_TEMPLATE_FIND_CPP := $(RVM_SRC)/*.cpp $(RVM_SRC)/*/*.cpp
# RVM_ALL_CPP := $(wildcard $(RVM_TEMPLATE_FIND_CPP))
# RVM_ALL_CPP_DIRS = $(subst $(RVM_SRC)/, ,$(dir $(RVM_ALL_CPP)))
# RVM_ALL_CPP_WITH_DIRS = $(subst $(RVM_SRC)/, ,$(RVM_ALL_CPP))
# RVM_CREATE_OBJ_SUBDIR := $(foreach d,$(RVM_ALL_CPP_DIRS),$(shell mkdir -p $(RVM_OBJ_DIR)/$(d)))
# RVM_OBJ := $(patsubst %.cpp,%.o,$(RVM_ALL_CPP_WITH_DIRS))
# RVM_OBJ := $(addprefix $(RVM_OBJ_DIR)/,$(RVM_OBJ))
#####################################
##################################### CONSTANTS

# INCLUDES ###################################
include $(CONF_DIR)/Makefile.colors

#--------------------------------------------------------



ECHO_CMN_BUILD := echo-build-cmn

# TARGETS ###################################
MKDIR_BUILD := $(CMN_OBJ_DIR) $(CMN_INC_DIR)
CP_INC  := copy-include

PHONY += cmn-build
cmn-build: $(ECHO_CMN_BUILD) $(MKDIR_BUILD) $(CP_INC) 
	@echo "$(YELLOW)END BUILD COMMON$(RESET)"

# $(RVM_BIN):  $(RVM_OBJ)
# 	@echo "$(PURPLE)[LN]$(RESET) $@ <- ($(RVM_OBJ))"
# 	@g++ -o $@ $(RVM_OBJ)


# $(RVM_OBJ_DIR)/%.o: $(RVM_SRC)/%.cpp
# 	@echo "$(GREEN)[CP]$(RESET) $@ <- $<"
# 	@g++ $(RVM_CXXFLAGS) -c $< -o $@ 

$(ECHO_CMN_BUILD):
	@echo "$(YELLOW)BUILD COMMON$(RESET)"

PHONY += cmn-clean
cmn-clean:
	@echo "$(YELLOW)CLEAN COMMON$(RESET)"
	@echo -n "$(RED)[DL]$(RESET) "
	rm -rf $(CMN_INC_DIR) $(CMN_OBJ_DIR)

# MKDIR 
$(CMN_OBJ_DIR):
	@mkdir -p $(CMN_OBJ_DIR) 

$(CMN_INC_DIR):
	@mkdir -p $(CMN_INC_DIR)

# COPY
PHONY += $(CP_INC)
$(CP_INC):
	@echo "$(GREEN)[COPY]$(RESET) $(CMN_INC_DIR) <- $(CMN_INC)"
	@cp -r $(CMN_INC)/* $(CMN_INC_DIR)/

# PHONY += ech
# ech:
# 	@echo $(CMN_OBJ)


.PHONY: $(PHONY)
#####################################
##################################### TARGETS
