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

CC = gcc
CFLAGS = -Wall -g -MMD 
#LDFLAGS = -L$(SRC_DIR)/libcomponent \
#	-L$(SRC_DIR)/libpower \
#	-L$(SRC_DIR)/libresistance \
#	-Wl,-rpath,$(SRC_DIR)/libcomponent,$(SRC_DIR)/libpower,$(SRC_DIR)/libresistance

LDFLAGS = -L./lib/ -Wl,-rpath,./lib/

LDLIBS = -lcomponent -lpower -lresistance

INC = -I$(SRC_DIR)/libcomponent \
	-I$(SRC_DIR)/libpower \
	-I$(SRC_DIR)/libresistance	

SRC_DIR := src
SOURCE := $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCE:.c=.o)
DEP = $(OBJECTS:.o=.d)
LIBS = libcomponent libpower libresistance

# Linking
$(TARGET) : $(OBJECTS) libcomponent libpower libresistance
	$(CC) $(LDFLAGS) $< $(LDLIBS) -o $@

# Complile and generate dependencies
%.o : %.c 
	$(CC) $(CFLAGS) -c $< $(INC) -o $@

# Create libray directory
libfolder: 
	mkdir -p lib

# Create libraries 
.PHONEY: libcomponent
libcomponent : | libfolder
	$(MAKE) -C $(SRC_DIR)/libcomponent
	cp $(SRC_DIR)/libcomponent/libcomponent.so lib/libcomponent.so

.PHONEY: libpower 
libpower: | libfolder
	$(MAKE) -C $(SRC_DIR)/libpower
	cp $(SRC_DIR)/libpower/libpower.so lib/libpower.so

.PHONEY: libresistance 
libresistance: | libfolder
	$(MAKE) -C $(SRC_DIR)/libresistance
	cp $(SRC_DIR)/libresistance/libresistance.so lib/libresistance.so


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
	rm -rf $(LIB_DIR)
	$(MAKE) -C $(SRC_DIR)/libcomponent clean
	$(MAKE) -C $(SRC_DIR)/libpower clean
	$(MAKE) -C $(SRC_DIR)/libresistance clean


# Create all install dirs
#installdirs: mkinstalldirs
#	$(SRC_DIR)/mkinstalldirs $(BINDIR) $(libdir)

# Installation
.PHONEY : install
install : lib $(TARGET) | libfolder 
	mkdir -p $(PREFIX)/bin
	mkdir -p $(PREFIX)/lib

	$(INSTALL_PROGRAM) $(TARGET) $(BINDIR)/$(TARGET)
	$(INSTALL_DATA) ./lib/libcomponent.so $(LIBDIR)/libcomponent.so
	$(INSTALL_DATA) ./lib/libresistance.so $(LIBDIR)/libpower.so
	$(INSTALL_DATA) ./lib/libresistance.so $(LIBDIR)/libresistance.so

# Unistall
.PHONEY : uninstall
uninstall:
	#rm -f $(PREFIX)/bin/$(TARGET)
	$(RM) $(BINDIR)/$(TARGET)
	$(RM) $(LIBDIR)/libcomponent.so
	$(RM) $(LIBDIR)/libpower.so
	$(RM) $(LIBDIR)/libresistance.so

# include all dependecy files 
-include $(DEP)
