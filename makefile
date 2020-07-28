CC = g++ -std=c++11
exe_file = 3dcollaborativegame

# Handle debug case
DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS := -g -Wall
else 
	CFLAGS := -DNDEBG -03
endif

#Enable the compiler to know where the standard libraries are
STDFLAGS := -isystem "mingw64" -isystem "mingw64/include" -isystem "mingw64/include/c++/10.1.0" -isystem "mingw64/lib/gcc/x86_64-w64-mingw32/10.1.0" -static-libgcc -static-libstdc++ -static

#Compile it as a Position Independent Executable (PIE)
CFLAGS := -no-pie

#Special flags to get FreeGLUT and OpenGL to work 
OGLFLAGS := freeglut-MinGW-3.0.0-1/lib/x64/libfreeglut.a -lopengl32

#Special flag to get the math library to work
MATHFLAG := -lm

#Get all .cpp files in the source directory
SRC_DIR := source
OBJ_DIR := objects
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

#Compile all .cpp files in the source directory and glad in the glad directory
$(exe_file): $(OBJ_FILES) $(OBJ_DIR)/glad.o
	$(CC) -o $@ $^ $(STDFLAGS) $(CFLAGS) $(MATHFLAG) $(OGLFLAGS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ_DIR)/glad.o: glad/glad.c
	$(CC) -c glad/glad.c -o $(OBJ_DIR)/glad.o $(CFLAGS)

clean:
	rm -rf $(exe_file) *.o

.PHONY: clean

