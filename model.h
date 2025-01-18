#ifndef MODEL_H
#define MODEL_H

#include <stdint.h>
#include "list.h"

#define SCHEDULE_MAX 4096

typedef enum {
    STATE_DONE,
    STATE_ACTIVE,
    STATE_CANCELED,
    STATE_DISABLED,
} TaskState;

typedef struct {
    char *name;
    char *id;
    TaskState state;
} Task;

typedef struct {
    TaskDaily daily[SCHEDULE_MAX];
    TaskWeek week[SCHEDULE_MAX];
    TaskMonth month[SCHEDULE_MAX];
    TaskYear year[SCHEDULE_MAX];
    TaskOnce once[SCHEDULE_MAX];
} Schedule;

// ---

typedef struct {
    uint8_t hour;
    uint8_t minute;
} Hour;

typedef struct {
    MonthDay day;
    uint8_t month;
} YearDay;

typedef uint8_t WeekDay;
typedef uint8_t MonthDay;
typedef uint8_t Month;
typedef int32_t Year;

// ---

typedef struct {
    Task task;
    Hour hour;
} TaskDaily;

typedef struct {
    Task task;
    
    WeekDay day;
    Hour hour;
} TaskWeek;

typedef struct {
    Task task;
    
    MonthDay day;
    Hour hour;
} TaskMonth;

typedef struct {
    Task task;
    
    MonthDay day;
    Month month;
    
    Hour hour;
} TaskYear;

typedef struct {
    Task task;
    
    MonthDay day;
    Month month;
    Year year;

    Hour hour;
} TaskOnce;

#endif
