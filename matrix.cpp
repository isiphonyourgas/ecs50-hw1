
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

int Matrix :: get(int r_index, int c_index)
{
  return content[r_index][c_index];
}
