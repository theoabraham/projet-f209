#include <iostream>
#include <fstream>
#include <string>
#include <array>

class Account {
    std::array<std::string, 5> string_arr;
    std::string _name = string_arr[1];
    int _wins=string_arr[3], _defeats=string_arr[4];
    int _num_played = _wins + _defeats;
    //int _nbFriends;
    //int _rank;

public:
    Account(std::string name): _name{name} {

    }
    int parse(const std::string& file_path, std::array<std::string, 4> * arr_addr){
        std::ifstream file;
        unsigned int num_of_line=0;

        file.open("Database/"+file_path);

        if (!file.is_open()){
            return 0;
        }

        while (num_of_line < 4){
            std::string line;
            getline(file, line);
            (*arr_addr)[num_of_line] = line;
            num_of_line++;
        }
        file.close();
        return 1;
    }
    void printProfile() {
	    //Affiche les informations du compte(pseudo, nb de parties jouées (victoires, défaites), nombre d'amis, classement)
    }

    std::string getName() {return _name;}
    int getGamesPlayed() {return _gamesPlayed;}
    int getWins() {return _wins;}
    int getDefeats() {return _defeats;}
    int getNbFriends() {return _nbFriends;}
    int getRank() {return _rank;}
    
    void setName(std::string newName) {_name = newName;}
    void setGamesPlayed(int newGamesPlayed) {_gamesPlayed = newGamesPlayed;}
    void setWins(int newWins) {_wins = newWins;}
    void setDefeats(int newDefeats) {_defeats = newDefeats;}
    void setNbFriends(int newNbFriends) {_nbFriends = newNbFriends;}
    void setRank(int newRank) {_rank = newRank;}
};