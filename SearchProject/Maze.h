#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include "Point.h"
using namespace std;

#define MAX_ROW	100
#define MAX_COL	100

// Maze Class
class Maze {
public:
	// Initializes maze from a file
	Maze(string mazeName);

	// Sets a value at a particular point
	void SetVal(int r, int c, char val);
	void SetVal(Point pt, char val);


	// Gets a value at a particular point
	char GetVal(Point pt);

	// Return start point
	Point StartPt() { return start; }
	
	// Return final point
	Point goalPt() { return goal; }

	// Returns the vector of coin locations
	vector<Point> getCoins() { return coins; }

	// Returns the vector of wsall locations
	vector<Point> getWalls() { return walls; }

	// Return width
	int Width() { return width;}

	// Return height
	int Height() { return height; }

	// Overload [] to allow pt as index
	char &operator[](Point pt) {
		if (pt.col >= width || pt.row >= height || pt.col < 0 || pt.row < 0) {
			cout << "Point out of bound, exiting";
			exit(0);
		}
		return map[pt.row][pt.col];
	}

	// Allows map to be printed by cout or written to file
	friend inline ostream& operator<<(ostream& os, Maze& maze) {
		for (int r = 0; r < maze.height; r++) {
			for (int c = 0; c < maze.width; c++) {
				os << maze.map[r][c];
			}
			os << endl;
		}
		return os;
	}

private:
	char map[MAX_COL][MAX_ROW];
	vector<Point> walls;
	vector<Point> coins;
	Point start;	// start postion
	Point goal;	    // goal position
	int width;
	int height;
};