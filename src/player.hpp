#include <iostream>
#include "Pawn.hpp"

class Player {
	int _id;
	Pawn _pawn;
	int _wallsLeft;
	std::string _name;
	bool _IA;
	public:
		Player(int id, Pawn pawn, int walls, std::string name, bool IA = false);
		
        //Getters
        Position pawnLocation(); 
		int getId();
		std::string getName();

        //Setters
		void setName(std::string newName);

        void playerMove();
};