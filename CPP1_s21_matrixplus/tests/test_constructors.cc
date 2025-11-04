#include "test.h"

TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.getrows(), 0);
  EXPECT_EQ(m.getcols(), 0);
}

TEST(S21MatrixTest, ParamConstructorValid) {
  S21Matrix m(3, 4);
  EXPECT_EQ(m.getrows(), 3);
  EXPECT_EQ(m.getcols(), 4);
}

TEST(S21MatrixTest, ParamConstructorInvalid) {
  EXPECT_THROW(S21Matrix(-1, 2), std::out_of_range);
  EXPECT_THROW(S21Matrix(2, -5), std::out_of_range);
}

TEST(S21MatrixTest, ConstOperatorAccess) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.5;
  A(0, 1) = 2.5;
  A(1, 0) = 3.5;
  A(1, 1) = 4.5;
  const S21Matrix& B = A;
  EXPECT_DOUBLE_EQ(B(0, 0), 1.5);
  EXPECT_DOUBLE_EQ(B(0, 1), 2.5);
  EXPECT_DOUBLE_EQ(B(1, 0), 3.5);
  EXPECT_DOUBLE_EQ(B(1, 1), 4.5);
}

TEST(S21MatrixTest, AssignmentOperator) {
  S21Matrix m(2, 2);
  S21Matrix new_m(1, 1);
  new_m = m;
  EXPECT_EQ(new_m, m);
}

TEST(S21MatrixTest, ParamOperatorInvalid) {
  S21Matrix m(2, 2);
  const S21Matrix& const_m = m;
  EXPECT_THROW(m(3, 3), std::out_of_range);
  EXPECT_THROW(const_m(3, 3), std::out_of_range);
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;
  S21Matrix copy(m);
  EXPECT_EQ(copy.getrows(), 2);
  EXPECT_EQ(copy.getcols(), 2);
  EXPECT_DOUBLE_EQ(copy(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(copy(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(copy(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(copy(1, 1), 4.0);
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.5;
  S21Matrix moved(std::move(m));
  EXPECT_EQ(moved.getrows(), 2);
  EXPECT_EQ(moved.getcols(), 2);
  EXPECT_DOUBLE_EQ(moved(0, 0), 1.5);
  EXPECT_EQ(m.getrows(), 0);
  EXPECT_EQ(m.getcols(), 0);
}

TEST(S21MatrixTest, SetRowsLarger) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m.setrows(4);
  EXPECT_EQ(m.getrows(), 4);
  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
}

TEST(S21MatrixTest, SetRowsSmaller) {
  S21Matrix m(3, 2);
  m(0, 0) = 1.0;
  m.setrows(2);
  EXPECT_EQ(m.getrows(), 2);
  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
}

TEST(S21MatrixTest, SetColsLarger) {
  S21Matrix m(2, 2);
  m(0, 0) = 5.0;
  m.setcols(3);
  EXPECT_EQ(m.getcols(), 3);
  EXPECT_DOUBLE_EQ(m(0, 0), 5.0);
}

TEST(S21MatrixTest, SetColsSmaller) {
  S21Matrix m(2, 3);
  m(0, 2) = 7.0;
  m.setcols(2);
  EXPECT_EQ(m.getcols(), 2);
}

TEST(S21MatrixTest, SetParamInvalid) {
  S21Matrix m(2, 2);
  EXPECT_THROW(m.setcols(-5), std::invalid_argument);
  EXPECT_THROW(m.setrows(-1), std::invalid_argument);
}