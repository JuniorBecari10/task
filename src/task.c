#include "task.h"
#include "list.h"

Schedule init_schedule() {
    // TODO: read from file and lock the file
    
    return (Schedule) {
        .daily = new_list(sizeof(TaskDaily), (DropFn) drop_task),
        .weekly = new_list(sizeof(TaskWeekly), (DropFn) drop_task),
        .monthly = new_list(sizeof(TaskMonthly), (DropFn) drop_task),
        .yearly = new_list(sizeof(TaskYearly), (DropFn) drop_task),
        .once = new_list(sizeof(TaskOnce), (DropFn) drop_task),
    };
}

void free_schedule(Schedule *schedule) {
    free_list(&schedule->daily);
    free_list(&schedule->weekly);
    free_list(&schedule->monthly);
    free_list(&schedule->yearly);
    free_list(&schedule->once);

    // the struct lives on the stack, so no need for deallocation
}

void drop_task(Task *task) {
    free(task->id);
}
