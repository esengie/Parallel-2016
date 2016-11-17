#pragma once
#include <utility>

typedef float ELEM;

struct matrix {
	size_t dim;
	ELEM** arr;
};

matrix allocate(size_t n);

std::pair<matrix, size_t> sequential(matrix const& a, matrix const& b);
std::pair<matrix, size_t> parallel(matrix const& a, matrix const& b);
