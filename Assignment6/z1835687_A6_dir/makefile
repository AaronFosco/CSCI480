#  _______________________________________________________________
# /                                                               \
#||  Course: CSCI-480      Assignment #: 6   Semester: Spring2019 ||
#||                                                               ||
#||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 1          ||
#||                                                               ||
#||  TA's Name: Joshua Boley                                      ||
#||                                                               ||
#||  Due: Wednesday 4/10/2019 by 11:59PM                          ||
#||                                                               ||
#||  Description:                                                 ||
#||    This will make the program compile correctly               ||
#||                                                               ||
# \_______________________________________________________________/

# Compiler variables
CCFLAGS = -Wall -std=c++11

# Rule to link object code files to create executable file
Assign6: Assignment6.o
	g++ $(CCFLAGS) -o Assign6 Assignment6.o

# Rules to compile source code file to object code
Assignment6.o: Assignment6.cpp
	g++ $(CCFLAGS) -c Assignment6.cpp


# Pseudo-target to remove object code and executable files
clean:
	-rm *.o Assign6
