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