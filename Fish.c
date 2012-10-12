#include <stdio.h>
#include <time.h>
#include <stdlib.h>
typedef struct{
char Type;
int SpawnTime;
int StarveTime;
}Cell;

typedef struct{
bool left;
bool right;
bool up;
bool down;
}Move;

bool CeckCell(Cell M)
{
	if (M.Type == 'e')
	{
		return true;
	}
	return false;
}

int main(void)
{
int NumRows = 10;
int NumCols = 10;
Cell world[NumRows][NumCols];
int i;
int j;
for(i=0 i < 10;i++)
{

	for(j=0 j < 10;j++)
	{       
		Move Available;
		if(i+1 > 10 || )
                {
                      Available.left = CheckCell(world[0][j]);
   		}
		else
		{
                      Available.left = CheckCell(world[i+1][j]);
		}

		CheckCell(world[i][j]);
                
		srand(time(NULL));
		int r = rand();
                
	}

}

}

