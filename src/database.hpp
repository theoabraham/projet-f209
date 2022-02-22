#include <iostream>
#include "account.hpp"

class Database {
    int _publicKey;
    int _privateKey;
public:
	Database();
    void signUp();   //Créer un nouveau compte dans la base de données 
    bool login();   //Cherche si le compte existe dans la base de données, renvoie True si le compte existe, False sinon
    void prompt(std::string option) { //Demande à l'utilisateur s'il souhaite s'inscrire ou se connecter 
        if (option == "signup") {
            signUp();
        }
        login();
    }

    void saveGame(Account userAccount, std::string saveName);    //Sauvegarde une partie dans le fichier du compte de l'hôte de la partie
    void loadGame(Account userAccount, std::string saveName);    //Vérifie s'il existe une sauvegarde du nom saveName dans le fichier lié au userAccount
    void deleteSave(Account userAccount, std::string saveName); //Détruit une sauvegarde du nom saveName dans le fichier lié au userAccount

    void deleteAccount(Account userAccount);    //Efface le fichier lié au userAccount
    	                                        //renvoie vers la demande prompt()
                                                
    void addFriend(Account userAccount, Account friendAccount);  //userAccount demande friendAccount en ami
    void acceptFriend(Account userAccount,Account friendAccount, bool isAccepted); //Accepte ou refuse la demande en ami de friendAccount envoyé à userAccount
    void deleteFriend(Account userAccount,Account friendAccount);    //Efface friendAccount de la liste d'amis de userAccount
};
/*
#include <iostream>
#include <fstream>
#include <string>
#include <array>

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

int check_pswd(const std::string& input_psw, const std::string& stocked_hash){
    std::hash<std::string> h;
    if (!(std::to_string(h(input_psw)) == stocked_hash)){ // si hash(psw) != hash_stocké
        return 0;
    }
    std::cout << "Mot de passe valide" << std::endl;
    return 1;
}

std::string create_psw(){
    std::string psw="a"; std::string pswv="b";
    std::hash<std::string> hashed;
    while (psw != pswv){
        std::cout << "Entrez votre mot de passe (/!\\ mot de passe visible): ";
        std::getline(std::cin, psw);
        std::cin.ignore();
        std::cout << "Confirmez le mot de passe: ";
        std::getline(std::cin, pswv);
        std::cin.ignore();

        if (psw != pswv){
            std::cout << "Mots de passe non valide / différents, veuillez réessayer." << std::endl;
        }
    }
    return std::to_string(hashed(psw));
}

int is_file_ok(const std::string &filepath){
    for (auto &c: filepath){
        if (c=='/' or c=='.' or c==' '){
            return 0;
        }
    }
    return 1;
}

void create_file(const std::string& filename){
    std::fstream output_file;
    const std::string board="/////\n"; const std::string win="winned_game\n"; const std::string loosed="loosed_game\n";
    std::string psw = create_psw() + '\n';
    FILE *o_file = fopen(("Database/"+filename).c_str(), "w");
    if (o_file){
        fwrite(psw.c_str(), 1, psw.size(), o_file);
        fwrite(board.c_str(), 1, board.size(), o_file);
        fwrite(win.c_str(), 1, win.size(), o_file);
        fwrite(loosed.c_str(), 1, loosed.size(), o_file);
    }
}

void build_mat_from_str(const std::string& str){
    unsigned int i=0;unsigned int j=0;
    for (unsigned char c:str) {
        int int_c = (int) c;
        if (49 <= int_c && int_c <= 57){// ord('0')=48 et ord('9')=59 -> on cherche juste les entier entre 1 et 9
            j+= (int_c-48);             // par exemple '3' --> ord('3')=51 --> 51-48 = 3
            std::cout << "Positionné à la case:" << i << ',' << j << std::endl;
        }else if (c=='/'){
            i+=1;                       //saute une ligne
            j=0;                        //repart à la colone 0
            std::cout << "Départ à la case:" << i << ',' << j << std::endl;
        }else{
            // appelle le constructeur piece{char} -> implique avoir un constructeur qui prend un char en paramètre
            std::cout << "Construction de la piece "<< c << " en:" << i << ',' << j << std::endl;
            j+=1;                       //passe a la case suivante une fois la piece ajoutée
        }
    }
}

void some_db_method_but_its_a_function(){
    std::array<std::string, 4> string_arr;
    std::string input_file;
    std::string psw;

    std::cout << "Entrez un nom de fichier : " << std::endl;
    std::getline(std::cin, input_file);

    if (!is_file_ok(input_file)){
        std::cout << "Le fichier entré comporte un caractère interdit..." << std::endl;
        return;
    }

    if (!parse(input_file, &string_arr)){  // si fichier existe pas
        std::string ans;
        std::cout << "Fichier non existant..." << std::endl;
        while (ans != "n" and ans != "N" and ans !="Y" and ans !="y"){
            std::cout << "Voulez vous créé une nouvelle entrée (Y/n)? "; std::cin >> ans;
        }
        if (ans =="n"){
            return;
        }
        create_file(input_file);
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
    build_mat_from_str(string_arr[1]);
}

int main() {
    some_db_method_but_its_a_function();
    return 0;
}
*/