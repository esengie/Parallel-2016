#include <vector>
#include <fstream>
#include <iomanip>

#include "conv.h"

void read_matrix(std::ifstream& is, matrix& m) {
  for (size_t i = 0; i < m.dim; ++i) {
    for (size_t j = 0; j < m.dim; ++j) {
      is >> m.arr[i][j];
    }
  }
}

void print_matrix(std::ostream& out, matrix const& m) {
	using namespace std;
	for (size_t i = 0; i < m.dim; ++i) {
		for (size_t j = 0; j < m.dim; ++j) {
			out << fixed << setprecision(3) << m.arr[i][j] << " ";
		}
		out << endl;
	}
}


int main() {
  std::ifstream in("input.txt");
  std::ofstream out("output.txt");
  size_t n, m;
  in >> n >> m;
  matrix a = create_matrix(n);
  matrix b = create_matrix(m);

  read_matrix(in, a);
  read_matrix(in, b);
  matrix c = compute(a, b);

  print_matrix(out, c);
  return 0;
}
