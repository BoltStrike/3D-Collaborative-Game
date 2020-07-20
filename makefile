CC = g++ -std=c++11
exe_file = 3dcollaborativegame


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
OGLFLAGS := GLUT-MinGW-3.7.6-6/lib/libglut32.a -lglu32 -lopengl32
OGLFLAGS := GLUT-MinGW-3.7.6-6/lib/libglut32.a -lglu32 -lopengl32
#OGLFLAGS := freeglut-MinGW-3.0.0-1/lib/libfreeglut.a -lglu32 -lopengl32

#Special flag to get the math library to work
MATHFLAG := -lm

#all: $(exe_file)

$(exe_file): main.o graphics.o geometry.o glad.o
	$(CC) main.o graphics.o geometry.o glad.o -o $(exe_file) $(CFLAGS) $(MATHFLAG) $(OGLFLAGS)
main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)
graphics.o: graphics.cpp
	$(CC) -c graphics.cpp $(CFLAGS)
geometry.o: geometry.cpp
	$(CC) -c geometry.cpp $(CFLAGS)
glad.o: glad/glad.c
	$(CC) -c glad/glad.c $(CFLAGS)

clean:
	rm -f *.out *.o $(exe_file).exe

.PHONY: clean
