#ifndef __pos_h
#define __pos_h

#include "util.h"

typedef struct pos
{
    uint x;
    uint y;
} pos_t;

pos_t pos_add(pos_t a, pos_t b)
{
    pos_t r = {.x = a.x + b.x, .y = a.y + b.y};
    return r;
}

pos_t pos_sub(pos_t a, pos_t b)
{
    pos_t r = {.x = a.x - b.x, .y = a.y - b.y};
    return r;
}

pos_t pos_mul(pos_t a, pos_t b)
{
    pos_t r = {.x = a.x * b.x, .y = a.y * b.y};
    return r;
}

uint pos_dot(pos_t a, pos_t b)
{
    return a.x * b.x + a.y * b.y;
}

uint pos_cross(pos_t a, pos_t b)
{
    return a.x * b.y - a.y * b.x;
}

#endif // __pos_h
