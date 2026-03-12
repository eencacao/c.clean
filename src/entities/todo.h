#ifndef TODO_H
#define TODO_H

#define MAX_TODOS 128
#define TITLE_LEN 256
#define DATE_LEN  32

typedef struct {
    int  id;
    char title[TITLE_LEN];
    int  completed;
    char created_at[DATE_LEN];
} Todo;

#endif
