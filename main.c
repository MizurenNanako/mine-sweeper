#include "printer_cli.h"
#include "input.h"
#include <ncurses.h>

void __attribute__((constructor)) init();
void __attribute__((destructor)) destory();

void cursor_move_up(pos_t *pos, pos_t rect)
{
    if (pos->y > 1)
        pos->y--;
}
void cursor_move_down(pos_t *pos, pos_t rect)
{
    if (pos->y < rect.y)
        pos->y++;
}
void cursor_move_left(pos_t *pos, pos_t rect)
{
    if (pos->x > 1)
        pos->x--;
}
void cursor_move_right(pos_t *pos, pos_t rect)
{
    if (pos->x < rect.x)
        pos->x++;
}

void (*cur_move[])(pos_t *pos, pos_t rect) = {
    NULL,
    cursor_move_up,
    cursor_move_down,
    cursor_move_left,
    cursor_move_right,
};

int main()
{
    void *que = inque_create();
    input_handler_run(que);
    game_info_t info = {
        .MINE = 114,
        .REMAIN = 514,
        .MARK = 1919,
        .SCORE = 810,
        .cursor_pos = {.x = 5, .y = 5},
    };
    void *printer = printer_create();
    printer_init(printer, 0, 0, &info);
    pos_t rect = printer_get_cursor_range(printer);
    printer_render(printer);
    enum instruction ins;
    do
    {
        printer_show(printer);
        while (inque_empty(que))
            ;
        switch (ins = inque_front(que))
        {
        case instruct_up:
            info.MARK++;
            cur_move[ins](&info.cursor_pos, rect);
            break;
        case instruct_down:
            info.MINE++;
            cur_move[ins](&info.cursor_pos, rect);
            break;
        case instruct_left:
            info.REMAIN++;
            cur_move[ins](&info.cursor_pos, rect);
            break;
        case instruct_right:
            info.SCORE++;
            cur_move[ins](&info.cursor_pos, rect);
            break;
        default:
            break;
        }
        printer_render(printer);
        inque_pop(que);
    } while (ins != instruct_esc);
    input_handler_stop();
    inque_delete(que);
    return 0;
}

void init()
{
    initscr();            // Start curses mode
    raw();                // Line buffering disabled
    keypad(stdscr, TRUE); // We get F1, F2 etc..
    noecho();             // Don't echo() while we do getch
    set_escdelay(10);
    clear();
    move(0, 0);
    refresh();
}

void destory()
{
    endwin(); // End curses mode
}