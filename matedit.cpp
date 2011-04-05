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

int main(int argc, char *argv[])
{
  char d;
  int mrows = 0, mcols = 0;
  int i,j;
  string dstring;
	ofstream f;
 // Matrix *data;
  if (argc == 2)// there will be 2 arguments
  {
    mrows = 2;
    mcols = 2;//read from files
    
  } else {//checks the dimensions of the matrix
		f.open( argv[1], ios::out | ios::binary );
    mrows = atoi(argv[2]);
    mcols = atoi(argv[3]);
  }

  int **data = new int*[mrows];
	for( i = 0; i < mrows; i++ )
		data[i] = new int[mcols];
  if( check != 4)
  {
    for(i = 0; i < mrows; i++)
    {
      for(j=0; j < mcols; j++)
      {
        data[i][j] = 0;
      }
    }
  } else {
    for(i = 0; i < mrows; i++)
    {
      for(j = 0; i < mcols; j++)
      {
        data[i][j] = 12;
      }
    }
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
      c += 13;
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

  while(1)
  {
    d = getch();
		if(d == 's')
			saveFile( data, mrows, mcols, f );
    if(d == 'q')
      break;
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
