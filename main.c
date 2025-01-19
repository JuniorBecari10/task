#include <stdio.h>

#include "util.h"
#include "task.h"
#include "operation.h"

int main(int argc, char *argv[]) {
    // to parse the operation we don't need to initialize
    Operation operation = parse_operation(argc, argv);

    // if it's been typed incorrectly we bail out.
    if (operation.type == OP_ERROR) {
        return 1;
    }

    init_util();
    Schedule schedule = init_schedule();


    free_schedule(&schedule);
    free_util();

    return 0;
}
