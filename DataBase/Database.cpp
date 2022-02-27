//
// Created by alex on 2/23/22.
//

#include "Database.h"


int DatabaseHandler::parse(const std::string& file_path, std::array<std::string, 5> * arr_addr){
    std::ifstream file;
    unsigned int num_of_line=0;

    file.open("Data/"+file_path);

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

int DatabaseHandler::check_pswd(const std::string& input_psw, const std::string& stocked_hash){
    std::hash<std::string> h;
    if (!(std::to_string(h(input_psw)) == stocked_hash)){ // si hash(psw) != hash_stocké
        return 0;
    }
    std::cout << "Mot de passe valide" << std::endl;
    return 1;
}

std::string DatabaseHandler::create_psw(){
    std::hash<std::string> hashed;
    std::string psw;std::string pswv;
    do{
        std::cout<< "Entrez votre mot de passe: ";
        std::cin >> psw;
        std::cout<< "Confirmez votre mot de passe: ";
        std::cin >> pswv;
    }while (psw != pswv);
    return std::to_string(hashed(psw));
}

int DatabaseHandler::is_string_valid(const std::string &filepath){
    for (auto &c: filepath){
        if (c=='/' or c=='.' or c==' ')return 0;
    }
    return 1;
}

std::string DatabaseHandler::create_file(const std::string& filename){
    std::fstream output_file;
    const std::string board="/////\n"; const std::string win="0\n"; const std::string loosed="0\n";
    std::string psw = create_psw() + '\n';
    FILE *o_file = fopen(("Data/"+filename).c_str(), "w");
    if (o_file){
        fwrite(psw.c_str(), 1, psw.size(), o_file);
        fwrite(board.c_str(), 1, board.size(), o_file);
        fwrite(win.c_str(), 1, win.size(), o_file);
        fwrite(loosed.c_str(), 1, loosed.size(), o_file);
    }
    fclose(o_file);
    return filename;
}

DatabaseHandler::DatabaseHandler() {
    std::string input_file;
    std::string psw;

    //entre le fichier
    std::cout << "Entrez un nom de fichier : " << std::endl;
    std::getline(std::cin, input_file);

    //vérifie la syntaxe
    if (!is_string_valid(input_file)){
        std::cout << "Le fichier entré comporte un caractère interdit..." << std::endl;
        return;
    }

    // parse le fichier donné
    if (!parse(input_file, &string_arr)){  // si fichier existe pas
        std::string ans;
        std::cout << "Fichier non existant..." << std::endl;
        while (ans != "n" and ans != "N" and ans !="Y" and ans !="y"){
            std::cout << "Voulez vous créé une nouvelle entrée (Y/n)? "; std::cin >> ans;
        }
        if (ans =="n"){
            return;
        }
        std::string new_file = create_file(input_file);
        parse(new_file, &string_arr);
        return;
    }
    std::cout << "______________________________" << std::endl;
    std::cout << "Fichier " << input_file << " trouvé \nEntez votre mot de passe: " << std::endl;
    std::cin >> psw;

    if(!check_pswd(psw, string_arr[0])){
        std::cout << "Erreur, mauvais mot de passe." << std::endl;
        return;
    }
    std::cout << "______________________________" << std::endl;
    std::cout << "Construction de la matrice" << std::endl;
    std::cout << "..." << std::endl;
}

int main() {
    DatabaseHandler dbh;
    return 0;
}
