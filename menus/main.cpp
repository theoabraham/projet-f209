#include <menu.hpp>
#include <windowNCurses.hpp>

int main() {
    WindowNCurses window;
    Menu *menu = new Menu{6, window.getCols()-12, window.getRows()-8, 5};
    window.addMenu(menu);
    WINDOW *firstTestMenu = window.getMenus().at(0);
    while (1) {
        window.update()
        window.handleInput();
        for (int i=0;i<2;i++) {
            if (i==menu->getSelected())
                wattron(firstTestMenu, A_REVERSE);
            mvwprintw(firstTestMenu, i+1, 1, choices[i].c_str());
            wattroff(firstTestMenu, A_REVERSE);
        }
        choice = wgetch(menuwin);

        
        if (choice==10) {
            break;
        }
    }

    getch();
    endwin();
    delete menu;
}

