#include "test.h"

TEST(S21MatrixTest, Equal_2x2) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = B(0, 0) = 1.0;
  A(0, 1) = B(0, 1) = 2.0;
  A(1, 0) = B(1, 0) = 3.0;
  A(1, 1) = B(1, 1) = 4.0;

  EXPECT_TRUE(A.eq_matrix(B));
  EXPECT_TRUE(A == B);
}

TEST(S21MatrixTest, NotEqual_DifferentSizes) {
  S21Matrix A(2, 3);
  S21Matrix B(3, 2);

  EXPECT_FALSE(A.eq_matrix(B));
  EXPECT_FALSE(A == B);
}

TEST(S21MatrixTest, NotEqual_OneDifferentElement) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);

  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j) A(i, j) = B(i, j) = i * 3 + j;

  B(1, 1) += 1.0;

  EXPECT_FALSE(A.eq_matrix(B));
  EXPECT_FALSE(A == B);
}

TEST(S21MatrixTest, Equal_4x4) {
  S21Matrix A(4, 4);
  S21Matrix B(4, 4);

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j) A(i, j) = B(i, j) = static_cast<double>(i + j);

  EXPECT_TRUE(A.eq_matrix(B));
  EXPECT_TRUE(A == B);
}

TEST(S21MatrixTest, Equal_Approximate) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = 1.0000001;
  B(0, 0) = 1.0000002;
  A(0, 1) = 2.0;
  B(0, 1) = 2.0;
  A(1, 0) = 3.0;
  B(1, 0) = 3.0;
  A(1, 1) = 4.0;
  B(1, 1) = 4.0;

  EXPECT_TRUE(A.eq_matrix(B));
  EXPECT_TRUE(A == B);
}

TEST(S21MatrixTest, EmptyMatricesEqual) {
  S21Matrix A;
  S21Matrix B;

  EXPECT_TRUE(A.eq_matrix(B));
  EXPECT_TRUE(A == B);
}