#pragma once
#include <string>

class player {
public:
	std::string Name;
	int HP;
	int ATK;
	int DEF;
	int SPD;

	player(const std::string& name = "—EŽÒ", int hp = 120, int atk = 25, int def = 8, int spd = 12)
		: Name(name), HP(hp), ATK(atk), DEF(def), SPD(spd) {
	}
};
