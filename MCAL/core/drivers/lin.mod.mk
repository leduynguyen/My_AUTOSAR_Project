# Lin
obj-$(USE_LIN) += Lin_PBcfg.o
obj-$(USE_LIN) += Lin_Lcfg.o
obj-$(USE_LIN)-$(CFG_MPC560X) += LinFlex.o
obj-$(USE_LIN)-$(CFG_MPC5744P) += LinFlex.o
obj-$(USE_LIN)-$(CFG_MPC5746C) += LinFlex.o
obj-$(USE_LIN)-$(CFG_MPC5748G) += LinFlex.o
obj-$(USE_LIN)-$(CFG_MPC5777M) += LinFlex.o
obj-$(USE_LIN)-$(CFG_MPC5643L) += LinFlex.o
obj-$(USE_LIN)-$(CFG_SPC56XL70) += LinFlex.o
obj-$(USE_LIN)-$(CFG_MPC5645S) += LinFlex.o
obj-$(USE_LIN)-$(CFG_MPC560X) += LinFlex_Common.o
obj-$(USE_LIN)-$(CFG_MPC5744P) += LinFlex_Common.o
obj-$(USE_LIN)-$(CFG_MPC5746C) += LinFlex_Common.o
obj-$(USE_LIN)-$(CFG_MPC5748G) += LinFlex_Common.o
obj-$(USE_LIN)-$(CFG_MPC5777M) += LinFlex_Common.o
obj-$(USE_LIN)-$(CFG_MPC5643L) += LinFlex_Common.o
obj-$(USE_LIN)-$(CFG_SPC56XL70) += LinFlex_Common.o
obj-$(USE_LIN)-$(CFG_MPC5645S) += LinFlex_Common.o
obj-$(USE_LIN)-$(CFG_MPC5516) += Lin.o
obj-$(USE_LIN)-$(CFG_MPC5567) += Lin.o
obj-$(USE_LIN)-$(CFG_MPC563XM) += Lin.o
obj-$(USE_LIN)-$(CFG_MPC5644A) += Lin.o
obj-$(USE_LIN)-$(CFG_MPC5668) += Lin.o
obj-$(USE_LIN)-$(CFG_ZYNQ) += Lin.o
obj-$(USE_LIN)-$(CFG_JAC6) += Lin.o

#Jacinto6 reqiures timer for hwbug
#obj-$(USE_LIN)-$(CFG_JAC6) += Timer.o