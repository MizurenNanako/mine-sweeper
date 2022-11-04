#ifndef __ctable_h
#define __ctable_h

#include "util.h"

struct ctable;

/**
 * @brief Create a char table (2d)
 * 
 * @param w_ 
 * @param h_ 
 * @return struct ctable* 
 */
struct ctable *ctable_create(int w_, int h_);

/**
 * @brief Delete a char table (2d)
 * 
 * @param p 
 */
void ctable_delete(struct ctable *p);

/**
 * @brief Get value from ctable
 * 
 * @param this 
 * @param x x >= 0 and x < ctable.w
 * @param y y >= 0 and y < ctable.h
 * @return char 
 */
char ctable_get(struct ctable *this, uint x, uint y);

/**
 * @brief Set value to ctable
 * 
 * @param this 
 * @param x x >= 0 and x < ctable.w
 * @param y y >= 0 and y < ctable.h
 * @param v value to set
 */
void ctable_set(struct ctable *this, uint x, uint y, char v);

#endif // __ctable_h