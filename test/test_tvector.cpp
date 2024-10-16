#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, cant_create_vector_with_null_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(0));
}

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(20);
	TDynamicVector<int> v1(v);

	ASSERT_EQ(v1, v);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(20);
	for (size_t i = 0; i < 20; i++)
		v[i] = i;
	TDynamicVector<int> v1(v);

	v1[5] = 1000;

	ASSERT_NE(v[5], v1[5]);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);

	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);

  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(5);

	ASSERT_ANY_THROW(v.at(-5));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(5);

	ASSERT_ANY_THROW(v.at(999));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(20);

	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(15);
	TDynamicVector<int> v1(15);

	ASSERT_NO_THROW(v = v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1(5);

	v1 = v;

	EXPECT_EQ(v.size(), v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1(5);

	ASSERT_NO_THROW(v = v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1(10);
	for (size_t i = 0; i < 10; i++)
		v[i] = i;
	for (size_t i = 0; i < 10; i++)
		v1[i] = i;

	EXPECT_TRUE(v1 == v);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(10);
	for (size_t i = 0; i < 10; i++)
		v[i] = i;
	
	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1(8);

	EXPECT_TRUE(v != v1);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);

	int val = 2;

	v[0] = 1; v[1] = 7; v[2] = 3;
	v1[0] = 3; v1[1] = 9; v1[2] = 5;

	EXPECT_EQ(v1, v + val);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);

	int val = 2;

	v[0] = 3; v[1] = 9; v[2] = 5;
	v1[0] = 1; v1[1] = 7; v1[2] = 3;

	EXPECT_EQ(v1, v - val);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);

	int val = 2;

	v[0] = 3; v[1] = 9; v[2] = 5;
	v1[0] = 6; v1[1] = 18; v1[2] = 10;

	EXPECT_EQ(v1, v * val);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);

	v[0] = 1; v[1] = 1; v[2] = 1;
	v1[0] = 2; v1[1] = 2; v1[2] = 2;

	EXPECT_EQ(v1, v + v);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(2);

	ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);

	v[0] = 1; v[1] = 1; v[2] = 1;
	v1[0] = 0; v1[1] = 0; v1[2] = 0;

	EXPECT_EQ(v1, v - v);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(2);

	ASSERT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> v1(3);

	int val = 6;

	v[0] = 1; v[1] = 1; v[2] = 1;
	v1[0] = 2; v1[1] = 2; v1[2] = 2;

	EXPECT_EQ(val, v * v1);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1(5);

	ASSERT_ANY_THROW(v * v1);
}

TEST(TDynamicVector, can_move_vector)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < 5; ++i) {
		v[i] = i; v1[i] = i;
	}

	TDynamicVector<int> v2(std::move(v1));

	ASSERT_EQ(v1.size(), 0);
	ASSERT_EQ(v2.size(), 5);
	ASSERT_EQ(v, v2);
}

TEST(TDynamicVector, can_move_assign_vector)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(1);
	for (size_t i = 0; i < 5; ++i) {
		v[i] = i; v1[i] = i;
	}

	v2 = std::move(v1);

	ASSERT_EQ(v1.size(), 0);
	ASSERT_EQ(v2.size(), 5);
	ASSERT_EQ(v, v2);
}



