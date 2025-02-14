#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>

static char* get_home_task_file();

void init_util() {
    TASKS_FILE_PATH = get_home_task_file();
    srand((unsigned int) time(NULL));
}

void free_util() {
    free(TASKS_FILE_PATH);
}

// returns NULL on error, or when the file doesn't exist.
// 1 -> not enough memory
// 2 -> "could not read"

// if an error occurs, 'out_length' won't be set.
char* read_file(const char* path, uint32_t *out_length) {
    FILE* file = fopen(path, "rb");

    // the file couldn't be open, mostly because it doesn't exist
    if (file == NULL)
        return NULL;

    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char* buffer = (char*) malloc(file_size + 1);

    // not enough memory
    if (buffer == NULL)
        return VOID(1);

    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);

    // could not read file
    if (bytes_read < file_size)
        return VOID(2);
    
    buffer[bytes_read] = '\0';
    fclose(file);

    *out_length = file_size + 1;
    return buffer;
}

// ---

static char* get_home_task_file() {
    const char *home_dir = getenv("HOME");
    if (home_dir == NULL) {
        ERROR("Error: HOME environment variable is not set.\n");
        return NULL;
    }

    size_t full_path_len = strlen(home_dir) + strlen("/.tasks") + 1;
    char *task_file_path = (char*) malloc(full_path_len);

    if (task_file_path == NULL) {
        ERROR("Error: Memory allocation failed while generating tasks file path.\n");
        return NULL;
    }

    snprintf(task_file_path, full_path_len, "%s/.tasks", home_dir);
    return task_file_path;
}
