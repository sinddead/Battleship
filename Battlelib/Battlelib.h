#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <random>
#include <iostream>

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
	inline Position(): x_(1), y_(1){}
	inline Position(const Position&) = default;
	Position(int x, int y);

	inline int getx() const { return x_; }
	inline int gety() const { return y_; }
	void setx(int x);
	void sety(int y);

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

	CellState& get(int x, int y) { return field_[(y - 1) * FIELDSIZE + (x - 1)]; }
	const CellState& get(int x, int y) const { return field_[(y - 1) * FIELDSIZE + (x - 1)]; }
	bool canPlaceShip_(Ship s, bool vertical, const Position& pos) const;
	bool isShipDead_(const Warship& w) const;
	void markAroundDead_(const Warship& w);
public:
	Gamefield();
	CellState check(int x, int y) const;
	inline char shipsAlive() const { return ships_alive_; }
	inline const std::vector<Warship>& ships() const { return ships_; }
	inline bool inBounds(int x, int y) const {
		return x >= 1 && x <= FIELDSIZE && y >= 1 && y <= FIELDSIZE;}
	bool placeShip(Ship s, bool vertical, const Position& pos);
	void randomPlacement();
	bool shoot(const Position& p);
	void markVisibleShot(const Position& p, CellState state);
	void print(bool hideShips = false) const;
	};

class Player{
private:
	Gamefield yourBoard_;
	Gamefield opponentBoard_;
	GameState gamestate_ =GameState::InProgress;
	std::string name_;
public:
	Player() = default;
    inline Player(const std::string& n) : name_(n) {}

    inline const std::string& name() const { return name_; }
    inline GameState gamestate() const { return gamestate_; }
    inline const Gamefield& yourBoard() const { return yourBoard_; }
    inline const Gamefield& opponentBoard() const { return opponentBoard_; }
    inline void setName(const std::string& n) { name_ = n; }
    inline void setGamestate(GameState s) { gamestate_ = s; }
    inline Gamefield& yourBoard() { return yourBoard_; }
    inline Gamefield& opponentBoard() { return opponentBoard_; }
    bool makeMove(int x, int y, Gamefield& enemyRealBoard);
};

class Battle{
private:
	Player p1_;
	Player p2_;
	bool is_ended_;

	void turn_(Player& attacker, Player& defender);
public:
	Battle() = default;
	inline Battle(Player a, Player b) : p1_(std::move(a)), p2_(std::move(b)) {}
	inline bool isEnded() const { return is_ended_; }
	inline const Player& player1() const { return p1_; }
	inline const Player& player2() const { return p2_; }

	void setup();
	void run();
	void printBoth() const;
};