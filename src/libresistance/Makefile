#Local make file
SHELL = /bin/bash
#Variables

TARGET = libresistance.so
CC = gcc
CFLAGS = -Wall -g -MMD -fPIC
SRCDIR = .
SOURCE = libresistance.c
OBJECTS = $(SOURCE:.c=.o)
DEP = $(OBJECTS:.o=.d)

# Complile and generate dependencies
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create libraries
$(TARGET): $(OBJECTS)
	$(CC) -shared -L. $< -o $(TARGET)

.PHONEY : lib 
lib : $(TARGET)

.PHONEY : all
all: $(TARGET)

# Remove all created files
.PHONEY : clean
clean:
	rm -f $(OBJECTS) $(TARGET) $(DEP)


# include all dependecy files 
-include $(DEP)

