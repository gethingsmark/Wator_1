#include <stdio.h>
#include <time.h>
#include <stdlib.h>
typedef struct{
Shark* shark;
Fish* fish;
}Cell;

typedef struct{
int SpawnTime;
}Fish;

typedef struct{
int SpawnTime;
int StarveTime;
}Shark;

typedef struct{
bool left;
bool right;
bool up;
bool down;
}Move;

bool CheckIfEmty(Cell *M)
{
	if(*M.shark == NULL && *M.fish == NULL)
	{
		return true;
	}
	return false;
}
int ChooseCell(Move Available)
{
	bool x = false;
	int Dirrection;
	if (Available.left == false &&
		Available.right == false &&
		Available.up ==false &&
		Available.down ==false)
	{
		x = true
		Dirrection = -1;
	}
	while(x == false)
	{
		srand(time(NULL));
		int r = rand() / 3;
		Dirrection = r;
		switch(r){
			case(0):
		    if(Available.left == true)
				x = true;
			break;
			case(1):
			if(Available.right == true)
				x = true;
			break;
			case(2):
			if(Available.up == true)
				x = true;
			break;
			case(3):
			if(Available.down == true)
				x = true;
			break;
		}
	}
	return Dirrection;
}

void FishMove(Cell* Moveto, Cell* fish){
	if(*fish.SpawnTime == 0)
	{
		fish.SpawnTime = 3;
		Moveto.fish = new Fish;
		*(Moveto.fish).SpawnTime = 3;
		return;
	}
	Moveto.fish = fish.fish;
	*(Moveto.fish).SpawnTime--;
	fish.fish = NULL;
}

void FishUpdate(Cell * fish, cell[][] * tempworld, int x, int y, int range)
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
Cell * world[NumRows][NumCols];
int i;
int j;
for(i=0 i < 10;i++)
{

	for(j=0 j < 10;j++)
	{       
		FishUpdate(world[i][j], world, i, j, 9);   
	}

}

}

