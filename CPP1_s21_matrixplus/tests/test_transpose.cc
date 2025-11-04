#include "test.h"

TEST(S21MatrixTest, Transpose_3x2) {
  S21Matrix A(3, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A(2, 0) = 5;
  A(2, 1) = 6;
  S21Matrix T = A.transpose();
  EXPECT_EQ(T.getrows(), 2);
  EXPECT_EQ(T.getcols(), 3);
  EXPECT_EQ(T(0, 0), 1);
  EXPECT_EQ(T(1, 0), 2);
  EXPECT_EQ(T(0, 1), 3);
  EXPECT_EQ(T(1, 1), 4);
  EXPECT_EQ(T(0, 2), 5);
  EXPECT_EQ(T(1, 2), 6);
}
