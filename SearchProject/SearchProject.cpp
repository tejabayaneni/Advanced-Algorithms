#include <utility>
#include <math.h>
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include "Point.h"
#include "Maze.h"
using namespace std;

/*
 * Assignment Written by Varick Erickson.
 * Inspired by PACMAN assignment written/developed by Dan Klein and Ron Parr
 */

// Direction related constants
enum Direction {NORTH, SOUTH, EAST, WEST};
const string directions[4] = {"North", "South", "East", "West"};

// Searches you need to implement
vector<Point>* DFS(Maze&, bool(*isGoalState)(Point pt, Maze& maze));
vector<Point>* BFS(Maze&, bool(*isGoalState)(Point pt, Maze& maze));
vector<Point>* UCS(Maze&, bool(*isGoalState)(Point pt, Maze& maze), double(*CostFunction)(Point pt));
vector<Point>* AStar(Maze&, bool(*isGoalState)(Point pt, Maze& maze),double(*Heuristic)(Point pt, Maze maze));

// Goal functions
bool FinalPositionGoal(Point , Maze& );
bool CornerGoal(Point , Maze& );

// Cost functions
double StayEast(Point pt);
double StayWest(Point pt);
double ManhattanDistance(Point pt,Maze& maze);//to calculate manhattan distance
double EuclideanDistance(Point pt,Maze& maze);//to calculate EuclideanDistance
//double Heuristic(Point pt,Maze& maze);
// Cost heuristics
double Heuristic(Point pt, Maze maze) {
	double a=ManhattanDistance(pt,maze);//calling manhattan distance
	//double a=EuclideanDistance(pt,maze);//calling euclidean distance
	return a;
}
//calculating manhattan distance
double ManhattanDistance(Point pt,Maze& maze){
	Point finalpoint = maze.goalPt();
	double x=finalpoint.row-pt.row;
	double y=finalpoint.col-pt.col;
	double distance=abs(x)+abs(y);
	return distance;
}
//calculating EuclideanDistance
double EuclideanDistance(Point pt,Maze& maze){
	Point finalpoint = maze.goalPt();
	double x=finalpoint.row-pt.row;
	double y=finalpoint.col-pt.col;
	double distance=pow(x,2)+pow(y,2);
	double euclead=sqrt(distance);
	return euclead;
}
///////  Add your Heuristic prototypes here

// Used for priority queue
bool ComparePoints(Point a, Point b) {
	return a.cost > b.cost;
}

// A couple of convenience functionss
bool ValidDirection(int, Point, Maze&);
bool NotInSet(Point, set<Point>&);

int main()
{
	string filename;
	cout << "Enter Maze file name: ";
	cin >> filename;
	//filename = "tinyMaze.txt"; // Hard coded for testing
	// Initialize the maze
	Maze maze(filename);
	cout << maze << endl;
	vector<Point>* soln;
	// Examples of calls
	//soln=BFS(maze, FinalPositionGoal);
	//soln = DFS(maze, FinalPositionGoal);
	soln = AStar(maze, FinalPositionGoal, Heuristic);// in the heuristic added manhattand and EuclideanDistance
	//soln = UCS(maze, FinalPositionGoal, StayEast);
	//soln = UCS(maze, FinalPositionGoal, StayWest);
	cout << "\nTotal Cost: " << soln->back().cost << endl;
	for (int i = 0; i < soln->size(); i++) {
		maze.SetVal(soln->at(i), '*');
	}
	cout << maze << endl;
	return 0;
}

vector<Point>* DFS(Maze& maze, bool(*isGoalState)(Point pt, Maze& maze)) {
	/* Example how to check goal state
	if (isGoalState(pt, maze)) {		// How to check goal state
		// Stuff
	}
	*/
	// Your code Here
	stack<Point> mystack;//initialize stack
	vector<Point>* result = new vector<Point>;//taking the vector for the path
	set<Point> visited;//to check whether we visited that node already
	Point initialstart = maze.StartPt();//taking the start point
	mystack.push(initialstart);//pushing it to the stack
	while (!mystack.empty()) {//checking whether queue is empty or not
		Point a = mystack.top();//taking the first element
		result->push_back(a);//adding that to the vector
		mystack.pop();//popping the element from the stack
		visited.insert(a);
			if (isGoalState(a, maze)) {
					cout<<"Goal Reached at:\t"<<"("<<a.row<<","<<a.col<<")\n";
					for (Point i:a.path){
						result->push_back(i);
					}
					result->push_back(Point(a.row,a.col,a.cost));// inserting goal node to the vector pointer

					return result;//returning the vector
			}
			else {
				cout<<"Current:\t"<<"("<<a.row<<","<<a.col<<")\n";
				//getting the children for the current node in the 4 possible ways
				if (ValidDirection(NORTH, a, maze)) {
					// checking whether the child is already in the set or not
						cout<<"Successor:\t"<<"("<<a.row-1<<","<<a.col<<")\t" << "North\n";
						vector<Point> pt=a.path;//adding the path
						pt.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
						mystack.push(Point(a.row-1,a.col,a.cost+1,pt));//inseting the child node to stack

				}

				if (ValidDirection(EAST, a, maze)) {
					if(NotInSet(Point(a.row,a.col+1),visited)){// checking whether the child is already in the set or not
						cout<<"Successor:\t"<<"("<<a.row<<","<<a.col+1<<")\t"<<"East\n";
						vector<Point> pt=a.path;//adding the path
						pt.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
						mystack.push(Point(a.row,a.col+1,a.cost+1,pt));//inseting the child node to stack
					}
				}
				if (ValidDirection(SOUTH, a, maze)) {
					if(NotInSet(Point(a.row+1,a.col),visited)){// checking whether the child is already in the set or not
						cout<<"Successor:\t"<<"("<<a.row+1<<","<<a.col<<")\t"<<"South\n";
						vector<Point> pt=a.path;//adding the path
						pt.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
						mystack.push(Point(a.row+1,a.col,a.cost+1,pt));///inseting the child node to stack
					}
				}
				if (ValidDirection(WEST, a, maze)) {
					if(NotInSet(Point(a.row,a.col-1),visited)){// checking whether the child is already in the set or not
						cout<<"Successor:\t"<<"("<<a.row<<","<<a.col-1<<")\t"<<"West\n";
						vector<Point> pt=a.path;//adding the path
						pt.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
						mystack.push(Point(a.row,a.col-1,a.cost+1,pt));///inseting the child node to stack
					}
				}
			}
		}
		return nullptr;
	}




vector<Point>* BFS(Maze& maze, bool(*isGoalState)(Point pt, Maze& maze)) {
	// Your code Here
	queue<Point> myqueue;//initialized queue
	vector<Point>* result = new vector<Point>;
	set<Point> visited;//initialize set to check whether the nodes are already explored or not
	Point initialstart = maze.StartPt();
	myqueue.push(initialstart);//inserting element to queue
	//visited.insert(initialstart);
	while (!myqueue.empty()) {//checking until queue is empty
		Point a = myqueue.front();
		myqueue.pop();
		visited.insert(a);//adding node to the visited set
			if (isGoalState(a, maze)) {
				for(Point pt : a.path) {
					result->push_back(pt);//inserting all the points in the path to the vector pointer
				}
				result->push_back(Point(a.row,a.col,a.cost));// inserting goal node to the vector pointer
				return result;
			}
			else {
				cout<<"Current:\t"<<"("<<a.row<<","<<a.col<<")\n";
				if (ValidDirection(NORTH, a, maze)) {
					if(NotInSet(Point(a.row-1,a.col),visited)){// checking whether the child is already in the set or not
						cout<<"Successor:\t"<<"("<<a.row-1<<","<<a.col<<")\t" << "North\n";
						vector<Point> pt=a.path;//adding the path
						pt.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
						myqueue.push(Point(a.row-1,a.col,a.cost+1,pt));//inseting the child node to QUEUE
						visited.insert(Point(a.row-1,a.col));
					}
				}
				if (ValidDirection(EAST, a, maze)) {
					if(NotInSet(Point(a.row,a.col+1),visited)){// checking whether the child is already in the set or not
						cout<<"Successor:\t"<<"("<<a.row<<","<<a.col+1<<")\t"<<"East\n";
						vector<Point> pt=a.path;//adding the path
						pt.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
						myqueue.push(Point(a.row,a.col+1,a.cost+1,pt));//inseting the child node to QUEUE
						visited.insert(Point(a.row,a.col+1));
					}
				}
				if (ValidDirection(SOUTH, a, maze)) {
					if(NotInSet(Point(a.row+1,a.col),visited)){// checking whether the child is already in the set or not
						cout<<"Successor:\t"<<"("<<a.row+1<<","<<a.col<<")\t"<<"South\n";
						vector<Point> pt=a.path;//adding the path
						pt.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
						myqueue.push(Point(a.row+1,a.col,a.cost+1,pt));//inseting the child node to QUEUE
						visited.insert(Point(a.row+1,a.col));
					}
				}
				if (ValidDirection(WEST, a, maze)) {
					if(NotInSet(Point(a.row,a.col-1),visited)){// checking whether the child is already in the set or not
						cout<<"Successor:\t"<<"("<<a.row<<","<<a.col-1<<")\t"<<"West\n";
						vector<Point> pt=a.path;//adding the path
						pt.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
						myqueue.push(Point(a.row,a.col-1,a.cost+1,pt));//inseting the child node to QUEUE
						visited.insert(Point(a.row,a.col-1));
					}
				}
			}
		}
	return nullptr;
}

vector<Point>* UCS(Maze& maze, bool(*isGoalState)(Point pt, Maze& maze), double(*CostFunction)(Point pt)) {
	// Priority Queue of points. Container specified as vector and a compare function is provided
	priority_queue<Point, vector<Point>, decltype(&ComparePoints)> neighbors(ComparePoints);
	vector<Point>* result = new vector<Point>;
	Point initialstart = maze.StartPt();
	set <Point> visited;
	neighbors.push(initialstart);//insert top element
	// Your code Here
	while(!neighbors.empty()){
	  Point a=neighbors.top();
	  neighbors.pop();//removing the first element from the queue
		visited.insert(a);
	    if (isGoalState(a, maze)) {
				cout<<"Goal Reached at:\t"<<"("<<a.row<<","<<a.col<<")\n";
				for(Point pt : a.path) {
					result->push_back(pt);//inserting all nodes in the path to the vector pointer
				}
				result->push_back(Point(a.row,a.col,a.cost));// inserting goal node to the vector pointer
				return result;
	    }else {
	      cout<<"Current:\t"<<"("<<a.row<<","<<a.col<<")\n";
	      if (ValidDirection(NORTH, a, maze)) {
	        if(NotInSet(Point(a.row-1,a.col),visited)){// checking whether the child is already in the set or not
	          cout<<"Successor:\t"<<"("<<a.row-1<<","<<a.col<<")\t"<<"North\n";
	          double h=CostFunction(Point(a.row-1,a.col));
						vector<Point> pt=a.path;//adding the path
					 	pt.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
						//a.cost=maze.setVal(a,a.cost);
	          cout<<"cost="<<a.cost <<"\n";
	        neighbors.push(Point(a.row - 1, a.col,a.cost+h,pt));//inseting the child node to QUEUE
					visited.insert(Point(a.row-1,a.col));

	      }
	      }

	      if (ValidDirection(EAST, a, maze)) {
	          if(NotInSet(Point(a.row,a.col+1),visited)){// checking whether the child is already in the set or not
	            cout<<"Successor:\t"<<"("<<a.row<<","<<a.col+1<<")\t"<<"East\n";
	            double h=CostFunction(Point(a.row,a.col+1));
							//a.cost=setVal(a,a.cost);
	           	cout<<"cost="<<a.cost <<"\n";
							vector<Point> pt=a.path;//adding the path
							pt.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
	        	neighbors.push(Point(a.row, a.col+1,a.cost+h,pt));//inseting the child node to QUEUE
						visited.insert(Point(a.row,a.col+1));

	      }
	    }
	    if (ValidDirection(SOUTH, a, maze)) {
	      if(NotInSet(Point(a.row+1,a.col),visited)){// checking whether the child is already in the set or not
	        cout<<"Successor:\t"<<"("<<a.row+1<<","<<a.col<<")\t"<<"South\n";
	       double h=CostFunction(Point(a.row+1,a.col));
					//	a.cost=maze.SetVal(a,a.cost);
	        	cout<<"cost="<<a.cost <<"\n";
					vector<Point> pt=a.path;//adding the path
					pt.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
	      	neighbors.push(Point(a.row + 1, a.col,a.cost+h,pt));//inseting the child node to QUEUE
					visited.insert(Point(a.row+1,a.col));

	    }
	  }
	      if (ValidDirection(WEST, a, maze)) {
	        if(NotInSet(Point(a.row,a.col-1),visited)){// checking whether the child is already in the set or not
	          cout<<"Successor:\t"<<"("<<a.row<<","<<a.col-1<<")\t"<<"West\n";
	          double h=CostFunction(Point(a.row,a.col-1));
						vector<Point> pt=a.path;//adding the path
						pt.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
							//a.cost=SetVal(a,a.cost);
	          	cout<<"cost="<<a.cost <<"\n";
	        	neighbors.push(Point(a.row, a.col - 1,a.cost+h,pt));//inseting the child node to QUEUE
						visited.insert(Point(a.row,a.col-1));

	      }
	    }
	    }
	  }


	return nullptr;
}

vector<Point>* AStar(Maze& maze, bool(*isGoalState)(Point pt, Maze& maze),double(*Heuristic)(Point pt, Maze maze)) {
	priority_queue<Point, vector<Point>, decltype(&ComparePoints)> frontier(ComparePoints);
	vector<Point>* result = new vector<Point>;
	Point initialstart = maze.StartPt();//start point
	set <Point> visited;
	frontier.push(initialstart);
	while(!frontier.empty()){
	  Point a=frontier.top();
		frontier.pop();
		visited.insert(a);
	    if (isGoalState(a, maze)) {
				for(Point i:a.path){
					result->push_back(i);// inserting all nodes in the path to the vector pointer
				}
				result->push_back(Point(a.row,a.col,a.cost));/// inserting goal node to the vector pointer
				return result;
	    }else {
	      cout<<"Current:\t"<<"("<<a.row<<","<<a.col<<")\n";

	      if (ValidDirection(NORTH, a, maze)) {
	        if(NotInSet(Point(a.row-1,a.col),visited)){// checking whether the child is already in the set or not
	          cout<<"Successor:\t"<<"("<<a.row-1<<","<<a.col<<")\t"<<"North\n";
	          double h=Heuristic(Point(a.row-1,a.col),maze);
						vector<Point> pt1=a.path;//adding the path
						pt1.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
						cout<<"cost="<<a.cost <<"\n";
	        	frontier.push(Point(a.row - 1, a.col,a.cost+h,pt1));//inseting the child node to QUEUE
						visited.insert(Point(a.row-1,a.col));
	      }
	      }
	      if (ValidDirection(EAST, a, maze)) {
	          if(NotInSet(Point(a.row,a.col+1),visited)){// checking whether the child is already in the set or not
	            cout<<"Successor:\t"<<"("<<a.row<<","<<a.col+1<<")\t"<<"East\n";
	             double h=Heuristic(Point(a.row,a.col+1),maze);
							vector<Point> pt1=a.path;//adding the path
							pt1.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
							cout<<"cost="<<a.cost <<"\n";
	        	frontier.push(Point(a.row, a.col + 1,a.cost+h,pt1));//inseting the child node to QUEUE
						visited.insert(Point(a.row,a.col+1));

	    }
		}
	    if (ValidDirection(SOUTH, a, maze)) {
	      if(NotInSet(Point(a.row+1,a.col),visited)){// checking whether the child is already in the set or not
	        cout<<"Successor:\t"<<"("<<a.row+1<<","<<a.col<<")\t"<<"South\n";
	        double h=Heuristic(Point(a.row+1,a.col),maze);
					vector<Point> pt1=a.path;//adding the path
					pt1.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
					cout<<"cost="<<a.cost <<"\n";
	      	frontier.push(Point(a.row + 1, a.col,a.cost+h,pt1));//inseting the child node to QUEUE
					visited.insert(Point(a.row+1,a.col));
	    }
	  }
	      if (ValidDirection(WEST, a, maze)) {
	        if(NotInSet(Point(a.row,a.col-1),visited)){// checking whether the child is already in the set or not
	          cout<<"Successor:\t"<<"("<<a.row<<","<<a.col-1<<")\t"<<"West\n";
	          double h=Heuristic(Point(a.row,a.col-1),maze);
						vector<Point> pt1=a.path;//adding the path
						pt1.push_back(Point(a.row, a.col,a.cost));//inserting row,col, cost to the path
					  cout<<"cost="<<a.cost <<"\n";
	        	frontier.push(Point(a.row, a.col - 1,a.cost+h,pt1));//inseting the child node to QUEUE
						visited.insert(Point(a.row,a.col-1));
	      }
			}
	    }

	  }

	return nullptr;
}

/*
* Cost function that penalizes being in
* positions on the East side of the board.
* The cost for stepping into a position(r, c) is 2^c.
*/
double StayWest(Point pt) {

	return pt.col*pt.col;
}

/*
* Cost function that penalizes being in
* positions on the West side of the board.
* The cost for stepping into a position(r, c) is 0.5^c.
*/
double StayEast(Point pt) {
	return pow(0.5,pt.col);
}

/*
* Goal function where navigating to 'F' position
* is considered the goal.
*/
bool FinalPositionGoal(Point pt, Maze& maze) {
	return maze[pt] == 'F';
}


/*
 * Checks if child is in mySet.
 */
bool NotInSet(Point child, set<Point>& mySet) {
	return mySet.find(child) == mySet.end();
}

/*
 * Checks if direction dir is valid given the point pt
 * and the map of the maze.
 */
bool ValidDirection(int dir, Point pt, Maze& maze) {
	//cout << "Checking " << directions[dir] << endl;
	switch (dir) {
	case NORTH:
		pt.row = pt.row - 1;
		break;
	case EAST:
		pt.col = pt.col + 1;
		break;
	case SOUTH:
		pt.row = pt.row + 1;
		break;
	case WEST:
		pt.col = pt.col - 1;
		break;
	default:
		return false;
	}
	//cout << pt.row << "," << pt.col << endl;
	if (pt.row > maze.Height() || pt.row < 0 ||
		pt.col > maze.Width() || pt.col < 0 ||
		maze[pt] == '@' || maze[pt] == '%') {
		return false;
	}

	return true;
}
