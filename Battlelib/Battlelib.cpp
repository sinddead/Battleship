#include "Battlelib.h"

Position::Position(int x, int y) {
    if (x < 1 || y < 1 || x>10 || y>10) throw std::logic_error("This position not in field");
    x_ = x;
    y_ = y;
}

void Position::setx(int x) {
    if (x < 1 || x>10) throw std::logic_error("This position not in field");
    x_ = x;
}
void Position::sety(int y) {
    if (y < 1 || y>10) throw std::logic_error("This position not in field");
    y_ = y;
}

bool Warship::is_ship_cell(const Position& pos) const {
	for (const Position& p : cells_) {
		if (pos == p) return true;
	}
	return false;
}

Warship::Warship(Ship s, bool vertical, Position pos): s_(s), is_vertical_(vertical), pos_(pos) {
    int len = static_cast<int>(s_);
    for (int i = 0; i < len; ++i) {
        Position p;
        if (is_vertical_) p = Position(pos.getx(), pos.gety() + i);
        else p = Position(pos.getx() + i, pos.gety());
        cells_.push_back(p);
    }
}