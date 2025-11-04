#include "test.h"

TEST(S21MatrixTest, MulNumberBasic) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A.mul_number(2.0);
  EXPECT_DOUBLE_EQ(A(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(A(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 8.0);
}

TEST(S21MatrixTest, MulNumberZero) {
  S21Matrix A(1, 3);
  A(0, 0) = -1.5;
  A(0, 1) = 0.5;
  A(0, 2) = 10;
  A.mul_number(0.0);
  EXPECT_DOUBLE_EQ(A(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(A(0, 2), 0.0);
}

TEST(S21MatrixTest, MulNumberNegative) {
  S21Matrix A(1, 2);
  A(0, 0) = 3;
  A(0, 1) = -4;
  A.mul_number(-2);
  EXPECT_DOUBLE_EQ(A(0, 0), -6);
  EXPECT_DOUBLE_EQ(A(0, 1), 8);
}

TEST(S21MatrixTest, OperatorMulEqualNumber) {
  S21Matrix A(2, 1);
  A(0, 0) = 1.5;
  A(1, 0) = -2.0;
  A *= 3.0;
  EXPECT_DOUBLE_EQ(A(0, 0), 4.5);
  EXPECT_DOUBLE_EQ(A(1, 0), -6.0);
}

TEST(S21MatrixTest, OperatorMulNumber) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  S21Matrix B = A * 0.5;
  EXPECT_DOUBLE_EQ(B(0, 0), 0.5);
  EXPECT_DOUBLE_EQ(B(0, 1), 1.0);
  EXPECT_DOUBLE_EQ(B(1, 0), 1.5);
  EXPECT_DOUBLE_EQ(B(1, 1), 2.0);
  EXPECT_DOUBLE_EQ(A(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 4.0);
}

TEST(S21MatrixTest, OperatorMulNumberCommutativity) {
  S21Matrix A(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  S21Matrix B = 0.5 * A;
  EXPECT_DOUBLE_EQ(B(0, 0), 0.5);
  EXPECT_DOUBLE_EQ(B(0, 1), 1.0);
  EXPECT_DOUBLE_EQ(B(1, 0), 1.5);
  EXPECT_DOUBLE_EQ(B(1, 1), 2.0);
  EXPECT_DOUBLE_EQ(A(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 4.0);
}