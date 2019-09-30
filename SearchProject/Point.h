#pragma once
#include <vector>
#include <string>

using namespace std;

/*
 * Simple class for representing points.
 * Variables:
 * row  - Row value for point
 * col  - Column value for point
 * path - Path to this point stored as a vector (a starting node will have no values)
 * cost - Cost up to this point (only used for cost searches like UCS or A*)
 */
class Point {
public:
	// Public for convenience
	int row;
	int col;
	vector<Point> path;		// Path to this point
	double cost;			// Cost up to this point

	Point() {
		row = 0;
		col = 0;
		cost = 0;

	}

	Point(int r, int c) {
		row = r;
		col = c;
		cost = 0;

	}
	//overloaded to calculate the cost
	Point(int r, int c,double cc) {
		row = r;
		col = c;
		cost = cc;

	}
	//overloaded to calculate cost and path
	Point(int r, int c,double cc, vector<Point> p) {
		row = r;
		col = c;
		cost = cc;
		path = p;
	}

	/*
	// Overload to allow for assignment
	inline Point operator=(Point& other) {
		row = other.row;
		col = other.col;
		return *this;
	}
	*/

	// Overload to allow printing
	// friend inline ostream& operator<<(ostream& os, Point& pt) {
	// 	os << "(" + std::to_string(pt.row) << "," << std::to_string(pt.col) << ")";
	// 	return os;
	// }
};



// Overload to make the stl containers work
inline bool operator==(const Point& lhs, const Point& rhs) {
	return lhs.row == rhs.row && lhs.col == rhs.col;
}

// Overload to make the stl containers work
inline bool operator<(const Point& lhs, const Point& rhs) {
	string rhsStr = "(" + std::to_string(rhs.row) + "," + std::to_string(rhs.col) + ")";
	string lhsStr = "(" + std::to_string(lhs.row) + "," + std::to_string(lhs.col) + ")";
	return lhsStr < rhsStr;
}

// Overload to make hashing work
namespace std
{
	template <>
	struct hash<Point>
	{
		size_t operator()(const Point& pt) const
		{
			return hash<int>()(pt.row) ^ hash<int>()(pt.col);
		}
	};
}
