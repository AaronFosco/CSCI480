#  _______________________________________________________________
# /                                                               \
#||  Course: CSCI-480      Assignment #: 4   Semester: Spring2019 ||
#||                                                               ||
#||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 1          ||
#||                                                               ||
#||  TA's Name: Joshua Boley                                      ||
#||                                                               ||
#||  Due: Friday 3/12/2019 by 11:59PM                             ||
#||                                                               ||
#||  Description:                                                 ||
#||    This will make the program compile correctly               ||
#||                                                               ||
# \_______________________________________________________________/

# Compiler variables
CCFLAGS = -Wall -std=c++11

# Rule to link object code files to create executable file
Assign4: Assignment4.o Process.o
	g++ $(CCFLAGS) -o Assign4 Assignment4.o Process.o

# Rules to compile source code file to object code
Assignment4.o: Assignment4.cpp Assignment4.h Process.h
	g++ $(CCFLAGS) -c Assignment4.cpp

Process.o: Process.cpp Process.h
	g++ $(CCFLAGS) -c Process.cpp

#Header file dependency
Process.h: Assignment4.h

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o Assign4
