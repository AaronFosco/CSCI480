#  _______________________________________________________________
# /                                                               \
#||  Course: CSCI-480      Assignment #: 5   Semester: Spring2019 ||
#||                                                               ||
#||  NAME:  Aaron Fosco    Z-ID: z1835687     Section: 1          ||
#||                                                               ||
#||  TA's Name: Joshua Boley                                      ||
#||                                                               ||
#||  Due: Sunday 3/24/2019 by 11:59PM                             ||
#||                                                               ||
#||  Description:                                                 ||
#||    This will make the program compile correctly               ||
#||                                                               ||
# \_______________________________________________________________/

# Compiler variables
CCFLAGS = -Wall -std=c++11 -pthread

# Rule to link object code files to create executable file
Assign5: Assignment5.o
	g++ $(CCFLAGS) -o Assign5 Assignment5.o

# Rules to compile source code file to object code
Assignment5.o: Assignment5.cpp
	g++ $(CCFLAGS) -c Assignment5.cpp

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o Assign5
