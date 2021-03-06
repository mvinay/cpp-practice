#include "lists/ArrayList.h"
#include <gtest/gtest.h>

#include <algorithm>

using namespace ds;
using namespace utils;

class ArrayListTests : public ::testing::Test {
protected:
  virtual void SetUp() {
    v1.push_back(1);
    v2.push_back(2);
    v2.push_back(3);
  }

  // virtual void TearDown() {}

  ds::ArrayList<int> v0{};
  ds::ArrayList<int> v1{};
  ds::ArrayList<int> v2{};
};

TEST_F(ArrayListTests, InitVec) { ASSERT_EQ(0, v0.size()); }

TEST_F(ArrayListTests, PushBackTests) {
  ASSERT_EQ(1, v1.size());
  ASSERT_EQ(1, v1.at(0));
  ASSERT_EQ(1, v1.front());
  ASSERT_EQ(1, v1.back());
  ASSERT_EQ(1, v1[0]);

  ASSERT_EQ(2, v2.size());
  ASSERT_EQ(2, v2.at(0));
  ASSERT_EQ(3, v2.at(1));
  ASSERT_EQ(3, v2[1]);
}

TEST_F(ArrayListTests, InsertTests) {

  v0.insert(1, 0);
  ASSERT_EQ(1, v0.at(0));

  v1.prepend(5);
  ASSERT_EQ(5, v1.at(0));
  EXPECT_EQ(2, v1.size());

  v2.insert(4, 1);
  EXPECT_EQ(3, v2.at(2));
  EXPECT_EQ(4, v2.at(1));
  EXPECT_EQ(3, v2.size());
}

TEST_F(ArrayListTests, DeleteTests) {

  v0.insert(1, 0);
  EXPECT_EQ(1, v0.pop());
  EXPECT_EQ(0, v0.size());
  EXPECT_EQ(true, v0.empty());

  v1.prepend(5);
  EXPECT_EQ(5, v1.deleteAt(0));
  EXPECT_EQ(1, v1.at(0));
  EXPECT_EQ(1, v1.size());

  v2.insert(4, 1);
  EXPECT_EQ(4, v2.deleteAt(1));
  EXPECT_EQ(3, v2.at(1));
  EXPECT_EQ(2, v2.at(0));
  EXPECT_EQ(2, v2.size());

  v2.clear();
  EXPECT_EQ(0, v2.size());
}

TEST_F(ArrayListTests, CapacityTests) {
  EXPECT_EQ(true, (v1.capacity() > v1.size()));

  v2.resize(100);
  EXPECT_EQ(100, v2.capacity());
}

TEST_F(ArrayListTests, NegativeTests) {
  ASSERT_THROW(v0.at(1), std::out_of_range);
  ASSERT_THROW(v0[3], std::out_of_range);
  ASSERT_THROW(v0.pop(), std::out_of_range);
  ASSERT_THROW(v1.at(-1), std::out_of_range);
  ASSERT_THROW(v1.deleteAt(1000), std::out_of_range);
  ASSERT_THROW(v2.insert(1, 100), std::out_of_range);
  ASSERT_THROW(v2.resize(1), std::invalid_argument);
}

TEST_F(ArrayListTests, ReverseTests) {
  v2.reverse();
  EXPECT_EQ(3, v2[0]);
  EXPECT_EQ(2, v2[1]);
}

struct TestObj {

  int a, b, c;
};

TEST(GenericArrayListTest, AllTests) {
  ArrayList<TestObj> TestArrayList;

  TestObj test;
  test.a = 10;
  test.b = 11;
  test.c = 12;
  TestArrayList.push_back(test);

  TestObj test2;
  test2.a = 15;
  test2.b = 16;
  test2.c = 17;
  TestArrayList.push_back(test2);

  TestArrayList.reverse();
  EXPECT_EQ(15, TestArrayList[0].a);
  TestArrayList.reverse();

  TestArrayList.push_back(test);

  EXPECT_EQ(3, TestArrayList.size());

  EXPECT_EQ(10, TestArrayList[0].a);
  EXPECT_EQ(16, TestArrayList[1].b);
  EXPECT_EQ(12, TestArrayList[2].c);
}

TEST(IteratorTests, IteratorTests) {
  ds::ArrayList<int> vec(5);
  int n = 0;
  std::generate(vec.begin(), vec.end(), [&n] { return n++; });
  int val = 0;
  for (const auto I : vec) {
    EXPECT_EQ(val++, I);
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
