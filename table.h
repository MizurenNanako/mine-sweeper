#pragma once

struct ctable;

struct ctable *ctable_create(int w_, int h_);
void ctable_delete(struct ctable *p);
