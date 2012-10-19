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
int moved;
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
int CheckIfEmtyShark(Cell * M)
{
	//return two if there is a fish to eat, 1 if there is a free space and 0 otherwise.
	if(M->shark == NULL && M->fish != NULL)
	{
		return 1;
	}
	if(M->shark == NULL && M->fish == NULL)
	{
		return 2;
	}
	return 0;
}
int ChooseCellShark(Move Available)
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
	//check to see if the shark can move to eat a fish before trying other movements.
	if(Available.left == 2 ||
		Available.right == 2 ||
		Available.up ==2 ||
		Available.down ==2)
	{
		while(x == 0)
		{
			srand(time(NULL));
			int r = rand() % 4;

			Dirrection = r;
			switch(r){
				case 0:
		   	 if(Available.left == 2)
					x = 1;
				break;
				case 1:
				if(Available.right == 2)
				x = 1;
				break;
				case 2:
				if(Available.up == 2)
				x = 1;
				break;
				case 3:
				if(Available.down == 2)
					x = 1;
				break;
			}
		}
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

void SharkMove(Cell * Moveto, Cell * currentCell){
	if(currentCell->shark->SpawnTime == 0)
	{
		currentCell->shark->SpawnTime = 3;
		Moveto->shark = malloc(sizeof(Shark));
		Moveto->shark->SpawnTime = 3;
		printf("Shark Spawned!!!!!!!! \n");
		
	}
	else
	{
		Moveto->shark = currentCell->shark;
		Moveto->shark->SpawnTime--;
		currentCell->shark = NULL;
	}
	
}

void SharkUpdate(Cell * currentCell, Cell *** tempworld, int x, int y, int range)
{   
	if(currentCell->shark != NULL && currentCell->shark->moved != 1)
	{
		currentCell->shark->moved = 1;
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
		Available.up = CheckIfEmtyShark(array[0]);
		Available.down = CheckIfEmtyShark(array[1]);
		Available.left = CheckIfEmtyShark(array[2]);
		Available.right = CheckIfEmtyShark(array[3]);
		int ChoosenCell = ChooseCellShark(Available);
		if (ChoosenCell != -1)
		{
			SharkMove(array[ChoosenCell], currentCell);
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
	Shark firstShark = {.SpawnTime = 3, .StarveTime = 2, .moved = 0};
	world[0][9].fish = malloc(sizeof(firstfish));
	world[0][9].shark = malloc(sizeof(firstShark));
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
				//FishUpdate(&world[i][j], &world, i, j, 9);
				SharkUpdate(&world[i][j], &world, i, j, 9);   
			}

		}
	} 
	i = 0;
	for (i = 0; i < NumRows; i++){  
	free( world [i]);  
	}	  
	free(world); 

}

