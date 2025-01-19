#include "operation.h"
#include "util.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    HOUR_OK,
    HOUR_INCORRECT_FORMAT,
    HOUR_OUT_OF_BOUNDS,
} ParseHourError;

static Operation default_operation();
static Hour parse_hour(char *str, ParseHourError *out_error);

Operation parse_operation(int argc, char *argv[]) {
    Operation operation = default_operation();

    // check whether an argument is provided.
    if (argc == 1) {
        ERROR("Please specify an option (add).\n");
        ERROR("Usage: <option> <...>\n");
        return operation;
    }

    // it is safe since we checked for the empty argument list above.
    char *op = argv[1];

    // add
    if (strcmp(op, "add") == 0) {
        // check whether a frequency is provided.
        if (argc == 2) {
            ERROR("Please specify a frequency (daily, weekly, monthly, yearly, once).\n");
            ERROR("Usage: add <frequency> <...>\n");
            return operation;
        }

        // structure:
        // add frequency (daily/weekly/monthly/yearly/once) <options (depends on frequency, but we'll parse accoringly to the structs)>

        char *freq = argv[2];

        // daily
        if (strcmp(freq, "daily") == 0) {
            // strucure:
            // add daily "name" <hour>

            if (argc != 5) {
                ERROR("Please specify a valid name and hour.\n");
                ERROR("Usage: add daily <name> <hour>\n");
                return operation;
            }

            char *name = argv[3];
            ParseHourError error = HOUR_OK;
            Hour hour = parse_hour(argv[4], &error);

            if (error != HOUR_OK) {
                switch (error) {
                    case HOUR_INCORRECT_FORMAT:
                        ERROR("Please specify a valid hour.\n");
                        ERROR("Usage: add daily <name> <hour>\n");
                        break;

                    case HOUR_OUT_OF_BOUNDS:
                        ERROR("Please specify values within the bounds of a valid hour.\n");
                        ERROR("Usage: add daily <name> <hour>\n");
                        break;
                
                    default:
                        // HOUR_OK
                        break;
                }

                // we haven't assigned to 'operation', so we simply return it.
                return operation;
            }

            TaskDaily daily = {
                .task = {
                    .name = name,
                    // .id = TODO,
                    .state = STATE_ACTIVE,
                    .frequency = FREQ_DAILY,
                },
                .hour = hour,
            };

            operation.type = OP_ADD;
            operation.operation.add.frequency = (Frequency) {
                .type = FREQ_DAILY,
                .frequency.daily = daily,
            };
        }

        else {
            // invalid option
            ERRORF("Invalid frequency: '%s'. Please specify a valid frequency (daily, weekly, monthly, yearly, once).\n", freq);
            ERROR("Usage: add <frequency> <...>\n");
        }
    }

    else {
        // invalid option
        ERRORF("Invalid option: '%s'. Please specify a valid option (add).\n", op);
        ERROR("Usage: <option> <...>\n");
    }

    return operation;
}

// ---

// the default is error (which ends the program)
static Operation default_operation() {
    return (Operation) { OP_ERROR, { .error = { } } };
}

static Hour parse_hour(char *str, ParseHourError *out_error) {
    Hour hour = { 0 };
    uint8_t hour_val, min_val;

    if (sscanf(str, "%hhd:%hhd", &hour_val, &min_val) != 2) {
        *out_error = HOUR_INCORRECT_FORMAT;
        return hour;
    }

    if (hour_val > 23 || min_val > 59) {
        *out_error = HOUR_OUT_OF_BOUNDS;
        return hour;
    }

    hour.hour = hour_val;
    hour.minute = min_val;

    *out_error = HOUR_OK;
    return hour;
}
