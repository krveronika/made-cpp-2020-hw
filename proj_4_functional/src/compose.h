//https://github.com/MuzaffarSoliyev/made-cpp-2020-hw/blob/proj_4_functional/proj_4_functional/src/compose.h
#include <iostream>

template<typename F>
struct Functor {
    F f;
    Functor(F f) : f(f) {}
    template<typename T>
    decltype(auto) operator()(T i) {
        return f(i);
    }
};

template <typename F1, typename F2>
struct Composer {
    F1 f1;
    F2 f2;
    
    Composer(F1 f1, F2 f2) : f1(f1), f2(f2) {}
    
    template <typename T>
    decltype(auto) operator()(T i) {
        return f2(f1(i));
    }
};

template<typename F>
decltype(auto) compose(F f) {
    return Functor<F>(f);
}

template <typename F1, typename F2>
decltype(auto) compose(F1 f, F2 g) {
    return Composer<F1, F2>{f, g};
}

template <typename F1, typename ... Args>
decltype(auto) compose(F1 f, Args ... args) {
    return compose(f, compose(args...));
}
