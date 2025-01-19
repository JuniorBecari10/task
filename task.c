#include "task.h"
#include "list.h"

Schedule init_schedule() {
    return (Schedule) {
        .daily = new_list(sizeof(TaskDaily)),
        .weekly = new_list(sizeof(TaskWeekly)),
        .monthly = new_list(sizeof(TaskMonthly)),
        .yearly = new_list(sizeof(TaskYearly)),
        .once = new_list(sizeof(TaskOnce)),
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
