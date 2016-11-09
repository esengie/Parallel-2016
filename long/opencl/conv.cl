typedef float ELEM;

void kernel eval(global const ELEM * const a, global const ELEM * const b, global ELEM * const c, int n, int m) {
  int idx = get_global_id(0);
  int cn = max(n , m);
  int i = idx / cn;
  int j = idx % cn;
  int hm = (m - 1) / 2;
  ELEM res = 0;

  for (int k = -hm; k <= hm; ++k) {
	int a_i = i + k;
    if (a_i < 0 || a_i >= n) {
      continue;
    }
    int b_i = k + hm;
    for (int l = -hm; l <= hm; ++l) {
      int a_j = j + l;
      if (a_j < 0 || a_j >= n) {
        continue;
      }
      int b_j = l + hm;
      res += a[a_i * n + a_j] * b[b_i * m + b_j];
    }
  }

  c[idx] = res;
}
