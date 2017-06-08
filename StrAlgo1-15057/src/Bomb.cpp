#include "Bomb.h"

Bomb::Bomb(){
	id = '0';
	radius = 0;
	fuse = 0;
}

Bomb::Bomb(char d, int r, int f){
	id = d;
	radius = r;
	fuse = f;
}

Bomb::Bomb(const Bomb& b){
	id = b.id;
	radius = b.radius;
	fuse = b.fuse;
}

Bomb::~Bomb(){}

Bomb& Bomb::operator=(const Bomb& b){
	id = b.id;
	radius = b.radius;
	fuse = b.fuse;
	return *this;
}

char Bomb::GetID(){
	return id;
}

int Bomb::GetRadius(){
	return radius;
}

int Bomb::GetFuse(){
	return fuse;
}
		
ostream& operator<<(ostream& os, const Bomb& b){
	os << "ID     : " << b.id << endl;
	os << "Radius : " << b.radius << endl;
	os << "Fuse   : " << b.fuse << endl;
}


