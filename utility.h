#pragma once

#include <cstddef>
#include <type_traits>
#include <limits>
#include <cmath>

template <typename Type>
bool is_equal(const Type& lhv, const Type& rhv)
{
	if constexpr (std::is_floating_point_v<Type>)
		return std::abs(lhv - rhv) < std::numeric_limits<Type>::epsilon();

	return lhv == rhv;
}