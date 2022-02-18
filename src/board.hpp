#include <iostream>
#include <vector>
#include "Cell.hpp"

class Board {
    int _size;
    std::vector<std::vector<Cell>> _matrix;
public:
    Board();
    Board(int size) {
        _size = size;
        for (int i = 0; i < size; i++) {
            std::vector<Cell> ligne;
            for (int j = 0; j < size; j++) {
                ligne.push_back(Cell());
            _matrix.push_back(ligne);
            }
        }
    };
    
    std::string boardDisplay() {
        //Double boucles for: 
            //Impression ligne par ligne du plateau;
        std::string print_board;
        for (int i = 0; i < _size; i++) {
            for (int j = 0; j < _size; j++) {
                //ajoute un string représentant une case du plateau à la valeur de retour
            }
        }
        return print_board;
    };

    void boundCells() {
        //Double boucles for: 
            //Attribue à chaque Cell des pointeurs de ses voisins dans Cell->neighbours
    };
};
