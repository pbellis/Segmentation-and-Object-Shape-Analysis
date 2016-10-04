#include "GBT_7.h"

const std::array<unsigned, GBT_7::MaxPower> GBT_7::Pow7 {{ 
		1, 7, 49, 343, 2401, 16807, 117649, 823543, 5764801, 40353607 
}};

const std::array<std::array<unsigned, GBT_7::MaxPower>, GBT_7::MaxPower> GBT_7::AdditionTable{{
	{{ 0,  1,  2,  3,  4,  5,  6 }},
	{{ 1,  9,  3, 25,  5, 13,  0}},
	{{ 2,  3, 18, 19,  6,  0, 43}},
	{{ 3, 25, 19, 27,  0,  1,  2}},
	{{ 4,  5,  6,  0, 29, 37, 31}},
	{{ 5, 13,  0,  1, 37, 38,  4}},
	{{ 6,  0, 43,  2, 31,  4, 47}}
}};

const std::array<unsigned, 7> GBT_7::ComplimentTable {{
		0, 6, 5, 4, 3, 2, 1
}};

const std::array<std::array<unsigned, 2>, 7> GBT_7::DecomposeTable {{
	{{ 0, 0 }},
	{{ 1, 5 }},
	{{ 2, 3 }},
	{{ 3, 1 }},
	{{ 4, 6 }},
	{{ 5, 4 }},
	{{ 6, 2 }}
}};

const std::array<std::array<unsigned, 3>, 7> SimplifyTable {{
	{{ 0, 0, 0 }},
	{{ 6, 2, 4 }},
	{{ 1, 4, 5 }},
	{{ 4, 5, 6 }},
	{{ 2, 3, 6 }},
	{{ 1, 3, 5 }}
}};

void GBT_7::Log7(unsigned value, unsigned &ret) {
	for (unsigned p = 0; p < MaxPower; ++p) {
		if (Pow7[p] > value) {
			ret = p - 1;
			return;
		}
	}
}

void GBT_7::LeftShift(unsigned value, unsigned shift, unsigned &ret) {
	ret = value / Pow7[shift];
}

void GBT_7::RightShift(unsigned value, unsigned shift, unsigned &ret) {
	ret = value * Pow7[shift];
}

void GBT_7::ValueToDigits(unsigned value, std::array<unsigned, MaxPower> &ret) {
	std::fill(ret.begin(), ret.end(), 0);

	int m = 1, mm = 7;

	for (int p = 0; p < MaxPower; p++) {
		ret[p] = (int)((value % mm) / m);
		m = mm;
		mm *= 7;
	}
}

void GBT_7::DigitsToValue(const std::array<unsigned, MaxPower> &digits, unsigned &ret) {
	ret = 0;
	int m = 1;

	for (int p = 0; p < MaxPower; p++) {
		ret += digits[p] * m;
		m *= 7;
	}
}

void GBT_7::CoordToValue(const std::array<unsigned, 2> &coord, unsigned &ret) {
	
}

void GBT_7::ValueToCoord(unsigned value, std::array<unsigned, 2> &ret) {
}

void GBT_7::DigitsToString(const std::array<unsigned, MaxPower> &digits, std::string &ret) {
	ret.clear();
	ret.reserve(MaxPower);

	for (unsigned p = 0; p < MaxPower; ++p) {
		ret += std::to_string(digits[p]);
	}
}

void GBT_7::Addition(unsigned x, unsigned y, unsigned &ret) {
	ret = 0;

	if (x < 7 && y < 7) {
		ret = AdditionTable[x][y];
	}
	else {
		std::array<unsigned, MaxPower> dx, dy;
		ValueToDigits(x, dx);
		ValueToDigits(y, dy);
		unsigned t = 0, c = 0, d = 0, m = 1;
		for (int p = 0; p < MaxPower; p++) {
			Addition(c, AdditionTable[dx[p]][dy[p]], t);
			c = t / 7;
			d += (t % 7) * m;
			m *= 7;
		}
		ret = d;
	}
}

void GBT_7::Complement(unsigned value, unsigned &ret) {
	ret = 0;

	std::array<unsigned, MaxPower> digits;
	ValueToDigits(value, digits);
	for (int p = 0; p < MaxPower; p++) {
		digits[p] = ComplimentTable[digits[p]];
	}

	DigitsToValue(digits, ret);
}

void GBT_7::AdditionN(unsigned value, unsigned n, unsigned &ret) {
	ret = 0;
	
	if (n == 0) {
	}
	else if (n == 1) {
		ret = value;
	}
	else if (n == 2) {
		Addition(value, value, ret);
	}
	else if (n % 2 == 0) {
		unsigned half_addition;
		AdditionN(value, n / 2, half_addition);

		Addition(half_addition, half_addition, ret);
	}
	else {
		unsigned half_addition;
		AdditionN(value, n / 2, half_addition);

		unsigned off_one_addition;
		Addition(half_addition, half_addition, off_one_addition);

		Addition(value, off_one_addition, ret);
	}
}

void GBT_7::Decompose(unsigned value, std::array<unsigned, 7> &ret) {
	// TODO
}

void GBT_7::Simplify(const std::array<unsigned, 7> &steps, std::array<unsigned, 7> &ret) {
	// TODO
}
void GBT_7::Compose(const std::array<unsigned, 7> &steps, unsigned &ret) {
	// TODO
}