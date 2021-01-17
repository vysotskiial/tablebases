#pragma once

#include <set>
#include <array>
#include <iostream>

struct Coords {
	unsigned x;
	unsigned y;
	bool valid() { return (x < 8 && y < 8); }
};

inline Coords operator+(const Coords &lhs, const Coords &rhs)
{
	return {lhs.x + rhs.x, lhs.y + rhs.y};
}

inline bool operator<(const Coords &lhs, const Coords &rhs)
{
	return (lhs.x < rhs.x || ((lhs.x == rhs.x) && (lhs.y < rhs.y)));
}

inline bool operator==(const Coords &lhs, const Coords &rhs)
{
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

inline std::ostream &operator<<(std::ostream &ostr, const Coords &c)
{
	ostr << c.x << ' ' << c.y << '\n';
	return ostr;
}

inline std::ostream &operator<<(std::ostream &ostr, const std::set<Coords> &c)
{
	for (auto &coord : c) {
		ostr << coord;
	}
	return ostr;
}

class Piece {
protected:
	Coords coords;

public:
	virtual void add_controlled_squares(std::set<Coords> &controlled,
	                                    std::array<std::array<bool, 8>, 8>) = 0;
	Piece(unsigned x, unsigned y): coords({x, y}) {}
};

class Knight : public Piece {
public:
	void add_controlled_squares(std::set<Coords> &controlled,
	                            std::array<std::array<bool, 8>, 8>) final
	{
		for (auto i = 1u; i < 3u; i++)
			for (auto j = 0; j <= 2; j += 2)
				for (auto k = 0; k <= 2; k += 2) {
					auto x_c = coords.x + (1 - j) * i;
					auto y_c = coords.y + (1 - k) * (3 - i);
					if (x_c < 8 && y_c < 8)
						controlled.insert({x_c, y_c});
				}
	}

	Knight(unsigned x, unsigned y): Piece(x, y) {}
};

class Bishop : public Piece {
public:
	void add_controlled_squares(std::set<Coords> &controlled,
	                            std::array<std::array<bool, 8>, 8> board) override
	{
		for (auto i = 0u; i <= 2; i += 2)
			for (auto j = 0u; j <= 2; j += 2) {
				Coords step{1 - i, 1 - j};
				for (Coords c = coords + step; c.valid(); c = c + step) {
					controlled.insert(c);
					if (board[c.x][c.y])
						break;
				}
			}
	}
	Bishop(unsigned x, unsigned y): Piece(x, y) {}
};

class Rook : public Piece {
public:
	void add_controlled_squares(std::set<Coords> &controlled,
	                            std::array<std::array<bool, 8>, 8> board) override
	{
		for (auto i = 0u; i < 2; i++)
			for (auto j = 0u; j <= 2; j += 2) {
				Coords step{(1 - i) * (1 - j), i * (1 - j)};
				for (Coords c = coords + step; c.valid(); c = c + step) {
					controlled.insert(c);
					if (board[c.x][c.y])
						break;
				}
			}
	}
	Rook(unsigned x, unsigned y): Piece(x, y) {}
};

class Queen : public Rook, public Bishop {
public:
	void add_controlled_squares(std::set<Coords> &controlled,
	                            std::array<std::array<bool, 8>, 8> board) final
	{
		Rook::add_controlled_squares(controlled, board);
		Bishop::add_controlled_squares(controlled, board);
	}
	Queen(unsigned x, unsigned y): Rook(x, y), Bishop(x, y) {}
};
