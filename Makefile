#MAKEFILE for main program
#Variables
SHELL = /bin/sh

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
INSTALL_DATA = $(INSTALL)
# Local lib directory
LOCAL_LIBDIR = ./lib

CC = gcc
CFLAGS = -Wall -g -MMD 
#LDFLAGS = -L$(SRC_DIR)/libcomponent \
#	-L$(SRC_DIR)/libpower \
#	-L$(SRC_DIR)/libresistance \
#	-Wl,-rpath,$(SRC_DIR)/libcomponent,$(SRC_DIR)/libpower,$(SRC_DIR)/libresistance

#LDFLAGS = -L./$(LOCAL_LIBDIR)/ -Wl,-rpath,./$(LOCAL_LIBDIR)/
LDFLAGS = -L$(LOCAL_LIBDIR) -Wl,-rpath,$(LOCAL_LIBDIR)

LDINSTALLFLAGS = -L$(LIBDIR) -Wl,-rpath,$(LIBDIR)
LDLIBS = -lcomponent -lpower -lresistance

INC = -I$(SRC_DIR)/libcomponent \
	-I$(SRC_DIR)/libpower \
	-I$(SRC_DIR)/libresistance	

SRC_DIR := src
SOURCE := $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCE:.c=.o)
HEADERS = $(wildcard $(SRC_DIR)/libcomponent/*.h) \
		  $(wildcard $(SRC_DIR)/libpower/*.h) \
		  $(wildcard $((SRC_DIR)/libresistance/*.h))
DEP = $(OBJECTS:.o=.d)
#LIBS = libcomponent libpower libresistance

# Linking
$(TARGET) : $(OBJECTS) libcomponent libpower libresistance
	$(CC) $(LDFLAGS) $< $(LDLIBS) -o $@

# Linking for install
installtarget : $(OBJECTS) lib 
	$(CC) $(LDINSTALLFLAGS) $< $(LDLIBS) -o $(TARGET)

# Complile and generate dependencies
%.o : %.c 
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

# Create local libray directory
libfolder: 
	mkdir -p $(LOCAL_LIBDIR)
	chmod 700 $(LOCAL_LIBDIR)

# Create libraries 
.PHONEY: libcomponent
libcomponent : | libfolder
	$(MAKE) -C $(SRC_DIR)/libcomponent
	cp $(SRC_DIR)/libcomponent/libcomponent.so $(LOCAL_LIBDIR)/libcomponent.so

.PHONEY: libpower 
libpower: | libfolder
	$(MAKE) -C $(SRC_DIR)/libpower
	cp $(SRC_DIR)/libpower/libpower.so $(LOCAL_LIBDIR)/libpower.so

.PHONEY: libresistance 
libresistance: | libfolder
	$(MAKE) -C $(SRC_DIR)/libresistance
	cp $(SRC_DIR)/libresistance/libresistance.so $(LOCAL_LIBDIR)/libresistance.so


# Create all libraries
.PHONEY : lib
lib : libcomponent libpower libresistance 
	$(MAKE) libcomponent
	$(MAKE) libpower
	$(MAKE) libresistance

.PHONEY : all
all: $(TARGET)

.PHONEY : clean
clean: 
	$(RM) $(OBJECTS) $(TARGET) $(DEP) 
	rm -rf $(LOCAL_LIBDIR)
	$(MAKE) -C $(SRC_DIR)/libcomponent clean
	$(MAKE) -C $(SRC_DIR)/libpower clean
	$(MAKE) -C $(SRC_DIR)/libresistance clean


# Create all install dirs
#installdirs: mkinstalldirs
#	$(SRC_DIR)/mkinstalldirs $(BINDIR) $(libdir)

# Installation
.PHONEY : install
install : lib 
	mkdir -p $(BINDIR)
	mkdir -p $(LIBDIR)
	mkdir -p $(INCLUDEDIR)

	$(INSTALL_DATA) $(SRC_DIR)/libcomponent/libcomponent.h $(INCLUDEDIR)/libcomponent.h
	$(INSTALL_DATA) $(SRC_DIR)/libpower/libpower.h $(INCLUDEDIR)/libpower.h
	$(INSTALL_DATA) $(SRC_DIR)/libresistance/libresistance.h $(INCLUDEDIR)/libresistance.h
	
	$(INSTALL_DATA) $(LOCAL_LIBDIR)/libcomponent.so $(LIBDIR)/libcomponent.so
	$(INSTALL_DATA) $(LOCAL_LIBDIR)/libpower.so $(LIBDIR)/libpower.so
	$(INSTALL_DATA) $(LOCAL_LIBDIR)/libresistance.so $(LIBDIR)/libresistance.so

	$(MAKE) installtarget

	$(INSTALL_PROGRAM) $(TARGET) $(BINDIR)/$(TARGET)


# Unistall
.PHONEY : uninstall
uninstall:
	#rm -f $(PREFIX)/bin/$(TARGET)
	$(RM) $(BINDIR)/$(TARGET)
	$(RM) $(LIBDIR)/libcomponent.so
	$(RM) $(LIBDIR)/libpower.so
	$(RM) $(LIBDIR)/libresistance.so
	$(RM) $(INCLUDEDIR)/libcomponent.h
	$(RM) $(INCLUDEDIR)/libpower.h
	$(RM) $(INCLUDEDIR)/libresistance.h
	


# include all dependecy files 
-include $(DEP)
