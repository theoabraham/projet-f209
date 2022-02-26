#include <iostream>
#include <ncurses.h>

using namespace std;

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW* menuwin = newwin(6, xMax-12, yMax-8, 5);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true);

    string choices[3] = {"1. Play", "2. Exit"};
    int choice;
    int highlight = 0;

    while (1) {
        for (int i=0;i<2;i++) {
            if (i==highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 1, choices[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }
        choice = wgetch(menuwin);

        switch (choice) {
            case KEY_UP:
                highlight == 0 ? highlight = 1 : highlight--;
                break;
            case KEY_DOWN:
                highlight == 1 ? highlight = 0 : highlight++;
                break;
            default:
                break;
        }
        if (choice == 10) {
            if (highlight == 0) {
                printw("You selected : 1. Play");
                refresh();
            }
            else {
                break;
            }
        }
    }

    endwin();

    return 0;
}