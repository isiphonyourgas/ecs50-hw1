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
cout <<" Test\n";
  check = arg_check(argc);
  if (check != 0)
  {
    //read_matrix();
  } else {//matrix is initialized
    
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


