//
// Created by alex on 2/23/22.
//

#ifndef PROJET_F209_DATABASE_H
#define PROJET_F209_DATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <iterator>


class DatabaseHandler {
private:
    std::array<std::string, 6> string_arr;
    std::vector<std::string> friendList;
    std::vector<std::string> toAddList;
    std::string username;
public:
    // Constructeurs
    DatabaseHandler();

    // Getters Setters
    std::string getPlayerBoard()const{return string_arr[1];}
    int getWinGames()const{return std::stoi(string_arr[2]);}
    int getLoseGames()const{return std::stoi(string_arr[3]);}
    int getTotalGames()const{return getWinGames()+getLoseGames();}
    std::vector<std::string> getToAddFriendList() const{return toAddList;}
    std::vector<std::string>  getFriendList() const {return friendList;}

    // Méthode "bool"
    int checkPswd(const std::string& input_psw, const std::string& stocked_hash);
    int is_string_valid(const std::string &filepath);
    bool does_file_exist(const std::string &filename);
    // Méthodes
    int parse(const std::string& file_path, std::array<std::string, 6> * arr_addr);
    std::string createPsw();
    std::string createFile(const std::string& filename);
    void writeFriends(const std::string& filename,const std::string &friends_str);
    void writeFriendstoAdd(const std::string &friends_name);
    void transferFriend();
    void addfriend(const std::string& friendname);

};
#endif //PROJET_F209_DATABASE_H
