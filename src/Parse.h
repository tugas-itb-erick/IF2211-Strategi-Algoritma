/* File : Parse.h */

#pragma once

#include "Bomb.h"
#include "Map.h"
#include "Player.h"
#include "stdafx.h"
using namespace std;

void Parse(Map &m, map<char,Player> &p, map<pair<int,int>, Bomb> &b, string filename);
void Enter(FILE *f);
