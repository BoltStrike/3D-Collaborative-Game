
#include "program_log.h"

/******************************************************************************
 * This function outputs the given message to the console and a file called
 * "program_log.txt" in the same directory as the executable. By default,
 * the message is appended to the same file. If the value new_file=true, the
 * "program_log.txt" file will be deleted, and a new "program_log.txt" file
 * will be generated.
 * Params:
 * 		message 	- The message to be outputted
 *		new_file	- Boolean determining if a new log file will be generated
 *****************************************************************************/
void program_log (const char *message, bool new_file) {
	FILE *f;
	if (new_file) f = fopen("program_log.txt", "w+");
	else f = fopen("program_log.txt", "a+");
	fprintf(f, "%s", message);
	fclose(f);
	printf("%s", message);
}

/******************************************************************************
 * This function outputs the given message to the console and a file called
 * "program_log.txt" in the same directory as the executable. By default,
 * the message is appended to the same file. If the value new_file=true, the
 * "program_log.txt" file will be deleted, and a new "program_log.txt" file
 * will be generated. This function has been overloaded to accept std::string
 * arguments.
 * Params:
 * 		message 	- The message to be outputted
 *		new_file	- Boolean determining if a new log file will be generated
 *****************************************************************************/
void program_log (std::string message, bool new_file) {
	program_log(message.c_str(), new_file);
}
