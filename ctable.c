#include "ctable.h"
#include <stdlib.h>
#include <string.h>

struct ctable
{
    uint w;
    uint h;
    char *data;
};

struct ctable *ctable_create(int w_, int h_)
{
    newp(p, struct ctable);
    p->data = malloc(w_ * h_);
    memset(p->data, 0, w_ * h_);
    p->w = w_ ? w_ : 1;
    p->h = h_ ? h_ : 1;
    return p;
}

void ctable_delete(struct ctable *this)
{
    free(this->data);
    free(this);
}

char ctable_get(struct ctable *this, uint x, uint y)
{
    return this->data[x * this->h + y];
}

void ctable_set(struct ctable *this, uint x, uint y, char v)
{
    this->data[x * this->h + y] = v;
}
