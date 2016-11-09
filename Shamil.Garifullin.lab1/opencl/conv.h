#pragma once

typedef float ELEM;

struct matrix {
	size_t dim;
	ELEM** arr;
};

matrix create_matrix(size_t n);

matrix compute(matrix const& a, matrix const& b);
