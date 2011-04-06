// Aaron Okano, Jason Wong, Gowtham Vijayaragavan, Meenal Tambe

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <curses.h>
#include <string>
#include <sstream>

using namespace std;

// row and col variables are the current row and col in the matrix
// topr and topc are the row and col of the top left position
// nrows and ncols are the max rows/cols per screen
int row, col, topr, topc, nrows, ncols;

// r() and c() convert the current position in the matrix to
// the position of the cursor when it's aligned with the current box
inline int r(int arg = row) { return arg - topr; }

inline int c(int arg = col) { return (arg - topc + 1) * 12; }

// reads in the data file
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

// saves the data file
void saveFile( int *data[], int mrows, int mcols, ofstream &file )
{
  int i,j;
  // write rows and columns first
  file.write((char*)&mrows,4);
  file.write((char*)&mcols,4);

  // write actual data
  for( i = 0; i < mrows; i++ )
  {
    for( j = 0; j < mcols; j++ )
    {
      file.write((char*)&data[i][j], 4);
    }
  }
}

// create new matrix filled with zeros
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

void draw( int *data[], int tr, int tc, int mrows, int mcols )
{
	int tmprow = row;
	int tmpcol = col;
  topr = tr;
	topc = tc;
  stringstream ss;
  int i, j;
  string dstring;
  // Here we make a string (dstring) of spaces with a length of 12
  // and then replace the last spaces with the number stored in
  // the matrix array.
  for(i = topr; i < (nrows < mrows-topr ? nrows + topr : mrows); i++)
  {
    for(j = topc; j < (ncols < mcols-topc ? ncols + topc : mcols); j++)
    {
      dstring = "            ";
      ss << data[i][j];
      dstring += ss.str();
      dstring = dstring.substr(ss.str().length(), 12);
      addstr(dstring.c_str());
      tmpcol++;
      move(r(tmprow),c(tmpcol)-11);
      refresh();
      // reset the stream
      ss.flush();
      ss.str("");
    }
    tmprow++;
    tmpcol = 0;
    move(r(tmprow),c(tmpcol)-11);
    ss.str("");
  }
}

// main function. tests whether a file exists. open and reads the existing file.
int main(int argc, char *argv[])
{
  char d; // used with getch
  int mrows = 0, mcols = 0;
  //int i,j, 
  int **data;
  string dstring;
  string cmd, cmd_part;
  ofstream f;
  ifstream p;
  if (argc == 2)// there will be 2 arguments
  {
    p.open( argv[1], ios::in | ios::binary );
    // if the file doesn't exist.
    if( !p )
    {
      cout << "There is no file " << argv[1] << "." << endl;
      return 0;
    }
    // reads in the file and the user inputs for rows and columns
    data = readFile( mrows, mcols, p );
    p.close(); 
  } 
  else 
  {
    //checks the dimensions of the matrix
    mrows = atoi(argv[2]);
    mcols = atoi(argv[3]);
    data = newMatrix( mrows, mcols );
  }
  // using ncurses for the display in the new window
  WINDOW *wnd;
  wnd = initscr();
  //getmaxyx(wnd,nrows,ncols);
	nrows = LINES - 1; // How many rows or columns of the
	ncols = COLS/12;  // matrix can fit on one screen
  clear();
  noecho();
  refresh();
  topr = 0; topc = 0;
	row = 0; col = 0;

	move(r(), c()-11);
	draw( data, 0, 0, mrows, mcols );

  move(r(),c());

  // set to blank to start
  cmd = "";
  // loop to create original commands to save the file and exit
  while(1)
  {
    // d will be added to the cmd string if it's not '\n'
    d = getch();
    // when enter is pressed, process the characters stored in cmd
    if( d == '\n')
    {
      // command for "save and exit"
      if(cmd == "sve")
      {
        f.open( argv[1], ios::out | ios::binary );
        saveFile( data, mrows, mcols, f );
        f.close();
        break;
      }
     // move the cursor
      else if(cmd.substr(0,2) == "mc")
      {
        // make a stream from cmd, ignore the "mc" portion
        // and then read in the integers that follow into
        // row and col
        stringstream command;
        command << cmd;
        command.ignore( 3, ' ');
        command >> row;
        command >> col;
				row--; col--; // because position (1,1) should be (0,0)
				if( row > topr + nrows || col > topc + ncols )
				  draw( data, row, col, mrows, mcols );
			  else if( row < topr || col < topc )
				  draw( data, row, col, mrows, mcols );
        // move to correct position
        move( r(), c() );
      }
      else
      {
        // go back to beginning of loop if something went wrong
        continue;
      }
      cmd = ""; // reset cmd
    } 
    else
    {  
      // if enter is not pressed, add the character to cmd
      cmd += d;
      }
  } 
  endwin();
  return 0;
}

