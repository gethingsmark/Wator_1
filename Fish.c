#include <stdio.h>
#include <time.h>
#include <stdlib.h>


typedef struct{
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

int CheckIfEmty(Cell *M)
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
		int r = rand() / 3;
		Dirrection = r;
		switch(r){
			case(0):
		    if(Available.left == 1)
				x = 1;
			break;
			case(1):
			if(Available.right == 1)
				x = 1;
			break;
			case(2):
			if(Available.up == 1)
				x = 1;
			break;
			case(3):
			if(Available.down == 1)
				x = 1;
			break;
		}
	}
	return Dirrection;
}

void FishMove(Cell* Moveto, Cell* fish){
	if(fish->fish->SpawnTime == 0)
	{
		fish->fish->SpawnTime = 3;
		Moveto->fish = malloc(sizeof(Fish));
		Moveto->fish->SpawnTime = 3;
		
	}
	else
	{
		Moveto->fish = fish->fish;
		Moveto->fish->SpawnTime--;
		fish->fish = NULL;
	}
	
}

void FishUpdate(Cell * fish, Cell** tempworld, int x, int y, int range)
{   
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
	Cell * array[4] = {tempworld[x][top],tempworld[x][bot],tempworld[left][y],tempworld[right][y]}
	Available.up = CheckCell(array[0])
	Available.down = CheckCell(array[1])
	Available.left = CheckCell(array[2])
	Available.right = CheckCell(array[3])
	int ChoosenCell = ChooseCell(Available)
	if (ChooseCell != -1)
	{
		FishMove(array[ChooseCell], fish);
	}
}

int main(void)
{
	int NumRows = 10;
	int NumCols = 10;
	Cell world[NumRows][NumCols];
	int i;
	int j;
	for(i=0; i < 10;i++)
	{

		for(j=0; j < 10;j++)
		{       
			FishUpdate(world[i][j], world, i, j, 9);   
		}

	}

}

