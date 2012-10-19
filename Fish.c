#include <stdio.h>
#include <time.h>
#include <stdlib.h>


typedef struct{
int moved; 
int SpawnTime;
}Fish;

typedef struct{
int SpawnTime;
int StarveTime;
}Shark;

typedef struct{
Shark * shark;
Fish * fish;
}Cell;

typedef struct{
int left;
int right;
int up;
int down;
}Move;

int CheckIfEmty(Cell * M)
{
	if(M->shark == NULL && M->fish == NULL)
	{
		return 1;
	}
	return 0;
}
int ChooseCell(Move Available)
{
	int x = 0;
	int Dirrection = 0;
	if (Available.left == 0 &&
		Available.right == 0 &&
		Available.up ==0 &&
		Available.down ==0)
	{
		x = 1;
		Dirrection = -1;
	}
	while(x == 0)
	{
		srand(time(NULL));
		int r = rand() % 4;

		Dirrection = r;
		switch(r){
			case 0:
		    if(Available.left == 1)
				x = 1;
			break;
			case 1:
			if(Available.right == 1)
				x = 1;
			break;
			case 2:
			if(Available.up == 1)
				x = 1;
			break;
			case 3:
			if(Available.down == 1)
				x = 1;
			break;
		}
	}
	return Dirrection;
}

void FishMove(Cell * Moveto, Cell * currentCell){
	if(currentCell->fish->SpawnTime == 0)
	{
		currentCell->fish->SpawnTime = 3;
		Moveto->fish = malloc(sizeof(Fish));
		Moveto->fish->SpawnTime = 3;
		printf("Fish Spawned!!!!!!!! \n");
		
	}
	else
	{
		Moveto->fish = currentCell->fish;
		Moveto->fish->SpawnTime--;
		currentCell->fish = NULL;
	}
	
}

void FishUpdate(Cell * currentCell, Cell *** tempworld, int x, int y, int range)
{   
	if(currentCell->fish != NULL && currentCell->fish->moved != 1)
	{
		currentCell->fish->moved = 1;
		Move Available;
		int top = y - 1;
		int bot = y + 1;
		int left = x - 1;
		int right = x + 1;
		if (top < 0)
			top = range;
		if (left < 0)
			left = range;
		if (right > range)
			right = 0;
		if (bot > range)
			bot = 0;
		Cell * array[4] = {&(*tempworld)[x][top],&(*tempworld)[x][bot],&(*tempworld)[left][y],&(*tempworld)[right][y]};
		Available.up = CheckIfEmty(array[0]);
		Available.down = CheckIfEmty(array[1]);
		Available.left = CheckIfEmty(array[2]);
		Available.right = CheckIfEmty(array[3]);
		int ChoosenCell = ChooseCell(Available);
		if (ChoosenCell != -1)
		{
			FishMove(array[ChoosenCell], currentCell);
		}
	}
}
Cell ** Make2dArray(int row,int col)
{
	Cell ** array;
	array = (Cell**) malloc(row*sizeof(Cell*));  
	int i = 0;
	for (i = 0; i < row; i++)  
		array[i] = (Cell*) malloc(col*sizeof(Cell));  

   return array;  
}

int main(void)
{
	int NumRows = 10;
	int NumCols = 10;
	Cell ** world = Make2dArray(NumRows,NumCols);
	Fish firstfish = { .moved = 0, .SpawnTime = 3};
	world[0][9].fish = malloc(sizeof(firstfish));
	int i;
	int j;
	int x = 1;
	while(x != 0)
	{
		for(i=0; i < 10;i++)
		{

			for(j=0; j < 10;j++)
			{   
				if(world[i][j].fish != NULL)    
					world[i][j].fish->moved = 0;
			}

		}
		for(i=0; i < 10;i++)
		{

			for(j=0; j < 10;j++)
			{       
				FishUpdate(&world[i][j], &world, i, j, 9);   
			}

		}
	} 
	i = 0;
	for (i = 0; i < NumRows; i++){  
	free( world [i]);  
	}	  
	free(world); 

}

