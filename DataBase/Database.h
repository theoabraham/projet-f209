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
    std::array<std::string, 4> string_arr;

public:
    DatabaseHandler();
    int parse(const std::string& file_path, std::array<std::string, 4> * arr_addr);
    int check_pswd(const std::string& input_psw, const std::string& stocked_hash);
    std::string create_psw();
    int is_string_valid(const std::string &filepath);
    void create_file(const std::string& filename);

};


#endif //PROJET_F209_DATABASE_H
