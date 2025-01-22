#include "task.h"
#include "list.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// static uint64_t random_uint64();
static Schedule parse_tasks_file(char *content, uint32_t length);

Schedule init_schedule() {
    // TODO: lock the file
    uint32_t length;
    char *content = read_file(TASKS_FILE_PATH, &length);

    // the file does not exist, return an empty schedule.
    if (content == NULL) {
        return (Schedule) {
            .daily = new_list(sizeof(TaskDaily)),
            .weekly = new_list(sizeof(TaskWeekly)),
            .monthly = new_list(sizeof(TaskMonthly)),
            .yearly = new_list(sizeof(TaskYearly)),
            .once = new_list(sizeof(TaskOnce)),
        };
    }
    
    // an error occurred, exit the program.
    else if (content == VOID(1) || content == VOID(2)) {
        // here we will call exit(), it won't leak memory because
        // no allocations will have been made at this point
        ERROR("An error occurred while reading the tasks file.\n");

        if (content == VOID(1))
            ERROR("Not enough memory available.\n");
        else // content == VOID(2)
            ERROR("Could not read file.");

        exit(1);
    }

    // success
    Schedule s = parse_tasks_file(content, length);

    free(content);
    return s;
}

void free_schedule(Schedule *schedule) {
    free_list(&schedule->daily);
    free_list(&schedule->weekly);
    free_list(&schedule->monthly);
    free_list(&schedule->yearly);
    free_list(&schedule->once);

    // the struct lives on the stack, so no need for deallocation
}

// TODO: use a simpler ID (maybe use a counter)
uint64_t generate_id() {
    uint64_t timestamp = (uint64_t) time(NULL);
    //uint32_t random_part = (uint32_t) rand();

    return timestamp;
}

// ---

// static uint64_t random_uint64() {
//     uint64_t result = 0;

//     for (int i = 0; i < 4; i++)
//         result = (result << 16) | (rand() & 0xFFFF);

//     return result;
// }

static Schedule parse_tasks_file(char *content, uint32_t length) {

}
