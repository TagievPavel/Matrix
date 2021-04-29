#pragma once

#include <cstddef>
#include <ostream>

struct Mdim
{
	std::size_t m{}, n{};
};

bool operator == (const Mdim& lhv, const Mdim& rhv) noexcept
{
	return lhv.m == rhv.m && lhv.n == rhv.n;
}

bool operator != (const Mdim& lhv, const Mdim& rhv) noexcept
{
	return !(lhv == rhv);
}

bool canmul(const Mdim& lhv, const Mdim& rhv) noexcept
{
	return lhv.n == rhv.m;
}

bool square(const Mdim& param) noexcept
{
	return param.m == param.n;
}

bool inrnge(const Mdim& lhv, const Mdim& rhv) noexcept
{
	return rhv.m < lhv.m && rhv.n < lhv.n;
}

auto& operator << (std::ostream& out, const Mdim& mdim)
{
	return out << "(" << mdim.m << ", " << mdim.n << ")";
}