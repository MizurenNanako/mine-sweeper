#include "input.h"
#include <ncurses.h>
#include <threads.h>

typedef enum instruction inst_t;

typedef struct quere_node
{
    inst_t inst;
    struct quere_node *prev;
    struct quere_node *next;
} qnd_t;

struct input_quere
{
    mtx_t *lock;
    qnd_t *watcher;
};

qnd_t *qnode_create(inst_t ins, qnd_t *pr, qnd_t *ne)
{
    newp(p, qnd_t);
    p->inst = ins;
    p->prev = pr;
    p->next = ne;
    return p;
}

struct input_quere *inque_create()
{
    newp(p, struct input_quere);
    newp(q, qnd_t);
    q->inst = instruct_non;
    q->prev = q;
    q->next = q;
    p->watcher = q;
    p->lock = malloc(sizeof(mtx_t));
    mtx_init(p->lock, mtx_plain);
    return p;
}

void inque_delete(struct input_quere *this)
{
    mtx_lock(this->lock);
    check_ptr(this);
    register qnd_t *w = this->watcher;
    qnd_t *q = w->next;
    while (q != w)
    {
        qnd_t *t = q;
        q = q->next;
        free(t);
    }
    free(w);
    mtx_unlock(this->lock);
    free(this->lock);
    free(this);
}

void inque_append(struct input_quere *this, enum instruction ins)
{
    mtx_lock(this->lock);
    register qnd_t *w = this->watcher;
    qnd_t *q = qnode_create(ins, w->prev, w);
    w->prev->next = q;
    w->prev = q;
    mtx_unlock(this->lock);
}

enum instruction inque_front(struct input_quere *this)
{
    register qnd_t *w = this->watcher;
    if (w->next != w)
        return w->next->inst;
    err_out_of_range(*this);
}

void inque_pop(struct input_quere *this)
{
    mtx_lock(this->lock);
    register qnd_t *w = this->watcher;
    if (w->next != w)
    {
        qnd_t *q = w->next;
        w->next = q->next;
        q->next->prev = w;
        free(q);
        mtx_unlock(this->lock);
        return;
    }
    mtx_unlock(this->lock);
    err_out_of_range(*this);
}

int inque_empty(struct input_quere *this)
{
    return this->watcher->next == this->watcher;
}

thrd_t input_handler_thread = 0;
volatile u8 input_handler_flag = 1;

int input_handler_loop(void *quere)
{
    struct input_quere *q = quere;
    while (input_handler_flag)
    {
        switch (getch())
        {
        case KEY_UP:
            inque_append(q, instruct_up);
            break;
        case KEY_DOWN:
            inque_append(q, instruct_down);
            break;
        case KEY_LEFT:
            inque_append(q, instruct_left);
            break;
        case KEY_RIGHT:
            inque_append(q, instruct_right);
            break;
        case 27: // ESC or ALT
        case 'q':
            inque_append(q, instruct_esc);
            break;
        case 'm':
            inque_append(q, instruct_mark);
            break;
        case 's':
            inque_append(q, instruct_select);
        default:
            break;
        }
    }
}

void input_handler_run(struct input_quere *quere)
{
    if (input_handler_thread)
        err("There's already an input handler running.");
    input_handler_flag = 1;
    thrd_create(&input_handler_thread, input_handler_loop, quere);
}

void input_handler_stop()
{
    input_handler_flag = 0;
    thrd_join(input_handler_thread, NULL);
    input_handler_thread = 0;
}