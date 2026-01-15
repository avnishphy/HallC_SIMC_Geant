include ./rules.make
# Makefile for the ROOT test programs.
# This Makefile shows nicely how to compile and link applications
# using the ROOT libraries on all supported platforms.
#
# Copyright (c) 2000 Rene Brun and Fons Rademakers
#
# Author: Fons Rademakers, 29/2/2000

ARCH          = linuxegcs

CXX           =
ObjSuf        = o
SrcSuf        = cxx
ExeSuf        =
DllSuf        = so
OutPutOpt     = -o 
DictSuf       = Dict.o

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)



ifeq ($(ARCH),linux)
# Linux with gcc 2.7.2.x
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif

ifeq ($(ARCH),linuxrh42)
# Linux with gcc 2.7.2.x (RedHat 4.2)
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif

ifeq ($(ARCH),linuxdeb)
# Linux with gcc 2.7.2.x
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif

ifeq ($(ARCH),linuxdeb2)
# Linux with gcc 2.7.2.x
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif

ifeq ($(ARCH),linuxsuse6)
# Linux with gcc 2.7.2.x
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif

ifeq ($(ARCH),linuxegcs)
# Linux with egcs (>= RedHat 5.2)
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif

ifeq ($(ARCH),linuxkcc)
# Linux with the KAI compiler
CXX           = KCC
CXXFLAGS      = -fPIC +K0
LD            = KCC
LDFLAGS       = -O
SOFLAGS       =
endif

ifeq ($(ARCH),linuxppcegcs)
# MkLinux with egcs/glibc
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared -Wl,-soname,
endif

ifeq ($(ARCH),linuxia64gcc)
# Itanium Linux with gcc 2.9x
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif

ifeq ($(ARCH),linuxia64sgi)
# Itanium Linux with sgiCC
CXX           = sgiCC
CXXFLAGS      = -O -Wall -fPIC
LD            = gsgiCC
LDFLAGS       = -O
SOFLAGS       = -shared
endif

ifeq ($(ARCH),linuxalphaegcs)
# Alpha Linux with egcs
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif

ifeq ($(ARCH),linuxarm)
# ARM Linux with egcs
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif

ifeq ($(CXX),)
$(error $(ARCH) invalid architecture)
endif

CXXFLAGS     += $(ROOTCFLAGS)
CXXFLAGS     += -ggdb
LIBS          = $(ROOTLIBS) $(SYSLIBS) 
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)

#------------------------------------------------------------------------------

SRC := $(shell ls T*.cxx -1 | grep -v Dict)
HEA :=$(SRC:%.cxx=%.h)
OBJS :=$(SRC:%.cxx=%.$(ObjSuf))
DOBJS :=$(SRC:%.cxx=%Dict.$(ObjSuf))
LIBR :=$(SRC:%.cxx=lib%.$(DllSuf))

ARSRC := $(shell ls TARS*.cxx)
ARSRC += TDouble.cxx TShort.cxx TDoubleArray.cxx TShortArray.cxx
AOBJS :=$(ARSRC:%.cxx=%.$(ObjSuf))
ADOBJS :=$(ARSRC:%.cxx=%Dict.$(ObjSuf))
ALIBR :=$(ARSRC:%.cxx=lib%.$(DllSuf))
ADALL :=$(AOBJS) $(ADOBJS)


DECSRC=THaArrayString.cxx  THaCrateMap.cxx THaEvData.cxx THaHelicity.cxx\
THaCodaData.cxx     THaEpicsStack.cxx  THaFastBusWord.cxx  THaSlotData.cxx\
THaCodaFile.cxx     THaEtClient.cxx    THaGenDetTest.cxx   THaUsrstrutils.cxx\
DECOBJS:=$(DECSRC:%.cxx=%.o)
#DECLIB:=$(DECSRC:%.cxx=lib%.so)

TDVCSBaseO           =TDVCSBase.$(ObjSuf) \
                       TDVCSBaseDict.$(ObjSuf)

TDVCSBaseS           =TDVCSBase.$(SrcSuf) \
                       TDVCSBaseDict.$(SrcSuf)

TDVCSBaseSO          =libTDVCSBase.$(DllSuf)

TDVCSDBO        =TDVCSDB.$(ObjSuf) \
                       TDVCSDBDict.$(ObjSuf)

TDVCSDBS           =TDVCSDB.$(SrcSuf) \
                       TDVCSDBDict.$(SrcSuf)

TDVCSDBSO          =libTDVCSDB.$(DllSuf)

TDVCSGeometryO       =TDVCSGeometry.$(ObjSuf) \
                      TDVCSGeometryDict.$(ObjSuf)

TDVCSGeometryS       =TDVCSGeometry.$(SrcSuf) \
                      TDVCSGeometryDict.$(SrcSuf)

TDVCSGeometrySO      =libTDVCSGeometry.$(DllSuf)

TDVCSParametersO       =TDVCSParameters.$(ObjSuf) \
                      TDVCSParametersDict.$(ObjSuf)

TDVCSParametersS       =TDVCSParameters.$(SrcSuf) \
                      TDVCSParametersDict.$(SrcSuf)

TDVCSParametersSO      =libTDVCSParameters.$(DllSuf)

TDVCSEventO          =TDVCSEvent.$(ObjSuf) \
                      TDVCSEventDict.$(ObjSuf)

TDVCSEventS          =TDVCSEvent.$(SrcSuf) \
                      TDVCSEventDict.$(SrcSuf)

TDVCSEventSO         =libTDVCSEvent.$(DllSuf)

TDVCSEventMCO          =TDVCSEventMC.$(ObjSuf) \
                      TDVCSEventMCDict.$(ObjSuf)

TDVCSEventMCS          =TDVCSEventMC.$(SrcSuf) \
                      TDVCSEventMCDict.$(SrcSuf)

TDVCSEventMCSO         =libTDVCSEventMC.$(DllSuf)

TCaloEventO          =TCaloEvent.$(ObjSuf) \
                      TCaloEventDict.$(ObjSuf)

TCaloEventS          = TCaloEvent.$(SrcSuf) \
                      TCaloEventDict.$(SrcSuf)

TCaloEventSO         = libTCaloEvent.$(DllSuf)

TPAEventO            =TPAEvent.$(ObjSuf) \
                        TPAEventDict.$(ObjSuf)

TPAEventS            = TPAEvent.$(SrcSuf) \
                        TPAEventDict.$(SrcSuf)

TPAEventSO           = libTPAEvent.$(DllSuf)

TCaloBaseO          = TCaloBase.$(ObjSuf) \
                      TCaloBaseDict.$(ObjSuf)

TCaloBaseS          = TCaloBase.$(SrcSuf) \
                      TCaloBaseDict.$(SrcSuf)

TCaloBaseSO          = libTCaloBase.$(DllSuf)

TCaloTriggerO          = TCaloTrigger.$(ObjSuf) \
                      TCaloTriggerDict.$(ObjSuf)

TCaloTriggerS          = TCaloTrigger.$(SrcSuf) \
                      TCaloTriggerDict.$(SrcSuf)

TCaloTriggerSO          = libTCaloTrigger.$(DllSuf)

TPATriggerO          = TPATrigger.$(ObjSuf) \
                      TPATriggerDict.$(ObjSuf)

TPATriggerS          = TPATrigger.$(SrcSuf) \
                      TPATriggerDict.$(SrcSuf)

TPATriggerSO          = libTPATrigger.$(DllSuf)

TPABaseO             = TPABase.$(ObjSuf) \
                       TPABaseDict.$(ObjSuf)

TPABaseS             = TPABase.$(SrcSuf) \
                       TPABaseDict.$(SrcSuf)

TPABaseSO            = libTPABase.$(DllSuf)

TCaloBlockO          = TCaloBlock.$(ObjSuf) \
                      TCaloBlockDict.$(ObjSuf)

TCaloBlockS          = TCaloBlock.$(SrcSuf) \
                      TCaloBlockDict.$(SrcSuf)

TCaloBlockSO         = libTCaloBlock.$(DllSuf)

TPABlockO            = TPABlock.$(ObjSuf) \
                        TPABlockDict.$(ObjSuf)

TPABlockS            = TPABlock.$(SrcSuf) \
                        TPABlockDict.$(SrcSuf)

TPABlockSO           = libTPABlock.$(DllSuf)

TCaloClusterO          = TCaloCluster.$(ObjSuf) \
                      TCaloClusterDict.$(ObjSuf)

TCaloClusterS          = TCaloCluster.$(SrcSuf) \
                      TCaloClusterDict.$(SrcSuf)

TCaloClusterSO         = libTCaloCluster.$(DllSuf)

TCaloGeometryO    = TCaloGeometry.$(ObjSuf) \
                      TCaloGeometryDict.$(ObjSuf)

TCaloGeometryS    = TCaloGeometry.$(SrcSuf) \
                      TCaloGeometryDict.$(SrcSuf)

TCaloGeometrySO   = libTCaloGeometry.$(DllSuf)

TCaloParametersO    = TCaloParameters.$(ObjSuf) \
                      TCaloParametersDict.$(ObjSuf)

TCaloParametersS    = TCaloParameters.$(SrcSuf) \
                      TCaloParametersDict.$(SrcSuf)

TCaloParametersSO   = libTCaloParameters.$(DllSuf)

TCaloCalibrationO    = TCaloCalibration.$(ObjSuf) \
                      TCaloCalibrationDict.$(ObjSuf)

TCaloCalibrationS    = TCaloCalibration.$(SrcSuf) \
                      TCaloCalibrationDict.$(SrcSuf)

TCaloCalibrationSO   = libTCaloCalibration.$(DllSuf)

TPAGeometryO        = TPAGeometry.$(ObjSuf) \
                      TPAGeometryDict.$(ObjSuf)

TPAGeometryS        = TPAGeometry.$(SrcSuf) \
                      TPAGeometryDict.$(SrcSuf)

TPAGeometrySO       = libTPAGeometry.$(DllSuf)

TPAParametersO      = TPAParameters.$(ObjSuf) \
                      TPAParametersDict.$(ObjSuf)

TPAParametersS      = TPAParameters.$(SrcSuf) \
                      TPAParametersDict.$(SrcSuf)

TPAParametersSO     = libTPAParameters.$(DllSuf)

TPACalibrationO     = TPACalibration.$(ObjSuf) \
                      TPACalibrationDict.$(ObjSuf)

TPACalibrationS     = TPACalibration.$(SrcSuf) \
                      TPACalibrationDict.$(SrcSuf)

TPACalibrationSO    = libTPACalibration.$(DllSuf)

TARSBaseO          =TARSBase.$(ObjSuf) \
                      TARSBaseDict.$(ObjSuf)

TARSBaseS          = TARSBase.$(SrcSuf) \
                      TARSBaseDict.$(SrcSuf)

TARSBaseSO         = libTARSBase.$(DllSuf)

TARSWaveO          =TARSWave.$(ObjSuf) \
                      TARSWaveDict.$(ObjSuf)

TARSWaveS          = TARSWave.$(SrcSuf) \
                      TARSWaveDict.$(SrcSuf)

TARSWaveSO         = libTARSWave.$(DllSuf)

TARSChannelO          =TARSChannel.$(ObjSuf) \
                      TARSChannelDict.$(ObjSuf)

TARSChannelS          = TARSChannel.$(SrcSuf) \
                      TARSChannelDict.$(SrcSuf)

TARSChannelSO         = libTARSChannel.$(DllSuf)

TFloatO          =TFloat.$(ObjSuf) \
                      TFloatDict.$(ObjSuf)

TFloatS          = TFloat.$(SrcSuf) \
                      TFloatDict.$(SrcSuf)

TFloatSO         = libTFloat.$(DllSuf)

TBlockO           =TBlock.$(ObjSuf) \
                       TBlockDict.$(ObjSuf)

TBlockS           =TBlock.$(SrcSuf) \
                       TBlockDict.$(SrcSuf)

TBlockSO          =libTBlock.$(DllSuf)

TARSArrayO           =TARSArray.$(ObjSuf) \
                       TARSArrayDict.$(ObjSuf)

TARSArrayS           =TARSArray.$(SrcSuf) \
                       TARSArrayDict.$(SrcSuf)

TARSArraySO          =libTARSArray.$(DllSuf)

TShortO          =TShort.$(ObjSuf) \
                      TShortDict.$(ObjSuf)

TShortS          = TShort.$(SrcSuf) \
                      TShortDict.$(SrcSuf)

TShortSO         = libTShort.$(DllSuf)

TShortArrayO          =TShortArray.$(ObjSuf) \
                      TShortArrayDict.$(ObjSuf)

TShortArrayS          = TShortArray.$(SrcSuf) \
                      TShortArrayDict.$(SrcSuf)

TShortArraySO         = libTShortArray.$(DllSuf)

MAINO               = Calana.$(ObjSuf)
MAINS               = Calana.$(SrcSuf)
MAIN                = Calana$(ExeSuf)

MAIN2O               = msqltomysql.$(ObjSuf)
MAIN2S               = msqltomysql.$(SrcSuf)
MAIN2                = msqltomysql$(ExeSuf)

CODALIBS =  libevio.so  libswap.so libet.so


#OBJS          = $(TDVCSBaseO) $(TDVCSGeometryO) $(TDVCSParametersO) $(TDVCSEventMCO) $(TDVCSEventO) $(TCaloEventO) $(TCaloBlockO) $(TCaloClusterO) $(TCaloBaseO) $(TCaloGeometryO) $(TCaloParametersO) $(TCaloCalibrationO) $(TARSBaseO) $(TARSWaveO) $(TARSChannelO) $(TPABaseO) $(TPAGeometryO) $(TPAParametersO) $(TPACalibrationO) $(TPAEventO) $(TPABlockO) $(TCaloTriggerO) $(TFloatO) $(TShortO) $(TPATriggerO) $(TBlockO) $(TARSArrayO) $(TShortArrayO) $(MAINO) $(MAIN2O)

SLIB          = $(TDVCSBaseSO) $(TDVCSGeometrySO) $(TDVCSParametersSO) $(TDVCSEventMCSO) $(TDVCSEventSO) $(TCaloEventSO) $(TCaloBlockSO) $(TCaloClusterSO) $(TCaloBaseSO) $(TCaloGeometrySO) $(TCaloParametersSO) $(TARSBaseSO) $(TARSWaveSO) $(TARSChannelSO) $(TCaloCalibrationSO) $(TPABaseSO) $(TPAGeometrySO) $(TPAParametersSO) $(TPACalibrationSO) $(TPAEventSO) $(TPABlockSO) $(TCaloTriggerSO) $(TPATriggerSO) $(TFloatSO) $(TShortSO) $(TBlockSO) $(TARSArraySO) $(TShortArraySO) $(TDVCSDBSO)

PROGRAMS      = $(MAIN) $(MAIN2)

#------------------------------------------------------------------------------

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

all:            $(PROGRAMS) doc

lib:            $(SLIB)

doc:
	root.exe -b -q make_html.C

%.$(ObjSuf):%.$(SrcSuf) %.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

%Dict.$(SrcSuf):%.h
	rootcint -f $@ -c $<

$(MAIN): $(MAINO) $(SLIB) $(ADALL)
	$(LD) $(CXXFLAGS) $(LIBS) $^ -o $@ 

$(MAIN2): $(MAIN2O) libTDVCSDB.so
	$(LD) $(CXXFLAGS) $(LIBS) $^ -o $@ 

lib%.$(DllSuf): %Dict.$(ObjSuf) %.$(ObjSuf)
	$(LD) $(SOFLAGS) $(CXXFLAGS) $^ -o $@

vclean:
		@rm -f $(OBJS) core

distclean:      clean
		@rm -f $(PROGRAMS) $(SLIB) *Dict.* *.def

getsrc: $(LIBR)
	#echo $(SRC)
	#echo $(OBJS)
	#echo $(DOBJS)
	#echo $(LIBR)

Main: Main.o $(ADALL)
	echo $(ADALL)
	$(LD) $^ $(ROOTLIBS) -o $@


re: re.o $(ADALL)
	echo $(ADALL)
	$(LD) $^ $(ROOTLIBS) -o $@

Cal: $(LIBR) Calana.o $(CODALIBS)
	$(LD) $^ $(ROOTGLIBS) -L. -let -o Calana


clean_evio:
	rm -f evio.o swap_util.o swapped_intcpy.o

libevio.so: evio.o swapped_intcpy.o
	$(LD) -shared  $^ -o$@


libswap.so: swap_util.o
	$(LD) -shared $^ -o$@

sw : libevio.so libswap.so
	g++ -shared -fPIC  evio.o swapped_intcpy.o -olibevio.so

Ca: $(OBJS) $(DOBJS) THCalo.o THPA.o THPADict.o THCaloDict.o Calana.o
	$(LD) $^ $(ROOTGLIBS) -o Calana

decoder: decoder.o $(OBJS)  $(DOBJS) swap_util.o swapped_intcpy.o evio.o 
	echo $(OBJS)
	$(LD) $^ $(ROOTGLIBS) -o $@ -L$(CODA)/Linux/lib/ -let

decoderXY.o: decoderXY.C
	g++ -O -Wall -fPIC -D_REENTRANT  -I/usr/local/root//include -ggdb -c decoderXY.C

decoderXY: decoderXY.o $(OBJS)  $(DOBJS) swap_util.o swapped_intcpy.o evio.o 
	echo $(OBJS)
	$(LD) $^ $(ROOTGLIBS) -o $@ -L$(CODA)/Linux/lib/ -let

dec2: dec2.o $(OBJS)  $(DOBJS) swap_util.o swapped_intcpy.o evio.o 
	echo $(OBJS)
	$(LD) $^ $(ROOTGLIBS) -o $@ -L$(CODA)/Linux/lib/ -let

dec3: dec3.o $(OBJS)  $(DOBJS) swap_util.o swapped_intcpy.o evio.o 
	echo $(OBJS)
	$(LD) $^ $(ROOTGLIBS) -o $@ -L$(CODA)/Linux/lib/ -let

libet.so:
	cp libet.sav libet.so

disp:disp.o libTGDVCS.so $(OBJS) $(DOBJS) swap_util.o swapped_intcpy.o evio.o
	$(LD) $^ $(LIBS) $(ROOTGLIBS) -o $@ -L$(CODA)/Linux/lib/ -let

TDVCSGlobal2.o:
#	g++ $(INCLUDES) -c -fPIC TDVCSGlobal2.C
	g++ $(INCLUDES) -c -fPIC TDVCSGlobal2.cxx

TDVCSGlobal2Dict.o : TDVCSGlobal2.o  TDVCSGlobalDict.cxx TDVCSGlobalDict.o
#	rootcint -f TDVCSGlobal2Dict.cxx -c TDVCSGlobal2h TDVCSGlobal_LinkDef.h
	rootcint -f TDVCSGlobal2Dict.cxx -c TDVCSGlobal2.h TDVCSGlobal_LinkDef.h
	g++ -fPIC `root-config --cflags` -c TDVCSGlobal2Dict.cxx
	g++ -shared `root-config --cflags` -o libTDVCSGlobal2.so TDVCSGlobal2.o TDVCSGlobal2Dict.o 

biglib: $(OBJS) $(DOBJS) TDVCSGlobal2Dict.o TDVCSGlobal2.o
	$(LD) $(LIBS) $(SOFLAGS) $(CXXFLAGS) -lmysqlclient -L  /usr/lib64/mysql/ $^ -o libDVCS.so


ro: hrse_acceptance_maps2.o hrse.o
	$(LD) $^ $(ROOTGLIBS) $^ -o $@

libTJ.so: TJDict.o TJ.o hrse_acceptance_maps2.o hrse.o
	$(LD) $(SOFLAGS) $(CXXFLAGS) $^ -o $@
