#pragma once

#include <vector>
#include <cassert>
#include <initializer_list>
#include <algorithm>

#include "Mdim.h"
#include "utility.h"

template <typename Type = long double>
class Matrix
{
	using Line = std::vector<Type>;
	using Grid = std::vector<Line>;

	using initializer_matrix = std::initializer_list<std::initializer_list<Type>>;

public:
	Matrix() : grid{}, mdim{} {};

	Matrix(const Matrix<Type>& other) : 
		grid(other.grid), 
		mdim(other.mdim) {}

	Matrix(Matrix<Type>&& other) noexcept : 
		grid(std::move(other.grid)), 
		mdim(std::move(other.mdim)) 
	{
		other.mdim = { 0, 0 };
	}

	Matrix(const std::size_t m, const std::size_t n);

	Matrix(initializer_matrix matrix);

public:
	const Mdim& dim() const noexcept;

	void resize(const std::size_t m, const std::size_t n);

	Line& line(const std::size_t idx);
	const Line& line(const std::size_t idx) const;

	Matrix<Type> transpose() const;

public:
	Matrix<Type>& operator = (const Matrix<Type>& other);
	Matrix<Type>& operator = (Matrix<Type>&& other) noexcept;

	Type& operator () (const std::size_t m, const std::size_t n);
	const Type& operator () (const std::size_t m, const std::size_t n) const;

private:
	Grid grid;
	Mdim mdim;

};

template<typename Type>
inline Matrix<Type>::Matrix(const std::size_t m, const std::size_t n) : Matrix()
{
	grid.assign(m, Line(n));
	mdim = { m, n };
}

template<typename Type>
inline Matrix<Type>::Matrix(initializer_matrix matrix) : 
	Matrix(matrix.size(), matrix.begin()->size())
{
	std::copy(matrix.begin(), matrix.end(), grid.begin());
}

template<typename Type>
inline const Mdim& Matrix<Type>::dim() const noexcept
{
	return mdim;
}

template<typename Type>
inline void Matrix<Type>::resize(const std::size_t m, const std::size_t n)
{
	grid.resize(m);

	for (auto& line : grid)
		line.resize(n);

	mdim = { m, n };
}

template<typename Type>
inline typename Matrix<Type>::Line& Matrix<Type>::line(const std::size_t idx)
{
	assert(idx < mdim.m && "Out of range");
	return grid[idx];
}

template<typename Type>
inline const typename Matrix<Type>::Line& Matrix<Type>::line(const std::size_t idx) const
{
	assert(idx < mdim.m && "Out of range");
	return grid[idx];
}

template<typename Type>
inline Matrix<Type> Matrix<Type>::transpose() const
{
	Matrix<Type> transposed(mdim.n, mdim.m);

	return transposed;
}

template<typename Type>
inline Matrix<Type>& Matrix<Type>::operator=(const Matrix<Type>& other)
{
	if (this == &other) return *this;

	grid = other.grid;
	mdim = other.mdim;

	return *this;
}

template<typename Type>
inline Matrix<Type>& Matrix<Type>::operator=(Matrix<Type>&& other) noexcept
{
	if (this == &other) return *this;

	grid = std::move(other.grid);
	mdim = std::move(other.mdim);

	other.mdim = { 0, 0 };

	return *this;
}

template<typename Type>
inline Type& Matrix<Type>::operator()(const std::size_t m, const std::size_t n)
{
	assert(inrnge(mdim, { m, n }) && "Out of range");
	return grid[m][n];
}

template<typename Type>
inline const Type& Matrix<Type>::operator()(const std::size_t m, const std::size_t n) const
{
	assert(inrnge(mdim, { m, n }) && "Out of range");
	return grid[m][n];
}

template <typename Type>
auto& operator << (std::ostream& out, const Matrix<Type>& matrix)
{
	const auto mdim = matrix.dim();

	if (dequal(mdim, { 0, 0 })) return out << "Matrix empty";

	const std::size_t
		maxrow = 10, 
		maxcol = 10;

	const Mdim mid = { maxrow / 2, maxcol / 2 };
	const Mdim mis = { mdim.m - maxrow, mdim.n - maxcol };

	const bool 
		ziprow = maxrow < mdim.m, 
		zipcol = maxcol < mdim.n;

	for (std::size_t i{}; i < mdim.m; ++i)
	{
		if (ziprow && i == mid.m)
		{
			out << mis.m << " more lines...\n";
			i += mis.m;
		}

		for (std::size_t j{}; j < mdim.n; ++j)
		{
			if (zipcol && j == mid.n)
			{
				out << mis.n << " more elements...\t";
				j += mis.n;
			}

			out << matrix(i, j) << "\t";
		}
		out << "\n";
	}

	return out;
}
