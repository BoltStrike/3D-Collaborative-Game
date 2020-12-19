
#include "file_tosstream.h"

/******************************************************************************
 * This function reads in a file as a string. Defaults to an empty string upon
 * failing to read the file.
 * Params:
 * 		filepath - The filepath to the file relative to the executable
 *****************************************************************************/
std::stringstream file_tosstream (const char *filepath) {
	std::stringstream stream;	// Will store file
	std::ifstream file;			// Will read file
	// Ensure the file can throw exceptions
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	// Attempt to read file into the string. Upon failure, log the error.
	try {
		file.open(filepath);		// Open file (might fail)
		stream << file.rdbuf();		// Put file contents into stream
		file.close();				// Close file
	}
	catch (std::ifstream::failure & e) {
		std::string message = "ERROR::Failed to read file ";
		message.append(filepath);
		program_log(message.c_str());
	}

	return stream;
}
