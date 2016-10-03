#pragma once
#include <array>
#include <string>

class GBT_7
{
private:
	static const unsigned MaxPower = 10;
	static const std::array<unsigned, MaxPower> Pow7;

	static const std::array<std::array<unsigned, MaxPower>, MaxPower> AdditionTable;
	static const std::array<unsigned, 7> ComplimentTable;
	static const std::array<std::array<unsigned, 2>, 7> DecomposeTable;
	static const std::array<std::array<unsigned, 3>, 7> SimplifyTable;

	static const std::array<std::array<float, 2>, 7> VectorTable;

private:
	static void Log7(unsigned value, unsigned &ret);
	static void LeftShift(unsigned value, unsigned shift, unsigned &ret);
	static void RightShift(unsigned value, unsigned shift, unsigned &ret);

	static void ValueToDigits(unsigned value, std::array<unsigned, MaxPower> &ret);
	static void DigitsToValue(const std::array<unsigned, MaxPower> &digits, unsigned &ret);

	static void CoordToValue(const std::array<unsigned, 2> &coord, unsigned &ret);
	static void ValueToCoord(unsigned value, std::array<unsigned, 2> &ret);

	static void DigitsToString(const std::array<unsigned, MaxPower> &digits, std::string &ret);

	static void Addition(unsigned x, unsigned y, unsigned &ret);
	static void Complement(unsigned value, unsigned &ret);

	static void AdditionN(unsigned value, unsigned n, unsigned &ret);

	static void Decompose(unsigned value, std::array<unsigned, 7> &ret);
	static void Simplify(const std::array<unsigned, 7> &steps, std::array<unsigned, 7> &ret);
	static void Compose(const std::array<unsigned, 7> &steps, unsigned &ret);
public:
	GBT_7();
	~GBT_7();
};

