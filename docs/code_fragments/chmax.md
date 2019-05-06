# chmax
```cpp
template<typename T1, typename T2>
inline bool chmax (T1& a, T2 b) {
  if (a < b) a = b, return true;
  return false;
}
```
