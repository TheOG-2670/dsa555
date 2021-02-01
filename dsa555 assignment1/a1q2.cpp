#include "wall.h"
#include "disjointset.h"
#include <cstdlib> //rand()


/*This function accepts a DisjointSet object, two integers for the number of rows and columns, and an integer for the pre-calculated
total number of walls that can exist for the maze.

It will sequentially create all column walls and then all row walls, and finally randomly re-arrange all walls to prepare for the
wall-breaking maze formation in generateMaze*/
Wall *createWalls(DisjointSet& d, int row, int col, int totalWalls)
{
	//store all generated row and column walls locally
	Wall *walls = new Wall[totalWalls];
	//returns pointer of local wall array at end
	Wall *wallsReturned=nullptr;

	int wallCount = 0;
	int cellValue = 0;

	//create column walls
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (d.makeSet(cellValue))
			{
				if ((j == 0 && i == 0)
					|| (j == 0 && col > 1)) //first cell (works for both single row and single column mazes)
				{
					//sets first cell of wall (firs wall in current row/col)
					walls[wallCount].set(cellValue, -1);
				}

				if ((col > 1 && j > 0) /*multi-column maze and multi-row/column maze*/
					|| (row > 1 && i > 0 && col == 1) /*multi-row maze*/)
				{
					if ((j == 1) /*multi-column and multi-row/column maze*/
						|| (i == 1 && col == 1) /*multi-row maze*/)
					{
						//sets second cell of wall (first wall in current row/col)
						walls[wallCount].set(walls[wallCount].cell1(), cellValue);
						wallCount++;
					}
					else
					{
						//sets previous cell as first and new cell as second for all subsequent column walls
						walls[wallCount].set(walls[wallCount - 1].cell2(), cellValue);
						wallCount++;
					}

				}

				cellValue++;
			}
		}
	}

	//create row walls
	int wallColCount = wallCount;
	int wallRowCount = (totalWalls - wallColCount);
	for (int i = 0; i <= wallRowCount - row; i++)
	{
		//checks previous wall's first cell to avoid making duplicate wall
		if (walls[i].cell1() != walls[wallCount - 1].cell1())
		{

			walls[wallCount++].set(walls[i].cell1(), walls[i + (col - 1)].cell1());
		}


		walls[wallCount++].set(walls[i].cell2(), walls[i + (col - 1)].cell2());
	}

	//randomize the wall positions
	Wall tempWalls;
	for (int i = 0; i < totalWalls; i++)
	{
		int chosenWall = rand() % totalWalls;
		tempWalls = walls[i];
		walls[i] = walls[chosenWall];
		walls[chosenWall] = tempWalls;
	}

	//copy address of wall array to another wall pointer to allow memory deallocation of array and return wall pointer
	wallsReturned = walls;
	walls = nullptr;
	delete[] walls;
	return wallsReturned;
}

//accepts 2 integers for number of rows and columns, and array of wall objects
/*this function will generate a maze using the number of rows, columns and wall array provided. it will generate all possible walls
that can exist in the maze and then randomly pick walls to break down by joining two cells if they are not in the same path. It will
then return the remaining walls*/
int generateMaze(int row, int col, Wall walls[])
{
	DisjointSet d(row * col);
	int totalWalls = (row - 1) * col + (col - 1) * row;
	Wall *localWalls = createWalls(d, row, col, totalWalls);
	int finalWallCount = 0;

	for (int i = 0; i < totalWalls; i++)
	{
		if (d.findSet(localWalls[i].cell1()) != d.findSet(localWalls[i].cell2()))
		{
			d.unionSets(localWalls[i].cell1(), localWalls[i].cell2());
		}
		else
		{
			walls[finalWallCount++] = localWalls[i];
		}
	}

	return finalWallCount;
}