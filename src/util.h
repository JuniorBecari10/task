#ifndef UTIL_H
#define UTIL_H

#define ERROR(msg) fprintf(stderr, msg)
#define ERRORF(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#define VOID(n) (void*)n

char *TASKS_FILE_PATH;

void init_util();
void free_util();

char* read_file(const char* path, uint32_t *out_length);

#endif
