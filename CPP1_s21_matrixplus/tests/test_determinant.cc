#include "test.h"

TEST(S21MatrixTest, Determinant_2x2) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  double det = A.determinant();
  EXPECT_DOUBLE_EQ(det, -2.0);
}
TEST(S21MatrixTest, Determinant_ExceptionOnNonSquare) {
  S21Matrix A(2, 3);
  EXPECT_THROW(A.determinant(), std::logic_error);
}

TEST(S21MatrixTest, Determinant_4x4) {
  S21Matrix A(4, 4);

  A(0, 0) = 3;
  A(0, 1) = 2;
  A(0, 2) = 0;
  A(0, 3) = 1;
  A(1, 0) = 4;
  A(1, 1) = 0;
  A(1, 2) = 1;
  A(1, 3) = 2;
  A(2, 0) = 3;
  A(2, 1) = 0;
  A(2, 2) = 2;
  A(2, 3) = 1;
  A(3, 0) = 9;
  A(3, 1) = 2;
  A(3, 2) = 3;
  A(3, 3) = 1;

  double expected_det = 24.0;
  double det = A.determinant();

  EXPECT_NEAR(det, expected_det, 1e-7);
}

TEST(S21MatrixTest, Zero_RowsCols_Determinant) {
  S21Matrix A(0, 0);
  EXPECT_THROW(A.determinant(), std::invalid_argument);
}