all: laba_2

laba_2: main.o interface.o student.o subject_class.o teacher.o
	g++ main.o interface.o student.o subject_class.o teacher.o

main.o: main.cpp
	g++ -c main.cpp

interface.o: interface.cpp 
	g++ -c interface.cpp 

student.o: student.cpp
	g++ -c student.cpp 

subject_class.o: subject_class.cpp
	g++ -c subject_class.cpp

teacher.o: teacher.cpp
	g++ -c teacher.cpp

clean:
	rm -rf *o laba_2