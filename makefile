# Define the C++ compiler to use
CXX = g++

# Define any compile-time flags
CXXFLAGS = -Wall -g

# Define any directories containing header files other than /usr/include
#
# INCLUDES =

# Define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
#
# LFLAGS =

# Define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
#
# LIBS =

# Define the C++ source files
SRCS = Line.cpp Track.cpp

# Define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#   For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .cpp of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.cpp=.o)

# Define the executable file 
MAIN = program

#
# The following part of the Makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

all:    $(MAIN)
    @echo  Simple compiler named $(MAIN) has been compiled

$(MAIN): $(OBJS) 
    $(CXX) $(CXXFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# To start over from scratch, type 'make clean'. This removes the executable
# file, as well as old .o object files and *~ backup files:
#
clean:
    $(RM) *.o *~ $(MAIN)

# DO NOT DELETE THIS LINE -- make depend needs it