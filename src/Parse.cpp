/* File : Parse.cpp */

#include "Parse.h"

void Parse(Map &m, map<char,Player> &p, map<pair<int,int>, Bomb> &b, string filename){
	FILE *file;
	const char * fname = filename.c_str();
	int nb, nk, bounty;
	
	/* Open File */
	file = fopen(fname, "r");
	
	/* Read Header */
	fscanf(file, "Map Width: %d, ", &nb);
	fscanf(file, "Map Height: %d, ", &nk);
	fscanf(file, "Current Round: %*d, Seed: %*ld, PlayerBounty: %d\n", &bounty);
	
	/* Read Map */
	char c;
	Map new_m(nb, nk);
	for(int i=0; i<nb; i++){
		for(int j=0; j<nk; j++){
			fscanf(file, "%c", &c);
			if (c == '*')
				c = ' ';
			new_m[i][j] = c;
		}
		fscanf(file, "\n", &c);
	}
	m = new_m;
	
	/* Read Players and Bombs */
	while (fgetc(file) != EOF){
		char key;
		int points;
		int bombs = 0;
		int bag;
		int radius;
		int x, y;
		char status[256];
		
		Enter(file);
		Enter(file);
		fscanf(file, "Key: %c\n", &key); 
		fscanf(file, "Points: %d\n", &points);
		fscanf(file, "Status: %s\n", status);
		
		fscanf(file, "Bombs: ");
		c = fgetc(file);
		ungetc(c, file);
		if (c == '{'){
			do{
				++bombs;
				int bx, by, fuse, brad;
				fscanf(file, "{x:%d,", &by);
				fscanf(file, "y:%d,", &bx);
				fscanf(file, "fuse:%d,radius:%d}", &fuse, &brad);
				
				pair<int,int> ibomb(bx-1,by-1);
				Bomb bomb(key, brad, fuse);
				b[ibomb] = bomb;
				
				c = fgetc(file);
			}while ((c != '\n') && (c != EOF));
		}
		
		fscanf(file, "BombBag: %d\n", &bag);
		fscanf(file, "BlastRadius: %d\n", &radius);
		Enter(file);
		fgetc(file);
		
		if (strcmp(status, "Dead") != 0){
			m.search(key, x, y);
			Player player(key, points, x, y, bombs, bag+bombs, radius);
			p[key] = player;
		}
	}
	
	/* Close File */
	fclose(file);
}

void Enter(FILE *f){
	char c;
	
	do{
		c = fgetc(f);
	}while ((c != '\n') && (c != EOF));
}
