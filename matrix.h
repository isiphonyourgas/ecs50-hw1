#ifndef MATRIX_H
#define mATRIX_H


using namespace std;

class Matrix
{
public:
  Matrix();
  Matrix(int a, int b);
  int get(int r_index, int c_index) const;
  void set(int r_index, int c_index, int value);
  //void clear();
private:
  int rows, cols;
  int **content;
};

#endif
