#Local make file
SHELL = /bin/sh
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
	$(CC) -shared -fPIC libcomponent.o -o $(TARGET)


.PHONEY : all
all: $(TARGET)

# Remove all created files
.PHONEY : clean
clean:
	$(RM) $(OBJECTS) $(TARGET) $(DEP)

# include all dependecy files 
-include $(DEP)