#  DVCS rules to be included in makefile
#
#
#
#
   MAIND = $(shell touch temppwd.txt;pwd >>"temppwd.txt")
# determine the directory of the checkout
   DVCSMAINDIR =  $(DVCS_SOFT)
   ROOTLIBS      = $(shell root-config --libs)	
   ROOTGLIBS     = $(shell root-config --glibs)
   SODIR=$(DVCSMAINDIR)/lib
   HANADIR=$(DVCSMAINDIR)/v0.65

# Linux with egcs
   INCLUDES     += -I$(shell root-config --incdir)	
#   INCLUDES     += -I$(ANALYZER)/src
   INCLUDES	+= -I$(DVCSMAINDIR)/include
   INCLUDES	+= -I$(DVCSMAINDIR)/UsingNamespace.h 
   INCLUDES	+= -I$(DVCSMAINDIR)/v0.65/src
   INCLUDES	+= -I$(DVCSMAINDIR)/analysis
   INCLUDES	+= -include "./UsingNamespaceStd.h"

   MAKEDEPEND    = gcc
   CXX           = g++
#   CXXFLAGS      = -O -Wall -fno-rtti -fno-exceptions -fPIC $(INCLUDES)
   CXXFLAGS      = -O -Wall -ggdb -fno-exceptions -fPIC $(INCLUDES)
   LD            = g++
   LDFLAGS       = 
   SOFLAGS       = -shared
   TOOLLIB	 = $(DVCSMAINDIR)/arstool/libARSTool.so
   ANALIB 	 = $(DVCSMAINDIR)/analysis/libTRateClass.so
   DBLIBS	 = $(SODIR)/libTGetInfo.so $(SODIR)/libTRunI.so
   DECLIB 	 = libdec.so
   ETLIBS	= -L $(CODA)/Linux/ -let -lcoda
   HALIBS 	= -L ../v0.65/ -ldc -lHallA -lscaler
   OBJS = $(TOOLLIB) $(ANALIB) $(DBLIBS)
   ALLC := $(shell ls T*.cxx) 
   LIBT := $(ALLC:%.cxx=%.so)
   LIBTODO := $(addprefix lib,$(LIBT))	

%.o:%.cxx %.d
	$(CXX) $(CXXFLAGS) -c $<

%.o:%.C
	$(CXX) $(CXXFLAGS) -c $<

%.o:%.cc
	$(CXX) $(CXXFLAGS) -c $<

%Dict.cxx:%.h
	rootcint -f $@ -c $<
	
%:%Dict.o %.o
	$(LD) $(CXXFLAGS) $^ -o $@ 

lib%.so: %Dict.o %.o 
	$(LD) $(SOFLAGS) $(CXXFLAGS) $^ -o $@
	#cp $@ $(DVCSMAINDIR)/lib

%.d:	%.cxx
	@echo Creating dependencies for $<
#	@$(SHELL) -ec '$(CXX) -MM $(CXXFLAGS) -c $< \
#		| sed '\''s%\($*\)\.o[ :]*%\1.o $@ : %g'\'' > $@; \
#		[ -s $@ ] || rm -f $@'
	@$(SHELL) -ec '$(MAKEDEPEND) -MM $(INCLUDES) -c $< \
		| sed '\''s%^.*\.o%$*\.o%g'\'' \
		| sed '\''s%\($*\)\.o[ :]*%\1.o $@ : %g'\'' > $@; \
		[ -s $@ ] || rm -f $@'

libs: $(LIBTODO)
	touch rootlogon.C
	
	$(shell echo {$(foreach obj,$(LIBTODO),gSystem->Load("$(obj)");)}>>"rootlogon.C")
	echo "Making libs..."

m:
	$(MAIND)

maindir:
	echo $(DVCSMAINDIR)

clean:
	rm G*.h *Dict* *.o *.so *~ *# core

getdir: getdir.cc 
	$(CXX) getdir.cc $(INCLUDES) -o getdir
	mv getdir ~/bin/	
	


