#include "Database.h"

/*
 * Passe en revue uun fichier texte pour placer dans une liste différentes informations
 * soit l une liste:
 *      l[0]=mot de passe, l[1]=plateau, l[2]=parties gagnées, l[3]=parties perdues, l[4]=amis a ajouter, l[5]=amis
 */
int DatabaseHandler::parse(const std::string& file_path, std::array<std::string, 6> * arr_addr){
    std::ifstream file;
    unsigned int num_of_line=0;

    // ouvre le fichier
    file.open("Data/"+file_path);

    if (!file.is_open()){
        return 0;
    }

    // pour chaque line du fichier place le dans la liste
    while (num_of_line < string_arr.size()){
        std::string line;
        getline(file, line);
        (*arr_addr)[num_of_line] = line;
        num_of_line++;
    }
    // mets à jours friendsList et toAddList
    std::istringstream to_add_str(string_arr[4]);
    std::istringstream friend_str(string_arr[5]);
    toAddList = std::vector<std::string>(std::istream_iterator<std::string>{to_add_str},std::istream_iterator<std::string>());
    friendList = std::vector<std::string>(std::istream_iterator<std::string>{friend_str},std::istream_iterator<std::string>());
    file.close();
    return 1;
}
/*
 * Vérifie si le mot de passe entré une fois hashé équivaut au hash stocké dans le fichier texte
 */
int DatabaseHandler::checkPswd(const std::string& input_psw, const std::string& stocked_hash){
    std::hash<std::string> h;
    if (!(std::to_string(h(input_psw)) == stocked_hash)){ // si hash(psw) != hash_stocké
        return 0;
    }
    std::cout << "Mot de passe valide" << std::endl;
    return 1;
}

/*
 * Demande à l'utilisateur d'entrer deux fois son mdp sans espace !, une fois validé, le mdp est hashé et retourné
 */
std::string DatabaseHandler::createPsw() {
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

/*
 * vérifier si un ficher donné en entrée est valide (ne correspond pas à un dossier , fichier caché, etc)
 */
int DatabaseHandler::is_string_valid(const std::string &filepath){
    for (auto &c: filepath){
        if (c=='/' or c=='.' or c==' ')return 0;
    }
    return 1;
}

/**
 * @brief return vrai si le fichier donné en paramètre est existant
 * @param filename
 * @return
 */
bool DatabaseHandler::does_file_exist(const std::string &filename) {
    std::ifstream ifile("Data/"+filename);
    if (ifile.is_open()){
        return 1;
    }else{
        return 0;
    }
}
/**
 * @brief créé un fichier avec des valeures initiale
 * @param filename
 * @return
 */
std::string DatabaseHandler::createFile(const std::string& filename){
    const std::string board="/////\n"; const std::string win="0\n"; const std::string loosed="0\n";
    const std::string none1="none\n"; const std::string none2="none";
    std::string psw = createPsw() + '\n' ;
    FILE *o_file = fopen(("Data/"+filename).c_str(), "w");
    if (o_file){
        fwrite(psw.c_str(), 1, psw.size(), o_file);
        fwrite(board.c_str(), 1, board.size(), o_file);
        fwrite(win.c_str(), 1, win.size(), o_file);
        fwrite(loosed.c_str(), 1, loosed.size(), o_file);
        fwrite(none1.c_str(), 1, none1.size(), o_file);
        fwrite(none2.c_str(), 1, none2.size(), o_file);
    }
    fclose(o_file);
    return filename;
}
/**
 * @brief Ecrit dans un fichier donnéé une liste d'amis
 * @param filename
 * @param friends_str
 */
void DatabaseHandler::writeFriends(const std::string &filename, const std::string &friends_str) {
    const std::string board=string_arr[1]+"\n"; const std::string win=string_arr[2]+"\n";
    const std::string loosed=string_arr[3]+"\n";const std::string none="none\n";
    std::string psw = string_arr[0]+"\n";
    FILE *o_file = fopen(("Data/"+filename).c_str(), "w");
    if (o_file){
        fwrite(psw.c_str(), 1, psw.size(), o_file);
        fwrite(board.c_str(), 1, board.size(), o_file);
        fwrite(win.c_str(), 1, win.size(), o_file);
        fwrite(loosed.c_str(), 1, loosed.size(), o_file);
        fwrite(none.c_str(), 1, none.size(), o_file);
        fwrite(friends_str.c_str(), 1, friends_str.size(), o_file);
    }
    fclose(o_file);
}
/**
 * @brief Transfer les amis de la liste toAdd à FriendList en demandant à l'utilsateur
 */
void DatabaseHandler::transferFriend() {
    for (std::string s : toAddList){
        std::string ans;
        if (s=="none"){
            std::cout << "Aucune demande en amis :weary:" << std::endl;
            return;
        }
        while (ans != "n" and ans != "N" and ans !="Y" and ans !="y"){
            std::cout << "Voulez vous ajoutez " << s << " en amis ? (Y/n) : "; std::cin >> ans;
        }
        if (ans == "Y" or ans == "y"){
            friendList.push_back(s);
        }
    }
}
/**
 * @brief écrit les amis à ajouter dans la ligne 5 du fichier texte
 * @param friends_name
 */
void DatabaseHandler::writeFriendstoAdd(const std::string &friends_name) {
    // recupération temporaire des données de temp;
    std::array<std::string, 6> temp;
    parse(friends_name, &temp);
    //réécriture en fichier
    const std::string board=temp[1]+"\n"; const std::string win=temp[2]+"\n";
    const std::string loosed=temp[3]+"\n";const std::string none="none";
    const std::string friends= username+"\n";
    std::string psw = temp[0]+"\n";
    FILE *o_file = fopen(("Data/"+friends_name).c_str(), "w");
    if (o_file){
        fwrite(psw.c_str(), 1, psw.size(), o_file);
        fwrite(board.c_str(), 1, board.size(), o_file);
        fwrite(win.c_str(), 1, win.size(), o_file);
        fwrite(loosed.c_str(), 1, loosed.size(), o_file);
        fwrite(friends.c_str(), 1, friends.size(), o_file);
        fwrite(none.c_str(), 1, none.size(), o_file);
    }
    fclose(o_file);
}

/**
 * @brief Affiche une liste des amis
 */
void DatabaseHandler::listFriends() {
    for (std::string s:friendList){
        if (s!= "none") std::cout << s << std::endl;
    }
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
        std::string new_file = createFile(input_file);
        parse(new_file, &string_arr);
        return;
    }
    //met a jout le nom
    username=input_file;

    //demande le mdp
    std::cout << "______________________________" << std::endl;
    std::cout << "Fichier " << username << " trouvé \nEntrez votre mot de passe: ";
    std::cin >> psw;

    //vérification du mdp
    if(!checkPswd(psw, string_arr[0])){
        std::cout << "Erreur, mauvais mot de passe." << std::endl;
        return;
    }
    //mise à jours des amis
    std::cout << "______________________________" << std::endl;
    std::cout << "Mise à jours des amis:" << std::endl;
    transferFriend();
    //réécriture dans le fichier
    std::string friends_str;
    for (std::string s:friendList){
        friends_str += (s + " ");
    }
    writeFriends(username, friends_str);
    std::cout << "Voici votre liste d'amis:"<<std::endl;
    listFriends();
    std::cout << "______________________________" << std::endl;
    //ajout d'amis
    std::cout << "Ajouts d'amis:" << std::endl;

    std::string friends;
    while (friends != "N" and friends != "n"){
        std::cout << "Entrez un amis a ajouter (N/n pour annuler): ";
        std::cin >> friends;
        if (friends != "N" and friends != "n") {
            if (!does_file_exist(friends) or username == friends) {
                std::cout << "Amis innexistant / impossible à ajouter" << std::endl;
            } else {
                writeFriendstoAdd(friends);
            }
        }
    }
    std::cout << "______________________________" << std::endl;
    std::cout << "Construction de la matrice" << std::endl;
    std::cout << "..." << std::endl;
}

int main(){
    DatabaseHandler dbh;
    return 0;
}