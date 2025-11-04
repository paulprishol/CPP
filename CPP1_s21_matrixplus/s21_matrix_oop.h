#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <cmath>
#include <cstring>
#include <iostream>

constexpr double APPROX = 1e-7;

class S21Matrix {
 private:
  int rows_, cols_;
  double* matrix_;

 public:
  // constructors and destructors

  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& o);
  S21Matrix(S21Matrix&& o);
  ~S21Matrix();

  // operator overloading

  S21Matrix& operator=(const S21Matrix& o);
  S21Matrix& operator=(S21Matrix&& o);
  bool operator==(const S21Matrix& o) const;
  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;
  S21Matrix& operator+=(const S21Matrix& o);
  S21Matrix operator+(const S21Matrix& o) const;
  S21Matrix& operator-=(const S21Matrix& o);
  S21Matrix operator-(const S21Matrix& o) const;
  S21Matrix& operator*=(const S21Matrix& o);
  S21Matrix& operator*=(const double num);
  S21Matrix operator*(const S21Matrix& o) const;
  S21Matrix operator*(const double num) const;
  friend S21Matrix operator*(double num, const S21Matrix& matrix);

  // operations

  bool eq_matrix(const S21Matrix& o) const;
  void sum_matrix(const S21Matrix& o);
  void sub_matrix(const S21Matrix& o);
  void mul_number(const double num);
  void mul_matrix(const S21Matrix& o);
  S21Matrix transpose();
  S21Matrix calc_complements();
  double determinant();
  S21Matrix inverse_matrix();
  S21Matrix minor(const int im, const int jm);

  int getrows() const;
  int getcols() const;
  void setrows(const int new_rows);
  void setcols(const int new_cols);
  void resize(const int new_rows, const int new_cols);
};

#endif
