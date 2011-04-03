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

bool arg_check(int argc, char *argv[])//will initialize a matrix
{
  int nrows, ncols;
  if (argc > 4)//Checks for the number of arguments
    {
    cout << "Error: Too many arguements in command line\n";
    return false;
    }
  if (argc == 3)//Checks for only 3 arguements
    {
    cout << "Error: Missing the number of columns in command line\n";
    return false;
    }
  if (argc == 1)//Checks for the number of arguments
    {
    cout << "Error: Missing filename\n";
    return false;
    }
  return true;// Arguements are correct
}//arg_check
