#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>
#include <menuOptions.hpp>

class Menu {
    int y, x, h, w;
    std::vector<MenuOptionAbstract *> options;
public:
    Menu(int y, int x, int h, int w);

    int getY() {return y;}
    int getX() {return x;}
    int getH() {return h;}
    int getW() {return w;}
    std::vector<MenuOptionAbstract *> const &getOptions() const {return options;}
    
    void addOption(MenuOptionAbstract *option);
    void execInput(int key);

    ~Menu() {
        for (MenuOptionAbstract *o : options)
            delete o;
    }
};

#endif