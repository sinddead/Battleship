#pragma once
#include <vector>
#include <string>

enum class Ship { 
	wsl1=1,
	wsl2=2,
	wsl3=3,
	wsl4=4 };

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
	inline Position(): x_(0), y_(0){}
	inline Position(const Position&) = default;
	inline Position(int x, int y): x_(x), y_(y) {}

	inline int getx() const { return x_; }
	inline int gety() const { return y_; }
	inline void setx(int x) { x_=x; }
	inline void sety(int y) { y_=y; }

	inline bool operator==(const Position& other) const {
		return x_ == other.x_ && y_ == other.y_;
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
	Warship()=delete;
	Warship(Ship, bool, Position);

	inline Ship getship() const { return s_; }
	inline void setship(Ship s) { s_=s; }
	inline bool getvertical() const { return is_vertical_; }
	inline const Position& getpos() const { return pos_; }
	inline const std::vector<Position>& getcells() const { return cells_; }
	inline int size() const { return static_cast<int>(s_); }
	
	bool is_ship_cell(const Position& pos) const;
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