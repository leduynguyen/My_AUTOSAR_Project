#SchM
inc-y += $(ROOTDIR)/system/SchM
vpath-$(USE_SCHM) += $(ROOTDIR)/system/SchM
ifeq ($(filter SchM.o,$(obj-y)),)
obj-$(USE_SCHM) += SchM.o
endif