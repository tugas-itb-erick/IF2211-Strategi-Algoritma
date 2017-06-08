/* File : Map.h */

#pragma once

#include "stdafx.h"
using namespace std;

#define MAX 101

class Map{
	public:
		/* Constructor */
		Map();
		Map(int, int);
		Map(const Map&);
		/* Destructor */
		~Map();
		/* Getter */
		int GetRow();
		int GetCol();
		/* Output */
		friend ostream& operator<<(ostream&, const Map&);
		/* Operator */
		Map& operator=(const Map&);
		void search(char, int&, int&);
		/* Operator[][] */
	    class Proxy {
		        friend class Map;
		    public:
		        char& operator[](int c)
		        {
		            return parent.data[r][c];
		        }
		    private:
		        Proxy(Map &parent_, int row_) : 
		            parent(parent_),
		            r(row_)
		        {}
		
		        Map& parent;
		        int r;
	    };
	    
	    Proxy operator[](int x)
	    {
	        return Proxy(*this, x);
	    }
	    
	private:
		int row;
		int col;
		char ** data;
};
