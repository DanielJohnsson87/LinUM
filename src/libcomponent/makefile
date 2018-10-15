#Local make file

#Variables

TARGET = libcomponent.so
CC = gcc
CFLAGS = -Wall -g -MMD -fPIC
SRC_DIR = .
SOURCE = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCE:.c=.o)
DEP = $(OBJECTS:.o=.d)


# Complile and generate dependencies
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create libraries
$(TARGET): $(OBJECTS)
	#$(AR) crv $@ $^
	$(CC) -shared -L. libcomponent.o -o $(TARGET)

.PHONEY : lib 
lib : $(TARGET)

.PHONEY : all
all: $(TARGET)

.PHONEY : clean
clean:
	rm -f $(OBJECTS) $(TARGET) $(DEP)

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