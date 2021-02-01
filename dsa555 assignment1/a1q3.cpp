#include "wall.h"
#include "maze.h"

/*
Parameters:
The runMaze function accepts a maze runner object, path array, starting/current cell and destination cell as integers.

Behavior:
This function will step through each accessible cell in the maze, mark it as visited and add it to its current path
towards the endCell.
If the runner diverts onto a path that leads to a dead end, it will step back to the previous cell, unmark the
incorrect visited cell, and overwrite each bad cell in the path array with the correct cells once it reaches
and marks them as visited.

Return Value:
If the function returns a non-zero path length, it has successfully completed the maze.
If it returns a zero path length, this indicates there is no valid path from startCell to endCell, and the maze is 
declared impossible.
*/
int runMaze(Maze& theMaze, int path[], int startCell, int endCell) 
{
	static int pathIndex = 0;
	int row = 0;
	int col = 0;
	int result = 0;
	int finalPathLength = 0;

	//get the current cell's coordinates
	row = theMaze.getRow(startCell);
	col = theMaze.getCol(startCell);

	//mark the current cell as visited
	theMaze.mark(startCell);
	//add it to the path
	path[pathIndex] = startCell;

	//return final path length once the startCell has reached the endCell
	if (startCell == endCell)
	{
		//pathIndex+1 -> offset the first path index (which starts at 0) to correct the path length
		finalPathLength = pathIndex + 1;
		//reset the path counter to prepare for the next maze
		pathIndex = 0;
		//return the final path length to the last recursive runMaze call
		return finalPathLength;
	}

	//check if the next cell for the path is accessible and not already marked as being part of the path
	if ( theMaze.canGo(theMaze.getCell(row, col), theMaze.getCell(row, col + 1))
		&& !theMaze.isMarked(theMaze.getCell(row, col + 1)) )
	{
		//increment the path count for the next cell
		++pathIndex;

		//recursively call the maze runner function and retrieve the final path length
		result = runMaze(theMaze, path, theMaze.getCell(row, ++col), endCell);

		//check if final path length returned is greater than 0
		if (result > 0)
		{
			//pass the final path length up the recursive call stack until the first call is reached (in a1q3tester)
			return result; 
		}
		else
		{
			//step back from current cell position
			--col; 
			//unmark the visited (bad) cell
			theMaze.unMark( theMaze.getCell(row, col + 1) ); 
			//move path counter back to overwrite incorrect cells with correct ones
			--pathIndex;
		}
	}

	if ( theMaze.canGo(theMaze.getCell(row, col), theMaze.getCell(row, col - 1))
		&& !theMaze.isMarked(theMaze.getCell(row, col - 1)) )
	{
		++pathIndex;
		result = runMaze(theMaze, path, theMaze.getCell(row, --col), endCell);

		if (result > 0)
		{
			return result;
		}
		if (result == 0)
		{
			++col;
			theMaze.unMark( theMaze.getCell(row, col  -1) );
			--pathIndex;
		}
	}

	if ( theMaze.canGo(theMaze.getCell(row, col), theMaze.getCell(row+1, col))
		&& !theMaze.isMarked(theMaze.getCell(row+1, col)) )
	{
		++pathIndex;
		result = runMaze(theMaze, path, theMaze.getCell(++row, col), endCell);

		if (result > 0)
		{
			return result;
		}
		if (result == 0)
		{
			--row;
			theMaze.unMark( theMaze.getCell(row + 1, col) );
			--pathIndex;
		}
	}


	if ( theMaze.canGo(theMaze.getCell(row, col), theMaze.getCell(row - 1, col))
		&& !theMaze.isMarked(theMaze.getCell(row - 1, col)) )
	{
		++pathIndex;
		result = runMaze(theMaze, path, theMaze.getCell(--row, col), endCell);

		if (result > 0)
		{
			return result;
		}
		if (result == 0)
		{
			++row;
			theMaze.unMark( theMaze.getCell(row - 1, col) );
			--pathIndex;
		}
	}

	//return 0 if the maze is impossible or a dead end is reached
	return 0;
}