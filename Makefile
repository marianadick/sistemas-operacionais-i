# Defining compiler and compiler flags
CPP = g++
CPPFLAGS = -Wall

# Executable name (ADD HERE THE NAME OF THE EXECUTABLE GENERATED)
EXE = main

# List of source codes (ADD HERE C++ SOURCE FILE NAMES)
SRCS = main.cc cpu.cc main_class.cc thread.cc system.cc debug.cc

# List of header files (ADD HERE C++ HEADER FILE NAMES)
HDRS = cpu.h main_class.h traits.h thread.h system.h debug.h

# Generate object files (.o) from source files
OBJS = $(SRCS:.c=.o)

# Compilling files ($@ refers to the Target being generated, in this case where are refering to (EXE) targe which is defined as 'prog')
$(EXE): $(OBJS) $(HDRS) Makefile
	@ echo "-> COMPILLING FILES"
	$(CPP) $(CPPFLAGS) -o $@ $(OBJS)
	@ echo "-> DONE!"
	@ echo "-> Run './$(EXE)' to execute the code"

# Dependencies
$(OBJS): $(HDRS) Makefile
