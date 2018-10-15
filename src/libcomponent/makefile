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
	$(CC) -shared -fPIC libcomponent.o -o $(TARGET)

.PHONEY : lib 
lib : $(TARGET)

.PHONEY : all
all: $(TARGET)

.PHONEY : clean
clean:
	rm -f $(OBJECTS) $(TARGET) $(DEP)

# include all dependecy files 
-include $(DEP)