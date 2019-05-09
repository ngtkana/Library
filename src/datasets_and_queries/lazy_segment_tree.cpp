#include <bits/stdc++.h>
using namespace std;
// begin
struct segment_tree {
  int sz;
  int Sz;
  int ht;
  vector<T> seg;
  vector<U> act;
  vector<bool> has_act;
  const function<T(T, T)> o;
  const function<void(T&, U)> oo;
  const function<void(U&, U)> ooo;
  const function<void(U&)> twice;
  const function<U(U)> half;
  const T tid;
  const U uid;
  public:
    segment_tree(
        int n,
        const function<T(T, T)> merge_function,
        const function<void(T&, U)> action,
        const function<void(U&, U)> composition,
        const function<void(U&)> twice,
        const function<U(U)> half,
        const T seg_id,
        const U act_id
      )
        : o(merge_function)
        , oo(action)
        , ooo(composition)
        , twice(twice)
        , half(half)
        , tid(seg_id)
        , uid(act_id)
      {
        ht = 1, sz = 1;
        while(sz < n) ht++, sz <<= 1;
        Sz = sz << 1;
        seg.assign(Sz, tid);
        act.resize(Sz, act_id);
        has_act.assign(Sz, false);
      }
    
    segment_tree(
        const vector<T>& data,
        const function<T(T, T)> merge_function,
        const function<void(T&, U)> action,
        const function<void(U&, U)> composition,
        const function<void(U&)> twice,
        const function<U(U)> half,
        const T seg_id,
        const U act_id
      )
        : segment_tree(
            data.size(),
            merge_function,
            action,
            composition,
            twice,
            half,
            seg_id,
            act_id
          )
      {
        copy(data.begin(), data.end(), seg.begin() + sz);
        for (int i = sz - 1; i >= 1; i--) seg[i] = o(seg[i << 1], seg[(i << 1) + 1]);
      }
    
    inline int lft (int i) {return i << 1;}
    inline int rgt (int i) {return (i << 1) + 1;}
    inline int upp (int i) {return i >> 1;}

    inline void propagate (
        int k,
        int L,
        int R
      )
      {
        if (has_act[k]) {
          oo(seg[k], act[k]);
          if (k < sz) {
            ooo(act[lft(k)], half(act[k]));
            ooo(act[rgt(k)], half(act[k]));
            has_act[lft(k)] = has_act[rgt(k)] = true;
          }
          act[k] = uid, has_act[k] = false;
        }
      }

    void update (
        int l,
        int r,
        T x,
        int k = 1,
        int L = 0,
        int R = -1
      )
      {
        if (R == -1) R = sz;
        if (k == 1) for (int i = 0; i < ht - 1; i++) twice(x);
        propagate(k, L, R);
        if (R <= l || r <= L) return;
        if (l <= L && R <= r) {
          ooo(act[k], x), has_act[k] = true;
          propagate(k, L, R);
        } else {
          int C = (L + R) >> 1;
          update(l, r, half(x), lft(k), L, C);
          update(l, r, half(x), rgt(k), C, R);
          seg[k] = o(seg[lft(k)], seg[rgt(k)]);
        }
      }
    
    T find (
        int l,
        int r,
        int k = 1,
        int L = 0,
        int R = -1
      )
      {
        if (R == -1) R = sz;
        propagate(k, L, R);
        if (R <= l || r <= L) return tid;
        if (l <= L && R <= r) {
          propagate(k, L, R);
          return seg[k];
        } else {
          int C = (L + R) >> 1;
          T lv = find(l, r, lft(k), L, C);
          T rv = find(l, r, rgt(k), C, R);
          seg[k] = o(seg[lft(k)], seg[rgt(k)]);
          return o(lv, rv);
        }
      }

    void print(int w = 4) {
      for (int i(1), last(2), output_size(w << ht); last <= Sz; last <<= 1, output_size >>= 1) {
        for (; i < last; i++) {
          cout << right << setw(w) << seg[i];
          cout << setw(2) <<  " <";
          cout << left << setw(output_size - w - 2);
          cout << (has_act[i] ? to_string(act[i]) : "");
        }
        cout << endl;
      }
    }
};
// end
