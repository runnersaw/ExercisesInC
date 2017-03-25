
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

int main(int argc, char *argv[]) {
	int append = 0;
	char *filename = NULL;

	// Parse arguments
	for (int i=1; i<argc; i++) {
		char *arg = argv[i];
		if (arg[0] == '-') {
			if (strcmp(arg, "-a") || strcmp(arg, "--append")) {
				append = 1;
			} else {
				printf("Unrecognized argument %s\n", arg);
				return -1;
			}
		} else {
			if (filename == NULL) {
				filename = arg;
			} else {
				printf("Don't put two file arguments\n");
				return -1;
			}
		}
	}

	// Malloc it and make sure that there's a null char at the end, in case
	// the user overruns MAX_INPUT_SIZE
	char *input = malloc((MAX_INPUT_SIZE + 1) * sizeof(char));
	input[MAX_INPUT_SIZE] = '\0';

	// Open file
	FILE *file = NULL;
	if (append) {
		file = fopen(filename, "a");
	} else {
		file = fopen(filename, "w");
	}

	if (file == NULL) {
		printf("Error opening file.\n");
		return -1;
	}

	// Read from stdin repeatedly
	while (fgets(input, MAX_INPUT_SIZE, stdin) != NULL) {
		// Write to file
		fprintf(file, "%s", input);

		// Print to stdout
		printf("%s", input);
	}

	return 0;
}