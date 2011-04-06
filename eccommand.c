nclude <curses.h>  // required
#include <stdlib.h>


int r,c,  // current row and column (upper-left is (0,0))
    nrows,  // number of rows in window
    ncols,  // number of columns in window
    rmax, cmax, c1;

int data[10][10];
char sentence[80];
char *tokenPtr;
char numstr[6];

void draw()

{  clear();
   int r, c, c1;
   r = 0; c = 0; c1 = 0;
   for (r=0; r < rmax; r++)
      {	for (c=0; c < cmax; c++) 
          {  sprintf(numstr, "%3d", data[r][c]);
             c1 = 4 * (1 + c);
             mvaddstr(r, c1, numstr); 
          }
      }
    refresh();
}


int main()

{  int i, j;    
   WINDOW *wnd;
   rmax = 3;
   cmax = 4;

   wnd = initscr();  // curses call to initialize window
   // cbreak();  // curses call to set no waiting for Enter key
   noecho();  // curses call to set no echoing
   getmaxyx(wnd,nrows,ncols);  // curses call to find size of window
   clear();  // curses call to clear screen, send cursor to position (0,0)
   refresh();  // curses call to implement all changes since last refresh

   r = 0; c = 0; c1 = 0;
   for (r=0; r < rmax; r++)
      {	for (c=0;c < cmax; c++) 
          {  data[r][c] = 0; 
          }
      }
   draw();

   r = 0; c = 0; c1 = 0;
   while (1)  {
      getstr(sentence);
      tokenPtr = strtok(sentence, " "); // begin tokenizing sentence

      if (strstr(sentence,"mc") != NULL) {
          tokenPtr = strtok(NULL, " ");  // read move cursor to row
          r = atoi(tokenPtr);

          tokenPtr = strtok(NULL, " ");  // read move cursor to col
          c = atoi(tokenPtr);
          c1 = 4 * (1 + c);

          move(r,c1);  // curses call to move cursor to row r, column c
          refresh();
      }
      else if (strstr(sentence,"ec") != NULL) {
          while (1)
          {
             tokenPtr = strtok(NULL, " ");
             if (tokenPtr == NULL) break;

             data[r][c] = atoi(tokenPtr);

             c++;
             if (c < cmax) 
             {
                 c1 = 4 * (1 + c);
             } else 
             {
                 r++;
                 if (r < rmax) 
                 {
                     c = 0; c1 = 0;
                 } else
                 {
                     r = 0; c = 0; c1 = 0; // reached beyond rmax hence reseting back to 0,0
                 }
             }
          }
          draw();
      } 
      else break;

    }

   endwin();  // curses call to restore the original window and leave
   return 0;





}
