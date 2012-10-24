#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cell.h"
#include "Fish.h"
#include "Shark.h"

Cell ** Make2dArray(int row,int col)
{
	Cell ** array;
	array = (Cell**) malloc(row*sizeof(Cell*));  
	int i = 0;
	for (i = 0; i < row; i++)  
		array[i] = (Cell*) malloc(col*sizeof(Cell));  

   return array;  
}
Cell * randomEmptyCell(Cell ** world,int row,int col)
{
	int randomCol = rand() % row;
	int randomRow = rand() % col;
	while(world[randomRow][randomCol].fish != 0 || world[randomRow][randomCol].shark != 0)
	{
		randomCol = rand() % row;
		randomRow = rand() % col;
	}
	return &world[randomRow][randomCol] ;
}
void PopulateWorld(int nFish,int nSharks,int rows, int cols,Cell ** world)
{
	int i;

	Cell * p;
	for (i = 0; i < nFish; ++i)
	{
		p = randomEmptyCell(world,rows,cols);
		p->fish =  malloc(sizeof(Fish));
		p->fish->moved = -1;
		p->fish->SpawnTime=0;
	}
	int j;
	for (j = 0; j < nSharks; ++j)
	{
		p = randomEmptyCell(world,rows,cols);
		p->shark =  malloc(sizeof(Shark));
		p->shark->moved = -1;
		p->shark->SpawnTime = 0;
		p->shark->StarveTime = 4;
	}

}
int main(void)
{
	srand(time(NULL));
	int NumRows = 10;
	int NumCols = 10;
	Cell ** world = Make2dArray(NumRows,NumCols);
	PopulateWorld(4,6,NumRows,NumCols,world);
	
	int i;
	int j;
	int Year = 0;
	while(Year != 30)
	{
		for(i=0; i < 10;i++)
		{

			for(j=0; j < 10;j++)
			{       
				if(world[i][j].fish != 0 && world[i][j].fish->moved != Year){  
					world[i][j].fish->moved = Year;
					FishUpdate(&world[i][j], world, i, j, 9);
				}
				else if(world[i][j].shark != 0 && world[i][j].shark->moved != Year)
				{
					world[i][j].shark->moved = Year;
					SharkUpdate(&world[i][j], world, i, j, 9);
				}
			}
      		
      	}
		for(i=0; i < 10;i++)
		{

			for(j=0; j < 10;j++)
			{   
				if(world[i][j].shark != 0)
					printf("[ S ]");
				else if(world[i][j].fish != 0)
					printf("[ F ]");
				else
					printf("[   ]");
				
			}
			printf("\n");

		}
		printf("\n\n");
		
		sleep(1);
		Year++;
	} 

	for (i = 0; i < NumRows; i++){  
	free( world [i]);  
	}	  
	free(world); 

}
