#include "test.h"

TEST(S21MatrixTest, SumMatrixBasic) {
  S21Matrix A(2, 2), B(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;
  B(0, 0) = 4.0;
  B(0, 1) = 3.0;
  B(1, 0) = 2.0;
  B(1, 1) = 1.0;
  A.sum_matrix(B);

  EXPECT_DOUBLE_EQ(A(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(A(1, 0), 5.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 5.0);
}

TEST(S21MatrixTest, SumMatrixThrowOnSizeMismatch) {
  S21Matrix A(2, 2), B(3, 3), C(3, 3);
  EXPECT_THROW(A.sum_matrix(B), std::invalid_argument);
  EXPECT_THROW(C = A + B, std::invalid_argument);
  EXPECT_THROW(A += B, std::invalid_argument);
}

TEST(S21MatrixTest, OperatorPlusEqual) {
  S21Matrix A(2, 2), B(2, 2);
  fill_matrix(A, 2.0);
  fill_matrix(B, 3.0);
  A += B;
  EXPECT_DOUBLE_EQ(A(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(B(1, 1), 3.0);
  EXPECT_DOUBLE_EQ(B(1, 0), 3.0);
}

TEST(S21MatrixTest, OperatorPlus) {
  S21Matrix A(2, 2), B(2, 2);
  fill_matrix(A, 1);
  fill_matrix(B, 2);
  S21Matrix C = A + B;
  EXPECT_DOUBLE_EQ(C(0, 0), 3);
  EXPECT_DOUBLE_EQ(C(1, 1), 3);
  EXPECT_DOUBLE_EQ(A(0, 0), 1);
  EXPECT_DOUBLE_EQ(B(0, 0), 2);
}
