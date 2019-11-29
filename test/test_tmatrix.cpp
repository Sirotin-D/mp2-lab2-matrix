#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> A(2);
	A[0][0] = 1; A[0][1] = 2;
	A[1][1] = 3;
	TMatrix<int> B(A);
	EXPECT_EQ(A, B);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> A(2);
	A[0][0] = 1; A[0][1] = 2;
	A[1][1] = 3;
	TMatrix<int> B(A);
	EXPECT_NE(&A, &B);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> A(2);
	EXPECT_EQ(2, A.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> A(1);
	A[0][0] = 1;
	EXPECT_EQ(1, A[0][0]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> A(2);
	ASSERT_ANY_THROW(A[-1][-1]);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> A(2);
	ASSERT_ANY_THROW(A[3][3]);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> A(2);
	ASSERT_NO_THROW(A = A);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> A(1);
	A[0][0] = 1;
	TMatrix<int> B(1);
	B[0][0] = 11;
	A = B;
	TMatrix<int> EXP(1);
	EXP[0][0] = 11;
	EXPECT_EQ(EXP, A);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> A(1);
	TMatrix<int> B(2);
	A = B;
	EXPECT_EQ(2, A.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> A(1);
	TMatrix<int> B(2);
	B[0][0] = 0; B[0][1] = 1;
	B[1][1] = 2;
	A = B;
	TMatrix<int> EXP(2);
	EXP[0][0] = 0; EXP[0][1] = 1;
	EXP[1][1] = 2;
	EXPECT_EQ(EXP, A);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> A(2);
	A[0][0] = 0; A[0][1] = 1;
	A[1][1] = 2;
	TMatrix<int> B(A);
	EXPECT_EQ(true, A == B);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> A(1);
	EXPECT_EQ(true, A == A);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> A(1);
	TMatrix<int> B(2);
	EXPECT_EQ(true, A != B);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> A(2);
	A[0][0] = 0; A[0][1] = 1;
	A[1][1] = 2;
	TMatrix<int> B(A);
	TMatrix<int> EXP(2);
	EXP[0][0] = 0; EXP[0][1] = 2;
	EXP[1][1] = 4;
	EXPECT_EQ(EXP, A + B);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> A(1);
	TMatrix<int> B(2);
	ASSERT_ANY_THROW(A + B);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> A(2);
	A[0][0] = 0; A[0][1] = 1;
	A[1][1] = 2;
	TMatrix<int> B(2);
	B[0][0] = 1; B[0][1] = 3;
	B[1][1] = 5;
	TMatrix<int> EXP(2);
	EXP[0][0] = -1; EXP[0][1] = -2;
	EXP[1][1] = -3;
	EXPECT_EQ(EXP, A - B);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> A(1);
	TMatrix<int> B(2);
	ASSERT_ANY_THROW(A - B);
}

