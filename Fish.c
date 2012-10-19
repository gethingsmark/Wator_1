#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//Cell Structure
typedef struct{
Shark* shark;
Fish* fish;
}Cell;

//Fish Structure
typedef struct{
int SpawnTime;
}Fish;

//Shark Structure
typedef struct{
int SpawnTime;
int StarveTime;
}Shark;

//Move Structure hold the availbe places to move
typedef struct{
bool left;
bool right;
bool up;
bool down;
}Move;

//Checks if the pointers to the shark and fish in a give cell are null and
//returns true if they are both empty
bool CheckIfEmty(Cell *M)
{
	if(*M.shark == NULL && *M.fish == NULL)
	{
		return true;
	}
	return false;
}

//checks if there is anywere you can move too, if not then you return -1 to so the fish wont move
//if there are places that you can move then a random number is generated and saved to a dirrection variable 
//then checks if that dirrection that you wish to move in is availble
//if its not then repeats last step till one is found
//if it is then breaks loop and returns dirrection that we want to move in
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
	Available.up = CheckIfEmty(array[0])
	Available.down = CheckIfEmty(array[1])
	Available.left = CheckIfEmty(array[2])
	Available.right = CheckIfEmty(array[3])
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

