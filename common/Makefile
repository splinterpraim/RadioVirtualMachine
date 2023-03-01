# libcommon.a
.DEFUALT=cmn-build
# INCLUDES ###################################
include $(CONF_DIR)/Makefile.colors
include $(CONF_DIR)/Makefile.settings



PHONY :=
# CONSTANTS ###################################
CMN_BIN := $(LIB_DIR)/libcommon.a
CMN_SRC := $(CUR_DIR)/src
CMN_INC := $(CUR_DIR)/include
# RVM_TESTS := $(CUR_DIR)/tests
CMN_INC_DIR := $(INC_DIR)/common
CMN_OBJ_DIR := $(OBJ_DIR)/common
CMN_CXXFLAGS := $(DEBUG_FLAGS) -std=c++14 -I$(CMN_INC_DIR)

CMN_TEMPLATE_FIND_CPP := $(CMN_SRC)/*.cpp $(CMN_SRC)/*/*.cpp
CMN_ALL_CPP := $(wildcard $(CMN_TEMPLATE_FIND_CPP))
CMN_ALL_CPP_DIRS = $(subst $(CMN_SRC)/, ,$(dir $(CMN_ALL_CPP)))
CMN_ALL_CPP_NO_SRCDIR = $(subst $(CMN_SRC)/, ,$(CMN_ALL_CPP))
CMN_CREATE_OBJ_SUBDIR := $(foreach d,$(CMN_ALL_CPP_DIRS),$(shell mkdir -p $(CMN_OBJ_DIR)/$(d)))
CMN_OBJ := $(patsubst %.cpp,%.o,$(CMN_ALL_CPP_NO_SRCDIR))
CMN_OBJ := $(addprefix $(CMN_OBJ_DIR)/,$(CMN_OBJ))
#####################################
##################################### CONSTANTS




#--------------------------------------------------------


CMN := cmn-build
ECHO_CMN_BUILD := echo-build-cmn

# TARGETS ###################################
MKDIR_BUILD := $(CMN_OBJ_DIR) $(CMN_INC_DIR)
CP_INC  := copy-include

PHONY += cmn-build
cmn-build: $(ECHO_CMN_BUILD) $(MKDIR_BUILD) $(CP_INC) $(CMN_BIN)
	@echo "$(YELLOW)END BUILD COMMON LIB$(RESET)"

$(CMN_BIN):  $(CMN_OBJ)
	@echo "$(PURPLE)[LN]$(RESET) $@ <- ($(CMN_OBJ))"
	ar -rc $@ $(CMN_OBJ)
	ranlib $@


$(CMN_OBJ_DIR)/%.o: $(CMN_SRC)/%.cpp
	@echo "$(GREEN)[CP]$(RESET) $@ <- $<"
	@g++ -c $< -o $@ $(CMN_CXXFLAGS)

$(ECHO_CMN_BUILD):
	@echo "$(YELLOW)BUILD COMMON LIB$(RESET)"

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
