int insert_bit(int x, int j, int v) {
  int low = x & ((1 << j) - 1);
  return ((x >> j) << (j + 1)) + (v << j) + low;
}
