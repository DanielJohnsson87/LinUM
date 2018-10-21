#MAKEFILE for main program
# Authors:
# Thomas Johansson
# DanielJohnsson
# Mårten Norman
#
# Date: 2018-10-15

SHELL = /bin/bash

#Variables

# main program of make file
TARGET = electrotest
PREFIX = /usr/local
# install dir for excutebals
EXEC_PREFIX = $(PREFIX)
# install for binaries
BINDIR = $(EXEC_PREFIX)/bin
# install dir for header files
INCLUDEDIR = $(PREFIX)/include
# install dir for libraies
LIBDIR = $(PREFIX)/lib
# defalut install command
INSTALL = install -m 775
# install command for main program
INSTALL_PROGRAM = $(INSTALL)
# install command for libraies
INSTALL_DATA = $(INSTALL) -t
# Local lib directory
LOCAL_LIBDIR = lib

CC = gcc
CFLAGS = -Wall -g -MMD 
INC = -I$(SRCDIR)/libcomponent \
	-I$(SRCDIR)/libpower \
	-I$(SRCDIR)/libresistance	

# Link options
LDFLAGS = -L$(LOCAL_LIBDIR) -Wl,-rpath,$(LOCAL_LIBDIR)
LDINSTALLFLAGS = -L$(LIBDIR) -Wl,-rpath,$(LIBDIR)
LDLIBS = -lcomponent -lpower -lresistance
#*************************************************************

SRCDIR = src
SOURCE = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCE:.c=.o)
DEP = $(OBJECTS:.o=.d)

HEADERS = $(wildcard $(SRCDIR)/libcomponent/*.h) \
		  $(wildcard $(SRCDIR)/libpower/*.h) \
		  $(wildcard $((SRCDIR)/libresistance/*.h))


# Linking of target after all libraies have been compiled
$(TARGET) : $(OBJECTS) | lib 
	$(CC) $(LDFLAGS) $< $(LDLIBS) -o $@

# Linking of target for install
installtarget :  $(OBJECTS) | lib 
	$(CC) $(LDINSTALLFLAGS) $< $(LDLIBS) -o $(TARGET)

# Complile and generate dependencies
%.o : %.c 
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

# Create local libray directory
libfolder: 
	mkdir -p $(LOCAL_LIBDIR)


# Create libraries 
.PHONEY: libcomponent
libcomponent : | libfolder
	$(MAKE) -C $(SRCDIR)/libcomponent
	cp $(SRCDIR)/libcomponent/libcomponent.so $(LOCAL_LIBDIR)/libcomponent.so

.PHONEY: libpower 
libpower: | libfolder
	$(MAKE) -C $(SRCDIR)/libpower
	cp $(SRCDIR)/libpower/libpower.so $(LOCAL_LIBDIR)/libpower.so

.PHONEY: libresistance 
libresistance: | libfolder
	$(MAKE) -C $(SRCDIR)/libresistance
	cp $(SRCDIR)/libresistance/libresistance.so $(LOCAL_LIBDIR)/libresistance.so


# Create all libraries
.PHONEY : lib
lib : libcomponent libpower libresistance 

.PHONEY : all
all: $(TARGET)

.PHONEY : clean
clean: 
	$(RM) $(OBJECTS) $(TARGET) $(DEP) 
	rm -rf $(LOCAL_LIBDIR)
	$(MAKE) -C $(SRCDIR)/libcomponent clean
	$(MAKE) -C $(SRCDIR)/libpower clean
	$(MAKE) -C $(SRCDIR)/libresistance clean

# Create all install dirs
.PHONEY :installdirs
installdirs:
	mkdir -p $(BINDIR)
	mkdir -p $(LIBDIR)
	mkdir -p $(INCLUDEDIR)


# Installation
.PHONEY : install
install : lib | installdirs 

	$(INSTALL_DATA) $(INCLUDEDIR) $(SRCDIR)/libcomponent/libcomponent.h
	$(INSTALL_DATA) $(INCLUDEDIR) $(SRCDIR)/libpower/libpower.h
	$(INSTALL_DATA) $(INCLUDEDIR) $(SRCDIR)/libresistance/libresistance.h

	$(INSTALL_DATA) $(LIBDIR) $(LOCAL_LIBDIR)/libcomponent.so
	$(INSTALL_DATA) $(LIBDIR) $(LOCAL_LIBDIR)/libpower.so
	$(INSTALL_DATA) $(LIBDIR) $(LOCAL_LIBDIR)/libresistance.so
	
	$(MAKE) installtarget

	$(INSTALL_PROGRAM) $(TARGET) $(BINDIR)/$(TARGET)


# Unistall
.PHONEY : uninstall
uninstall:
	$(RM) $(BINDIR)/$(TARGET)
	$(RM) $(LIBDIR)/libcomponent.so
	$(RM) $(LIBDIR)/libpower.so
	$(RM) $(LIBDIR)/libresistance.so
	$(RM) $(INCLUDEDIR)/libcomponent.h
	$(RM) $(INCLUDEDIR)/libpower.h
	$(RM) $(INCLUDEDIR)/libresistance.h
	
# include all dependecy files 
-include $(DEP)
