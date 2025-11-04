#include "test.h"

TEST(S21MatrixTest, SubMatrixBasic) {
  S21Matrix A(2, 2), B(2, 2);
  A(0, 0) = 5.0;
  A(0, 1) = 6.0;
  A(1, 0) = 7.0;
  A(1, 1) = 8.0;
  B(0, 0) = 1.0;
  B(0, 1) = 2.0;
  B(1, 0) = 3.0;
  B(1, 1) = 4.0;

  A.sub_matrix(B);
  EXPECT_DOUBLE_EQ(A(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(A(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 4.0);
}

TEST(S21MatrixTest, SubMatrixThrowOnSizeMismatch) {
  S21Matrix A(2, 2), B(1, 2), C(2, 2);
  EXPECT_THROW(A.sub_matrix(B), std::invalid_argument);
  EXPECT_THROW(C = A - B, std::invalid_argument);
  EXPECT_THROW(A -= B, std::invalid_argument);
}

TEST(S21MatrixTest, OperatorMinusEqual) {
  S21Matrix A(2, 2), B(2, 2);
  fill_matrix(A, 5.0);
  fill_matrix(B, 3.0);
  A -= B;
  EXPECT_DOUBLE_EQ(A(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 2.0);
}

TEST(S21MatrixTest, OperatorMinus) {
  S21Matrix A(2, 2), B(2, 2);
  fill_matrix(A, 6.0);
  fill_matrix(B, 1.0);
  S21Matrix C = A - B;
  EXPECT_DOUBLE_EQ(C(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(C(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(A(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(B(0, 0), 1.0);
}