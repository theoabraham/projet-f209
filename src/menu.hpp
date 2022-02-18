#include <iostream>
#include <vector>
#include "player.hpp"

class Menu {
	Player _connectedPlayer;

	public:
		Menu(Player player) : _connectedPlayer{ player } {}  //constructeur
		
		std::string printMenu(std::vector<std::string> options);
			//Cette fonction a pour but d'afficher un menu a l'écran, quels que soit les éléments du menu.
			/*
			Exemple:
			"Choisissez une action:
			 *Créer une partie (p)
			 *(Se connecter a/Gérer) un compte (a)"
			*/

        void userChoice();
            //cin>>printMenu(options)>>endl;
            //Effectue une action en fonction de l'input de l'utilisateur.

        void logOut();
            //Déconnecte le joueur actuel
            //Renvoi sur l'écran de connexion

        void destroyAccount();
            //Appel à logOut()
            //Database::DeleteAccount()

        void createRoom();
            //Cette fonction crée une instance de la classe Lobby(Player host).

        void joinRoom();
            //Cette fonction ne prend pas de paramètre, mais demande à l'utilisateur une ID de Lobby, puis vérifie si le Lobby existe.
            //Si le Lobby existe, le rejoint. Autrement, redemande un ID.
};