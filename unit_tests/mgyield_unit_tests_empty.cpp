#include <iostream>
#include <iomanip>
#include <string>

#include <clocale>
#include <stdexcept>
#include <gtest/gtest.h>

#include "mgyield.h"

TEST(ConstructorDestructor, Empty)
{
  ::mg::yield_generator<int> g;
  EXPECT_TRUE(g.is_empty());
}

TEST(ConstructorDestructor, EmptyGenerator_01)
{
  ::mg::yield_generator<int> g([](const mg::yield_operator<int>&){});
  EXPECT_FALSE(g.is_empty());
}

TEST(ConstructorDestructor, EmptyGenerator_02)
{
  ::mg::yield_generator<int> g([](const mg::yield_operator<int>&, int){}, 1);
  EXPECT_FALSE(g.is_empty());
}

TEST(ConstructorDestructor, EmptyGenerator_03)
{
  int i{0};
  ::mg::yield_generator<int> g([](const mg::yield_operator<int>&, int&){}, ::std::ref(i));
  EXPECT_FALSE(g.is_empty());
}

TEST(ConstructorDestructor, EmptyGenerator_04)
{
  int i{0};
  ::std::string s;
  ::mg::yield_generator<int> g([](const mg::yield_operator<int>&, int&, const ::std::string&){}, ::std::ref(i), s);
  EXPECT_FALSE(g.is_empty());
}

TEST(Next, Empty)
{
  ::mg::yield_generator<int> g;
  EXPECT_TRUE(g.is_empty());
  EXPECT_FALSE(g.is_finished());
  EXPECT_FALSE(g.next());
}

TEST(Next, EmptyGenerator_01)
{
  ::mg::yield_generator<int> g([](const mg::yield_operator<int>&){});
  EXPECT_FALSE(g.is_empty());
  EXPECT_FALSE(g.is_finished());

  EXPECT_FALSE(g.next());
  EXPECT_TRUE(g.is_finished());
}

TEST(Next, EmptyGenerator_02)
{
  bool generator_called{false};
  ::mg::yield_generator<int> g([&generator_called](const mg::yield_operator<int>&){generator_called = true;});
  EXPECT_FALSE(g.is_empty());
  EXPECT_FALSE(g.is_finished());
  EXPECT_FALSE(generator_called);

  EXPECT_FALSE(g.next());
  EXPECT_TRUE(g.is_finished());
  EXPECT_TRUE(generator_called);
}

TEST(Next, EmptyGenerator_03)
{
  ::mg::yield_generator<int> g([](const mg::yield_operator<int>&){throw ::std::runtime_error("Test exception");});
  EXPECT_FALSE(g.is_empty());
  EXPECT_FALSE(g.is_finished());

  EXPECT_THROW(g.next(), ::std::runtime_error);
  EXPECT_TRUE(g.is_finished());

  EXPECT_FALSE(g.next());
}
