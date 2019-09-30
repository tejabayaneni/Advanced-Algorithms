#include "Maze.h"

Maze::Maze(string mazeName)
{
	ifstream mazeFile(mazeName);

	if (!mazeFile.good()) {
		cout << "Could not open file " << mazeName << endl;
		exit(0);
	}

	int row = 0;

	// Read the file line by line an initialize the maze
	string line;
	while (getline(mazeFile, line)) {
		//cout << line << endl;
		if (line.length() > 0)
			width = line.length();
		for (int i = 0; i < (int)line.length(); i++) {
			map[row][i] = line[i];
			if (map[row][i] == 'S' || map[row][i] == 'P') {
				start.row = row;
				start.col = i;
				//map[row][i] = ' ';
			}
			else if (map[row][i] == 'F') {
				goal.row = row;
				goal.col = i;
			}
			else if (map[row][i] == '%' || map[row][i] == '@') {
				walls.push_back(Point(row, i));
			}
			else if (map[row][i] == '.') {
				coins.push_back(Point(row, i));
			}
		}
		row++;
	}

	// figure out the number of rows and columns
	height = row;
}

void Maze::SetVal(int r, int c, char val)
{
	if (c >= width || r >= height ||
		c < 0 || r < 0) {
		cout << "Point out of bound, exiting";
		exit(0);
	}
	map[r][c] = val;
}

void Maze::SetVal(Point pt, char val)
{
	if (pt.col >= width || pt.row >= height || pt.col < 0 || pt.row < 0) {
		cout << "Point out of bound, exiting";
		exit(0);
	}
	map[pt.row][pt.col] = val;
}


char Maze::GetVal(Point pt)
{
	if (pt.col >= width || pt.row >= height || pt.col < 0 || pt.row < 0) {
		cout << "Point out of bound, exiting";
		exit(0);
	}
	return map[pt.row][pt.col];
}
