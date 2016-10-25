#declare the variable
CC=gcc
FLAGS =-g -Wall
INCLUDES = -I../../Cadvance/lib/include
# define any directories containing header files other than /usr/include
LIBS = -L../../Cadvance/lib/implementation
#define any directories containing implementation of the files in INCLUDES
#../../lib means up 2 level then search for /lib
LFLAGS= -lutility
#to run all the .a file
CFLAGS=-c $(FLAG)
SRCS=tsp.c ga.c 
OBJS= $(SRCS:.c=.o)
EXECUTABLE=tsp


#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings

#action
all: $(EXECUTABLE) $(SRCS) 
$(EXECUTABLE): $(OBJS)
	$(CC) $(FLAGS)  $(INCLUDES) -o $(EXECUTABLE) $(OBJS) $(LIBS) $(LFLAGS) -lm	
.c.o: 
	$(CC) $(INCLUDES) $(CFLAGS)  $< -o $@
clean: 
	rm -f core $(OBJS)  $(EXECUTABLE)