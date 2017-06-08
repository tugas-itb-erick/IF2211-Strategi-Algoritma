/* File : Map.cpp */

#include "Map.h"

Map::Map() : row(MAX), col(MAX){
	data = new char*[row];
	for(int i=0; i<row; i++){
		data[i] = new char[col];
		for(int j=0; j<col; j++)
			data[i][j] = '#';
	}
}

Map::Map(int r, int c) : row(r), col(c){
	data = new char*[row];
	for(int i=0; i<row; i++){
		data[i] = new char[col];
		for(int j=0; j<col; j++)
			data[i][j] = '#';
	}
}

Map::Map(const Map& m) : row(m.row), col(m.col){
	data = new char*[row];
	for(int i=0; i<row; i++){
		data[i] = new char[col];
		for(int j=0; j<col; j++)
			data[i][j] = m.data[i][j];
	}
}

Map::~Map(){
	for(int i=0; i<row; i++)
		delete [] data[i];
	delete [] data;
}

int Map::GetRow(){
	return row;
}

int Map::GetCol(){
	return col;
}

Map& Map::operator=(const Map& m){
	row = m.row;
	col = m.col;
	
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++)
			data[i][j] = m.data[i][j];
	}
	
	return *this;
}

void Map::search(char c, int& x, int& y){
	bool found = false;
	int i = 0;
	int j;
	
	while ((i<row) && !found){
		j = 0;
		while ((j<col) && !found){
			if (isalpha(c)){
				if ((data[i][j] == toupper(c)) || (data[i][j] == tolower(c))){
					found = true;
					x = i;
					y = j;
				}else
					j++;
			}else{
				if (data[i][j] == c){
					found = true;
					x = i;
					y = j;
				}else
					j++;
			}
		}
		if (!found)
			i++;
	}
	
}

ostream& operator<<(ostream& out, const Map& m){
	out << "Row = " << m.row << endl;
	out << "Col = " << m.col << endl;
	for(int i=0; i<m.row; i++){
		for(int j=0; j<m.col; j++){
			out << m.data[i][j];
			if (j < m.col-1)
				out << " ";
		}
		out << endl;
	}
	return out;
}





