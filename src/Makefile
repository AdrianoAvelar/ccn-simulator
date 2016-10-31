#
# OMNeT++/OMNEST Makefile for ccnpp
#
# This file was generated with the command:
#  opp_makemake -f --deep -I../../inet-3.0/src/inet/linklayer/common -I../../inet-3.0/src -I../../inet-3.0/src/inet/transportlayer/contract/udp -I../../inet-3.0/src/inet/networklayer/contract/ipv6 -I../include -I../../inet-3.0/src/inet/routing/ospfv2/messagehandler -I../../inet-3.0/src/inet/common/queue -I../../inet-3.0/src/inet/routing/ospfv2 -I../../inet-3.0/src/inet/networklayer/contract/ipv4 -I../../inet-3.0/src/inet/common -I../../inet-3.0/src/inet/networklayer/common -I../../inet-3.0/src/inet/networklayer/ipv4 -I../../inet-3.0/src/inet/networklayer/contract -L../../inet-3.0/out/$$\(CONFIGNAME\)/src -lgpac -lINET -DINET_IMPORT -KINET_PROJ=../../inet-3.0
#

# Name of target to be created (-o option)
TARGET = ccnpp$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../../inet-3.0/src/inet/linklayer/common \
    -I../../inet-3.0/src \
    -I../../inet-3.0/src/inet/transportlayer/contract/udp \
    -I../../inet-3.0/src/inet/networklayer/contract/ipv6 \
    -I../include \
    -I../../inet-3.0/src/inet/routing/ospfv2/messagehandler \
    -I../../inet-3.0/src/inet/common/queue \
    -I../../inet-3.0/src/inet/routing/ospfv2 \
    -I../../inet-3.0/src/inet/networklayer/contract/ipv4 \
    -I../../inet-3.0/src/inet/common \
    -I../../inet-3.0/src/inet/networklayer/common \
    -I../../inet-3.0/src/inet/networklayer/ipv4 \
    -I../../inet-3.0/src/inet/networklayer/contract \
    -I. \
    -IAppMessages \
    -Iapplication \
    -Icache \
    -Iccn-lite \
    -Icontent \
    -Inetwork \
    -Iospfn \
    -Iospfn/interface \
    -Iospfn/messagehandler \
    -Iospfn/neighbor \
    -Iospfn/router \
    -Ivideotraffic \
    -Ivideotraffic/FileHandlers \
    -Ivideotraffic/VideoHandlers \
    -Ivideotraffic/evalvid

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../../inet-3.0/out/$(CONFIGNAME)/src  -lgpac -lINET
LIBS += -Wl,-rpath,`abspath ../../inet-3.0/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/CcnInet.o \
    $O/Util.o \
    $O/Parser.o \
    $O/CcnAdmin.o \
    $O/shared.o \
    $O/Ccn.o \
    $O/CcnCore.o \
    $O/application/CcnDummyApp.o \
    $O/application/CcnVideoApp.o \
    $O/application/CcnMobilityAgent.o \
    $O/cache/prob_cache.o \
    $O/cache/lru_cache.o \
    $O/cache/base_cache.o \
    $O/cache/RankCache.o \
    $O/content/Ccnr.o \
    $O/content/zipf.o \
    $O/network/ForwardingTable.o \
    $O/ospfn/OSPFNNeighborhood.o \
    $O/ospfn/OSPFNRouting.o \
    $O/ospfn/interface/OSPFNInterfaceStateDown.o \
    $O/ospfn/interface/OSPFNInterfaceStatePointToPoint.o \
    $O/ospfn/interface/OSPFNInterfaceState.o \
    $O/ospfn/interface/OSPFNInterface.o \
    $O/ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.o \
    $O/ospfn/messagehandler/OSPFNLinkStateRequestHandler.o \
    $O/ospfn/messagehandler/OSPFNHelloHandler.o \
    $O/ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.o \
    $O/ospfn/messagehandler/OSPFNMessageHandler.o \
    $O/ospfn/neighbor/OSPFNNeighborState.o \
    $O/ospfn/neighbor/OSPFNNeighborStateFull.o \
    $O/ospfn/neighbor/OSPFNNeighbor.o \
    $O/ospfn/neighbor/OSPFNNeighborStateInit.o \
    $O/ospfn/neighbor/OSPFNNeighborStateExchangeStart.o \
    $O/ospfn/neighbor/OSPFNNeighborStateDown.o \
    $O/ospfn/router/OSPFNRouter.o \
    $O/videotraffic/VideoTrafficGenerator.o \
    $O/videotraffic/VideoTrace.o \
    $O/videotraffic/VideoTraffic.o \
    $O/videotraffic/QoEMetric.o \
    $O/videotraffic/FileHandlers/DumpFile.o \
    $O/videotraffic/FileHandlers/SenderTrace.o \
    $O/videotraffic/VideoHandlers/Stat.o \
    $O/videotraffic/VideoHandlers/Read.o \
    $O/videotraffic/VideoHandlers/WriteMP4.o \
    $O/videotraffic/VideoHandlers/Misc.o \
    $O/videotraffic/VideoHandlers/Bits.o \
    $O/videotraffic/VideoHandlers/EvaluateTrace.o \
    $O/videotraffic/VideoHandlers/Error.o \
    $O/CcnAppMessage_m.o \
    $O/CcnPacket_m.o \
    $O/AppMessages/MobilityAppMessage_m.o \
    $O/ospfn/OSPFNTimer_m.o \
    $O/ospfn/OSPFN_Event_m.o \
    $O/ospfn/OSPFNPacket_m.o \
    $O/videotraffic/VideoPacket_m.o

# Message files
MSGFILES = \
    CcnAppMessage.msg \
    CcnPacket.msg \
    AppMessages/MobilityAppMessage.msg \
    ospfn/OSPFNTimer.msg \
    ospfn/OSPFN_Event.msg \
    ospfn/OSPFNPacket.msg \
    videotraffic/VideoPacket.msg

# Other makefile variables (-K)
INET_PROJ=../../inet-3.0

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) -DINET_IMPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f ccnpp ccnpp.exe libccnpp.so libccnpp.a libccnpp.dll libccnpp.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f AppMessages/*_m.cc AppMessages/*_m.h
	$(Q)-rm -f application/*_m.cc application/*_m.h
	$(Q)-rm -f cache/*_m.cc cache/*_m.h
	$(Q)-rm -f ccn-lite/*_m.cc ccn-lite/*_m.h
	$(Q)-rm -f content/*_m.cc content/*_m.h
	$(Q)-rm -f network/*_m.cc network/*_m.h
	$(Q)-rm -f ospfn/*_m.cc ospfn/*_m.h
	$(Q)-rm -f ospfn/interface/*_m.cc ospfn/interface/*_m.h
	$(Q)-rm -f ospfn/messagehandler/*_m.cc ospfn/messagehandler/*_m.h
	$(Q)-rm -f ospfn/neighbor/*_m.cc ospfn/neighbor/*_m.h
	$(Q)-rm -f ospfn/router/*_m.cc ospfn/router/*_m.h
	$(Q)-rm -f videotraffic/*_m.cc videotraffic/*_m.h
	$(Q)-rm -f videotraffic/FileHandlers/*_m.cc videotraffic/FileHandlers/*_m.h
	$(Q)-rm -f videotraffic/VideoHandlers/*_m.cc videotraffic/VideoHandlers/*_m.h
	$(Q)-rm -f videotraffic/evalvid/*_m.cc videotraffic/evalvid/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc AppMessages/*.cc application/*.cc cache/*.cc ccn-lite/*.cc content/*.cc network/*.cc ospfn/*.cc ospfn/interface/*.cc ospfn/messagehandler/*.cc ospfn/neighbor/*.cc ospfn/router/*.cc videotraffic/*.cc videotraffic/FileHandlers/*.cc videotraffic/VideoHandlers/*.cc videotraffic/evalvid/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/Ccn.o: Ccn.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/CcnAdmin.o: CcnAdmin.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/Parser.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/CcnAppMessage_m.o: CcnAppMessage_m.cc \
	CcnAppMessage_m.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h
$O/CcnCore.o: CcnCore.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/lru_cache.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/CcnInet.o: CcnInet.cc \
	../include/CcnInet.h \
	../include/ForwardingTable.h \
	../include/Util.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/CcnPacket_m.o: CcnPacket_m.cc \
	CcnPacket_m.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h
$O/Parser.o: Parser.cc \
	../include/Parser.h
$O/Util.o: Util.cc \
	../include/Util.h \
	../include/ccnsim.h \
	../include/client.h \
	videotraffic/commons.h
$O/shared.o: shared.cc \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h
$O/AppMessages/MobilityAppMessage_m.o: AppMessages/MobilityAppMessage_m.cc \
	AppMessages/MobilityAppMessage_m.h
$O/application/CcnDummyApp.o: application/CcnDummyApp.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnDummyApp.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	videotraffic/FileHandlers/DumpFile.h \
	videotraffic/QoEMetric.h \
	videotraffic/VideoTrace.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/application/CcnMobilityAgent.o: application/CcnMobilityAgent.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/CcnMobilityAgent.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	AppMessages/MobilityAppMessage_m.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNRouting.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/application/CcnVideoApp.o: application/CcnVideoApp.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/CcnVideoApp.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	videotraffic/FileHandlers/DumpFile.h \
	videotraffic/QoEMetric.h \
	videotraffic/VideoTrace.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/cache/RankCache.o: cache/RankCache.cc \
	../include/RankCache.h \
	../include/Util.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/decision_policy.h \
	CcnPacket_m.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h
$O/cache/base_cache.o: cache/base_cache.cc \
	../include/RankCache.h \
	../include/Util.h \
	../include/always_policy.h \
	../include/base_cache.h \
	../include/betweenness_centrality.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/decision_policy.h \
	../include/fix_policy.h \
	../include/lcd_policy.h \
	../include/never_policy.h \
	../include/prob_cache.h \
	../include/statistics.h \
	CcnPacket_m.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h
$O/cache/lru_cache.o: cache/lru_cache.cc \
	../include/Ccnr.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/lru_cache.h \
	../include/shared.h \
	../include/zipf.h \
	CcnPacket_m.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h
$O/cache/prob_cache.o: cache/prob_cache.cc \
	../include/decision_policy.h \
	../include/prob_cache.h \
	CcnPacket_m.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h
$O/content/Ccnr.o: content/Ccnr.cc \
	../include/Ccnr.h \
	../include/Util.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnPacket_m.h \
	videotraffic/FileHandlers/DumpFile.h \
	videotraffic/FileHandlers/SenderTrace.h \
	videotraffic/VideoPacket_m.h \
	videotraffic/VideoTraffic.h \
	videotraffic/VideoTrafficGenerator.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h
$O/content/zipf.o: content/zipf.cc \
	../include/zipf.h
$O/network/ForwardingTable.o: network/ForwardingTable.cc \
	../include/ForwardingTable.h \
	../include/Util.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h
$O/ospfn/OSPFNNeighborhood.o: ospfn/OSPFNNeighborhood.cc \
	../include/ccnsim.h \
	../include/client.h \
	ospfn/OSPFNNeighborhood.h \
	ospfn/OSPFNcommon.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h
$O/ospfn/OSPFNPacket_m.o: ospfn/OSPFNPacket_m.cc \
	ospfn/OSPFNPacket_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h
$O/ospfn/OSPFNRouting.o: ospfn/OSPFNRouting.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNRouting.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/OSPFNTimer_m.o: ospfn/OSPFNTimer_m.cc \
	ospfn/OSPFNTimer_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h
$O/ospfn/OSPFN_Event_m.o: ospfn/OSPFN_Event_m.cc \
	ospfn/OSPFN_Event_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h
$O/ospfn/interface/OSPFNInterface.o: ospfn/interface/OSPFNInterface.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNRouting.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/interface/OSPFNInterfaceState.h \
	ospfn/interface/OSPFNInterfaceStateDown.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/interface/OSPFNInterfaceState.o: ospfn/interface/OSPFNInterfaceState.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/interface/OSPFNInterfaceState.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/interface/OSPFNInterfaceStateDown.o: ospfn/interface/OSPFNInterfaceStateDown.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/interface/OSPFNInterfaceState.h \
	ospfn/interface/OSPFNInterfaceStateDown.h \
	ospfn/interface/OSPFNInterfaceStatePointToPoint.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/interface/OSPFNInterfaceStatePointToPoint.o: ospfn/interface/OSPFNInterfaceStatePointToPoint.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/interface/OSPFNInterfaceState.h \
	ospfn/interface/OSPFNInterfaceStateDown.h \
	ospfn/interface/OSPFNInterfaceStatePointToPoint.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.o: ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/messagehandler/OSPFNHelloHandler.o: ospfn/messagehandler/OSPFNHelloHandler.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.o: ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/messagehandler/OSPFNLinkStateRequestHandler.o: ospfn/messagehandler/OSPFNLinkStateRequestHandler.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/messagehandler/OSPFNMessageHandler.o: ospfn/messagehandler/OSPFNMessageHandler.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/neighbor/OSPFNNeighbor.o: ospfn/neighbor/OSPFNNeighbor.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/neighbor/OSPFNNeighborStateDown.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/neighbor/OSPFNNeighborState.o: ospfn/neighbor/OSPFNNeighborState.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/neighbor/OSPFNNeighborStateDown.o: ospfn/neighbor/OSPFNNeighborStateDown.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/neighbor/OSPFNNeighborStateDown.h \
	ospfn/neighbor/OSPFNNeighborStateInit.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/neighbor/OSPFNNeighborStateExchangeStart.o: ospfn/neighbor/OSPFNNeighborStateExchangeStart.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/neighbor/OSPFNNeighborStateDown.h \
	ospfn/neighbor/OSPFNNeighborStateExchangeStart.h \
	ospfn/neighbor/OSPFNNeighborStateFull.h \
	ospfn/neighbor/OSPFNNeighborStateInit.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/neighbor/OSPFNNeighborStateFull.o: ospfn/neighbor/OSPFNNeighborStateFull.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/neighbor/OSPFNNeighborStateDown.h \
	ospfn/neighbor/OSPFNNeighborStateExchangeStart.h \
	ospfn/neighbor/OSPFNNeighborStateFull.h \
	ospfn/neighbor/OSPFNNeighborStateInit.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFTimer.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/interface/OSPFInterface.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/messagehandler/DatabaseDescriptionHandler.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/messagehandler/HelloHandler.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/messagehandler/IMessageHandler.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/messagehandler/LinkStateAcknowledgementHandler.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/messagehandler/LinkStateRequestHandler.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/messagehandler/LinkStateUpdateHandler.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/messagehandler/MessageHandler.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/neighbor/OSPFNeighbor.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/router/LSA.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/router/OSPFcommon.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/neighbor/OSPFNNeighborStateInit.o: ospfn/neighbor/OSPFNNeighborStateInit.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/neighbor/OSPFNNeighborStateDown.h \
	ospfn/neighbor/OSPFNNeighborStateExchangeStart.h \
	ospfn/neighbor/OSPFNNeighborStateInit.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/ospfn/router/OSPFNRouter.o: ospfn/router/OSPFNRouter.cc \
	../include/Ccn.h \
	../include/CcnAdmin.h \
	../include/CcnCore.h \
	../include/CcnInet.h \
	../include/Ccnr.h \
	../include/ForwardingTable.h \
	../include/ICcnApp.h \
	../include/Util.h \
	../include/base_cache.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnAppMessage_m.h \
	CcnPacket_m.h \
	ospfn/OSPFNPacket_m.h \
	ospfn/OSPFNTimer_m.h \
	ospfn/OSPFNcommon.h \
	ospfn/interface/OSPFNInterface.h \
	ospfn/messagehandler/IOSPFNMessageHandler.h \
	ospfn/messagehandler/OSPFNDatabaseDescriptionHandler.h \
	ospfn/messagehandler/OSPFNHelloHandler.h \
	ospfn/messagehandler/OSPFNLinkStateAcknowledgementHandler.h \
	ospfn/messagehandler/OSPFNLinkStateRequestHandler.h \
	ospfn/messagehandler/OSPFNMessageHandler.h \
	ospfn/neighbor/OSPFNNeighbor.h \
	ospfn/neighbor/OSPFNNeighborState.h \
	ospfn/router/OSPFNRouter.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/common/TLVOption.h \
	$(INET_PROJ)/src/inet/common/TLVOption_m.h \
	$(INET_PROJ)/src/inet/common/XMLUtils.h \
	$(INET_PROJ)/src/inet/common/queue/AbstractQueue.h \
	$(INET_PROJ)/src/inet/common/queue/QueueBase.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/common/IPProtocolId_m.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3AddressResolver.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkDatagram.h \
	$(INET_PROJ)/src/inet/networklayer/contract/INetworkProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoute.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IRoutingTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4ControlInfo_m.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4Datagram_m.h \
	$(INET_PROJ)/src/inet/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/inet/routing/ospfv2/OSPFPacket_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPControlInfo_m.h \
	$(INET_PROJ)/src/inet/transportlayer/contract/udp/UDPSocket.h
$O/videotraffic/QoEMetric.o: videotraffic/QoEMetric.cc \
	videotraffic/QoEMetric.h
$O/videotraffic/VideoPacket_m.o: videotraffic/VideoPacket_m.cc \
	videotraffic/VideoPacket_m.h
$O/videotraffic/VideoTrace.o: videotraffic/VideoTrace.cc \
	../include/Ccnr.h \
	../include/Util.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnPacket_m.h \
	videotraffic/FileHandlers/DumpFile.h \
	videotraffic/QoEMetric.h \
	videotraffic/VideoHandlers/EvaluateTrace.h \
	videotraffic/VideoHandlers/Misc.h \
	videotraffic/VideoHandlers/Read.h \
	videotraffic/VideoHandlers/Stat.h \
	videotraffic/VideoHandlers/WriteMP4.h \
	videotraffic/VideoTrace.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h
$O/videotraffic/VideoTraffic.o: videotraffic/VideoTraffic.cc \
	../include/Ccnr.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnPacket_m.h \
	videotraffic/FileHandlers/DumpFile.h \
	videotraffic/FileHandlers/SenderTrace.h \
	videotraffic/VideoHandlers/EvaluateTrace.h \
	videotraffic/VideoHandlers/Misc.h \
	videotraffic/VideoHandlers/Read.h \
	videotraffic/VideoHandlers/Stat.h \
	videotraffic/VideoHandlers/WriteMP4.h \
	videotraffic/VideoPacket_m.h \
	videotraffic/VideoTraffic.h \
	videotraffic/VideoTrafficGenerator.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h
$O/videotraffic/VideoTrafficGenerator.o: videotraffic/VideoTrafficGenerator.cc \
	../include/CcnAdmin.h \
	../include/Ccnr.h \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	../include/zipf.h \
	CcnPacket_m.h \
	videotraffic/FileHandlers/DumpFile.h \
	videotraffic/FileHandlers/SenderTrace.h \
	videotraffic/VideoPacket_m.h \
	videotraffic/VideoTrafficGenerator.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/ByteArray.h \
	$(INET_PROJ)/src/inet/common/ByteArray_m.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/common/RawPacket.h \
	$(INET_PROJ)/src/inet/common/RawPacket_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h
$O/videotraffic/FileHandlers/DumpFile.o: videotraffic/FileHandlers/DumpFile.cc \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	videotraffic/FileHandlers/DumpFile.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h
$O/videotraffic/FileHandlers/SenderTrace.o: videotraffic/FileHandlers/SenderTrace.cc \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	videotraffic/FileHandlers/DumpFile.h \
	videotraffic/FileHandlers/SenderTrace.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h
$O/videotraffic/VideoHandlers/Bits.o: videotraffic/VideoHandlers/Bits.cc \
	videotraffic/VideoHandlers/Bits.h
$O/videotraffic/VideoHandlers/Error.o: videotraffic/VideoHandlers/Error.cc \
	videotraffic/VideoHandlers/Error.h
$O/videotraffic/VideoHandlers/EvaluateTrace.o: videotraffic/VideoHandlers/EvaluateTrace.cc \
	../include/ccnsim.h \
	../include/client.h \
	../include/shared.h \
	videotraffic/FileHandlers/DumpFile.h \
	videotraffic/VideoHandlers/EvaluateTrace.h \
	videotraffic/VideoHandlers/Misc.h \
	videotraffic/VideoHandlers/Read.h \
	videotraffic/VideoHandlers/Stat.h \
	videotraffic/VideoHandlers/WriteMP4.h \
	videotraffic/commons.h \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/ModuleAccess.h \
	$(INET_PROJ)/src/inet/common/NotifierConsts.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/inet/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/inet/networklayer/common/L3Address.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModuleIdAddress.h \
	$(INET_PROJ)/src/inet/networklayer/common/ModulePathAddress.h \
	$(INET_PROJ)/src/inet/networklayer/contract/IInterfaceTable.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv4/IPv4Address.h \
	$(INET_PROJ)/src/inet/networklayer/contract/ipv6/IPv6Address.h
$O/videotraffic/VideoHandlers/Misc.o: videotraffic/VideoHandlers/Misc.cc \
	videotraffic/VideoHandlers/Misc.h
$O/videotraffic/VideoHandlers/Read.o: videotraffic/VideoHandlers/Read.cc \
	videotraffic/VideoHandlers/Misc.h \
	videotraffic/VideoHandlers/Read.h \
	videotraffic/commons.h
$O/videotraffic/VideoHandlers/Stat.o: videotraffic/VideoHandlers/Stat.cc \
	videotraffic/VideoHandlers/Stat.h \
	videotraffic/commons.h
$O/videotraffic/VideoHandlers/WriteMP4.o: videotraffic/VideoHandlers/WriteMP4.cc \
	videotraffic/VideoHandlers/Bits.h \
	videotraffic/VideoHandlers/Misc.h \
	videotraffic/VideoHandlers/WriteMP4.h \
	videotraffic/commons.h

