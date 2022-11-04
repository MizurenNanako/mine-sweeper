#include <ncurses.h>

int main()
{
    int ch;

    initscr();            /* Start curses mode 		*/
    raw();                /* Line buffering disabled	*/
    keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
    noecho();             /* Don't echo() while we do getch */
    set_escdelay(10);

    printw("Type any character to see it in bold\n");
    ch = getch(); /* If raw() hadn't been called
                   * we have to press enter before it
                   * gets to the program 		*/
                  /* Without keypad enabled this will */
    while (1)
    {
        printw("%d ", ch);
        ch = getch();
    }

    /* Without noecho() some ugly escape
     * charachters might have been printed
     * on screen			*/
    refresh(); /* Print it on to the real screen */
    getch();   /* Wait for user input */
    endwin();  /* End curses mode		  */

    return 0;
}