#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(0, 0) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 0 || cols < 0) {
    throw std::out_of_range("Incorrect input, invalid matrix");
  }
  if (rows == 0 || cols == 0) {
    matrix_ = nullptr;
  } else {
    matrix_ = new double[rows_ * cols_]();
    for (int i = 0; i < rows_ * cols_; i++) {
      matrix_[i] = 0.0;
    }
  }
}

S21Matrix::S21Matrix(const S21Matrix& o)
    : rows_(o.rows_), cols_(o.cols_), matrix_(new double[rows_ * cols_]) {
  std::copy(o.matrix_, o.matrix_ + rows_ * cols_, matrix_);
}

S21Matrix::S21Matrix(S21Matrix&& o)
    : rows_(o.rows_), cols_(o.cols_), matrix_(o.matrix_) {
  o.rows_ = o.cols_ = 0;
  o.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { delete[] matrix_; }

double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row * cols_ + col];
}

const double& S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row * cols_ + col];
}

S21Matrix& S21Matrix::operator=(const S21Matrix& o) {
  if (this != &o) {
    if (rows_ != o.rows_ || cols_ != o.cols_) {
      delete[] matrix_;
      rows_ = o.rows_;
      cols_ = o.cols_;
      matrix_ = new double[rows_ * cols_];
    }
    std::copy(o.matrix_, o.matrix_ + rows_ * cols_, matrix_);
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& o) {
  if (this != &o) {
    delete[] matrix_;
    rows_ = o.rows_;
    cols_ = o.cols_;
    matrix_ = o.matrix_;
    o.rows_ = o.cols_ = 0;
    o.matrix_ = nullptr;
  }
  return *this;
}

bool S21Matrix::eq_matrix(const S21Matrix& o) const {
  bool res = true;
  if (rows_ == o.rows_ && cols_ == o.cols_) {
    for (int i = 0; i < rows_ * cols_; i++) {
      if (fabs(matrix_[i] - o.matrix_[i]) > APPROX && res) {
        res = false;
      }
    }
  } else {
    res = false;
  }
  return res;
}

bool S21Matrix::operator==(const S21Matrix& o) const { return eq_matrix(o); }

void S21Matrix::sum_matrix(const S21Matrix& o) {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::invalid_argument(
        "Incorrect input, the matrices should have the same size");
  }
  for (auto i = 0; i < rows_ * cols_; i++) {
    matrix_[i] = matrix_[i] + o.matrix_[i];
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix& o) const {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::invalid_argument(
        "Incorrect input, the matrices should have the same size");
  }
  S21Matrix res(*this);
  res.sum_matrix(o);
  return res;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& o) {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::invalid_argument(
        "Incorrect input, the matrices should have the same size");
  }
  this->sum_matrix(o);
  return *this;
}

void S21Matrix::sub_matrix(const S21Matrix& o) {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::invalid_argument(
        "Incorrect input, the matrices should have the same size");
  }
  for (auto i = 0; i < rows_ * cols_; i++) {
    matrix_[i] = matrix_[i] - o.matrix_[i];
  }
}

S21Matrix S21Matrix::operator-(const S21Matrix& o) const {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::invalid_argument(
        "Incorrect input, the matrices should have the same size");
  }
  S21Matrix res(*this);
  res.sub_matrix(o);
  return res;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& o) {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::invalid_argument(
        "Incorrect input, the matrices should have the same size");
  }
  this->sub_matrix(o);
  return *this;
}

void S21Matrix::mul_number(const double num) {
  for (auto i = 0; i < rows_ * cols_; i++) {
    matrix_[i] = matrix_[i] * num;
  }
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix res(*this);
  res.mul_number(num);
  return res;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  this->mul_number(num);
  return *this;
}

void S21Matrix::mul_matrix(const S21Matrix& o) {
  if (cols_ != o.rows_) {
    throw std::invalid_argument(
        "Incorrect input, the columns of the first matrix should be equal to "
        "the rows of the second");
  }
  S21Matrix res(rows_, o.cols_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < o.cols_; j++) {
      double c = 0;
      for (auto k = 0; k < cols_; k++) {
        c += matrix_[k + i * cols_] * o.matrix_[k * o.cols_ + j];
      }
      res.matrix_[i * o.cols_ + j] = c;
    }
  }
  *this = res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& o) const {
  if (cols_ != o.rows_) {
    throw std::invalid_argument(
        "Incorrect input, the columns of the first matrix should be equal to "
        "the rows of the second");
  }
  S21Matrix res(*this);
  res.mul_matrix(o);
  return res;
}

S21Matrix operator*(double num, const S21Matrix& matrix) {
  return matrix * num;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& o) {
  if (cols_ != o.rows_) {
    throw std::invalid_argument(
        "Incorrect input, the columns of the first matrix should be equal to "
        "the rows of the second");
  }
  this->mul_matrix(o);
  return *this;
}

S21Matrix S21Matrix::transpose() {
  S21Matrix res(cols_, rows_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      res.matrix_[rows_ * j + i] = matrix_[j + cols_ * i];
    }
  }
  return res;
}

double S21Matrix::determinant() {
  if (cols_ != rows_) {
    throw std::logic_error("Incorrect input, the matrix should be square");
  } else if (cols_ == 0) {
    throw std::invalid_argument(
        "Incorrect input, the matrix should have rows and cols greater than 0");
  }
  double res = 0;
  if (cols_ == 1) {
    res = matrix_[0];
  } else if (cols_ == 2) {
    res = matrix_[0] * matrix_[3] - matrix_[1] * matrix_[2];
  } else {
    S21Matrix tmp = this->calc_complements();
    for (auto i = 0; i < rows_; i++) {
      res += matrix_[i] * tmp.matrix_[i];
    }
  }
  return res;
}

S21Matrix S21Matrix::calc_complements() {
  if (cols_ != rows_) {
    throw std::logic_error("Incorrect input, the matrix should be square");
  } else if (cols_ == 0) {
    throw std::invalid_argument(
        "Incorrect input, the matrix should have rows and cols greater than 0");
  }
  S21Matrix res(rows_, cols_);
  if (cols_ == 1) {
    res.matrix_[0] = 1;
  } else {
    for (auto i = 0; i < rows_; i++) {
      for (auto j = 0; j < cols_; j++) {
        S21Matrix minor_matrix = this->minor(i, j);
        double minor_det = minor_matrix.determinant();
        res.matrix_[i * rows_ + j] = minor_det * pow(-1, i + j);
      }
    }
  }
  return res;
}

S21Matrix S21Matrix::inverse_matrix() {
  if (cols_ != rows_) {
    throw std::logic_error("Incorrect input, the matrix should be square");
  }
  double det = this->determinant();
  if (det == 0) {
    throw std::invalid_argument(
        "Incorrect input, the determinant of the matrix should not be equal to "
        "0");
  }
  S21Matrix res(rows_, cols_);
  res = (this->calc_complements()).transpose() * (1.0 / det);
  return res;
}

S21Matrix S21Matrix::minor(const int im, const int jm) {
  if (cols_ != rows_) {
    throw std::logic_error("Incorrect input, the matrix should be square");
  }
  S21Matrix res(rows_ - 1, cols_ - 1);
  int ik = 0;
  for (auto i = 0; i < rows_; i++) {
    int jk = 0;
    for (auto j = 0; j < cols_; j++) {
      if (i != im && j != jm) {
        res.matrix_[ik * (rows_ - 1) + jk] = matrix_[i * rows_ + j];
        jk++;
      }
    }
    if (i != im) ik++;
  }
  return res;
}

int S21Matrix::getrows() const { return rows_; }

int S21Matrix::getcols() const { return cols_; }

void S21Matrix::setrows(const int new_rows) { resize(new_rows, cols_); }

void S21Matrix::setcols(const int new_cols) { resize(rows_, new_cols); }

void S21Matrix::resize(const int new_rows, const int new_cols) {
  if (new_rows < 0 || new_cols < 0) {
    throw std::invalid_argument("Incorrect input, invalid matrix");
  }
  S21Matrix tmp(new_rows, new_cols);
  int min_rows = std::min(rows_, new_rows);
  int min_cols = std::min(cols_, new_cols);
  for (auto i = 0; i < min_rows; i++) {
    for (auto j = 0; j < min_cols; j++) {
      tmp.matrix_[i * new_cols + j] = (*this)(i, j);
    }
  }
  *this = std::move(tmp);
}