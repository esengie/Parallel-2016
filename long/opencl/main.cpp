#include <vector>
#include <fstream>
#include <cassert>
#include <iostream>

#include "conv.h"

static const float FLOAT_DELTA = 1e-3f;

void read_square_matrix(std::istream& is, matrix& m) {
  for (size_t i = 0; i < m.dim; ++i) {
    for (size_t j = 0; j < m.dim; ++j) {
      is >> m.arr[i][j];
    }
  }
}

std::pair<matrix, matrix> read_matrices(std::string const& filename) {
  std::ifstream is(filename);
  size_t n, m;
  is >> n >> m;
  assert(m % 2 == 1 && "m must be an odd number");
  matrix a = allocate(n);
  matrix b = allocate(m);

  read_square_matrix(is, a);
  read_square_matrix(is, b);

  return std::make_pair(a, b);
}

void assert_equals(matrix const& left, matrix const& right) {
  assert(left.dim == right.dim);
  for (size_t i = 0; i < left.dim; ++i) {
    for (size_t j = 0; j < left.dim; ++j) {
      assert(abs(left.arr[i][j] - right.arr[i][j]) < FLOAT_DELTA);
    }
  }
}


void print_matrix(matrix const& m, std::ostream& os) {
  for (size_t i = 0; i < m.dim; ++i) {
    for (size_t j = 0; j < m.dim; ++j) {
      os << " " << m.arr[i][j];
    }

    os << std::endl;
  }
}

extern bool run_tests(std::vector<std::pair<size_t, size_t>>);

int main(void) {
	if (!run_tests({{1024, 3}, {1024, 9}, {1, 9}, {31, 9}, {1023, 9}, {1024, 17}, {32, 1023}})) {
	  std::cerr << "Tests not passed" << std::endl;
    return 1;
  }

  std::cout << std::endl;

  auto p = read_matrices("input.txt");
  matrix a = p.first;
  matrix b = p.second;

  std::pair<matrix, size_t> seq_res = sequential(a, b);
  std::cout << "time in sequential evaluation = " << seq_res.second << " ns" << std::endl;;
  std::pair<matrix, size_t> par_res = parallel(a, b);
  std::cout << "time in parallel evaluation = " << par_res.second << " ns" << std::endl;
  std::cout << "acceleration = " << double(seq_res.second) / par_res.second << std::endl;

  std::cout << std::endl;
  assert_equals(seq_res.first, par_res.first);
  std::ofstream output_file("output.txt");
  print_matrix(par_res.first, output_file);
  std::cout << "parallel and sequential algorithms produce same matrices" << std::endl;
}
