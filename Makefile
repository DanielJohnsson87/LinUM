# MAKEFILE for main program
#Variables

TARGET = testmake
PREFIX = /usr/local
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
	rm -f $(OBJECTS) $(TARGET) $(DEP) 
	rm -rf $(LIB_DIR)
	$(MAKE) -C $(SRC_DIR)/libcomponent clean
	$(MAKE) -C $(SRC_DIR)/libpower clean
	$(MAKE) -C $(SRC_DIR)/libresistance clean

# Installation
.PHONEY : install
install : $(TARGET)
	mkdir -p $(PREFIX)/bin
	install -m 775 $< $(PREFIX)/bin

# Unistall
.PHONEY : uninstall
uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)

# include all dependecy files 
-include $(DEP)