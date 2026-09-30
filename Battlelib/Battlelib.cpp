#include "Battlelib.h"

Position::Position(int x, int y) {
    x_ = x;
    y_ = y;
}

void Position::setx(int x) {
    x_ = x;
}
void Position::sety(int y) {
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

Gamefield::Gamefield() {
    field_.resize(FIELDSIZE * FIELDSIZE);
    for (int y = 0; y < FIELDSIZE; ++y)
        for (int x = 0; x < FIELDSIZE; ++x)
            field_[y * FIELDSIZE + x] = CellState::Empty;
}

CellState Gamefield::check(int x, int y) const {
    if (!inBounds(x, y))
        throw std::logic_error("Coordinates out of range 1-10");
    return field_[(y - 1) * FIELDSIZE + (x - 1)];
}

bool Gamefield::canPlaceShip_(Ship s, bool vertical, const Position& pos) const {
    const int len = static_cast<int>(s);
    int tmpx = 0;
    int tmpy = 1;
    if (vertical) { tmpx = 1; tmpy = 0; }
    if (!inBounds(pos.getx(), pos.gety())) return false;

    const int endX = pos.getx() + tmpx * (len - 1);
    const int endY = pos.gety() + tmpy * (len - 1);
    if (!inBounds(endX, endY)) return false;
    for (int i = -1; i <= len; ++i) {
        for (int ox = -1; ox <= 1; ++ox) {
            for (int oy = -1; oy <= 1; ++oy) {
                const int cx = pos.getx() + tmpx * i + ox;
                const int cy = pos.gety() + tmpy * i + oy;
                if (!inBounds(cx, cy)) continue;
                if (field_[(cy - 1) * FIELDSIZE + (cx - 1)] == CellState::Alive)
                    return false;
            }
        }
    }
    return true;
}

bool Gamefield::placeShip(Ship s, bool vertical, const Position& pos) {
    if (!canPlaceShip_(s, vertical, pos)) return false;
    Warship w(s, vertical, pos);
    for (const Position& c : w.getcells()){
        get(c.getx(), c.gety()) = CellState::Alive;
}
    ships_.push_back(w);
    ++ships_alive_;
    return true;
}

bool Gamefield::isShipDead_(const Warship& w) const {
    for (const Position& c : w.getcells()) {
        if (get(c.getx(), c.gety()) != CellState::Dead)
            return false;
    }
    return true;
}

void Gamefield::randomPlacement() {
    std::mt19937 rd(std::random_device{}());
    std::uniform_int_distribution<int> distXY(1, FIELDSIZE);
    std::uniform_int_distribution<int> distDir(0, 1);

    const std::vector<Ship> allships = {
        Ship::wsl4,
        Ship::wsl3, Ship::wsl3,
        Ship::wsl2, Ship::wsl2, Ship::wsl2,
        Ship::wsl1, Ship::wsl1, Ship::wsl1, Ship::wsl1
    };

    for (std::size_t i = 0; i < allships.size(); ++i) {
        Ship s = allships[i];
        while (true) {
            bool v = distDir(rd) == 1;
            Position p(distXY(rd), distXY(rd));
            if (placeShip(s, v, p)) break;
        }
    }
}

bool Gamefield::shoot(const Position& p) {
    if (!inBounds(p.getx(), p.gety())) return false;
    CellState& cs = get(p.getx(), p.gety());
    if (cs == CellState::Hit || cs == CellState::Miss || cs == CellState::Dead)
        return false;

    for (std::size_t i = 0; i < ships_.size(); ++i) {
        Warship& w = ships_[i];
        if (!w.is_ship_cell(p)) continue;
        cs = CellState::Hit;
        if (isShipDead_(w)) {
            const std::vector<Position>& cells = w.getcells();
            for (std::size_t j = 0; j < cells.size(); ++j) {
                get(cells[j].getx(), cells[j].gety()) = CellState::Dead;
            }
            markAroundDead_(w);
            --ships_alive_;
        }
        return true;
    }

    cs = CellState::Miss;
    return false;
}

void Gamefield::markAroundDead_(const Warship& w) {
    const std::vector<Position>& cells = w.getcells();
    for (std::size_t i = 0; i < cells.size(); ++i) {
        Position c = cells[i];
        for (int ox = -1; ox <= 1; ++ox) {
            for (int oy = -1; oy <= 1; ++oy) {
                int nx = c.getx() + ox;
                int ny = c.gety() + oy;
                if (!inBounds(nx, ny)) continue;
                if (get(nx, ny) == CellState::Empty) get(nx, ny) = CellState::Miss;
            }
        }
    }
}

void Gamefield::markVisibleShot(const Position& p, CellState state) {
    if (!inBounds(p.getx(), p.gety())) return;
    get(p.getx(), p.gety()) = state;
}

void Gamefield::print(bool hideShips) const {
    std::cout << "    ";
    for (int x = 1; x <= FIELDSIZE; ++x) std::cout << x << ' ';
    std::cout << "\n";
    for (int y = 1; y <= FIELDSIZE; ++y) {
        std::cout << y << "  ";
        if (y < 10) std::cout << ' ';
        for (int x = 1; x <= FIELDSIZE; ++x) {
            CellState cs = get(x, y);
            char ch = '.';
            switch (cs) {
            case CellState::Empty: ch = '.'; break;
            case CellState::Alive: if (hideShips) ch = '.'; else ch = 'S'; break;
            case CellState::Hit:   ch = 'X'; break;
            case CellState::Miss:  ch = 'o'; break;
            case CellState::Dead:  ch = 'X'; break;
            }
            std::cout << ch << ' ';
        }
        std::cout << "\n";
    }
}
