#include <utility>
#include <vector>
#include <iostream>
#include "conv.h"

static const float FLOAT_DELTA = 1e-3f;

matrix generate_filled(size_t n, float value = 1) {
  matrix m = allocate(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      m.arr[i][j] = value;
    }
  }

  return m;
}

void output(matrix const& a){
	for (int i = 0; i < a.dim; ++i) {
		for (int j = 0; j < a.dim; ++j) {
			std::cout << a.arr[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

bool check_eq(matrix const& a, matrix const& b) {
  if(a.dim != b.dim) {
    return false;
  }
  //output(a);
  //output(b);
  for(int i = 0; i < a.dim; ++i) {
    for(int j = 0; j < a.dim; ++j) {
      if (abs(a.arr[i][j] - b.arr[i][j]) >= FLOAT_DELTA) {
        return false;
      }
    }
  }

  return true;
}

bool run_tests(std::vector<std::pair<size_t, size_t>> test_descriptions) {
  size_t failed_count = 0;

  for (auto desc : test_descriptions) {
    std::cout << "N = " << desc.first << ", M = " << desc.second << ". ";
    matrix a = generate_filled(desc.first);
    matrix b = generate_filled(desc.second);

    auto res_seq = sequential(a, b);
    auto res_par = parallel(a, b);

    if (!check_eq(res_seq.first, res_par.first)) {
      ++failed_count;
      std::cout << "failed";
    }
    else {
      std::cout << "passed";
    }

    std::cout << " (seq_time = " << res_seq.second << " ns, " << "par_time = " << res_par.second << " ns, speedup = " << static_cast<float>(res_seq.second) / res_par.second << std::endl;
  }

  std::cout << "Test summary: " << (test_descriptions.size() - failed_count) << " / " << test_descriptions.size() << " passed" << std::endl;

  return failed_count == 0;
}
