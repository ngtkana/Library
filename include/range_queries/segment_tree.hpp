template < typename Value, typename BinaryOp >
class segment_tree {
    int                  sz, n, N;
    BinaryOp             op;
    Value                id;
    std::vector< Value > table;

    auto& op_eq(Value& x, Value y) const
      { return x = op(x, y); }
    void merge(int u)
      { table.at(u) = op(table.at(2 * u), table.at(2 * u + 1)); }

  public:
    segment_tree(int sz, BinaryOp op, Value id):
      sz    (sz),
      n     (std::pow(2, int(std::log2(2 * sz - 1)))),
      N     (n * 2),
      op    (op),
      id    (id),
      table (N, id)
      {}

    auto& at(int i)       { return table.at(n + i); }
    auto& at(int i) const { return table.at(n + i); }
    auto collect() const {
      auto ret = std::vector<Value>(sz);
      for (auto i = 0; i < sz; i++)
        { ret.at(i) = at(i); }
      return ret;
    }
    auto query(int l, int r) const {
      auto const dfs = [&](auto&& f, int l, int r, int k, int L, int R) -> Value {
        return l <= L && R <= r
          ? table.at(k)
          : R <= l || r <= L
          ? id
          : op(
            f(f, l, r, 2 * k, L, (L + R) / 2),
            f(f, l, r, 2 * k + 1, (L + R) / 2, R)
          );
      };
      return dfs(dfs, l, r, 1, 0, n);
    }
    void build_oneline(int i)
      { for (i += n, i /= 2; i > 0; i /= 2) merge(i); }
    void build()
      { for (auto i = n - 1; i > 0; i--) merge(i); }
};

template<typename Value, typename BinaryOp>
auto make_segment_tree(int sz, BinaryOp op, Value id)
  { return segment_tree<Value, BinaryOp>(sz, std::move(op), id); }
