#ifndef OPERATION_H
#define OPERATION_H

#include "task.h"

/*

union Frequency {
    Daily(daily: TaskDaily)
    Weekly(weekly: TaskWeekly)
    Monthly(monthly: TaskMonthly)
    Yearly(yearly: TaskYearly)
    Once(once: TaskOnce)
}

union Operation {
    Add {
        frequency: Frequency
        name: str
    }
}

*/

// FrequencyType in 'task.h' because of import cycle

typedef struct {
    FrequencyType type;

    union {
        TaskDaily daily;
        TaskWeekly weekly;
        TaskMonthly monthly;
        TaskYearly yearly;
        TaskOnce once;
    } frequency;
} Frequency;

// ---

typedef enum {
    OP_ADD,
    OP_ERROR,
} OperationType;

typedef struct {
    OperationType type;
    union {
        struct {
            Frequency frequency;
        } add;

        struct { } error;
    } operation;
} Operation;

Operation parse_operation(int argc, char *argv[]);

#endif
