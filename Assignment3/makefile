#  _______________________________________________________________
# /                                                               \
#||  Course: CSCI-480      Assignment #: 3   Semester: Spring2019 ||
#||                                                               ||
#||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 1          ||
#||                                                               ||
#||  TA's Name: Joshua Boley                                      ||
#||                                                               ||
#||  Due: Monday 2/18/2019 by 11:59PM                             ||
#||                                                               ||
#||  Description:                                                 ||
#||    This will make the program compile correctly               ||
#||                                                               ||
# \_______________________________________________________________/

# Compiler variables
CCFLAGS = -Wall -std=c++11

# Rule to link object code files to create executable file
Assign3: Assignment3.o
	g++ $(CCFLAGS) -o Assign3 Assignment3.o

# Rules to compile source code file to object code
Assignment3.o: Assignment3.cpp
	g++ $(CCFLAGS) -c Assignment3.cpp


# Pseudo-target to remove object code and executable files
clean:
	-rm *.o Assign3
