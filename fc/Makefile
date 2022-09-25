
# .DEFUALT=fc_build
# INCLUDES ###################################
include $(CONF_DIR)/Makefile.colors
include $(CONF_DIR)/Makefile.settings



PHONY :=
# CONSTANTS ###################################
FC_BIN := $(BIN_DIR)/fc
FC_SRC := $(CUR_DIR)/src
FC_INC := $(CUR_DIR)/include
FC_TESTS := $(CUR_DIR)/tests
FC_INC_DIR := $(INC_DIR)/fc
FC_OBJ_DIR := $(OBJ_DIR)/fc
FC_CXXFLAGS := $(DEBUG_FLAGS) -std=c++14 -I$(INC_DIR)/common -I$(FC_INC_DIR)

FC_TEMPLATE_FIND_CPP := $(FC_SRC)/*.cpp $(FC_SRC)/*/*.cpp
FC_ALL_CPP := $(wildcard $(FC_TEMPLATE_FIND_CPP))
FC_ALL_CPP_DIRS = $(subst $(FC_SRC)/, ,$(dir $(FC_ALL_CPP)))
FC_ALL_CPP_WITH_DIRS = $(subst $(FC_SRC)/, ,$(FC_ALL_CPP))
FC_CREATE_OBJ_SUBDIR := $(foreach d,$(FC_ALL_CPP_DIRS),$(shell mkdir -p $(FC_OBJ_DIR)/$(d)))
FC_OBJ := $(patsubst %.cpp,%.o,$(FC_ALL_CPP_WITH_DIRS))
FC_OBJ := $(addprefix $(FC_OBJ_DIR)/,$(FC_OBJ))
#####################################
##################################### CONSTANTS


#--------------------------------------------------------



ECHO_FC_BUILD := echo-build-fc

# TARGETS ###################################
MKDIR_BUILD := $(FC_OBJ_DIR) $(FC_INC_DIR)
CP_INC  := copy-include

PHONY += fc-build
fc-build: $(ECHO_FC_BUILD) $(MKDIR_BUILD) $(CP_INC) $(FC_BIN)
	@echo "$(YELLOW)END BUILD FC$(RESET)"

$(FC_BIN):  $(FC_OBJ)
	@echo "$(PURPLE)[LN]$(RESET) $@ <- ($(FC_OBJ))"
	@g++ -o $@ $(FC_OBJ)


$(FC_OBJ_DIR)/%.o: $(FC_SRC)/%.cpp
	@echo "$(GREEN)[CP]$(RESET) $@ <- $<"
	@g++ $(FC_CXXFLAGS) -c $< -o $@ 

$(ECHO_FC_BUILD):
	@echo "$(YELLOW)BUILD FC$(RESET)"

PHONY += fc-clean
fc-clean:
	@echo "$(YELLOW)CLEAN FC$(RESET)"
	@echo -n "$(RED)[DL]$(RESET) "
	rm -rf $(FC_BIN) $(FC_INC_DIR) $(FC_OBJ_DIR)

# MKDIR 
$(FC_OBJ_DIR):
	@mkdir -p $(FC_OBJ_DIR) 

$(FC_INC_DIR):
	@mkdir -p $(FC_INC_DIR)

# COPY
PHONY += copy-include
copy-include:
	@cp -r $(FC_INC)/* $(FC_INC_DIR)/

PHONY += ech
ech:
	@echo $(FC_OBJ)


.PHONY: $(PHONY)
#####################################
##################################### TARGETS
