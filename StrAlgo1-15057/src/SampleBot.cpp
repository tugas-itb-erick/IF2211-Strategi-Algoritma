// SampleBot.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parse.h"
#include "Bomb.h"
#include "Map.h"
#include "Player.h"
using namespace std;

/*  Value Representation:
	DoNothing = 0, 
	MoveUp = 1, 
	MoveLeft = 2, 
	MoveRight = 3, 
	MoveDown = 4, 
	PlaceBomb = 5, 
	TriggerBomb = 6
*/

/* I/O */
void readStateFile(string filePath);
void writeMoveFile(char playerKey, string filePath);
/* Global */
bool danger[MAX][MAX];
/* Boolean */
void initBool(bool x[MAX][MAX]);
void setDanger(bool danger[MAX][MAX], Map &m, int x, int y, int r);
void printBool(bool x[MAX][MAX], int nb, int nk);
/* BFS */
int FindWall(Map &m, pair<int,int> pos);
int MoveToWall(Map &m, pair<int,int> pos);
int FindEscape(Map &m, pair<int,int> pos);
int MoveToEscape(Map &m, pair<int,int> pos, int distance);
int FindAny(Map &m, pair<int,int> pos, char target);
int MoveToAny(Map &m, pair<int,int> pos, int distance, char target);
/* Player Hunting */
char IsPlayerNearby(Map &m, pair<int,int> pos, int sight = 3);
bool IsParallelPlayer(Map &m, pair<int,int> pos, int r);
bool IsParallelBomb(Map &m, map<pair<int,int>, Bomb> &b, char id);


/* Main start here */
int main(int argc, char** argv)
{
	char playerKey = argv[1][0];
	string filePath = argv[2];

	cout << "Args: " << argc << std::endl;
	cout << "Player Key: " << argv[1] << std::endl;
	cout << "File Path: " << argv[2] << std::endl;

	readStateFile(filePath);
	writeMoveFile(playerKey, filePath);
	return 0;
}

void readStateFile(string filePath)
{
	cout << "Reading state file " << filePath + "/" + "state.json" << std::endl;
	string fileContent;
	string line;
	ifstream myfile(filePath + "/" + "state.json");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			fileContent += line += "\n";
		}
		myfile.close();
	}
}

void writeMoveFile(char playerKey, string filePath)
{
	cout << "Writing move file " << filePath + "/" + "move.txt" << std::endl;
	ofstream outfile(filePath + "/" + "move.txt");
	
	if (outfile.is_open())
	{
		/* Object Instances */
		Map GameMap;
		map<char,Player> PlayerList;
		map<pair<int,int>, Bomb> BombList;
		
		/* Read Object from File */
		string FileName = filePath + "/" + "map.txt";
		Parse(GameMap, PlayerList, BombList, FileName);
		
		/* Initial Boolean */
		initBool(danger);
		
		/* Set Danger Area */
		for(map<pair<int,int>,Bomb>::iterator it = BombList.begin(); it != BombList.end(); it++){
			setDanger(danger, GameMap, it->first.first, it->first.second, it->second.GetRadius());
		}
		
		/* Get Player Position */
		int a, b;
		GameMap.search(playerKey, a, b);
		
		/* Greedy */
		int x, out;
		pair<int,int> CurrPos (a,b);
		if (danger[a][b]){
			x = FindEscape(GameMap, CurrPos); // Find Nearest Escape
			out = MoveToEscape(GameMap, CurrPos, x);
		}else{
			int p, q, r, s;
			char c;
			
			p = FindAny(GameMap, CurrPos, '$');
			q = FindAny(GameMap, CurrPos, '!');
			// r = FindAny(GameMap, CurrPos, '&');
			s = Min2(p,q);
			if ((s >= 0) && (s <= 6)){ // Found PowerUp(s) Nearby
				if (s == p)
					out = MoveToAny(GameMap, CurrPos, s, '$');
				else // if (s == q)
					out = MoveToAny(GameMap, CurrPos, s, '!');
				//else
					//out = MoveToAny(GameMap, CurrPos, s, '&');
			}
			
			else if (IsParallelBomb(GameMap, BombList, playerKey)){
				out = 6; // Trigger Player's Bomb if enemy enter bomb radius
			}
			
			else if (IsParallelPlayer(GameMap, CurrPos, PlayerList[playerKey].GetRadius())){
				out = 5; // Put Bomb Parallel to Enemy, for Self-Defence
			}
			
			else if (( (c = IsPlayerNearby(GameMap, CurrPos, 3)) != -1) && !PlayerList[playerKey].IsWeaker(PlayerList[c])){
				out = MoveToAny(GameMap, CurrPos, 3, c);  // Chase Weaker Enemy Nearby
			}
			
			else if ((x = FindWall(GameMap, CurrPos)) != -1){ // Find Nearest Wall, If Exist
				if (x == 0){
					if (PlayerList[playerKey].GetBombs() > 0)
						out = 6; // Detonate Existing Bombs, Save Guaranteed
					else
						out = 5; // Place Bomb
				}else{
					out = MoveToWall(GameMap, CurrPos); // Go To Nearest Wall
				}
				
			}
			
			else { // Find Weakest Enemy
				map<char,Player>::iterator it = PlayerList.begin();
				if (it->first == playerKey){
					it++;
				}
				char weakest = it->first;
				
				for( ; it != PlayerList.end(); it++){
					if (it->second.IsWeaker(PlayerList[weakest]) && (it->first != playerKey))
						weakest = it->first;
				}
				
				out = MoveToAny(GameMap, CurrPos, 10, weakest); // Chase Weakest Enemy
				if (out == -1) // Unable to Chase because of Bombs
					out = 6;
			}
			
		}
		
		/* Clean Up */
		initBool(danger);
		
		/* Output To File */
		outfile << out << std::endl;
		outfile.close();
	}
}

void initBool(bool x[MAX][MAX]){
	for(int i=0; i<MAX; i++)
		for(int j=0; j<MAX; j++)
			x[i][j] = false;
}

void setDanger(bool danger[MAX][MAX], Map &m, int x, int y, int r){
	danger[x][y] = true;
	
	int i = x-1;
	bool stop = false;
	while ((i >= 0) && (i >= x-r) && !stop){
		if ((m[i][y] == '#') || (m[i][y] == '+'))
			stop = true;
		else{
			danger[i][y] = true;
			i--;
		}
	}
	
	i = x+1;
	stop = false;
	while ((i < MAX) && (i <= x+r) && !stop){
		if ((m[i][y] == '#') || (m[i][y] == '+'))
			stop = true;
		else{
			danger[i][y] = true;
			i++;
		}
	}

	int j = y-1;
	stop = false;
	while ((j >= 0) && (j >= y-r) && !stop){
		if ((m[x][j] == '#') || (m[x][j] == '+'))
			stop = true;
		else{
			danger[x][j] = true;
			j--;
		}
	}
	
	j = y+1;
	stop = false;
	while ((j < MAX) && (j <= y+r) && !stop){
		if ((m[x][j] == '#') || (m[x][j] == '+'))
			stop = true;
		else{
			danger[x][j] = true;
			j++;
		}
	}
}

void printBool(bool x[MAX][MAX], int nb, int nk){
	for(int i=0; i<nb; i++){
		for(int j=0; j<nk; j++){
			if (x[i][j])
				cout << "X";
			else
				cout << "-";
			cout << " ";
		}
		cout << endl;
	}
}

int FindWall(Map &m, pair<int,int> pos){
	bool visited[MAX][MAX];
	initBool(visited);
	
	int i = pos.first;
	int j = pos.second;
	queue<pair<int,int>> q;
	queue<int> qn;
	int n = 0;
	bool found = false;
	
	q.push(pos);
	qn.push(n);
	visited[i][j] = true;
	
	while(!q.empty() && !found){
		pair<int,int> currentIdx = q.front();
		n = qn.front();
		
		i = currentIdx.first;
		j = currentIdx.second;
		q.pop();
		qn.pop();
		
		if ((i+1 < m.GetRow()) && !visited[i+1][j] && !danger[i+1][j] 
		&& (m[i+1][j] != '#') && !isalpha(m[i+1][j]))
		{
			if (m[i+1][j] == '+')
				found = true;
			else{
				q.push(pair<int,int>(i+1, j));
				qn.push(n+1);
				visited[i+1][j] = true;
			}
		}
		
		if ((i-1 >= 0) && !visited[i-1][j] && !danger[i-1][j] 
		&& (m[i-1][j] != '#') && !isalpha(m[i-1][j]))
		{
			if (m[i-1][j] == '+')
				found = true;
			else{
				q.push(pair<int,int>(i-1, j));
				qn.push(n+1);
				visited[i+1][j] = true;
			}
		}
		
		if ((j+1 < m.GetCol()) && !visited[i][j+1] && !danger[i][j+1] 
		&& (m[i][j+1] != '#') && !isalpha(m[i][j+1]))
		{
			if (m[i][j+1] == '+')
				found = true;
			else{
				q.push(pair<int,int>(i, j+1));
				qn.push(n+1);
				visited[i][j+1] = true;
			}
		}
		
		if ((j-1 >= 0) && !visited[i][j-1] && !danger[i][j-1] 
		&& (m[i][j-1] != '#') && !isalpha(m[i][j-1]))
		{
			if (m[i][j-1] == '+')
				found = true;
			else{
				q.push(pair<int,int>(i, j-1));
				qn.push(n+1);
				visited[i][j-1] = true;
			}
		}
		
	}	
	
	if (found)
		return n;
	else
		return -1;
}

int MoveToWall(Map &m, pair<int,int> pos){
	vector<int> dir;
	vector<int> val;
	int i = pos.first;
	int j = pos.second;
	int x;
	
	/* Up */
	x = FindWall(m, pair<int,int>(i-1,j));
	if ((i-1 >= 0) && (x != -1) && !danger[i-1][j] && !isdigit(m[i-1][j]) &&
	((m[i-1][j] == ' ') || (m[i-1][j] == '$') || (m[i-1][j] == '&') || (m[i-1][j] == '!'))){
		val.push_back(x);
		dir.push_back(1);
	}
	
	/* Left */
	x = FindWall(m, pair<int,int>(i,j-1));
	if ((j-1 >= 0) && (x != -1) && !danger[i][j-1] && !isdigit(m[i][j-1]) &&
	((m[i][j-1] == ' ') || (m[i][j-1] == '$') || (m[i][j-1] == '&') || (m[i][j-1] == '!'))){
		val.push_back(x);
		dir.push_back(2);
	}
	
	/* Down */
	x = FindWall(m, pair<int,int>(i+1,j));
	if ((i+1 < m.GetRow()) && (x != -1) && !danger[i+1][j] && !isdigit(m[i+1][j]) &&
	((m[i+1][j] == ' ') || (m[i+1][j] == '$') || (m[i+1][j] == '&') || (m[i+1][j] == '!'))){
		val.push_back(x);
		dir.push_back(4);
	}
	
	/* Right */
	x = FindWall(m, pair<int,int>(i,j+1));
	if ((j+1 < m.GetCol()) && (x != -1) && !danger[i][j+1] && !isdigit(m[i][j+1]) &&
	((m[i][j+1] == ' ') || (m[i][j+1] == '$') || (m[i][j+1] == '&') || (m[i][j+1] == '!'))){
		val.push_back(x);
		dir.push_back(3);
	}
	
	if (val.empty()){
		return 0;
	}
	
	else{
		int imin = 0;
		for(int idx = 1; idx < (int)val.size(); idx++){
			if (val[idx] < val[imin])
				imin = idx;
		}
		return dir[imin];
	}
	
}

int FindEscape(Map &m, pair<int,int> pos){
	bool visited[MAX][MAX];
	initBool(visited);
	
	int i = pos.first;
	int j = pos.second;
	queue<pair<int,int>> q;
	queue<int> qn;
	int n = 0;
	bool found = false;
	
	q.push(pos);
	qn.push(n);
	visited[i][j] = true;
	
	while(!q.empty() && !found){
		pair<int,int> currentIdx = q.front();
		n = qn.front();
		
		i = currentIdx.first;
		j = currentIdx.second;
		q.pop();
		qn.pop();
		
		if ((i+1 < m.GetRow()) && !visited[i+1][j] && (m[i+1][j] != '#') && 
		(m[i+1][j] != '+') && !isalpha(m[i+1][j]) && !isdigit(m[i+1][j]))
		{
			if ((m[i+1][j] == ' ') && !danger[i+1][j])
				found = true;
			else{
				q.push(pair<int,int>(i+1, j));
				qn.push(n+1);
				visited[i+1][j] = true;
			}
		}
		
		if ((i-1 >= 0) && !visited[i-1][j] && (m[i-1][j] != '#') && 
		(m[i-1][j] != '+') && !isalpha(m[i-1][j]) && !isdigit(m[i-1][j]))
		{
			if ((m[i-1][j] == ' ') && !danger[i-1][j])
				found = true;
			else{
				q.push(pair<int,int>(i-1, j));
				qn.push(n+1);
				visited[i+1][j] = true;
			}
		}
		
		if ((j+1 < m.GetCol()) && !visited[i][j+1] && (m[i][j+1] != '#') && 
		(m[i][j+1] != '+') && !isalpha(m[i][j+1]) && !isdigit(m[i][j+1]))
		{
			if ((m[i][j+1] == ' ') && !danger[i][j+1])
				found = true;
			else{
				q.push(pair<int,int>(i, j+1));
				qn.push(n+1);
				visited[i][j+1] = true;
			}
		}
		
		if ((j-1 >= 0) && !visited[i][j-1] && (m[i][j-1] != '#') && 
		(m[i][j-1] != '+') && !isalpha(m[i][j-1]) && !isdigit(m[i][j-1]))
		{
			if ((m[i][j-1] == ' ') && !danger[i][j-1])
				found = true;
			else{
				q.push(pair<int,int>(i, j-1));
				qn.push(n+1);
				visited[i][j-1] = true;
			}
		}
		
	}	
	
	if (found)
		return n;
	else
		return -1;
}

int MoveToEscape(Map &m, pair<int,int> pos, int distance){
	vector<int> dir;
	vector<int> val;
	int i = pos.first;
	int j = pos.second;
	int x;
	
	if (distance == 0){
		/* Up */
		if ((i-1 >= 0) && (x != -1) && !danger[i-1][j] && !isdigit(m[i-1][j]) &&
		((m[i-1][j] == ' ') || (m[i-1][j] == '$') || (m[i-1][j] == '&') || (m[i-1][j] == '!')))
			return 1;
		/* Left */
		else if ((j-1 >= 0) && (x != -1) && !danger[i][j-1] && !isdigit(m[i][j-1]) &&
		((m[i][j-1] == ' ') || (m[i][j-1] == '$') || (m[i][j-1] == '&') || (m[i][j-1] == '!')))
			return 2;
		/* Down */
		else if ((i+1 < m.GetRow()) && (x != -1) && !danger[i+1][j] && !isdigit(m[i+1][j]) &&
		((m[i+1][j] == ' ') || (m[i+1][j] == '$') || (m[i+1][j] == '&') || (m[i+1][j] == '!')))
			return 4;
		/* Right */
		else if ((j+1 < m.GetCol()) && (x != -1) && !danger[i][j+1] && !isdigit(m[i][j+1]) &&
		((m[i][j+1] == ' ') || (m[i][j+1] == '$') || (m[i][j+1] == '&') || (m[i][j+1] == '!')))
			return 3;
		else
			return 6;
		
	}
	
	else{
	
		/* Up */
		x = FindEscape(m, pair<int,int>(i-1,j));
		if ((i-1 >= 0) && (x != -1) && !isdigit(m[i-1][j]) &&
		((m[i-1][j] == ' ') || (m[i-1][j] == '$') || (m[i-1][j] == '&') || (m[i-1][j] == '!'))){
			val.push_back(x);
			dir.push_back(1);
		}
		
		/* Left */
		x = FindEscape(m, pair<int,int>(i,j-1));
		if ((j-1 >= 0) && (x != -1) && !isdigit(m[i][j-1]) &&
		((m[i][j-1] == ' ') || (m[i][j-1] == '$') || (m[i][j-1] == '&') || (m[i][j-1] == '!'))){
			val.push_back(x);
			dir.push_back(2);
		}
		
		/* Down */
		x = FindEscape(m, pair<int,int>(i+1,j));
		if ((i+1 < m.GetRow()) && (x != -1) && !isdigit(m[i+1][j]) &&
		((m[i+1][j] == ' ') || (m[i+1][j] == '$') || (m[i+1][j] == '&') || (m[i+1][j] == '!'))){
			val.push_back(x);
			dir.push_back(4);
		}
		
		/* Right */
		x = FindEscape(m, pair<int,int>(i,j+1));
		if ((j+1 < m.GetCol()) && (x != -1) && !isdigit(m[i][j+1]) &&
		((m[i][j+1] == ' ') || (m[i][j+1] == '$') || (m[i][j+1] == '&') || (m[i][j+1] == '!'))){
			val.push_back(x);
			dir.push_back(3);
		}
		
		if (val.empty()){
			return 0;
		}
		
		else{
			int imin = 0;
			for(int idx = 1; idx < (int)val.size(); idx++){
				if (val[idx] < val[imin])
					imin = idx;
			}
			return dir[imin];
		}
		
	}
}

int FindAny(Map &m, pair<int,int> pos, char target){
	bool visited[MAX][MAX];
	initBool(visited);
	
	int i = pos.first;
	int j = pos.second;
	queue<pair<int,int>> q;
	queue<int> qn;
	int n = 0;
	bool found = false;
	
	q.push(pos);
	qn.push(n);
	visited[i][j] = true;
	
	while(!q.empty() && !found){
		pair<int,int> currentIdx = q.front();
		n = qn.front();
		
		i = currentIdx.first;
		j = currentIdx.second;
		q.pop();
		qn.pop();
		
		if ((i+1 < m.GetRow()) && !visited[i+1][j] && (m[i+1][j] != '#') && 
		(m[i+1][j] != '+') && !danger[i+1][j] && !isdigit(m[i+1][j]))
		{
			if (m[i+1][j] == target){
				found = true;
			}
			
			else{
				q.push(pair<int,int>(i+1, j));
				qn.push(n+1);
				visited[i+1][j] = true;
			}
		}
		
		if ((i-1 >= 0) && !visited[i-1][j] && (m[i-1][j] != '#') && 
		(m[i-1][j] != '+') && !danger[i-1][j] && !isdigit(m[i-1][j]))
		{
			if (m[i-1][j] == target){
				found = true;
			}
			
			else{
				q.push(pair<int,int>(i-1, j));
				qn.push(n+1);
				visited[i+1][j] = true;
			}
		}
		
		if ((j+1 < m.GetCol()) && !visited[i][j+1] && (m[i][j+1] != '#') && 
		(m[i][j+1] != '+') && !danger[i][j+1] && !isdigit(m[i][j+1]))
		{
			if (m[i][j+1] == target){
				found = true;
			}
			
			else{
				q.push(pair<int,int>(i, j+1));
				qn.push(n+1);
				visited[i][j+1] = true;
			}
		}
		
		if ((j-1 >= 0) && !visited[i][j-1] && (m[i][j-1] != '#') && 
		(m[i][j-1] != '+') && !danger[i][j-1] && !isdigit(m[i][j-1]))
		{
			if (m[i][j-1] == target){
				found = true;
			}
			
			else{
				q.push(pair<int,int>(i, j-1));
				qn.push(n+1);
				visited[i][j-1] = true;
			}
		}
		
	}	
	
	if (found)
		return n;
	else
		return -1;
}

int MoveToAny(Map &m, pair<int,int> pos, int distance, char target){
	vector<int> dir;
	vector<int> val;
	int i = pos.first;
	int j = pos.second;
	int x;
	
	if (distance == 0){
		/* Up */
		if ((i-1 >= 0) && !danger[i-1][j] && !isdigit(m[i-1][j]) && (m[i-1][j] == target))
			return 1;
		/* Left */
		else if ((j-1 >= 0) && !danger[i][j-1] && !isdigit(m[i][j-1]) && (m[i][j-1] == target))
			return 2;
		/* Down */
		else if ((i+1 < m.GetRow()) && !danger[i+1][j] && !isdigit(m[i+1][j]) && (m[i+1][j] == target))
			return 4;
		/* Right */
		else if ((j+1 < m.GetCol()) && !danger[i][j+1] && !isdigit(m[i][j+1]) && (m[i][j+1] == target))
			return 3;
		else
			return 6;
		
	}
	
	else{
	
		/* Up */
		x = FindAny(m, pair<int,int>(i-1,j), target);
		if ((i-1 >= 0) && (x != -1) && !isdigit(m[i-1][j]) && !danger[i-1][j] &&
		((m[i-1][j] == ' ') || (m[i-1][j] == '$') || (m[i-1][j] == '&') || (m[i-1][j] == '!'))){
			val.push_back(x);
			dir.push_back(1);
		}
		
		/* Left */
		x = FindAny(m, pair<int,int>(i,j-1), target);
		if ((j-1 >= 0) && (x != -1) && !isdigit(m[i][j-1]) && !danger[i][j-1] &&
		((m[i][j-1] == ' ') || (m[i][j-1] == '$') || (m[i][j-1] == '&') || (m[i][j-1] == '!'))){
			val.push_back(x);
			dir.push_back(2);
		}
		
		/* Down */
		x = FindAny(m, pair<int,int>(i+1,j), target);
		if ((i+1 < m.GetRow()) && (x != -1) && !isdigit(m[i+1][j]) && !danger[i+1][j] &&
		((m[i+1][j] == ' ') || (m[i+1][j] == '$') || (m[i+1][j] == '&') || (m[i+1][j] == '!'))){
			val.push_back(x);
			dir.push_back(4);
		}
		
		/* Right */
		x = FindAny(m, pair<int,int>(i,j+1), target);
		if ((j+1 < m.GetCol()) && (x != -1) && !isdigit(m[i][j+1]) && !danger[i][j+1] &&
		((m[i][j+1] == ' ') || (m[i][j+1] == '$') || (m[i][j+1] == '&') || (m[i][j+1] == '!'))){
			val.push_back(x);
			dir.push_back(3);
		}
		
		if (val.empty()){
			return 0;
		}
		
		else{
			int imin = 0;
			for(int idx = 1; idx < (int)val.size(); idx++){
				if (val[idx] < val[imin])
					imin = idx;
			}
			return dir[imin];
		}
		
	}
}

char IsPlayerNearby(Map &m, pair<int,int> pos, int sight){
	bool visited[MAX][MAX];
	initBool(visited);
	
	int i = pos.first;
	int j = pos.second;
	queue<pair<int,int>> q;
	queue<int> qn;
	int n = 0;
	
	q.push(pos);
	qn.push(n);
	visited[i][j] = true;
	
	while(!q.empty() && (n <= sight)){
		pair<int,int> currentIdx = q.front();
		n = qn.front();
		
		i = currentIdx.first;
		j = currentIdx.second;
		q.pop();
		qn.pop();
		
		if ((i+1 < m.GetRow()) && !visited[i+1][j] && (m[i+1][j] != '#') && 
		(m[i+1][j] != '+') && !danger[i+1][j] && !isdigit(m[i+1][j]))
		{
			if (isalpha(m[i+1][j])){
				return m[i+1][j];
			}
			
			else{
				q.push(pair<int,int>(i+1, j));
				qn.push(n+1);
				visited[i+1][j] = true;
			}
		}
		
		if ((i-1 >= 0) && !visited[i-1][j] && (m[i-1][j] != '#') && 
		(m[i-1][j] != '+') && !danger[i-1][j] && !isdigit(m[i-1][j]))
		{
			if (isalpha(m[i-1][j])){
				return m[i-1][j];
			}
			
			else{
				q.push(pair<int,int>(i-1, j));
				qn.push(n+1);
				visited[i+1][j] = true;
			}
		}
		
		if ((j+1 < m.GetCol()) && !visited[i][j+1] && (m[i][j+1] != '#') && 
		(m[i][j+1] != '+') && !danger[i][j+1] && !isdigit(m[i][j+1]))
		{
			if (isalpha(m[i][j+1])){
				return m[i][j+1];
			}
			
			else{
				q.push(pair<int,int>(i, j+1));
				qn.push(n+1);
				visited[i][j+1] = true;
			}
		}
		
		if ((j-1 >= 0) && !visited[i][j-1] && (m[i][j-1] != '#') && 
		(m[i][j-1] != '+') && !danger[i][j-1] && !isdigit(m[i][j-1]))
		{
			if (isalpha(m[i][j-1])){
				return m[i][j-1];
			}
			
			else{
				q.push(pair<int,int>(i, j-1));
				qn.push(n+1);
				visited[i][j-1] = true;
			}
		}
		
	}	
	
	/* Not Found */
	return -1;
}

bool IsParallelPlayer(Map &m, pair<int,int> pos, int r){
	bool found = false;
	int x = pos.first;
	int y = pos.second;
	
	int i = x-1;
	bool stop = false;
	while ((i >= 0) && (i >= x-r) && !stop && !found){
		if ((m[i][y] == '#') || (m[i][y] == '+') || isdigit(m[i][y]))
			stop = true;
		else if (isalpha(m[i][y]))
			found = true;
		else
			i--;
	}
	
	i = x+1;
	stop = false;
	while ((i < m.GetRow()) && (i <= x+r) && !stop && !found){
		if ((m[i][y] == '#') || (m[i][y] == '+') || isdigit(m[i][y]))
			stop = true;
		else if (isalpha(m[i][y]))
			found = true;
		else
			i++;
	}

	int j = y-1;
	stop = false;
	while ((j >= 0) && (j >= y-r) && !stop && !found){
		if ((m[x][j] == '#') || (m[x][j] == '+') || isdigit(m[x][j]))
			stop = true;
		else if (isalpha(m[x][j]))
			found = true;
		else
			j--;
	}
	
	j = y+1;
	stop = false;
	while ((j < m.GetCol()) && (j <= y+r) && !stop && !found){
		if ((m[x][j] == '#') || (m[x][j] == '+') || isdigit(m[x][j]))
			stop = true;
		else if (isalpha(m[x][j]))
			found = true;
		else
			j++;
	}
	
	return found;
}

bool IsParallelBomb(Map &m, map<pair<int,int>, Bomb> &b, char id){
	bool found = false;
	
	for(map<pair<int,int>, Bomb> ::iterator it = b.begin(); it != b.end(); it++){
		if (it->second.GetID() == id){
			int x = it->first.first;
			int y = it->first.second;
			int r = it->second.GetRadius();
			
			int i = x-1;
			bool stop = false;
			while ((i >= 0) && (i >= x-r) && !stop && !found){
				if ((m[i][y] == '#') || (m[i][y] == '+') || isdigit(m[i][y]))
					stop = true;
				else if (isalpha(m[i][y]))
					found = true;
				else
					i--;
			}
			
			i = x+1;
			stop = false;
			while ((i < m.GetRow()) && (i <= x+r) && !stop && !found){
				if ((m[i][y] == '#') || (m[i][y] == '+') || isdigit(m[i][y]))
					stop = true;
				else if (isalpha(m[i][y]))
					found = true;
				else
					i++;
			}
		
			int j = y-1;
			stop = false;
			while ((j >= 0) && (j >= y-r) && !stop && !found){
				if ((m[x][j] == '#') || (m[x][j] == '+') || isdigit(m[x][j]))
					stop = true;
				else if (isalpha(m[x][j]))
					found = true;
				else
					j--;
			}
			
			j = y+1;
			stop = false;
			while ((j < m.GetCol()) && (j <= y+r) && !stop && !found){
				if ((m[x][j] == '#') || (m[x][j] == '+') || isdigit(m[x][j]))
					stop = true;
				else if (isalpha(m[x][j]))
					found = true;
				else
					j++;
			}
			
			
		}
	}
	
	return found;
}




