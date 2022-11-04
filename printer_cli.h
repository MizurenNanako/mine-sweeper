#ifndef __printer_cli_h
#define __printer_cli_h

#include "util.h"

struct printer;
struct printer *printer_create();
void printer_delete(struct printer *this);
void printer_init(struct printer *this, uint w_, uint h_);
void printer_render(struct printer *this);
void printer_show(struct printer *this, FILE *stream);

/**
 * @brief Init or Reset printer
 * 
 * @param this 
 * @param w_ new screen width
 * @param h_ new screen height
 */
void printer_init(struct printer *this, uint w_, uint h_);

#endif // __printer_cli_h
