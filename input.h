#ifndef __input_h
#define __input_h

#include "util.h"

enum instruction
{
    instruct_non = 0,
    instruct_up,
    instruct_down,
    instruct_left,
    instruct_right,
    instruct_select,
    instruct_mark,
    instruct_esc,
};

struct input_quere;

struct input_quere *inque_create();
void inque_delete(struct input_quere *this);
void inque_append(struct input_quere *this, enum instruction ins);
enum instruction inque_front(struct input_quere *this);
void inque_pop(struct input_quere *this);
int inque_empty(struct input_quere *this);

void input_handler_run(struct input_quere *quere);
void input_handler_stop();

#endif // __input_h
