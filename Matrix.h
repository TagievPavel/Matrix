#pragma once

#include <vector>

#include "Mdim.h"

template <typename Type = long double>
class Matrix
{
	using Line = std::vector<Type>;
	using Grid = std::vector<Line>;

public:
	Matrix() = default;

private:
	Grid grid;
	Mdim mdim;

};