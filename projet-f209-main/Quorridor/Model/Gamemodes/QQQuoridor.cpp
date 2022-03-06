#include "QQQuoridor.hpp"
#include "../../Controller/Game.hpp"
#include "../../View/DisplayBoard.hpp"

std::vector<std::string> QQQuoridorBoard::divideInput(std::string &input) {
    std::vector<std::string> res;
    // Teste si l'entrée est un coup ou deux coups
    if ((input.size() != 5) and (input.size() != 11)) return res;

    std::string firstMove, secondMove;
    bool first = true;
    char separation = '/';

    for (long unsigned int i = 0; i < input.size(); i++) {
        if (first and (input[i] != separation)) {
            // Si c'est avant la séparation, c'est le premier coup
            firstMove += input[i];
        }
        else if (input[i] == separation) {
            first = false;
        }
        else {
            // Le deuxième coup se trouve après la séparation
            secondMove += input[i];
        }
    }
    res = {firstMove, secondMove}; // vecteur contenant les deux coups séparés
    return res;
}

bool QQQuoridorBoard::checkInput(std::string &input, int currentP) {
    bool res = false;
    std::vector<std::string> sepInput = divideInput(input);
    if (!sepInput.empty()) {
        // Si l'input n'est pas vide
        for (long unsigned int i = 0; i < sepInput.size(); i++) {
            if (sepInput[i] != "") {
                // Si le string n'est pas vide. Exemple: si le joueur n'entre qu'un coup, le deuxième string est vide
                if (sepInput[i].size() != 5) res = false;
                int len = 4;
                std::string typeOfMove{sepInput[i].substr(0, 1)};

                QQQuoridorPosition target_pos{sepInput[i].substr(2, len)};

                target_pos = target_pos * 2; //*2 pour avoir la vrai position sur la matrice

                currentPlayer = currentP;
                if (isValid(typeOfMove, target_pos, currentP)) {
                    executeMove(typeOfMove, target_pos, currentP);
                    if(typeOfMove=="H" or typeOfMove=="V"){
                        if(!possiblePaths()){
                            removeWall(typeOfMove, target_pos);
                            players[currentPlayer]->addWall();
                            res = false;
                        }
                    }
                    else res = true;
                }
                else res = false;
            }
        }
    }
    return res;
}

// Prend un y composé de deux chiffres. Exemple: g12, pos[1]=1 et pos[2]=2
QQQuoridorPosition::QQQuoridorPosition(std::string pos): Position(int(pos[0])-97, (int(pos[1])-48)*10 + (int(pos[2])-48)) {}

Position QQQuoridorPosition::operator=(const Position& other) {
    QQQuoridorPosition pos(*this);
    Position::operator=(other);
    return pos;
}
