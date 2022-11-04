#include "printer_cli.h"

#include <stdio.h>

int main()
{
    void *printer = printer_create();
    printer_init(printer, 0, 0);
    printer_render(printer);
    printer_show(printer, stdout);
    return 0;
}