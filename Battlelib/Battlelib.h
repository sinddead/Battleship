#pragma once
#include <vector>
#include <string>

enum class Ship { 
	wsl1,
	wsl2,
	wsl3,
	wsl4 };

enum class CellState {
	Empty,
	Alive,
	Hit,
	Miss,
	Dead
};

enum class GameState {
	InProgress,
	Player1Win,
	Player2Win
};

#define FIELDSIZE 10

class Position {
private:
	int x_;
	int y_;
public:
	Position() = default;
	Position(const Position&);
	Position(int, int);
	inline bool operator==(const Position& other) const {
		return x_ == other.x_ && y_ = other.y_;
	};
	inline bool operator!=(const Position& other) const {
		return !(*this == other);
	};
};

class Warship {
private:
	Ship s_;
	bool is_vertical_;
	Position pos_;
	std::vector<Position> cells_;
public:
	inline Ship getship() const { return s_; }

};

class Gamefield{
private:
	std::vector<Warship>  ships_;
	std::vector<CellState> field_;
	char ships_alive_ = 0;
	};
class Player{
private:
	Gamefield  yourBoard_;
	Gamefield   opponentBoard_;
	GameState   gamestate_;
	std::string name_;
};
class Battle{
private:
	Player p1_;
	Player p2_;
	bool is_ended_;
};