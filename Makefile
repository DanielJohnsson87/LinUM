# MAKEFILE for main program
#Variables

TARGET = testmake
PREFIX = /usr/local
CC = gcc
CFLAGS = -Wall -g -MMD 
LDFLAGS = -L$(SRC_DIR)/libcomponent \
	-L$(SRC_DIR)/libpower \
	-L$(SRC_DIR)/libresistance

LDLIBS = -lcomponent -lpower -lresistance

INC = -I$(SRC_DIR)/libcomponent \
	-I$(SRC_DIR)/libpower \
	-I$(SRC_DIR)/libresistance	

#BUILD_DIR := build
SRC_DIR := src
SOURCE := $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCE:.c=.o)
#OBJECTS = $(subst $(SRC_DIR),$(BUILD_DIR),$(SOURCE:.c=.o))
DEP = $(OBJECTS:.o=.d)
LIBS = libcomponent libpower libresistance


# Linking
$(TARGET) : $(OBJECTS) libcomponent libpower libresistance
	$(CC) $(LDFLAGS) $< $(LDLIBS) -o $@

# Complile and generate dependencies
%.o : %.c 
	$(CC) $(CFLAGS) -c $< $(INC) -o $@


# Create libraries
.PHONEY: libcomponent
libcomponent :
	$(MAKE) -C $(SRC_DIR)/libcomponent

.PHONEY: libpower
libpower:
	$(MAKE) -C $(SRC_DIR)/libpower

.PHONEY: libresistance
libresistance:
	$(MAKE) -C $(SRC_DIR)/libresistance

# Create all libraries
.PHONEY : lib 
lib : $(LIBS)
	$(MAKE) -C $(SRC_DIR)/libcomponent
	$(MAKE) -C $(SRC_DIR)/libpower
	$(MAKE) -C $(SRC_DIR)/libresistance

.PHONEY : all
all: $(TARGET)

.PHONEY : clean
clean: $(LIBS)
	rm -f $(OBJECTS) $(TARGET) $(DEP) $(LIBS)
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