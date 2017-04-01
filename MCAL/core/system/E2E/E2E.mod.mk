#E2E
obj-$(USE_E2E) += E2E.o
obj-$(USE_E2E) += E2E_P01.o
obj-$(USE_E2E) += E2E_P02.o
obj-$(USE_E2E) += E2E_P04.o
obj-$(USE_E2E) += E2E_P05.o
obj-$(USE_E2E) += E2E_P06.o
obj-$(USE_E2E) += E2E_SM.o
inc-$(USE_E2E) += $(ROOTDIR)/system/E2E
vpath-$(USE_E2E) += $(ROOTDIR)/system/E2E