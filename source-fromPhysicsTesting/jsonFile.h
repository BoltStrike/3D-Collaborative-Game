#ifndef JSON_FLIE
#define JSON_FILE

#include <File.h>

class JsonFile{
	File* file;
	//file name, index
	JsonFile(const char*);
	JsonFile(const char*,bool);
	~JsonFile();
	bool index(const char*);
	
	
}

#endif