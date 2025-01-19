#ifndef TASK_H
#define TASK_H

#include <stdint.h>

#include "list.h"

typedef uint8_t WeekDay;
typedef uint8_t MonthDay;
typedef uint8_t Month;
typedef int32_t Year;

typedef enum {
    FREQ_DAILY,
    FREQ_WEEKLY,
    FREQ_MONTHLY,
    FREQ_YEARLY,
    FREQ_ONCE,
} FrequencyType;

typedef struct {
    List daily;
    List weekly;
    List monthly;
    List yearly;
    List once;
} Schedule;

typedef enum {
    STATE_DONE,
    STATE_ACTIVE,
    STATE_CANCELED,
    STATE_DISABLED,
} TaskState;

typedef struct {
    char *name;
    char *id; // if it was a number?

    TaskState state;
    FrequencyType frequency;
} Task;

typedef struct {
    uint8_t hour;
    uint8_t minute;
} Hour;

typedef struct {
    MonthDay day;
    uint8_t month;
} YearDay;

// ---

typedef struct {
    Task task;
    Hour hour;
} TaskDaily;

typedef struct {
    Task task;
    
    WeekDay day;
    Hour hour;
} TaskWeekly;

typedef struct {
    Task task;
    
    MonthDay day;
    Hour hour;
} TaskMonthly;

typedef struct {
    Task task;
    
    MonthDay day;
    Month month;
    
    Hour hour;
} TaskYearly;

typedef struct {
    Task task;
    
    MonthDay day;
    Month month;
    Year year;

    Hour hour;
} TaskOnce;

Schedule init_schedule();
void free_schedule(Schedule *schedule);
void drop_task(Task *task);

#endif
