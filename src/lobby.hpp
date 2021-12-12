#include <iostream>
#include <vector>
#include "player.hpp"


class Lobby {

	int _id;    //L'id sera genere dans le constructeur
	Player _host;   //host est le joueur ayant cree le Lobby.
	std::vector<Player*> _invited;

	public:
		Lobby(Player host) : _host{host} {}
		    //Genere un id et l'attribue au Lobby

		std::string displayLobby();     //Cette fonction a pour but d'afficher les informations relatives au lobby, elle fera appel à la classe Menu

		void userChoice();      //Effectue une action en fonction de l'input de l'utilisateur.
		void inviteFriend();    //Demande un pseudo au host et invite le joueur nommé si possible. Si possible, ajoute le joueur dans le vecteur invited
		void kickPlayer();      //Demande un pseudo au host et retire le joueur nommé de invited s'il s'y trouve.

		std::string chooseGamemode();
			//Cette fonction permet de changer le mode de jeu voulu.
			//Le return type est str, mais il peut devenir
			//ce que vous voulez en fonction de comment on
            //transmet le mode de jeu.

		void startGame();
			//Verifie si la taille de invited est 2 ou 4.
			//Cette fonction commence la partie avec 
			//les parametres(mode de jeu) voulus.
};