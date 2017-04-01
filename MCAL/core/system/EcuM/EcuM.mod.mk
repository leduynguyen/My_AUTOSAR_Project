#EcuMFixed
obj-$(USE_ECUM_FIXED) += EcuM.o
obj-$(USE_ECUM_FIXED) += EcuM_Fixed.o
obj-$(USE_ECUM_FIXED) += EcuM_Main.o
obj-$(USE_ECUM_FIXED) += EcuM_PBcfg.o
obj-$(USE_ECUM_FIXED) += EcuM_PBHeader.o
obj-$(USE_ECUM_FIXED) += EcuM_GeneratedCallouts.o
ifeq ($(filter EcuM_Callout_Stubs.o,$(obj-y)),)
obj-$(USE_ECUM_FIXED) += EcuM_Callout_Stubs.o
endif
inc-$(USE_ECUM_FIXED) += $(ROOTDIR)/system/EcuM
vpath-$(USE_ECUM_FIXED) += $(ROOTDIR)/system/EcuM

#EcuMFlexible
obj-$(USE_ECUM_FLEXIBLE) += EcuM.o
obj-$(USE_ECUM_FLEXIBLE) += EcuM_Flexible.o
obj-$(USE_ECUM_FLEXIBLE) += EcuM_PBcfg.o
obj-$(USE_ECUM_FLEXIBLE) += EcuM_PBHeader.o
obj-$(USE_ECUM_FLEXIBLE) += EcuM_GeneratedCallouts.o
ifeq ($(filter EcuM_Callout_Stubs.o,$(obj-y)),)
obj-$(USE_ECUM_FLEXIBLE) += EcuM_Callout_Stubs.o
endif
inc-$(USE_ECUM_FLEXIBLE) += $(ROOTDIR)/system/EcuM
vpath-$(USE_ECUM_FLEXIBLE) += $(ROOTDIR)/system/EcuM