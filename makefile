CC = g++ -std=c++11
exe_file = collada_exporter


# Handle debug case
DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS := -g -Wall
else 
	CFLAGS := -DNDEBG -03
endif

#Compile it as a Position Independent Executable (PIE)
CFLAGS := -no-pie

#Special flags to get FreeGLUT and OpenGL to work
OGLFLAGS := -lglut -lGL -lGLU

#Special flag to get the math library to work
MATHFLAG := -lm

$(exe_file): main.o graphics.o geometry.o
	$(CC) main.o graphics.o geometry.o -o $(exe_file) $(CFLAGS) $(MATHFLAG) $(OGLFLAGS)
main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)
graphics.o: graphics.cpp
	$(CC) -c graphics.cpp $(CFLAGS)
geometry.o: geometry.cpp
	$(CC) -c geometry.cpp $(CFLAGS)

clean:
	rm -f *.out *.o $(exe_file)

.PHONY: clean
