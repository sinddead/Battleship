#include "Battlelib.h"

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