#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <disjoint_sets/quick_find.hpp>
#include <disjoint_sets/weighted_union_find_tree.hpp>

template <typename T>
struct disjoint_set_problem_slover
  : T
{
  disjoint_set_problem_slover(int n);
  auto is_equiv (int i, int j);
  auto unite (int i, int j);
};

// quick_find
template <>
disjoint_set_problem_slover<quick_find>::disjoint_set_problem_slover(int n)
  : quick_find::quick_find(n)
  {};

template <>
auto disjoint_set_problem_slover<quick_find>::is_equiv(int i, int j)
{
  return quick_find::is_equiv(i, j);
}

template <>
auto disjoint_set_problem_slover<quick_find>::unite(int i, int j)
{
  return quick_find::unite(i, j);
}

// weighted_union_find_tree
template <>
disjoint_set_problem_slover<weighted_union_find_tree<int>>::disjoint_set_problem_slover(int n)
  : weighted_union_find_tree<int>::weighted_union_find_tree(n)
  {};

template <>
auto disjoint_set_problem_slover<weighted_union_find_tree<int>>::is_equiv(int i, int j)
{
  return weighted_union_find_tree<int>::is_equiv(i, j);
}

template <>
auto disjoint_set_problem_slover<weighted_union_find_tree<int>>::unite(int i, int j)
{
  return weighted_union_find_tree<int>::unite(i, j, 0);
}


TEMPLATE_TEST_CASE
(
  "Disjoint Sets Test from the Sample Input of AOJ DSL_1_A",
  "[Union-find tree]",
  quick_find,
  weighted_union_find_tree<int>
)
{
  auto djs = disjoint_set_problem_slover<TestType>(5);
  djs.unite(1, 4);
  djs.unite(2, 3);
  REQUIRE(!djs.is_equiv(1, 2));
  REQUIRE(!djs.is_equiv(3, 4));
  REQUIRE( djs.is_equiv(1, 4));
  REQUIRE( djs.is_equiv(3, 2));
  djs.unite(1, 3);
  REQUIRE( djs.is_equiv(2, 4));
  REQUIRE(!djs.is_equiv(3, 0));
  djs.unite(0, 4);
  REQUIRE( djs.is_equiv(0, 2));
  REQUIRE( djs.is_equiv(3, 0));
}