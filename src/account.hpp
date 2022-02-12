#include <iostream>

class Account {
    std::string _name;
    int _gamesPlayed, _wins, _defeats;
    int _nbFriends;
    int _rank;

public:
    Account(std::string name): _name{name} {}

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