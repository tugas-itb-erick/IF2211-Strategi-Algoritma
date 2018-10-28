#include "Player.h"

Player::Player(){
	key='0';
	point=0;
	x=0;
	y=0;
	bombs=0;
	max_bag=0;
	blast_radius=0;
}

Player::Player(char _key,int _point,int _x ,int _y,int _bombs,int _max_bag,int _blast_radius)
{
	key=_key;
	point=_point;
	x=_x;
	y=_y;
	bombs=_bombs;
	max_bag=_max_bag;
	blast_radius=_blast_radius;
}

Player::Player(const Player& p)
{
	key=p.key;
	point=p.point;
	x=p.x;
	y=p.y;
	bombs=p.bombs;
	max_bag=p.max_bag;
	blast_radius=p.blast_radius;
}

Player& Player::operator=(const Player& p){
	key=p.key;
	point=p.point;
	x=p.x;
	y=p.y;
	bombs=p.bombs;
	max_bag=p.max_bag;
	blast_radius=p.blast_radius;
	return *this;
}

int Player::GetKey(){
	return key;
}

int Player::GetBombs(){
	return bombs;
}

int Player::GetMaxBag(){
	return max_bag;
}

int Player::GetRadius(){
	return blast_radius;
}

bool Player::IsWeaker(const Player& p){
	return (blast_radius <= p.blast_radius);
}

ostream& operator<<(ostream& os, const Player& p)
{
	os << "---------------------------" << endl;
	os << "Key: " << p.key << endl;
	os << "Points: " << p.point << endl;
	os << "x = " << p.x << " ; y = " << p.y << endl; 
	os << "Bombs: " << p.bombs << endl;
	os << "BombBag: " << p.max_bag << endl;
	os << "BlastRadius: " << p.blast_radius << endl;
	os << "---------------------------"	<< endl;
	return os;
}


