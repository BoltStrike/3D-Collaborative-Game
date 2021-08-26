CC = g++ -std=c++11 -pthread
exe_file = ubjConsoleEditor

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
else
	#STDFLAGS left blank to use standard Linux g++ complier
	STDFLAGS := 
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
$(exe_file): $(OBJ_FILES)
	$(CC) -o $@ $^ $(STDFLAGS) $(CFLAGS) $(MATHFLAG) $(GLFWFLAG) $(GLFLAG) $(LIBFLAG) $(UFLAG)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(UFLAG) -c -o $@ $<

clean:
	rm -rf $(exe_file) *.o

.PHONY: clean

