/* vulp.c */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define DELAY 5000

int main(int argc, char *argv[]) {
	char *fileName = argv[1];
	char buffer[60];
	int i;

	FILE *fileHandler;

	/* get user input */

	scanf("%50s", buffer);

	if (!access(fileName, W_OK)) {
		/*Simulating the Delay */ for (i = 0; i < DELAY; i++) {
			int a = i ^ 2;
		}

		fileHandler = fopen(fileName, "a+");
		if (fileHandler != NULL) {
			fwrite("\n", sizeof(char), 1, fileHandler);
			fwrite(buffer, sizeof(char), strlen(buffer), fileHandler);
			fwrite("\n", sizeof(char), 1, fileHandler);
			fclose(fileHandler);
		}
	} else {
		printf("No permission \n");
	}
}
