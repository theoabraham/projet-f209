#include "database.hpp"
#include <vector>

class FriendList {
    Database* _database;
	Account _userAccount;
    std::vector<std::string> _friends;
    
public:
    FriendList(Database* db, Account userAccount): _database{db}, _userAccount{userAccount} {}
	void addFriend(Account userAccount, Account friendAccount);     //Demande la liste d'amis de userAccount à database afin d'y ajouter friendAccount
    void deleteFriend(Account userAccount,Account friendAccount);    //Demande la liste d'amis de userAcount à database pour y supprimer un friendAccount
	bool isFriend(std::string friendName);      //Verifie si FriendName se trouve dans la liste _friends
    
    std::vector<std::string> getFriends();      //Retourne l'entierete de la liste d'amis 
};