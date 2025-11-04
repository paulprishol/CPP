#include "test.h"

TEST(S21MatrixTest, Inverse_2x2) {
  S21Matrix A(2, 2);
  A(0, 0) = 4;
  A(0, 1) = 7;
  A(1, 0) = 2;
  A(1, 1) = 6;
  S21Matrix Inv = A.inverse_matrix();
  EXPECT_NEAR(Inv(0, 0), 0.6, 1e-7);
  EXPECT_NEAR(Inv(0, 1), -0.7, 1e-7);
  EXPECT_NEAR(Inv(1, 0), -0.2, 1e-7);
  EXPECT_NEAR(Inv(1, 1), 0.4, 1e-7);
}

TEST(S21MatrixTest, Inverse_ExceptionOnZeroDeterminant) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 2;
  A(1, 1) = 4;
  EXPECT_THROW(A.inverse_matrix(), std::logic_error);
}

TEST(S21MatrixTest, Inverse_ExceptionOnNonSquare) {
  S21Matrix A(2, 3);
  EXPECT_THROW(A.inverse_matrix(), std::logic_error);
}

TEST(S21MatrixTest, Zero_RowsCols_Inverse) {
  S21Matrix A(0, 0);
  EXPECT_THROW(A.inverse_matrix(), std::invalid_argument);
}