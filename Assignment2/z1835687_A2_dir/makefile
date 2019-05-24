#  _______________________________________________________________
# /                                                               \
#||  Course: CSCI-480      Assignment #: 2   Semester: Spring2019 ||
#||                                                               ||
#||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 1          ||
#||                                                               ||
#||  TA's Name: Joshua Boley                                      ||
#||                                                               ||
#||  Due: Friday 2/8/2019 by 11:59PM                              ||
#||                                                               ||
#||  Description:                                                 ||
#||    This will make the program compile correctly               ||
#||                                                               ||
# \_______________________________________________________________/

# Compiler variables
CCFLAGS = -Wall -std=c++11

# Rule to link object code files to create executable file
Assign2: Assignment2.o
	g++ $(CCFLAGS) -o Assign2 Assignment2.o

# Rules to compile source code file to object code
Assignment2.o: Assignment2.cpp
	g++ $(CCFLAGS) -c Assignment2.cpp


# Pseudo-target to remove object code and executable files
clean:
	-rm *.o Assign2
