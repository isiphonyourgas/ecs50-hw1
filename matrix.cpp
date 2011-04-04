
#include <iostream>
#include "matrix.h"

Matrix :: Matrix() {}
Matrix :: Matrix (int a, int b)
{
  rows = a;
  cols = b;
  content = new int *[a];
  for(int i = 0; i < a; i++)
  {
    content[i] = new int(b);
  }
}

int Matrix :: get(int r_index, int c_index) const
{
  return content[r_index][c_index];
}

void Matrix :: set(int r_index, int c_index, int value)
{
  content[r_index][c_index] = value;
}


/*void Matrix :: clear()
{
  int i, j;
  for(i = 0; i < rows; i++)
  {
    for(j = 0; j < rows; j++)
    {
      this->set(i,j,0);
    }
  }
}*/
