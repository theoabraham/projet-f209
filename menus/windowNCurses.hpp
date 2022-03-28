#ifndef WINDOW_N_CURSES_HPP
#define WINDOW_N_CURSES_HPP

#include <ncurses.h>
#include <string>
#include <menu.hpp>

class WindowNCurses {
    int rows, cols;
    std::vector<WINDOW*> menus;
    std::vector<MenuOptionAbstract *> menuOptions;
    int selected = 0;
public:
    WindowNCurses::WindowNCurses();

    int getRows() const {return rows;}
    int getCols() const {return cols;}
    int getSelected() {return selected;}
    std::vector<WINDOW*> const &getMenus() const {return menus;}

    void addMenu(Menu* menu);
    void drawText(WINDOW* window, std::string text, float y, float x, bool highlight = false);
    void drawMenuOptions();
    void handleInput();

    void clear() {erase();}
    void update() {
        drawMenus();
        refresh();}
    void close() {
        for (int i=0;i<menus.size();i++)
            delete menus.at(i);
        endwin();
    }
};

#endif