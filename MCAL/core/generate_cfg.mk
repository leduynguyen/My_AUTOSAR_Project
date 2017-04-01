VERBOSITY_LEVEL = INFO
PYTHON_BIN ?= "/c/Python27/python.exe"
#JAVA_VM_PATH = $(JAVA_HOME)\bin\javaw.exe - Add this in Arctic Studio env when running from Arcticv Studio

ifneq ($(JAVA_VM_PATH),)
JAVA_VM_ARGUMENT = -vm "$(JAVA_VM_PATH)"
PY_JAVA_VM_ARGUMENT = --vm "$(JAVA_VM_PATH)"
else
endif

# Point to the core dir (relative path is ok)
CORE_DIR ?= ../core

# Point to the dir used as temporary workspace.
TEMP_WSP ?= $(BDIR)/tmp/wsp

comma:= ,
semicolon:= ;
empty:=
space:= $(empty) $(empty)
csl = $(subst $(space),$(comma),$(1))

$(TEMP_WSP):
	@echo MAKE: Generating $@
	mkdir -p $(TEMP_WSP)
	$(ECLIPSE_BIN) $(JAVA_VM_ARGUMENT) -application com.arccore.cli.projectimporter -verbosity DEBUG -data $(TEMP_WSP) -project $(CORE_DIR)

# $(1) - File to generate (*_Lcfg.c ..)
# $(2) - Configuration ARXMLs
# $(3) - Ecuc (in configuration ARXML)
# $(4) - Modules (i.e. Lin, Can etc)
# $(5) - Generators (for depedency)
define ADD_CONFIG_FILE
$(1): $(2) $(5) | $(TEMP_WSP)
ifeq ($(DEBUG),ON)
	@echo MAKE: Registering $(1) for Module: $(4) in Ecuc: $(3) using arxml-files: $(2)
else
	@echo MAKE: Adding: $(1)
endif
	@$(PYTHON_BIN) scripts/CLIGeneration/gen_buffer.py -a register -i "$(3)" -x $(sort $(2)) -m $(4)
endef

# $(1) Project Name (i.e. name of test)
# $(2) BSW Module CamelCase Name (i.e. Lin, LinSM, Can etc)
define ADD_MODULE
$(info Adding module: $(2))
$(foreach cfg_file,$($(1)_$(2)_CONFIG_FILES),$(eval $(call ADD_CONFIG_FILE,$(cfg_file),$($(1)_$(2)_ARXML_FILES),$($(1)_ECUC),$(2),$($(1)_$(2)_GEN))))
endef

# $(1) Project Name (i.e. name of test)
define ADD_GEN_RULE
$(BDIR)/$(1)_PREGEN_MARKER: $($(1)_PREGEN_RULES)
	touch $(BDIR)/$(1)_PREGEN_MARKER

.PHONY: $(1)
$(1): $($(1)_CONFIG_FILES) $(BDIR)/$(1)_PREGEN_MARKER
	@$(PYTHON_BIN) scripts/CLIGeneration/gen_buffer.py -a generate -i $($(1)_ECUC) $(PY_JAVA_VM_ARGUMENT) -e $(ECLIPSE_BIN) --ecuc $($(1)_ECUC) -p TempProject -o $($(1)_DIR) -d $(TEMP_WSP)
	@-rm -f generation_registry.json

.PHONY: clean_$(1)
clean_$(1):
	-rm -f $($(1)_DIR)/generate_$(1)

.PHONY: clean_$(1)_PREGEN_MARKER
clean_$(1)_PREGEN_MARKER:
	-rm $(BDIR)/$(1)_PREGEN_MARKER

clean_$(1)_cfg:
	-rm -f $($(1)_CONFIG_FILES)

CLEAN_RULES += clean_$(1)
CLEAN_CFG_RULES += clean_$(1)_cfg
CLEAN_MARKER_RULES += clean_$(1)_PREGEN_MARKER
ALL_RULES += $(1)
endef

include $(BDIR)/gen.mk

.PHONY: all
all: $(ALL_RULES)

.PHONY: soft_clean
soft_clean: $(CLEAN_RULES) $(CLEAN_MARKER_RULES)
	-rm -rdf $(TEMP_WSP)
	-rm -f generation_registry.json

.PHONY: clean
clean: soft_clean $(CLEAN_CFG_RULES)
