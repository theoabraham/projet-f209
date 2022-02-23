#include <windowNCurses.hpp>

WindowNCurses::WindowNCurses() {
    initscr();
    noecho();
    cbreak();
    getmaxyx(stdscr, rows, cols);
    keypad(stdscr, true);
}

void WindowNCurses::addMenu(Menu* menu) {
    WINDOW * addedMenu = newwin(menu->getH(), menu->getW(), menu->getY(), menu->getX());
    menus.push_back(addedMenu);
    for (MenuOptionAbstract *o : menu->getOptions())
        menuOptions.push_back(o);
    box(addedMenu, 0, 0);
    refresh();
    wrefresh(addedMenu);
    keypad(addedMenu, true);
}

void WindowNCurses::drawText(WINDOW* window, std::string text, float y, float x, bool highlight){
    if(highlight) attron(A_REVERSE);
    mvwprintw(window, y, x - text.length()*0.5, "%c", text);
    attrset(A_NORMAL);
}

void WindowNCurses::drawMenuOptions() {
    for (int i=0;i<menuOptions.size();i++) {
        if (i==getSelected())
            for (WINDOW *menu : menus)
                wattron(menu, A_REVERSE);
        mvwprintw(menu, i+1, 1, choices[i].c_str());
        wattroff(menu, A_REVERSE);
    }
}