
#include "program_log.h"

/******************************************************************************
 * This function outputs the given message to the console and a file called
 * "program_log.txt" in the same directory as the executable.
 * Params:
 * 		message - The message to be outputted
 *****************************************************************************/
void program_log (const char *message) {
	FILE *f;
	f = fopen("program_log.txt", "a+");
	fprintf(f, "%s\n", message);
	fclose(f);
	printf("%s\n", message);
}
