//
// Created by alex on 2/23/22.
//

#ifndef PROJET_F209_DATABASE_H
#define PROJET_F209_DATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <array>

class DatabaseHandler {
private:
    std::array<std::string, 5> string_arr;


public:
    // Constructeurs
    DatabaseHandler();

    // Getters Setters
    std::string getPlayerBoard()const{return string_arr[1];}
    int getWinGames()const{return std::stoi(string_arr[2]);}
    int getLoseGames()const{return std::stoi(string_arr[3]);}
    int getTotalGames()const{return getWinGames()+getLoseGames();}
    std::string getFriendList() const{return string_arr[4];}

    // Méthodes
    int parse(const std::string& file_path, std::array<std::string, 5> * arr_addr);
    int check_pswd(const std::string& input_psw, const std::string& stocked_hash);
    std::string create_psw();
    int is_string_valid(const std::string &filepath);
    std::string create_file(const std::string& filename);

};


#endif //PROJET_F209_DATABASE_H
