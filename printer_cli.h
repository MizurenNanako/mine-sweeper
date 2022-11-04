#ifndef __printer_cli_h
#define __printer_cli_h

#include "util.h"
#include "game_info.h"

struct printer;
struct printer *printer_create();
void printer_delete(struct printer *this);

/**
 * @brief Init or Reset printer
 *
 * @param this
 * @param w_ new screen width
 * @param h_ new screen height
 * @param pinfo_ pointer to gameinfo
 */
void printer_init(struct printer *this, uint w_, uint h_, game_info_t *pinfo_);
void printer_render(struct printer *this);
void printer_show(struct printer *this);
pos_t printer_get_cursor_range(struct printer *this);

#endif // __printer_cli_h
