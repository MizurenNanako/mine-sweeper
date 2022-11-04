#include "printer_cli.h"

#include <stdio.h>

int main()
{
    game_info_t info = {.MINE = 114};
    void *printer = printer_create();
    printer_init(printer, 0, 0, &info);
    printer_render(printer);
    printer_show(printer, stdout);
    info.REMAIN = 233;
    printer_render(printer);
    printer_show(printer, stdout);
    return 0;
}