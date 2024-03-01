CC = g++ -std=c++11 -pthread
exe_file = 3dcollaborativegame

# Use unicode UTF-8
UFLAG := -fextended-identifiers

# Handle debug case
DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS := -g -Wall
else 
	CFLAGS := -DNDEBG -03
endif


ifeq ($(shell echo "check_quotes"),"check_quotes")
	#Enable the compiler to know where the standard libraries are
	STDFLAGS := -isystem "mingw64" -static
	#Flag to link GLFW
	GLFWFLAG := glfw-3.3.2.bin.WIN64/lib-mingw-w64/libglfw3dll.a
	#Flag to link OpenGL
	GLFLAG := -lopengl32
	#Setting left blank to let Windows search CD for libraries
	LIBFLAG := 
else
	#STDFLAGS left blank to use standard Linux g++ complier
	STDFLAGS := 
	#Flag to link GLFW Linux version
	GLFWFLAG := glfw-master/glfw-build/src/libglfw.so 
	#Flag to link OpenGL Linux version
	GLFLAG := -lGL -ldl
	#Additional setting to get GLFW to run
	LIBFLAG := "-Wl,-rpath,$(PWD)/glfw-master/glfw-build/src/"
endif 

#Compile it as a Position Independent Executable (PIE)
CFLAGS := -no-pie

#Special flag to get the math library to work
MATHFLAG := -lm

#Get all .cpp files in the source directory
SRC_DIR := source
OBJ_DIR := objects
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/*/*/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

#Compile each file and the whole EXE
$(exe_file): $(OBJ_FILES) $(OBJ_DIR)/glad.o
	$(CC) -o $@ $^ $(STDFLAGS) $(CFLAGS) $(MATHFLAG) $(GLFWFLAG) $(GLFLAG) $(LIBFLAG) $(UFLAG)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(UFLAG) -c -o $@ $<
$(OBJ_DIR)/glad.o: glad/glad.c
	$(CC) $(CFLAGS) -c -o $(OBJ_DIR)/glad.o glad/glad.c

clean:
	rm -rf $(exe_file) *.o

.PHONY: clean

