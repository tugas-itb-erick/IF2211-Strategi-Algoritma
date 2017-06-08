/* File : driver.h */

#include "Parse.h"
#include "Bomb.h"
#include "Map.h"
#include "Player.h"

bool danger[MAX][MAX];
void initBool(bool x[MAX][MAX]);
void setDanger(bool danger[MAX][MAX], Map &m, int x, int y, int r);
void printBool(bool x[MAX][MAX], int nb, int nk);
int FindWall(Map &m, pair<int,int> pos);
int MoveToWall(Map &m, pair<int,int> pos);
int FindEscape(Map &m, pair<int,int> pos);
int MoveToEscape(Map &m, pair<int,int> pos, int distance);
int FindAny(Map &m, pair<int,int> pos, char target);
int MoveToAny(Map &m, pair<int,int> pos, int distance, char target);

int main(){
	Map m;
	map<char,Player> p;
	map<pair<int,int>, Bomb> b;
	
	Parse(m, p, b, "map.txt");
	
	// Test Map
	cout << m << endl;
	
	// Test Players
	for(map<char,Player>::iterator it = p.begin(); it != p.end(); it++){
		cout << it->second << endl;
	}
	
	// Test Bombs
	for(map<pair<int,int>,Bomb>::iterator it = b.begin(); it != b.end(); it++){
		cout << it->first.first << " " << it->first.second << " : " << it->second << endl;
	}
	
	
	// Test Danger
	initBool(danger);
	for(map<pair<int,int>,Bomb>::iterator it = b.begin(); it != b.end(); it++){
		setDanger(danger, m, it->first.first, it->first.second, it->second.GetRadius());
	}
	printBool(danger, m.GetRow(), m.GetCol());
	
	
	// Test BFS
	/* 1,1 ; 3,1 ; 11,5 ;  */
	cout << "Test Wall: " << endl;
	cout << "1,1 " << FindWall(m, pair<int,int>(1,1)) << endl;
	cout << "3,1 " << FindWall(m, pair<int,int>(3,1)) << endl;
	cout << "6,11 " << FindWall(m, pair<int,int>(6,11)) << endl;
	cout << "19,19 " << FindWall(m, pair<int,int>(19,19)) << endl;
	cout << "3,12 " << FindWall(m, pair<int,int>(3,12)) << endl;
	cout << "14,13 " << FindWall(m, pair<int,int>(14,13)) << endl;
	cout << "Test Move To Wall: " << endl;
	cout << "1,1 "   << MoveToWall(m, pair<int,int>(1,1)) << endl;
	cout << "3,1 "   << MoveToWall(m, pair<int,int>(3,1)) << endl;
	cout << "6,11 "  << MoveToWall(m, pair<int,int>(6,11)) << endl;
	cout << "19,19 " << MoveToWall(m, pair<int,int>(19,19)) << endl;
	cout << "3,12 "  << MoveToWall(m, pair<int,int>(3,12)) << endl;
	cout << "14,13 " << MoveToWall(m, pair<int,int>(14,13)) << endl;
	
	cout << "Test Escape: " << endl;
	cout << "1,1 " << FindEscape(m, pair<int,int>(1,1)) << endl;
	cout << "13,6 " << FindEscape(m, pair<int,int>(13,6)) << endl;
	cout << "5,11 " << FindEscape(m, pair<int,int>(5,11)) << endl;
	cout << "Test Move To Escape: " << endl;
	cout << "1,1 " << MoveToEscape(m, pair<int,int>(1,1), 0) << endl;
	cout << "13,6 " << MoveToEscape(m, pair<int,int>(13,6), 3) << endl;
	cout << "5,11 " << MoveToEscape(m, pair<int,int>(5,11), 4) << endl;
	
	cout << "Test PowerUP: " << endl;
	cout << "1,1 " << FindAny(m, pair<int,int>(1,1), '!') << endl;
	cout << "19,19 " << FindAny(m, pair<int,int>(19,19), '&') << endl;
	cout << "11,10 " << FindAny(m, pair<int,int>(11,10), '$') << endl;
	cout << "7,19 " << FindAny(m, pair<int,int>(7,19), '&') << endl;
	cout << "Test Move To PowerUP: " << endl;
	cout << "1,1 " << MoveToAny(m, pair<int,int>(1,1), 12, '!') << endl;
	cout << "19,19 " << MoveToAny(m, pair<int,int>(19,19), 12, '&') << endl;
	cout << "11,10 " << MoveToAny(m, pair<int,int>(11,10), 0, '$') << endl;
	cout << "7,19 " << MoveToAny(m, pair<int,int>(7,19), 0, '&') << endl;
	
			int cp, cq, cr, cs;
			cp = FindAny(m, pair<int,int>(9,19), '&');
			cq = FindAny(m, pair<int,int>(9,19), '$');
			cr = FindAny(m, pair<int,int>(9,19), '!');
			cs = MinDistance(cp,cq,cr);
			cout << "cp cq cr cs" << endl;
			cout << cp << " " << cq << " " << cr << " " << cs << endl;
			if (cs >= 0){ // Found PowerUp(s) Nearby
				if (cs == cp)
					cout << "cs==cp"<< MoveToAny(m, pair<int,int>(9,19), cp, '&') << endl;
				else if (cs == cq)
					cout << "cs==cq"<<MoveToAny(m, pair<int,int>(9,19), cq, '$') << endl;
				else
					cout << "else (cs==cr)"<<MoveToAny(m, pair<int,int>(9,19), cr, '!') << endl;
			}
			
			
	/*
	// Test Greedy
		int X, out;
		int A = 18;
		int B = 19;
		pair<int,int> CurrPos (A,B);
		if (danger[A][B]){
			X = BFS(m, CurrPos, ' '); // Find Nearest Escape
			out = Move(m, CurrPos, ' ', X);
		}else{
			X = BFS(m, CurrPos, '+'); // Find Nearest Wall
			if (X == 0){
				out = 5; // Place Bomb
			}else{
				out = Move(m, CurrPos, '+', X);
			}
		}
		
		cout << out << std::endl;
	*/
	return 0;
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
	
	/* Down */
	x = FindWall(m, pair<int,int>(i+1,j));
	if ((i+1 < m.GetRow()) && (x != -1) && !danger[i+1][j] && !isdigit(m[i+1][j]) &&
	((m[i+1][j] == ' ') || (m[i+1][j] == '$') || (m[i+1][j] == '&') || (m[i+1][j] == '!'))){
		val.push_back(x);
		dir.push_back(4);
	}
	
	/* Left */
	x = FindWall(m, pair<int,int>(i,j-1));
	if ((j-1 >= 0) && (x != -1) && !danger[i][j-1] && !isdigit(m[i][j-1]) &&
	((m[i][j-1] == ' ') || (m[i][j-1] == '$') || (m[i][j-1] == '&') || (m[i][j-1] == '!'))){
		val.push_back(x);
		dir.push_back(2);
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
		if ((i-1 >= 0) && !danger[i-1][j] && !isdigit(m[i-1][j]) &&
		((m[i-1][j] == ' ') || (m[i-1][j] == '$') || (m[i-1][j] == '&') || (m[i-1][j] == '!')))
			return 1;
		/* Down */
		else if ((i+1 < m.GetRow()) && !danger[i+1][j] && !isdigit(m[i+1][j]) &&
		((m[i+1][j] == ' ') || (m[i+1][j] == '$') || (m[i+1][j] == '&') || (m[i+1][j] == '!')))
			return 4;
		/* Left */
		else if ((j-1 >= 0) && !danger[i][j-1] && !isdigit(m[i][j-1]) &&
		((m[i][j-1] == ' ') || (m[i][j-1] == '$') || (m[i][j-1] == '&') || (m[i][j-1] == '!')))
			return 2;
		/* Right */
		else if ((j+1 < m.GetCol()) && !danger[i][j+1] && !isdigit(m[i][j+1]) &&
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
		
		/* Down */
		x = FindEscape(m, pair<int,int>(i+1,j));
		if ((i+1 < m.GetRow()) && (x != -1) && !isdigit(m[i+1][j]) &&
		((m[i+1][j] == ' ') || (m[i+1][j] == '$') || (m[i+1][j] == '&') || (m[i+1][j] == '!'))){
			val.push_back(x);
			dir.push_back(4);
		}
		
		/* Left */
		x = FindEscape(m, pair<int,int>(i,j-1));
		if ((j-1 >= 0) && (x != -1) && !isdigit(m[i][j-1]) &&
		((m[i][j-1] == ' ') || (m[i][j-1] == '$') || (m[i][j-1] == '&') || (m[i][j-1] == '!'))){
			val.push_back(x);
			dir.push_back(2);
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
			if (m[i+1][j] == target)
				found = true;
			else{
				q.push(pair<int,int>(i+1, j));
				qn.push(n+1);
				visited[i+1][j] = true;
			}
		}
		
		if ((i-1 >= 0) && !visited[i-1][j] && (m[i-1][j] != '#') && 
		(m[i-1][j] != '+') && !danger[i-1][j] && !isdigit(m[i-1][j]))
		{
			if (m[i-1][j] == target)
				found = true;
			else{
				q.push(pair<int,int>(i-1, j));
				qn.push(n+1);
				visited[i+1][j] = true;
			}
		}
		
		if ((j+1 < m.GetCol()) && !visited[i][j+1] && (m[i][j+1] != '#') && 
		(m[i][j+1] != '+') && !danger[i][j+1] && !isdigit(m[i][j+1]))
		{
			if (m[i][j+1] == target)
				found = true;
			else{
				q.push(pair<int,int>(i, j+1));
				qn.push(n+1);
				visited[i][j+1] = true;
			}
		}
		
		if ((j-1 >= 0) && !visited[i][j-1] && (m[i][j-1] != '#') && 
		(m[i][j-1] != '+') && !danger[i][j-1] && !isdigit(m[i][j-1]))
		{
			if (m[i][j-1] == target)
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
		/* Down */
		else if ((i+1 < m.GetRow()) && !danger[i+1][j] && !isdigit(m[i+1][j]) && (m[i+1][j] == target))
			return 4;
		/* Left */
		else if ((j-1 >= 0) && !danger[i][j-1] && !isdigit(m[i][j-1]) && (m[i][j-1] == target))
			return 2;
		/* Right */
		else if ((j+1 < m.GetCol()) && !danger[i][j+1] && !isdigit(m[i][j+1]) && (m[i][j+1] == target))
			return 3;
		else
			return 6;
		
	}
	
	else{
	
		/* Up */
		x = FindAny(m, pair<int,int>(i-1,j), target);
		if ((i-1 >= 0) && (x != -1) && !isdigit(m[i-1][j]) &&
		((m[i-1][j] == ' ') || (m[i-1][j] == '$') || (m[i-1][j] == '&') || (m[i-1][j] == '!'))){
			val.push_back(x);
			dir.push_back(1);
		}
		
		/* Down */
		x = FindAny(m, pair<int,int>(i+1,j), target);
		if ((i+1 < m.GetRow()) && (x != -1) && !isdigit(m[i+1][j]) &&
		((m[i+1][j] == ' ') || (m[i+1][j] == '$') || (m[i+1][j] == '&') || (m[i+1][j] == '!'))){
			val.push_back(x);
			dir.push_back(4);
		}
		
		/* Left */
		x = FindAny(m, pair<int,int>(i,j-1), target);
		if ((j-1 >= 0) && (x != -1) && !isdigit(m[i][j-1]) &&
		((m[i][j-1] == ' ') || (m[i][j-1] == '$') || (m[i][j-1] == '&') || (m[i][j-1] == '!'))){
			val.push_back(x);
			dir.push_back(2);
		}
		
		/* Right */
		x = FindAny(m, pair<int,int>(i,j+1), target);
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




