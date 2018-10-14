# MAKEFILE for main program
#Variables

TARGET = testmake
PREFIX = /usr/local
CC = gcc
CFLAGS = -I$(SRC_DIR)/$(LIBS) -Wall -g -MMD 
LDFLAGS = -L$(SRC_DIR)/$(LIBS)
LDLIBS = -lcomponent
#BUILD_DIR := build
SRC_DIR := src
SOURCE := $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCE:.c=.o)
#OBJECTS = $(subst $(SRC_DIR),$(BUILD_DIR),$(SOURCE:.c=.o))
DEP = $(OBJECTS:.o=.d)
LIBS = libcomponent

# Linking
$(TARGET) : $(OBJECTS) $(LIBS)
	$(CC) $(LDFLAGS) $< $(LDLIBS) -o $@

# Complile and generate dependencies
%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@


.PHONEY: $(LIBS)
$(LIBS):
	$(MAKE) -C $(SRC_DIR)/$@


.PHONEY : lib 
lib : $(LIBS)

.PHONEY : all
all: $(TARGET)

.PHONEY : clean
clean:
	rm -f $(OBJECTS) $(TARGET) $(DEP) $(LIBS)
	$(MAKE) -C $(SRC_DIR)/$(LIBS) clean

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