#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* get_home_task_file();

void init_util() {
    TASKS_FILE_PATH = get_home_task_file();
}

void free_util() {
    free(TASKS_FILE_PATH);
}

// ---

static char* get_home_task_file() {
    const char *home_dir = getenv("HOME");
    if (home_dir == NULL) {
        fprintf(stderr, "Error: HOME environment variable is not set.\n");
        return NULL;
    }

    size_t full_path_len = strlen(home_dir) + strlen("/.tasks") + 1;
    char *task_file_path = (char*) malloc(full_path_len);

    if (task_file_path == NULL) {
        fprintf(stderr, "Error: Memory allocation failed while generating tasks file path.\n");
        return NULL;
    }

    snprintf(task_file_path, full_path_len, "%s/.tasks", home_dir);
    return task_file_path;
}
