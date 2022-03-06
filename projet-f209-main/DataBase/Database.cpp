#include "Database.h"

void DatabaseHandler::setFriendsList(const std::string &fstr){
    std::istringstream friend_str(fstr);
    friendList = std::vector<std::string>(std::istream_iterator<std::string>{friend_str},std::istream_iterator<std::string>());
}

void DatabaseHandler::setToaddList(const std::string &fstr) {
    std::istringstream to_add_str(fstr);
    toAddList = std::vector<std::string>(std::istream_iterator<std::string>{to_add_str},std::istream_iterator<std::string>());
}

/**
 * @brief Passe en revue uun fichier texte pour placer dans une liste différentes informations soit l une liste:
 *      l[0]=mot de passe, l[1]=plateau, l[2]=parties gagnées, l[3]=parties perdues, l[4]=amis a ajouter, l[5]=amis
 * @param file_path nom du fichier à parse, pas besoin de spécifier /Data
 * @param arr_addr addresse mémoire de l'array de taille 6
 */
void DatabaseHandler::parse(const std::string& file_path, std::array<std::string, 6> * arr_addr){
    std::ifstream file;
    unsigned int num_of_line=0;

    // ouvre le fichier
    file.open("../DataBase/Data/"+file_path);

    // pour chaque line du fichier place le dans la liste
    while (num_of_line < string_arr.size()){
        std::string line;
        getline(file, line);
        (*arr_addr)[num_of_line] = line;
        num_of_line++;
    }
    // mets à jours friendsList et toAddList
    setToaddList(string_arr[4]);
    setFriendsList(string_arr[5]);
    file.close();
}
/**
 * @brief Vérifie si le mot de passe entré une fois hashé équivaut au hash stocké dans le fichier texte
 * @param input_psw mot de passe de l'utilisateur
 * @param stocked_hash le hash stocké dans son fichier (string_arr[0])
 * @return bool(int)
 */
int DatabaseHandler::checkPswd(const std::string& input_psw){
    std::hash<std::string> h;
    if (!(std::to_string(h(input_psw)) == string_arr[0])){ // si hash(psw) != hash_stocké
        return 0;
    }
    //std::cout << "Mot de passe valide" << std::endl;
    return 1;
}

/**
 * @brief Demande à l'utilisateur d'entrer deux fois son mdp sans espace !, une fois validé, le mdp est hashé et retourné
 * @return string du psw une fois hashé
 */
std::string DatabaseHandler::createPsw() {
    std::string psw;std::string pswv;
    do{
        std::cout<< "Entrez votre mot de passe: ";
        //std::cin >> psw;
        getline(std::cin,psw);
        std::cout<< "Confirmez votre mot de passe: ";
        //std::cin >> pswv;
        getline(std::cin,pswv);
    }while (psw != pswv);
    return psw;
}

/**
 * @brief vérifier si un ficher donné en entrée est valide (ne correspond pas à un dossier , fichier caché, etc)
 * @param filepath chemin d'accès à un fichier
 * @return (bool) int
 */
int DatabaseHandler::isStringValid(const std::string &filepath) {
    if (filepath =="") return 0;
    for (auto &c: filepath){
        if (c=='/' or c=='.' or c==' ') {
            //std::cout << "Le fichier entré comporte un caractère interdit..." << std::endl;
            return 0;
        }
    }
    return 1;
}

/**
 * @brief return vrai si le fichier donné en paramètre est existant
 * @param filename fichier dont l'existance doit être testée
 * @return (bool) int
 */
bool DatabaseHandler::does_file_exist(const std::string &filename) {
    std::ifstream ifile("../DataBase/Data/"+filename);
    if (ifile.is_open()){
        return 1;
    }else{
        return 0;
    }
}
/**
 * @brief créé un fichier avec des valeures initiale
 * @param filename nom du fichier à créé
 * @return le nom du fichier crée
 */
std::string DatabaseHandler::createFile(const std::string& filename,const std::string& inputpsw){
    std::hash<std::string> h;
    const std::string board="/////\n"; const std::string win="0\n"; const std::string loosed="0\n";
    const std::string none1="\n"; const std::string none2="";
    std::string psw =  std::to_string(h(inputpsw)) + '\n' ;
    FILE *o_file = fopen(("../DataBase/Data/"+filename).c_str(), "w");
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
void DatabaseHandler::writeFriends() {
    std::string friends_str=string_arr[5];
    for (auto &s: tempVect){
        friends_str += s + ' ';
    }
    const std::string board = string_arr[1] + "\n";
    const std::string win = string_arr[2] + "\n";
    const std::string loosed = string_arr[3] + "\n";
    const std::string none = "\n";
    std::string psw = string_arr[0] + "\n";
    FILE *o_file = fopen(("../DataBase/Data/" + username).c_str(), "w");
    if (o_file) {
        fwrite(psw.c_str(), 1, psw.size(), o_file);
        fwrite(board.c_str(), 1, board.size(), o_file);
        fwrite(win.c_str(), 1, win.size(), o_file);
        fwrite(loosed.c_str(), 1, loosed.size(), o_file);
        fwrite(none.c_str(), 1, none.size(), o_file);
        fwrite(friends_str.c_str(), 1, friends_str.size(), o_file);
    }
    fclose(o_file);
    tempVect.clear();
}
/**
 * @brief Transfer les amis de la liste toAdd à FriendList en demandant à l'utilsateur
 */
void DatabaseHandler::transferFriend() {
    for (std::string s : toAddList){
        std::string ans;
        if (s==""){
            std::cout << "Aucune demande en amis :weary:" << std::endl;
            return;
        }
        while (ans != "n" and ans != "N" and ans !="Y" and ans !="y"){
            std::cout << "Voulez vous ajoutez " << s << " en amis ? (Y/n) : ";
            getline(std::cin,ans);
            //std::cin >> ans;
        }
        if (ans == "Y" or ans == "y"){
            friendList.push_back(s);
        }
    }

    //réécriture dans le fichier
    std::string friends_str;
    for (std::string s:friendList){
        if (s!="") friends_str += (s + " ");
    }
    //writeFriends(friends_str);
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
    const std::string loosed=temp[3]+"\n";const std::string none="";
    std::string friends;
    temp[4]=="" ? friends = username + "\n" : friends = temp[4] + " " + username + "\n";
    std::string psw = temp[0]+"\n";
    FILE *o_file = fopen(("../DataBase/Data/"+friends_name).c_str(), "w");
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
        if (s!= "") std::cout << s << std::endl;
    }
}
// Méthodes "ask"
/**
 * @brief Demande à l'utilisateur d'entrer un fichier
 * @return nom du fichier
 */
std::string DatabaseHandler::askFile() {
    std::string input_file = "";
    // vérification de la syntaxe
    while(!isStringValid(input_file)){
        std::cout << "Entrez un nom de fichier : " << std::endl;
        std::getline(std::cin, input_file);
    }
    // si le fichier n'existe pas demande a l'utilisateur pour le crée
    if (!does_file_exist(input_file)) {
        std::cout << "Fichier non existant..." << std::endl;
        std::string ans = "";
        while (ans != "n" and ans != "N" and ans != "Y" and ans != "y") {
            std::cout << "Voulez vous créé une nouvelle entrée (Y/n)? ";
            getline(std::cin, ans);
            //std::cin >> ans;
        }
        if (ans == "n") {
            return "";
        }
        // crée le fichier
        std::string psw= createPsw();
        createFile(input_file, psw);
    }
    return input_file;
}

/**
 * @brief Demande un mot de passe à l'utilisateur
 * @return mot de passe
 */
std::string DatabaseHandler::askPswd() {
    std::string psw;
    std::cout << "Entrez votre mot de passe: ";
    std::getline(std::cin,psw);
    return psw;
}

/**
 * @brief Demande à l'utilisateur de rentrer en boucle des amis à ajouter
 */
void DatabaseHandler::askFriends() {
    std::string friends;
    while (friends != "N" and friends != "n"){
        std::cout << "Entrez un amis a ajouter (N/n pour annuler): ";
        getline(std::cin,friends);
        //std::cin >> friends;
        if (friends != "N" and friends != "n") {
            if (!does_file_exist(friends) or username == friends) {
                std::cout << "Amis innexistant / impossible à ajouter" << std::endl;
            } else {
                writeFriendstoAdd(friends);
            }
        }
    }
}
/**
 * @brief constructeur de l'objet databaseHandler
 * @param inputFile fichié donné en entrée, doit etre vérifié via DatabaseHandler::askFile()
 */
DatabaseHandler::DatabaseHandler(const std::string &inputFile) {
    // parse le fichier donné
    parse(inputFile, &string_arr);

    //met a jout le nom
    username=inputFile;
    /*
    //std::cout << "Fichier " << username << " trouvé." << std::endl;
    //std::cout << "______________________________" << std::endl;


    //demande + vérification du mdp
    std::cout << "Vérification du mdp:" << std::endl;

    if(!checkPswd(askPswd(), string_arr[0])){
        std::cerr << "Erreur, mauvais mot de passe." << std::endl;
        exit(1);
    }

    //mise à jours des amis
    std::cout << "______________________________" << std::endl;
    std::cout << "Mise à jours des amis:" << std::endl;
    transferFriend();

    std::cout << "______________________________" << std::endl;

    //liste d'amis
    std::cout << "Voici votre liste d'amis:"<<std::endl;
    listFriends();
    std::cout << "______________________________" << std::endl;

    //ajout d'amis
    std::cout << "Ajouts d'amis:" << std::endl;
    askFriends();
     */
}