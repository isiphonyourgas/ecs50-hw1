// Jason Wong, Gowtham Vijayaragavan, Meenal Tambe, Aaron Okano

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <curses.h>
#include "matrix.h"
#include <string>
#include <sstream>

using namespace std;


//int arg_check(int argc);
//void load_matrix(int* data[], int mrows, int mcols);

int rows, cols, r, c;

int** readFile( int &mrows, int &mcols, ifstream &file )
{
  int i,j;
  // read in the rows and columns first
  file.read( reinterpret_cast<char*>(&mrows), 4);
  file.read( reinterpret_cast<char*>(&mcols), 4);
  int **data = new int*[mrows];
  for( i = 0; i < mrows; i++ )
    data[i] = new int[mcols];
  
  // read in the matrix in row-major order
  for( i = 0; i < mrows; i++ )
    for( j = 0; j < mcols; j++ )
      file.read( reinterpret_cast<char*>(&data[i][j]), 4);

  return data;
}

void saveFile( int *data[], int mrows, int mcols, ofstream &file )
{
  int i,j;
  // write rows and columns first
  file.write((char*)&mrows,4);
  file.write((char*)&mcols,4);

  for( i = 0; i < mrows; i++ )
  {
    for( j = 0; j < mcols; j++ )
    {
      file.write((char*)&data[i][j], 4);
    }
  }
}

int** newMatrix( int mrows, int mcols )
{
  int i,j;
  int **data = new int*[mrows];
  for( i = 0; i < mrows; i++ )
    data[i] = new int[mcols];
  for(i = 0; i < mrows; i++)
  {
    for(j=0; j < mcols; j++)
    {
      data[i][j] = 0;
    }
  }
  return data;
}


int main(int argc, char *argv[])
{
  char d;
  int mrows = 0, mcols = 0;
  int i,j, rtemp, ctemp;
  int **data;
  string dstring;
  string cmd, cmd_part;
  ofstream f;
  ifstream p;
 // Matrix *data;
  if (argc == 2)// there will be 2 arguments
  {
    p.open( argv[1], ios::in | ios::binary );
    if( !p )
    {
      cout << "There is no file " << argv[1] << "." << endl;
      return 0;
    }
    data = readFile( mrows, mcols, p );
    p.close(); 
  } 
  else 
  {
    //checks the dimensions of the matrix
    //f.open( argv[1], ios::out | ios::binary );
    mrows = atoi(argv[2]);
    mcols = atoi(argv[3]);
    data = newMatrix( mrows, mcols );
  }

  WINDOW *wnd;
  wnd = initscr();
  getmaxyx(wnd,rows,cols);
  clear();
  noecho();
  //cbreaks();
  refresh();
  

  //load_matrix(data, mrows, mcols);

  move(r,c);
 // char *d;
  stringstream ss;
  for(i = 0; i < mrows; i++)
  {
    for(j = 0; j < mcols; j++)
    {
      dstring = "            ";
      ss << data[i][j];
      dstring += ss.str();
      dstring = dstring.substr(ss.str().length(), 12);
      addstr(dstring.c_str());
      //addch(' ');
      c += 12;
      move(r,c);
      refresh();
      ss.flush();
      ss.str("");
    }
    r++;
    c = 0;
    move(r,c);
    ss.str("");
  }
  cmd = "";
  while(1)
  {
    d = getch();
    if( d == '\n')
    {
      if(cmd == "sve")
      {
        f.open( argv[1], ios::out | ios::binary );
        saveFile( data, mrows, mcols, f );
        f.close();
        break;
      }
      else if(cmd.substr(0,2) == "mc")
      {
        stringstream command;
        command << cmd;
        command.ignore( 3, ' ');
        command >> rtemp;
        command >> ctemp;
        r = rtemp - 1;
        c = (ctemp * 12) - 1;
        move( r  , c);
      }
      else
      {
        continue;
      }
      cmd = "";
    } else {  
      cmd += d;
    }
  } 
  endwin();
  return 0;
}

/*int arg_check(int argc)
{
  if(argc == 4)
  {
    return 1;
  } else {
    return 0;
  }
}*/

/*void load_matrix(int* data[], int mrows, int mcols)
{
  int i, j;
  move(r,c);
  char *d;
  for(i = 0; i < mrows; i++)
  {
    d = itoa(data[i][j]);
    addch(*d);
    c++;
    move(r,c);
    refresh();
  }
  

}*/
