#Local make file

#Variables

TARGET = libresistance.so
CC = gcc
CFLAGS = -Wall -g -MMD -fPIC
SRC_DIR = .
SOURCE = libresistance.c#$(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCE:.c=.o)
DEP = $(OBJECTS:.o=.d)

# Complile and generate dependencies
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create libraries
$(TARGET): $(OBJECTS)
	#$(AR) crv $@ $^
	$(CC) -shared -L. libresistance.o -o $(TARGET)

.PHONEY : lib 
lib : $(TARGET)

.PHONEY : all
all: $(TARGET)

.PHONEY : clean
clean:
	rm -f $(OBJECTS) $(TARGET) $(DEP)

# Unistall
.PHONEY : uninstall
uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)

# include all dependecy files 
-include $(DEP)

# gamla versionen
# CC = gcc
# P_NAME = program
# COMPILE_FLAGS = -Wall -c
# LINK_FLAGS = -Wall -o $(P_NAME)
# all:
	#$(CC) $(COMPILE_FLAGS) program.c -o program.o
	#$(CC) $(COMPILE_FLAGS) -fPIC calc_resistance.c -o calc_resistance.o
	#$(CC) -shared -L. calc_resistance.o -o libcalc_resistance.so
	#$(CC) program.o -L. -lcalc_resistance -o program 
 #.PHONY: clean
 #clean:
#	-rm program.o calc_resistance.o
