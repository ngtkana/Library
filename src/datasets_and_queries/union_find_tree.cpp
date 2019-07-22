﻿class union_find_tree {
    int n;
    std::vector<int> prt;

  public:
    template<typename T>
    union_find_tree (T n) : n(n), prt(n, -1){}

      inline bool is_root (int x)        const {return prt.at(x) < 0;}

      inline int  size    (int x)        const {return -prt.at(find(x));}

      inline bool is_equiv(int x, int y) const {return find(x) == find(y);}

      inline int  find    (int x)        const {
        while (!is_root(x)) x = prt.at(x);
        return x;
      }

      // If x and y are newly connected, returns `true`.
      // The smaller one x becomes a child of the larger one y.
      inline bool unite   (int x, int y) {
        if ((x = find(x)) == (y = find(y))) return false;
        if (size(x) > size(y)) std::swap(x, y);
        prt.at(y) += prt.at(x);
        prt.at(x) = y;
        return true;
      }
};