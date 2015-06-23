/*
 * PathPlanner.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: colman
 */

#include "PathPlanner.h"
#include <stdio.h>
#include <vector>

using namespace std;

PathPlanner::PathPlanner() {
	// TODO Auto-generated constructor stub

}

PathPlanner::~PathPlanner() {
	// TODO Auto-generated destructor stub
}

bool solveMazeUtil(vector<bool> grid, unsigned gridWidth, unsigned gridHeight, unsigned locationX,
	unsigned locationY, unsigned goalX, unsigned goalY, vector<bool> solution);

vector<bool> PathPlanner::GetShortestPath(vector<bool> grid, unsigned gridWidth, unsigned gridHeight,
		unsigned locationX, unsigned locationY, unsigned goalX, unsigned goalY) {
	// Create a new solution grid
	vector<bool> solution(gridHeight * gridWidth);

	// Fill it with 1's (wall) and now we will mark the path with 0's (free)
	std::fill(solution.begin(), solution.end(), 1);

	// Solve the shortest path using solution
	solveMazeUtil(grid, gridWidth, gridHeight, locationX, locationY, goalX, goalY, solution);

	return solution;
}

/* A recursive utility function to solve Maze problem */
bool solveMazeUtil(vector<bool> grid, unsigned gridWidth, unsigned gridHeight, unsigned locationX,
		unsigned locationY, unsigned goalX, unsigned goalY, vector<bool> solution) {
    // Check if grid[x][y] is valid (didn't pass max width or height, isn't a wall and didn't visit yet)
    if(locationX > gridWidth || locationY > gridHeight
    		|| grid[locationX * locationY] == 1 || solution[locationX * locationY] == 0)
    	return false;

    // mark x,y as part of solution path
	solution[locationX * locationY] = 0;

	/* Move forward in x direction */
	if (solveMazeUtil(grid, gridWidth, gridHeight, locationX+1, locationY, goalX, goalY, solution))
		return true;

	/* If moving forward in x direction doesn't give solution then
		   Move backward in x direction  */
	if (locationX > 0 && solveMazeUtil(grid, gridWidth, gridHeight, locationX-1, locationY, goalX, goalY, solution))
		return true;

	/* If moving in x direction doesn't give solution then
	   Move down in y direction  */
	if (solveMazeUtil(grid, gridWidth, gridHeight, locationX, locationY+1, goalX, goalY, solution))
		return true;

	/* If moving in x direction doesn't give solution then
	   Move up in y direction  */
	if (locationY > 0 && solveMazeUtil(grid, gridWidth, gridHeight, locationX, locationY-1, goalX, goalY, solution))
		return true;

	/* If none of the above movements work then BACKTRACK:
		unmark x,y as part of solution path */
	solution[locationX * locationY] = 1;
	return false;
}
