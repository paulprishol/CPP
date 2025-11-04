#include "test.h"

TEST(S21MatrixTest, CalcComplements_2x2) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  S21Matrix C = A.calc_complements();
  EXPECT_EQ(C.getrows(), 2);
  EXPECT_EQ(C.getcols(), 2);
  EXPECT_EQ(C(0, 0), 4);
  EXPECT_EQ(C(0, 1), -3);
  EXPECT_EQ(C(1, 0), -2);
  EXPECT_EQ(C(1, 1), 1);
}

TEST(S21MatrixTest, CalcComplements_ExceptionOnNonSquare) {
  S21Matrix A(2, 3);
  EXPECT_THROW(A.calc_complements(), std::logic_error);
}

TEST(S21MatrixTest, CalcComplements_1x1) {
  S21Matrix A(1, 1);
  A(0, 0) = 5;
  S21Matrix C = A.calc_complements();
  EXPECT_EQ(C(0, 0), 1);
}

TEST(S21MatrixTest, Minor_ExceptionOnNonSquare) {
  S21Matrix A(2, 3);
  EXPECT_THROW(A.minor(1, 1), std::logic_error);
}

TEST(S21MatrixTest, Zero_RowsCols_CalcComplements) {
  S21Matrix A(0, 0);
  EXPECT_THROW(A.calc_complements(), std::invalid_argument);
}