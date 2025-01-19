#include <stdio.h>

#include "util.h"
#include "task.h"

int main(void) {
    init_util();
    Schedule schedule = init_schedule();


    free_schedule(&schedule);
    free_util();
}
