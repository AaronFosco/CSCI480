#  _______________________________________________________________
# /                                                               \
#||  Course: CSCI-480      Assignment #: 1   Semester: Spring2019 ||
#||                                                               ||
#||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 1          ||
#||                                                               ||
#||  TA's Name: Joshua Boley                                      ||
#||                                                               ||
#||  Due: Friday 1/25/2019 by 11:59PM                             ||
#||                                                               ||
#||  Description:                                                 ||
#||    This will make the program compile correctly               ||
#||                                                               ||
# \_______________________________________________________________/

# Compiler variables
CCFLAGS = -Wall -std=c++11

# Rule to link object code files to create executable file
Assign1: Assignment1.o
	g++ $(CCFLAGS) -o Assign1 Assignment1.o

# Rules to compile source code file to object code
Assignment1.o: Assignment1.cpp
	g++ $(CCFLAGS) -c Assignment1.cpp


# Pseudo-target to remove object code and executable files
clean:
	-rm *.o Assign1
