#include <menu.hpp>

Menu::Menu(int y, int x, int h, int w) : y(y), x(x), h(h), w(w) {
    addOption(new TextOption("1. Play"));
    addOption(new TextOption("2. Exit"));
}

void Menu::execInput(int key) {
    switch (key) {
            case KEY_UP:
                selected == 0 ? selected = options.size()-1 : selected--;
                break;
            case KEY_DOWN:
                selected == options.size()-1 ? selected = 0 : selected++;
                break;
            case KEY_ENTER:
                selected == 0 ? mvprintw(10, 5, "You selected : 1. Play") : endwin();
                break;
            default:
                break;
    }
};

void Menu::addOption(MenuOptionAbstract *option) {
    options.emplace_back(option);
}