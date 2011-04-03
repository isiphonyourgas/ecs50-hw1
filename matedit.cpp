// Jason Wong, Gowtham Vijayaragavan, Meenal Tambe, Aaron Okano

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <curses.h>


using namespace::std;

bool arg_check(int, char**);

int main(int argc, char *argv[])
{
  bool check;
  check = arg_check(argc, argv);
  if (check != 0)
  {
    cout << check << endl;;
  }
  return 0;
}

bool arg_check(int argc)
{
  if(argc == 4)
  {
    return false;
  } else {
    return true;
  }
}
