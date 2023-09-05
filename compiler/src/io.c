#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *file_name) {
    FILE *file_pointer = fopen(file_name,  "r");
    size_t file_size = 0;
    if(file_pointer) {
        fseek(file_pointer, 0, SEEK_END);
        file_size = ftell(file_pointer);
        fseek(file_pointer, 0, SEEK_SET);
        char *buffer = malloc(file_size + 1);
        if(buffer) {
            fread(buffer, 1, file_size, file_pointer);
        }
        fclose(file_pointer);
        return buffer;
    }
    printf("Could not find file");
    exit(EXIT_SUCCESS);
}