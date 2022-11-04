#ifndef __game_info_h
#define __game_info_h

#include "util.h"
#include "pos.h"

typedef struct game_info
{
    uint SCORE;
    uint MINE;
    uint MARK;
    uint REMAIN;
    pos_t cursor_pos;
} game_info_t;

#endif // __game_info_h
