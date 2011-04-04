// Jason Wong, Gowtham Vijayaragavan, Meenal Tambe, Aaron Okano

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <curses.h>
#include "matrix.h"


//using namespace::std;


int arg_check(int argc);

int main(int argc, char *argv[])
{
  int check;
  char d;
  int rows, cols;
 // Matrix *data;
  if (argc != 4)// there will be 2 arguments
  {
    //rows and cols
    //
  } else {//checks the dimensions of the matrix
    rows = atoi(argv[2]);
    cols = atoi(argv[3]);
  }
  int data[rows][cols];
  if( check != 4)
  {
    //read from file
  } else {
    //make all entries 0
  }

  return 0;
}

int arg_check(int argc)
{
  if(argc == 4)
  {
    return 1;
  } else {
    return 0;
  }
}


