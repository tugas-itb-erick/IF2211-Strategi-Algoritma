/* File : Bomb.h */

#pragma once

#include "stdafx.h"
using namespace std;

class Bomb{
	public:
		/* Konstruktor */
		Bomb();
		Bomb(char,int,int);
		Bomb(const Bomb&);
		~Bomb();
		/* Operator */
		Bomb& operator=(const Bomb&);
		/* Getter */
		char GetID();
		int GetRadius();
		int GetFuse();
		/* Output */
		friend ostream& operator<<(ostream&, const Bomb&);
	private:
		char id;
		int radius;
		int fuse;
};
