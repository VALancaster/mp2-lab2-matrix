#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, cant_create_matrix_with_null_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(0));
}

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(m);

	ASSERT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(m);

	m1[0][0] = 100;

	ASSERT_NE(m[0][0], m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(10);

	ASSERT_EQ(10, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(10);

	m[0][0] = 25;

	EXPECT_EQ(m[0][0], 25);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(10);

	ASSERT_ANY_THROW(m.at(-5).at(-5) = 25);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(10);

	ASSERT_ANY_THROW(m.at(1000).at(1000) = 25);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(10);

	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(10);

	ASSERT_NO_THROW(m1 = m);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(20);

	m1 = m;

	EXPECT_EQ(m.size(), m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(20);
	TDynamicMatrix<int> m1(10);

	ASSERT_NO_THROW(m = m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(10);

	EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(10);

	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(20);

	EXPECT_TRUE(m != m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicVector<int> m(5);
	TDynamicVector<int> m1(5);

	ASSERT_NO_THROW(m + m1);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicVector<int> m(5);
	TDynamicVector<int> m1(7);

	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicVector<int> m(5);
	TDynamicVector<int> m1(5);

	ASSERT_NO_THROW(m - m1);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicVector<int> m(5);
	TDynamicVector<int> m1(7);

	ASSERT_ANY_THROW(m - m1);
}

TEST(TDynamicMatrix, can_multiply_matrixes_with_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(2);

	m[0][0] = 1; m[0][1] = 2;
	m[1][0] = 3; m[1][1 ] = 4;

	m1[0][0] = 5; m1[0][1] = 6;
	m1[1][0] = 7; m1[1][1] = 8;

	m2[0][0] = 19; m2[0][1] = 22;
	m2[1][0] = 43; m2[1][1] = 50;
	
	ASSERT_EQ(m2, m * m1);
}

TEST(TDynamicMatrix, cant_multiply_matrixes_with_not_equal_size)
{
	TDynamicVector<int> m(5);
	TDynamicVector<int> m1(7);

	ASSERT_ANY_THROW(m * m1);
}

TEST(TDynamicMatrix, can_move_matrix)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(10);
	for (size_t i = 0; i < 10; i++)
		for (size_t j = 0; j < 10; j++)
		{
			m[i][j] = i * 10 + j;
			m1[i][j] = i * 10 + j;
		}

	TDynamicMatrix<int> m2(std::move(m1));

	ASSERT_EQ(m1.size(), 0);
	ASSERT_EQ(m2.size(), 10);
	ASSERT_EQ(m, m2);
}

TEST(TDynamicMatrix, can_move_assign_matrix)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(10);
	TDynamicMatrix<int> m2(1);
	for (size_t i = 0; i < 10; i++) 
		for (size_t j = 0; j < 10; j++)
		{
			m[i][j] = i * 10 + j;
			m1[i][j] = i * 10 + j;
		}

	m2 = std::move(m1);

	ASSERT_EQ(m1.size(), 0);
	ASSERT_EQ(m2.size(), 10);
	ASSERT_EQ(m, m2);
}
