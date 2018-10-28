/* File : Player.h */

#pragma once

#include "stdafx.h"
using namespace std;

class Player{
	public:
		Player();
		Player(char,int,int,int,int,int,int);
		Player(const Player&);
		Player& operator=(const Player&);
		int GetKey();
		int GetBombs();
		int GetMaxBag();
		int GetRadius();
		bool IsWeaker(const Player&);
		friend ostream& operator<<(ostream&, const Player&);
	private:
		char key;
		int point;
		int x;
		int y;
		int bombs;
		int max_bag;
		int blast_radius;
};
