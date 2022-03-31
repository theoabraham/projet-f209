#include <ncurses.h>
#include <locale.h>
#include <vector>

class WindowNC {
    public:
        WINDOW * boardWindow;
        WINDOW * boardBoxWindow;
        WINDOW * chatWindow;
        WINDOW * chatBoxWindow;
        WINDOW * inputWindow;
    public:
        WindowNC(){
            setlocale(LC_ALL, "");
            initscr();
            cbreak();

            int maxX, maxY;
            getmaxyx(stdscr, maxY, maxX);
            clear();

            boardBoxWindow = newwin(2*maxY/3, maxX/2, 0, 0);
            boardWindow = newwin(2*maxY/3 - 2, maxX/2 - 2, 1, 1);
            chatWindow = newwin(2*maxY/3 - 2, maxX/2 - 2, 1, maxX/2 + 2);
            chatBoxWindow = newwin(2*maxY/3, maxX/2, 0, maxX/2 + 1);
            inputWindow = newwin(maxY/3, maxX, 2*maxY/3, 0);
            refresh();
            box(boardBoxWindow, 0, 0);
            box(chatBoxWindow, 0, 0);
            box(inputWindow, 0, 0);
            wrefresh(boardBoxWindow);
            wrefresh(chatBoxWindow);
            wrefresh(inputWindow);
        }
        void fetchInput(char &buffer){ //Passage par reference pour que le contenu de buffer soit accessible dans d'autres fonctions.
            mvwgetstr(inputWindow, 1, 1, &buffer); //Récupère l'input dans inputWindow et stocke le contenu dans buffer
            werase(inputWindow);
            box(inputWindow, 0, 0);
            wrefresh(inputWindow);
        }


        void displayMenu(std::vector<const char*> options){
            clearWindow(chatBoxWindow);
            int y = 0;
            for(const char* option: options){
                y++;
                mvwprintw(chatBoxWindow, y, 1, option);
            }
            wrefresh(chatBoxWindow);
        }

        void clearWindow(WINDOW * window) {
            werase(window);
            box(window, 0, 0);
            wrefresh(window);
        }

};