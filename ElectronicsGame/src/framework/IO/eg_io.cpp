#include <IO/eg_io.h>

#include <stdio.h>
#include <stdlib.h>
#include <IO/eg_error.h>

char *readFile(char const *filename) {
    FILE *f;
	fopen_s(&f, filename, "rt");
	if(!f) {
		EG_ERROR(
            fprintf(stderr, "Failed to open file")
        );
	}
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = new char[length + 1] {0};
    fread(buffer, 1, length, f);
    fclose(f);
    return buffer;
}