// Aaron Okano, Jason Wong, Gowtham Vijayaragavan, Meenal Tambe

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <curses.h>
#include <string>
#include <sstream>

using namespace std;

int rows, cols, r, c;

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

// main function. tests whether a file exists. open and reads the existing file.
int main(int argc, char *argv[])
{
  char d; // used with getch
  int mrows = 0, mcols = 0;
  int i,j, rtemp, ctemp;
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
  getmaxyx(wnd,rows,cols);
  clear();
  noecho();
  refresh();

  move(r,c);
  stringstream ss;
  // Here we make a string (dstring) of spaces with a length of 12
  // and then replace the last spaces with the number stored in
  // the matrix array.
  for(i = 0; i < mrows; i++)
  {
    for(j = 0; j < mcols; j++)
    {
      dstring = "            ";
      ss << data[i][j];
      dstring += ss.str();
      dstring = dstring.substr(ss.str().length(), 12);
      addstr(dstring.c_str());
      c += 12;
      move(r,c);
      refresh();
      // reset the stream
      ss.flush();
      ss.str("");
    }
    r++;
    c = 0;
    move(r,c);
    ss.str("");
  }
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
        // rtemp and ctemp
        stringstream command;
        command << cmd;
        command.ignore( 3, ' ');
        command >> rtemp;
        command >> ctemp;
        // adjust to the "true" dimensions of the matrix
        r = rtemp - 1;
        c = (ctemp * 12) - 1;
        // move to correct position
        move( r  , c);
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

