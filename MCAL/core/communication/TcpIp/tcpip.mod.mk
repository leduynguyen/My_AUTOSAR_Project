#TCPIP
inc-$(USE_TCPIP) += $(ROOTDIR)/communication/TcpIp
vpath-$(USE_TCPIP) += $(ROOTDIR)/communication/TcpIp
ifeq ($(CFG_GNULINUX),y)
	obj-$(USE_TCPIP)-$(CFG_GNULINUX) += TcpIp_Linos.o
else
	obj-$(USE_TCPIP) += TcpIp.o
endif
obj-$(USE_TCPIP) += TcpIp_Cfg.o