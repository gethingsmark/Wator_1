#include <stdio.h>

int main(void)
{
  int NumRows = 10;
  int NumCols = 10;
  int grid[NumRows][NumCols];
  for (int j = 0; j < NumRows; j++)
    {
      for (int k = 0; k < NumCols; k++)
	{
	  printf("| |", grid[j][k]);
	}
      printf("\n");
    }
}
