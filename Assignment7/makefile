#  _______________________________________________________________
# /                                                               \
#||  Course: CSCI-480      Assignment #: 7   Semester: Spring2019 ||
#||                                                               ||
#||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 1          ||
#||                                                               ||
#||  TA's Name: Joshua Boley                                      ||
#||                                                               ||
#||  Due: Wednesday 4/24/2019 by 11:59PM                          ||
#||                                                               ||
#||  Description:                                                 ||
#||    This will make the program compile correctly               ||
#||                                                               ||
# \_______________________________________________________________/

# Compiler variables
CCFLAGS = -Wall -std=c++11

# Rule to link object code files to create executable file
Assign7: Assignment7.o
	g++ $(CCFLAGS) -o Assign7 Assignment7.o

# Rules to compile source code file to object code
Assignment7.o: Assignment7.cpp
	g++ $(CCFLAGS) -c Assignment7.cpp


# Pseudo-target to remove object code and executable files
clean:
	-rm *.o Assign7
