#include "printer_cli.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Frame Buffer :
 * Frame buffer array contains two frames, one on display and one in preparing.
 * A frame is a char array to be straightly printed out.
 * The frame in foreground is indicated by frame_current,
 *      which has only 2 value: 0 or 1,
 *      each print-prepare circle switches the value.
 * To prepare a frame, we print game_table then mask_table onto the buffer.
 *
 * WARNING: Frame is not ended with '\0', but length indicated by screen_w.
 */

#define ANSI_SCREEN_HEIGHT 24
#define ANSI_SCREEN_WIDTH 80
#define ANSI_BUFSIZE (ANSI_SCREEN_HEIGHT * ANSI_SCREEN_WIDTH)
// Width of Info Panel, it's minimal value is 8
#define GRAP 8

/**
 * @brief buildin_buf :
 * buildin buffers for ansi console.
 */
char buildin_buf[2][ANSI_BUFSIZE] = {
    {[0 ... ANSI_BUFSIZE - 1] = 0},
    {[0 ... ANSI_BUFSIZE - 1] = 0},
};

struct printer
{
    uint screen_w; // must greater than 20
    uint screen_h; // must greater than 10
    char *frame_buf[2];
    u8 frame_current;
    u8 use_buildin;
    char *line_buf;      // length always be screen_w+1
    game_info_t *p_info; // pointer to game ginfo, not owning.
};

struct printer *printer_create()
{
    newp(p, struct printer);
    p->screen_h = 0;
    p->screen_w = 0;
    p->frame_buf[0] = NULL;
    p->frame_buf[1] = NULL;
    p->line_buf = NULL;
    p->p_info = NULL;
}

void printer_delete(struct printer *this)
{
    check_ptr(this);
    if (!this->use_buildin)
        for (uint i = 0; i < 2; ++i)
            if (this->frame_buf[i])
                free(this->frame_buf[i]);
    free(this->line_buf);
    free(this);
}

// private func decl begin

void _render_border(struct printer *this);
void _render_info(struct printer *this);

// private func decl end

void printer_init(struct printer *this,
                  uint w_, uint h_, game_info_t *pinfo_)
{
    if (this->line_buf && w_ != this->screen_w)
    {
        free(this->line_buf);
        this->line_buf = NULL;
    }
    if (!this->use_buildin)
        for (uint i = 0; i < 2; ++i)
            if (this->frame_buf[i])
                free(this->frame_buf[i]);
    if (w_ < ANSI_SCREEN_WIDTH && h_ < ANSI_SCREEN_HEIGHT)
    {
        this->frame_buf[0] = buildin_buf[0];
        this->frame_buf[1] = buildin_buf[1];
        this->use_buildin = 1;
        this->screen_w = w_ >= 25 ? w_ : 25;
        this->screen_h = h_ >= 10 ? h_ : 10;
    }
    else
    {
        this->frame_buf[0] = malloc(w_ * h_ * sizeof(char));
        this->frame_buf[1] = malloc(w_ * h_ * sizeof(char));
        if (!(this->frame_buf[0] && this->frame_buf[1]))
            err_malloc;
        this->use_buildin = 0;
        this->screen_w = w_;
        this->screen_h = h_;
    }
    this->frame_current = 0;
    if (!this->line_buf)
        this->line_buf = malloc(this->screen_w + 1);
    check_ptr(pinfo_);
    this->p_info = pinfo_;
}

void printer_render(struct printer *this)
{
    _render_border(this);
    _render_info(this);
    this->frame_current = this->frame_current == 0;
}

void printer_show(struct printer *this, FILE *stream)
{
    register char *frm = this->frame_buf[this->frame_current];
    uint wth = this->screen_w;
    char *lbuf = this->line_buf;
    for (uint i = 0; i < this->screen_h; ++i)
    {
        memcpy(lbuf, frm + i * wth, wth);
        lbuf[wth] = '\n';
        lbuf[wth + 1] = 0;
        fprintf(stream, "%s", lbuf);
    }
    fflush(stream);
}

// private func impl

void _render_border(struct printer *this)
{
    register char *frm = this->frame_buf[this->frame_current == 0];
    register uint wth = this->screen_w;

    // upper border
    memset(frm, '-', wth);
    frm += wth;

    for (uint i = 0; i < this->screen_h - 2; ++i)
    {
        *(frm++) = '|';
        memset(frm, ' ', wth - (GRAP + 3));
        frm += wth - (GRAP + 3);
        *(frm++) = '|';
        memset(frm, ' ', GRAP);
        frm += GRAP;
        *(frm++) = '|';
    }

    // bottom border
    memset(frm, '-', wth);
}

void _render_info(struct printer *this)
{
    register char *frm = this->frame_buf[this->frame_current == 0];
    register uint wth = this->screen_w;
    char tmp[GRAP + 1] = {[0 ... GRAP] = 0};
    unsigned tmplen = 0;
    // start pos: wth - (GRAP + 1)
    frm += wth * 2 - (GRAP + 1);

#define write_literal(str)             \
    memcpy(frm, str, sizeof(str) - 1); \
    frm += wth;
#define write_int(val)                                       \
    tmplen = snprintf(tmp, GRAP, " % *d ", GRAP - 2, (val)); \
    memcpy(frm, tmp, tmplen - 1);                            \
    frm += wth;

    // Write score
    write_literal(" SCORE:");
    write_int(this->p_info->SCORE);
    write_literal(" MINES:");
    write_int(this->p_info->MINE);
    write_literal(" MARK:");
    write_int(this->p_info->MARK);
    write_literal(" REMAIN:");
    write_int(this->p_info->REMAIN);
}
