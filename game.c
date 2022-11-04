#include "game.h"
#include "game_info.h"
#include "ctable.h"

enum game_state
{
    gstate_start_uninit = -1,
    gstate_start_menu = 0,
    gstate_game_run = 1,
    gstate_game_menu = 2,
    gstate_game_failed = 3,
};

struct game
{
    enum game_state gstate;
    struct ctable *mask_table;
    struct ctable *game_table;
    game_info_t ginfo;
};

struct game *game_create()
{
    newp(p, struct game);
    p->gstate = gstate_start_uninit;
    p->game_table = NULL;
    p->mask_table = NULL;
    game_info_t tmp =
        {.SCORE = 0, .MARK = 0, .MINE = 0, .REMAIN = 0};
    p->ginfo = tmp;
    return p;
}

void game_delete(struct game *this)
{
    check_ptr(this);
    if (this->game_table)
        ctable_delete(this->game_table);
    if (this->mask_table)
        ctable_delete(this->mask_table);
    free(this);
}