#include <gtest/gtest.h>
#include <algorithm>
#include "pieces.h"

using namespace std;

TEST(test, knight_test)
{
	Knight k{0, 1};
	set<Coords> s{};
	k.add_controlled_squares(s, {});
	set<Coords> correct{{2, 0}, {2, 2}, {1, 3}};
	auto is_equal = equal(s.begin(), s.end(), correct.begin());
	ASSERT_TRUE(is_equal) << s;
}

TEST(test, bishop_test)
{
	Bishop b{3, 3};
	set<Coords> s{};
	array<array<bool, 8>, 8> board{};
	board[0][0] = true;
	board[1][1] = true;
	board[2][4] = true;
	board[5][1] = true;
	board[4][4] = true;
	set<Coords> correct{{2, 2}, {1, 1}, {4, 2}, {5, 1}, {4, 4}, {2, 4}};
	b.add_controlled_squares(s, board);
	auto is_equal = equal(s.begin(), s.end(), correct.begin());
	ASSERT_TRUE(is_equal) << s;
}

TEST(test, rook_test)
{
	Rook r{3, 3};
	set<Coords> s{};
	array<array<bool, 8>, 8> board{};
	board[3][1] = true;
	board[0][3] = true;
	board[3][5] = true;
	board[4][3] = true;
	set<Coords> correct{{3, 2}, {3, 1}, {0, 3}, {1, 3},
	                    {2, 3}, {3, 4}, {3, 5}, {4, 3}};
	r.add_controlled_squares(s, board);
	auto is_equal = equal(s.begin(), s.end(), correct.begin());
	ASSERT_TRUE(is_equal) << s;
}

TEST(test, queen_test)
{
	Queen q{3, 3};
	set<Coords> s{};
	array<array<bool, 8>, 8> board{};
	board[0][0] = true;
	board[1][1] = true;
	board[2][4] = true;
	board[5][1] = true;
	board[4][4] = true;
	board[3][1] = true;
	board[0][3] = true;
	board[3][5] = true;
	board[4][3] = true;
	set<Coords> correct{{3, 2}, {3, 1}, {0, 3}, {1, 3}, {2, 3}, {3, 4}, {3, 5},
	                    {4, 3}, {2, 2}, {1, 1}, {4, 2}, {5, 1}, {4, 4}, {2, 4}};
	q.add_controlled_squares(s, board);
	auto is_equal = equal(s.begin(), s.end(), correct.begin());
	ASSERT_TRUE(is_equal) << s;
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
