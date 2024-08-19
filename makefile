CC = gcc
CFLAGS = -lncurses -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c

all: sudoku run 

sudoku:
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./sudoku

# Target to clean up generated files
# clean:

#  	# rm -f sudoku $(ODIR)*.o
# 	@echo "Stopping the build process..."
	
 	

# Custom target to stop the build process
# stop:
# 	@echo "Stopping the build process..."
# 	$(MAKE) clean
# 	@exit 1

# CC = gcc
# CFLAGS = -lncurses -I$(IDIR) -Wall -g

# IDIR = ./include/
# SRCDIR = ./src/
# ODIR = ./obj/

# SOURCES = $(wildcard $(SRCDIR)*.c)
# OBJECTS = $(patsubst $(SRCDIR)%.c, $(ODIR)%.o, $(SOURCES))

# # Create the object directory if it doesn't exist
# $(ODIR):
# 	mkdir -p $(ODIR)

# all: $(ODIR) $(OBJECTS)
# 	$(CC) $(OBJECTS) $(CFLAGS) -o sudoku

# $(ODIR)%.o: $(SRCDIR)%.c $(IDIR)%.h
# 	$(CC) $(CFLAGS) -c -o $@ $<

# run: all
# 	./sudoku

# clean:
# 	rm -f sudoku $(ODIR)*.o

# .PHONY: all run clean
