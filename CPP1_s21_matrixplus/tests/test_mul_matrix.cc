#include "test.h"

TEST(S21MatrixTest, MulMatrixBasic) {
  S21Matrix A(2, 3), B(3, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;
  B(0, 0) = 7;
  B(0, 1) = 8;
  B(1, 0) = 9;
  B(1, 1) = 10;
  B(2, 0) = 11;
  B(2, 1) = 12;
  A.mul_matrix(B);
  ASSERT_EQ(A.getrows(), 2);
  ASSERT_EQ(A.getcols(), 2);
  EXPECT_DOUBLE_EQ(A(0, 0), 58);
  EXPECT_DOUBLE_EQ(A(0, 1), 64);
  EXPECT_DOUBLE_EQ(A(1, 0), 139);
  EXPECT_DOUBLE_EQ(A(1, 1), 154);
}

TEST(S21MatrixTest, MulMatrixThrowOnSizeMismatch) {
  S21Matrix A(2, 3), B(2, 2);
  EXPECT_THROW(A.mul_matrix(B), std::invalid_argument);
}

TEST(S21MatrixTest, OperatorMulEqual) {
  S21Matrix A(2, 2), B(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  B(0, 0) = 2;
  B(0, 1) = 0;
  B(1, 0) = 1;
  B(1, 1) = 2;
  A *= B;
  EXPECT_DOUBLE_EQ(A(0, 0), 4);
  EXPECT_DOUBLE_EQ(A(0, 1), 4);
  EXPECT_DOUBLE_EQ(A(1, 0), 10);
  EXPECT_DOUBLE_EQ(A(1, 1), 8);
}

TEST(S21MatrixTest, OperatorMulEqualThrowOnSizeMismatch) {
  S21Matrix A(2, 2), B(3, 3);
  EXPECT_THROW(A *= B, std::invalid_argument);
}

TEST(S21MatrixTest, OperatorMul) {
  S21Matrix A(1, 3), B(3, 1);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  B(0, 0) = 4;
  B(1, 0) = 5;
  B(2, 0) = 6;
  S21Matrix C = A * B;
  ASSERT_EQ(C.getrows(), 1);
  ASSERT_EQ(C.getcols(), 1);
  EXPECT_DOUBLE_EQ(C(0, 0), 32);
  EXPECT_DOUBLE_EQ(A(0, 0), 1);
  EXPECT_DOUBLE_EQ(B(2, 0), 6);
}

TEST(S21MatrixTest, OperatorMulThrowOnSizeMismatch) {
  S21Matrix A(2, 3), B(2, 2);
  EXPECT_THROW({ S21Matrix C = A * B; }, std::invalid_argument);
}