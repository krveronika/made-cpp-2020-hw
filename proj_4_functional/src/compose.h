#include <functional>
#include <iostream>

template <typename R, typename T> auto compose(std::function<R(T)> f) {
  return [=](T &x) { return f(x); };
}

template <typename A, typename B, typename C>
std::function<A(C)> compose(std::function<A(B)> f, std::function<B(C)> g) {
  return [f, g](C x) { return f(g(x)); };
}

template <typename F, typename... Args> auto compose(F f, Args &&... args) {
  return compose(f, compose(args...));
}
